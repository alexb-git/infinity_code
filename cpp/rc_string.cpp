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
RCString::CntStr::CntStr(const char* str) : m_ref_cnt(1)
{
    memcpy(this->m_str, str, strlen(str) + 1);
}

/* special ctor to support string concat */
RCString::CntStr::CntStr(const CntStr& cnt_str1, const CntStr& cnt_str2) :
                                                                m_ref_cnt(1)
{
    size_t len1 = strlen(cnt_str1.m_str);
    size_t len2 = strlen(cnt_str2.m_str);

    memcpy(m_str       , cnt_str1.m_str, len1     );
    memcpy(m_str + len1, cnt_str2.m_str, len2 + 1 );
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

const char* RCString::CntStr::GetStr() const
{
    return m_str;
}

void RCString::CntStr::SetChar(size_t index, char ch)
{
    CntStr *ptr = this;

    if ( this->GetRefCnt() > 1 )
    {
        /* case: more than one reference; NEED new allocation */

        /*  1. decrease previous RCString reference counter (--size)
            2. create new CntStr
            3. assign the new count string to this
            4. change char */

        this->DecRefCnt();

        ptr = new CntStr( this->m_str );
    }

    ptr->m_str[index] = ch;
}

/****************************************************************************
    ==========  nested class CharProxy within Class RCString  ==========
*****************************************************************************/
RCString::CharProxy::CharProxy(RCString& rc_string, size_t index) :
            m_rcstr(rc_string),
            m_index(index)
{}

RCString::CharProxy::CharProxy(const CharProxy& cp_):
                                            m_rcstr(cp_.m_rcstr),
                                            m_index(cp_.m_index)
{}

RCString::CharProxy RCString::CharProxy::operator=(char c)
{
    m_rcstr.SetChar(m_index, c);

    return *this;
}

RCString::CharProxy RCString::CharProxy::operator=(const CharProxy& cp_)
{
    /* SetChar of RCSring */
    m_rcstr.SetChar( this->m_index, cp_);

    return *this;
}

RCString::CharProxy::operator char() const
{
    return m_rcstr.GetChar(this->m_index);
}


/****************************************************************************
                ==========  Class RCString  ==========
*****************************************************************************/
RCString::CntStr* RCString::ImpCpyStr(const char *str)
{
    /* allocate memory */
    void *buff = new char[sizeof(size_t) + strlen(str) + 1];

    /*  place size_t type at the begining of the allocated memory and
        assignt value 1 to it (only one String instat points to string) */
    CntStr *cntstr = new(buff) CntStr(str);

    return cntstr;
}

/****************************************************************************
    ctor
*****************************************************************************/
RCString::RCString(const char *str): m_str( ImpCpyStr(str) )
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
        delete[] m_str;
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
    if ( m_str != str_.m_str )
    {
        /* case: not self assigment */
        this->~RCString();

        this->m_str = str_.m_str;
        this->m_str->IncRefCnt();
    }

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
    return strcmp(this->GetRCString(), str_.GetRCString() ) > 0;
}

/****************************************************************************
    comparison operator, if str_1 < str2_ returns True else False
*****************************************************************************/
bool RCString::operator<(const RCString& str_) const
{
    return strcmp(this->GetRCString(), str_.GetRCString() ) < 0;
}

/****************************************************************************
    to support operation s1[index]='a'
*****************************************************************************/
RCString::CharProxy RCString::operator[](size_t index)
{
    CharProxy local(*this, index);
    return local;
}

/****************************************************************************
    to support operation s1[index]='a'
*****************************************************************************/
const char RCString::operator[](size_t index) const
{
    return *(this->GetRCString() + index);
}

/****************************************************************************
    returns the length of the RCString
*****************************************************************************/
size_t RCString::Length() const
{
    return strlen(this->GetRCString());
}

/****************************************************************************
    Concate input_ RCString to the end of class RCString
*****************************************************************************/
RCString& RCString::Concat(const RCString& input_)
{
    size_t len_this  = this->Length();
    size_t len_other = input_.Length();

    char *buff = new char[sizeof(size_t) + len_this + len_other + 1];

    /* call special ctor of CntStr */
    CntStr *new_rcstr = new(buff) CntStr(  this->GetRCString(),
                                          input_.GetRCString());


    /* deallocate or decrement string ref of this */
    this->~RCString();

    /* m_str points to the newly allocated CntStr */
    this->m_str = new_rcstr;

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
    get char in a given index
*****************************************************************************/
char RCString::GetChar(size_t index)
{
    return this->GetRCString()[index];
}

/****************************************************************************
    set the char at the given index to 'c'
*****************************************************************************/
void RCString::SetChar(size_t index, char c)
{
    this->m_str->SetChar(index, c);
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
