#ifndef FILE_H_INCLUDED
#define FILE_H_INCLUDED
#include "bp.h"

typedef struct txt{
        int degree, root_pos;
        char file1[20], file2[20];
}Txt1;
char* getFileName();
bool isFileValid(FILE* const f,const char* const name);

void setTxt1Elements(char const* const buff, Txt1* const file, int size);
int fileTxt1(Txt1* const arquivo, int*  root);

void setTxt2Elements(char* const buff, void* ptr, const int size, const int degree);
void fileTxt2(const int degree, char* name);

bool writeBinFile(Data* const data, FILE* f);
void readBin(FILE* f, int type, int degree);

void setDataElements(char* const buff, Data* const data, const int size);
void fileData(Data* const data, char* name);

void print_out(void* ptr, int type, int degree);
void setNull(void* ptr, int type);
void resetlog();
void wait(unsigned short int sec);
#endif // FILE_H_INCLUDED
