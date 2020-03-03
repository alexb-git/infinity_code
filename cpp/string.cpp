/****************************************************************************
** Filename:    - string.cpp
** Code Author: - Alex B
** Mail:        - aether.alex@gmail.com
** Purpose:     - implementations of String library
** Date:        - 8/1/2018
** Version:     - 3
*****************************************************************************/
#include <cstring>   /* strlen, strcmp */
#include "string.h"  /* my_header */

namespace ilrd
{
/****************************************************************************
    allocate char array and copy str string into it
*****************************************************************************/
char* String::ImpCpyStr(const char *str)
{
    /* the needed length for the string +1 (terminating character)*/
    size_t str_len = strlen(str) + 1;

    /* allocate array to hold the given string */
    char *new_str = new char[str_len];

    /*  copy the given string into the new array
        (including the terminating null character)  */
    memcpy(new_str, str, str_len);

    return new_str;
}

/****************************************************************************
    ctor
*****************************************************************************/
String::String(const char *str): m_str( ImpCpyStr(str) )
{}

/****************************************************************************
    copy ctor
*****************************************************************************/
String::String(const String& str_): m_str( ImpCpyStr(str_.m_str) )
{}

/****************************************************************************
    dtor
*****************************************************************************/
String::~String()
{
    delete[] m_str;
    m_str = NULL;
}

/****************************************************************************
    assignment Operator
*****************************************************************************/
String& String::operator=(const String& str_)
{
    /* string length needed (+ 1 (terminating null character)) */
    size_t str_len = strlen(str_.m_str) + 1;

    /* allocate the needed length */
    char *buffer = new char[str_len];

    /*  copy the content of str_ (string class) into the content
        of current class object */
    memcpy(buffer, str_.m_str, str_len);

    /*  deallocate the content of m_str and point it to the
        newly allocated buffer */
    delete[] m_str;
    m_str = buffer;

    return *this;
}

/****************************************************************************
    Equality Operators, returns True is str1_ and str2_ are not equal,
    else returns False.
*****************************************************************************/
bool String::operator!=(const String& str_) const
{
    return !(*this == str_);
}

/****************************************************************************
    comparison operator, if  this_->m_str > str_ returns True else False
*****************************************************************************/
bool String::operator>(const String& str_) const
{
    return strcmp(m_str, str_.m_str) > 0;
}

/****************************************************************************
    comparison operator, if str_1 < str2_ returns True else False
*****************************************************************************/
bool String::operator<(const String& str_) const
{
    return strcmp(m_str, str_.m_str) < 0;
}

/****************************************************************************
    to support operation s1[index]='a'
*****************************************************************************/
char& String::operator[](size_t index)
{
    return m_str[index];
}

/****************************************************************************
    to support operation s1[index]='a'
*****************************************************************************/
const char String::operator[](size_t index) const
{
    return m_str[index];
}

/****************************************************************************
    returns the length of the string
*****************************************************************************/
size_t String::Length() const
{
    return strlen(this->m_str);
}

/****************************************************************************
    Concate input_ string to the end of class string
*****************************************************************************/
String& String::Concat(const String& input_)
{
    size_t len_this  = strlen(m_str);
    size_t len_input = strlen(input_.m_str);

    /*  allocate enough memory to contain 'this->m_str' and
        input 'input_.m_str' + 1 char for terminating character */
    char *new_str = new char[len_this + len_input + 1];

    /* copy this->m_str content into new string content */
    memcpy( new_str ,
            m_str   ,
            len_this);

    /* copy input_.m_str to new string from where the first string
       (this->m_str) finished */
    memcpy( new_str + len_this,
            input_.m_str,
            len_input + 1);

    /* deallocate the previoius content of m_str char array */
    delete[] m_str;

    /* data member points to the new concatenated array */
    m_str = new_str;

    return *this;
}

/****************************************************************************
    return the private data memeber char*
*****************************************************************************/
const char* String::GetString() const
{
    return this->m_str;
}

/****************************************************************************
    read string from stream
*****************************************************************************/
std::istream& operator>>(std::istream& IS_, String& obj)
{
    /* create buffer on the stack */
    const size_t buff_size = 100;
    char buffer[buff_size];

    /* pour the istream into the buffer */
    IS_.get (buffer, buff_size);

    /*  call (String) assignment operator and put the
        content of the buffer into the String object (obj) */
    obj = buffer;

    return IS_;
}

/****************************************************************************
    print out the string to output stream
*****************************************************************************/
std::ostream& operator<<(std::ostream& OS_, const String& obj)
{
    return OS_ << obj.GetString();
}

/****************************************************************************
    comparison operator to compare srt == "some string"
*****************************************************************************/
bool operator==(const String& str1_, const String& str2_)
{
    return strcmp(str1_.GetString(), str2_.GetString()) == 0;
}

}   // namespace ilrd
