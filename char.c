#include "bp.h"

bool isNumber(char ch){
    switch(ch){
        case'0':return True;
        case'1':return True;
        case'2':return True;
        case'3':return True;
        case'4':return True;
        case'5':return True;
        case'6':return True;
        case'7':return True;
        case'8':return True;
        case'9':return True;
        default:return False;
    }
}

int parseInt(char ch){
    switch(ch){
        case'0':return 0;
        case'1':return 1;
        case'2':return 2;
        case'3':return 3;
        case'4':return 4;
        case'5':return 5;
        case'6':return 6;
        case'7':return 7;
        case'8':return 8;
        case'9':return 9;
    }
}

void removeCh(char* str){
    int len = strlen(str)-1;
    if(str[len] == '\n'){
        str[len] = 0;
    }
}

bool isValidChar(const char ch){
    short v = (int)ch;
    if(v == 32 || v == 39 || v == 45 || v == 96)return True;
    else if(v > 64 && v < 91)return True;
    else if(v > 96 && v < 123)return True;
    else if(v > 127 && v < 181)return True;
    return False;
}

bool isLetter(const char ch){
    if((ch > 64 && ch < 91) || (ch > 96 && ch < 123))return True;
    return False;
}
