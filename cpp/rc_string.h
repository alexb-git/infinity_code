/***********************************************
  Filename: rc_String.h
  Purpose: implementation of RCString class
  Data Structure: RCString class
  Version: 5
 ***********************************************/
 #ifndef __RCStringS_CPP__
 #define __RCStringS_CPP__

 #include <cstddef>  /* size_t */
 #include <iostream> /* ostream, istream */

namespace ilrd
{


/****************************************************************************
             ==========  Class RCString  ==========
*****************************************************************************/
class RCString
{

private:
    class CharProxy; /* nested class */
    class CntStr;    /* nested class */


public:
    /*================== Constructors ==================*/
    RCString(const char *str = "");  // Ctor, non explicit on purpose
    RCString(const RCString& str);   // CCtor
    ~RCString();                     // Dtor

    /*================== Member Functions ================*/

    // assignment Operator
    RCString& operator=(const RCString& str);

    // Equality Operators, returns True is str1_ and str2_ are not equal,
    // else returns False.
    bool operator!=(const RCString& str) const;

    // comparison operator, if  this_->m_str > str_ returns True else False
    bool operator>(const RCString& str) const;

    // comparison operator, if str_1 < str2_ returns True else False
    bool operator<(const RCString& str) const;

    // to support operation s1[index]='a'
    CharProxy operator[](size_t index);

    /* when RCString is const, we want to prevent s1[index]='a'
    and on top of that, we also want to prevent write */
    const char operator[](size_t index) const;

    // returns the length of the RCString
    size_t Length() const;

    //Concate x_ RCString to the end of class RCString
    RCString& Concat(const RCString &other);

    //From RCString to char* - get RCString
    const char* GetRCString() const;

private:
    CntStr* ImpCpyStr(const char *str);     // allocate new class CntStr object
    char  GetChar(size_t index);            // get char in a given index
    void  SetChar(size_t index, char c);    // set the char at index to 'c'
    CntStr *m_str;                          // size + array of chars

}; // End of RCString Class

//=============== Global Memeber Functions =============/

// read RCString from stream
std::istream& operator>>(std::istream& IS, RCString& obj);
// print out the RCString to output stream
std::ostream& operator<<(std::ostream& OS, const RCString& obj);
//comparison operator to compare srt == "some RCString"
bool operator==(const RCString& str1, const RCString& str2);

/*==========  nested class CntStr within Class RCString  ==========*/
class RCString::CntStr
{
public:
    CntStr(const char* str = "");          // ctor,  non explicit on purpose

    // special ctor for str concat
    CntStr(const CntStr& cnt_str1, const CntStr& cnt_str2);
    CntStr(const CntStr& other);           // cctor
    const char* GetStr() const;            // Return the RCString
    size_t GetRefCnt() const;              // get reference counter
    void IncRefCnt();                      // increment reference counter
    void DecRefCnt();                      // Decrement reference counter
    void SetChar(size_t index, char ch);   // use placement new inside
                                           // cnt is 1 just modify RCString)
private:
    size_t m_ref_cnt;  // counter the number of references to the RCString
    char   m_str[1];   // pointer to the start of the RCString
};

/*==========  nested class CharProxy within Class RCString  ==========*/
class RCString::CharProxy
{
public:
    explicit CharProxy(RCString& rc_string, size_t index);
    CharProxy(const CharProxy& cp_);              // cctor
    CharProxy operator=(char c);                  // ((str[0] = 'a') = 'c');
    CharProxy operator=(const CharProxy& cp_);    // str1[0] = str2[1]
    operator char() const;                        // defined conversion from
                                                  // CharProxy to char
private:
    RCString&  m_rcstr;                // where char came from
    size_t     m_index;                // index of char in RCString
};



} // namespace ilrd

#endif /* __RCStringS_CPP__ */
