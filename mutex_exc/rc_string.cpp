/****************************************************************************
** Filename:    - rc_string.cpp
** Code Author: - Alex B
** Mail:        - aether.alex@gmail.com
** Purpose:     - implementations of RCString library
** Date:        - 25/1/2018
** Version:     - 3
*****************************************************************************/
#include <cstring>   /* strlen, strcmp */
#include "rc_string.h"  /* my_header */

namespace ilrd
{

/****************************************************************************
    ==========  nested class CntStr within Class RCString  ==========
*****************************************************************************/
RCString::CntStr::CntStr(const char* str)
{
    size_t str_len = strlen(str) + 1;

    /* allocate memory */
    char* ptr = new char[sizeof(size_t) + str_len];

    /*  place size_t type at the begining of the allocated memory and
        assignt value 1 to it (only one String instat points to string) */
    new(ptr) size_t(1);

    /* place type of char array char[] */
    new(ptr + sizeof(size_t)) char[str_len];

    memcpy(ptr + sizeof(size_t), str, str_len);
}

RCString::CntStr::~CntStr()
{
    /* deallocate the memory from where the first variable begins */
    delete &m_ref_cnt;
}

size_t RCString::CntStr::GetRefCnt() const
{
    return m_ref_cnt;
}

void RCString::CntStr::IncRefCnt()
{
    ++m_ref_cnt;
}

void RCString::CntStr::DecRefCnt()
{
    --m_ref_cnt;
}

char* RCString::CntStr::GetStr()
{
    return m_str;
}

void RCString::CntStr::SetChar(size_t index, char ch)
{
    m_str[index] = ch;
}


/****************************************************************************
    ==========  nested class CharProxy within Class RCString  ==========
*****************************************************************************/
/*RCString::*/CharProxy::CharProxy(RCString& rc_string, size_t index) :
            m_rcstr(rc_string),
            m_index(index)
{}

CharProxy::CharProxy(const CharProxy& cp_):
                                            m_rcstr(cp_.m_rcstr),
                                            m_index(cp_.m_index)
{}

CharProxy /*RCString::*/CharProxy::operator=(char c)
{
    // RCString new_rc_string = new RCString(m_str);


    return *this;
}

CharProxy /*RCString::*/CharProxy::operator=(const CharProxy& cp_)
{
    CntStr local;
    /* 1. create new RCString (or better new CntStr)
       2. decrease previous RCString appearence --size
       3. change char  */

}

/*RCString::*/CharProxy::operator char() const
{
    return *(m_rcstr.GetRCString() + m_index);
}




/****************************************************************************
                ==========  Class RCString  ==========
*****************************************************************************/

/****************************************************************************
    ctor
*****************************************************************************/
RCString::RCString(const char *str): m_str( new CntStr(str) )
{}

/****************************************************************************
    copy ctor
*****************************************************************************/
RCString::RCString(const RCString& str_): m_str( str_.m_str )
{
    m_str->IncRefCnt();
}

/****************************************************************************
    dtor
*****************************************************************************/
RCString::~RCString()
{
    if ( m_str->GetRefCnt() == 1 )
    {
        /* case: current string is the last one to point to CntStr */
        m_str->~CntStr();
        m_str = NULL;
    }
    else
    {
        /*  case: more that one Strings point to CntStr,
            no need to deallocate */
        m_str->DecRefCnt();
    }
}

/****************************************************************************
    assignment Operator
*****************************************************************************/
RCString& RCString::operator=(const RCString& str_)
{
    m_str = str_.m_str;
    m_str->IncRefCnt();

    return *this;
}

/****************************************************************************
    Equality Operators, returns True is str1_ and str2_ are not equal,
    else returns False.
*****************************************************************************/
bool RCString::operator!=(const RCString& str_) const
{
    return !(*this == str_);
}

/****************************************************************************
    comparison operator, if  this_->m_str > str_ returns True else False
*****************************************************************************/
bool RCString::operator>(const RCString& str_) const
{
    return strcmp(m_str->GetStr(), str_.m_str->GetStr()) > 0;
}

/****************************************************************************
    comparison operator, if str_1 < str2_ returns True else False
*****************************************************************************/
bool RCString::operator<(const RCString& str_) const
{
    return strcmp(m_str->GetStr(), str_.m_str->GetStr()) < 0;
}

/****************************************************************************
    to support operation s1[index]='a'
*****************************************************************************/
CharProxy RCString::operator[](size_t index)
{
    CharProxy local(*this, index);
    return local;
}

/****************************************************************************
    to support operation s1[index]='a'
*****************************************************************************/
const char RCString::operator[](size_t index) const
{
    return *(m_str->GetStr() + index);
}

/****************************************************************************
    returns the length of the RCString
*****************************************************************************/
size_t RCString::Length() const
{
    return strlen(m_str->GetStr());
}

/****************************************************************************
    Concate input_ RCString to the end of class RCString
*****************************************************************************/
RCString& RCString::Concat(const RCString& input_)
{
    // size_t len_this  = strlen(m_str->GetStr());
    // size_t len_input = strlen(input_.m_str->GetStr());
    //
    // /*  allocate enough memory to contain 'this->m_str' and
    //     input 'input_.m_str' + 1 char for terminating character */
    // char *new_str = new char[len_this + len_input + 1];
    //
    // /* copy this->m_str content into new RCString content */
    // memcpy( new_str ,
    //         m_str   ,
    //         len_this);
    //
    // /* copy input_.m_str to new RCString from where the first RCString
    //    (this->m_str) finished */
    // memcpy( new_str + len_this,
    //         input_.m_str,
    //         len_input + 1);
    //
    // /* deallocate the previoius content of m_str char array */
    // delete[] m_str;
    //
    // /* data member points to the new concatenated array */
    // m_str = new_str;

    return *this;
}

/****************************************************************************
    return the private data memeber char*
*****************************************************************************/
const char* RCString::GetRCString() const
{
    return m_str->GetStr();
}

/****************************************************************************
    read RCString from stream
*****************************************************************************/
std::istream& operator>>(std::istream& IS_, RCString& obj)
{
    /* create buffer on the stack */
    const size_t buff_size = 100;
    char buffer[buff_size];

    /* pour the istream into the buffer */
    IS_.get (buffer, buff_size);

    /*  call (RCString) assignment operator and put the
        content of the buffer into the RCString object (obj) */
    obj = buffer;

    /* TODO what do i do here */

    return IS_;
}

/****************************************************************************
    print out the RCString to output stream
*****************************************************************************/
std::ostream& operator<<(std::ostream& OS_, const RCString& obj)
{
    return OS_ << obj.GetRCString();
}

/****************************************************************************
    comparison operator to compare srt == "some RCString"
*****************************************************************************/
bool operator==(const RCString& str1_, const RCString& str2_)
{
    return strcmp(str1_.GetRCString(), str2_.GetRCString()) == 0;
}

}   // namespace ilrd
