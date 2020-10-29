#ifndef TOKEN_STREAM_H
#define TOKEN_STREAM_H
#include "Token.h"

const char number = '8'; // t.kind==number ��������, ��� t - �����
const char quit = 'q';  //  t.kind==quit ��������, ��� t - ������� ������
const char print = ';'; // t.kind==print ��������, ��� t - ������� ������ 
const string prompt = "> "; // ������������ ��� �������� �� ��,
const string result = "= "; // ��� ����� ������� ���������
const char name = 'a';
const char let = 'L';
const string declkey = "let";

class Token_stream
{
public:
    Token get();            //��������� �������
    void putback(Token t);  //���������� ������� � �����
    void ignore(char c);    //����������� ������� ��
    Token_stream() {};      //�� ������� ������������
private:
    bool full{ false };  // is there a Token in the buffer?
    Token buffer{ '\0' };        // here we keep a Token put back using putback()

};

#endif
