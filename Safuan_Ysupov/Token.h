#ifndef TOKEN_H // ��� ����������� ������
#define TOKEN_H
#include "std_lib_facilities.h"

class Token
{
public:
    char kind;
    double value;
    string name;
    // �������������� kind �������� ch
    Token(char ch) : kind{ ch } {}
    // �������������� kind � value
    Token(char ch, string n) : kind{ ch }, name{ n }  { }
    // �������������� kind � name
    Token(char ch, double val) : kind{ ch }, value{ val }  { }
};

#endif
