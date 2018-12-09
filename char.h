#ifndef CHAR_H_INCLUDED
#define CHAR_H_INCLUDED
#include <string.h>
typedef enum bolean{False=0,True}bool;

bool isNumber(char ch);
int parseInt(char ch);
void removeCh(char* str);
bool isValidChar(const char ch);
bool isLetter(const char ch);

#endif // CHAR_H_INCLUDED
