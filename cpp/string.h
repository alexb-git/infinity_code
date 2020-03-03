/***********************************************
  Filename: string.h
  Purpose: implementation of string class
  Data Structure: string data structure
  Version: 3
 ***********************************************/
 #ifndef __STRINGS_CPP__
 #define __STRINGS_CPP__

#include <cstddef>   /* size_t */
#include <iostream>  /* ostream istream */

namespace ilrd
{
class String
{
public:
    /*==================  Constructors  ==================*/
    String(const char *str = ""); // non explicit on purpose

    // copy ctor
    String(const String& str_);

    /*==================  Deconstructor  ==================*/
    ~String();

    /*================== Member Functions ================*/
    // assignment Operator
    String& operator=(const String& x_);

    // Equality Operators, returns True is str1_ and str2_ are not equal,
    // else returns False.
    bool operator!=(const String& str_) const;

    // comparison operator, if  this_->m_str > str_ returns True else False
    bool operator>(const String& str_) const;

    // comparison operator, if str_1 < str2_ returns True else False
    bool operator<(const String& str_) const;

    // to support operation s1[index]='a'
    char& operator[](size_t index);

    // to support operation 'a'==s1[index]
    const char operator[](size_t index) const;

    // returns the length of the string
    size_t Length() const;

    //Concate x_ string to the end of class string
    String& Concat(const String& x_);

    //From String to char* - get string
    const char* GetString() const;

private:
    char *m_str;

    // allocate char array and copy str string into it
    char* ImpCpyStr(const char *str);

}; // End of String Class

/*=============== Global Memeber Functions =============*/
// read string from stream
std::istream& operator>>(std::istream& IS_, String& obj);

// print out the string to output stream
std::ostream& operator<<(std::ostream& OS_, const String& obj);

//comparison operator to compare srt == "some string"
bool operator==(const String& str1_, const String& str2_);

}  // namespace ilrd

#endif /* __STRINGS_CPP__ */
