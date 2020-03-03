/* Made by Alex Budie 22.08.17 */

#ifndef WS2STRING_H
#define WS2STRING_H

/* Function that recieves pointer to string and retuns the length of the string */
size_t MyStrlen (const char *prt);

/* 	This FUNCTION will compare between MyStrcmp and strcmp in string.h library */
int MyStrcmp (const char* str1, const char* str2);

/* compares two strings irrespective of the case of characters */
int MyStrCaseCmp(const char *string1, const char *string2);

/* Copies the string pointed by source into the array pointed by destination */
char* MyStrcpy(char* destination, const char* source);

/*copies up to n characters from the string pointed to, by src to dest. 
  In a case where the length of src is less than that of n, the remainder 
  of dest will be padded with null bytes. */
char* MyStrNCpy(char *dest, const char *src, size_t n);

/* searches for the first occurrence of the character in the string */
char *MyStrChr(const char *str, int c);

/* duplicates the given string. allocates memory. retruns pointer to allocated memory */
char *MyStrDup(const char *string);

/* appends the string pointed to by src to the end of the string pointed to by dest */
char *MyStrCat(char *dest, const char *src);

/* appends the string pointed by src to the end of the string pointed 
   by dest up to n characters long */
char *MyStrNCat(char *dest, const char *src, size_t n);

/* This function finds the first occurrence of the substring needle in the string 
   haystack. The terminating '\0' characters are not compared. */
char *MyStrStr(const char *haystack, const char *needle);



#endif 
/* WS2STRING_H */