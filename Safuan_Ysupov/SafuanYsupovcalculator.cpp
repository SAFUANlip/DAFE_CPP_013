//Ysupov Safuan 17.10.20  
/*
������� �����������

������� ������:

������������ �������� �������� � ������� 2020 (09.10.20)
����������� ������ ������������ � ��� 2007 �.
����������� ������ ������������ � ������� 2006 �.
����������� ������ ������������ � ������� 2004 �.
���������� ������ ������������ (bs@cs.tamu.edu) ������ 2004 �.

��� ��������� ��������� �������� ��������� ������������.
���� �������������� �� ������ cin ; ����� - � ����� cou t.

������ ���� ��� ����� :

����������:
  ���������
  �����
  �����

�����:
    ;
�����:
    q

���������:
  ����
  ��������� + ����
  ��������� - ����

����:
  ���������_���������
  ���� * ���������_���������
  ���� / ���������_���������
  ���� % ���������_ ���������

���������_��������� :
  �����
  ( ��������� )
  - ���������_���������
  + ���������_���������

����� :
  �������_�_���������_������

���� �� ������ cin ����� Token stream � ������ ts.
*/
#include "std_lib_facilities.h"
#include <iostream>
using namespace std;



const char number = '8'; // t.kind==number ��������, ��� t - �����
const char quit = 'q';  //  t.kind==quit ��������, ��� t - ������� ������
const char print = ';'; // t.kind==print ��������, ��� t - ������� ������ 
const string prompt = "> "; // ������������ ��� �������� �� ��,
const string result = "= "; // ��� ����� ������� ���������
const char name = 'a';
const char let = 'L';
const string declkey = "let";

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

void Token_stream::putback(Token t)
{
    if (full)
        error("putback() into a full buffer");
    buffer = t;
    full = true;
}

Token Token_stream::get() //������ �� cin � ����������� Token 
{
    if (full)         // do we already have a Token ready?
    {
        full = false;   // remove Token from buffer
        return buffer;
    }

    char ch;
    cin >> ch;  // note that >> skips whitespace (space, newline, tab, ...)

    switch (ch)
    {
    case print:    // for "print"
    case quit:    // for "quit"
    case '(':
    case ')':
    case '{':
    case '}':
    case '+':
    case '-':
    case '*':
    case '/':
    case '%':
    case '=':
        return Token{ ch };      // let each character represent itself
    case '.':                    // ����� � ��������� ������ ����� ���������� � �����
        // �������� �������:
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':
    {
        cin.putback(ch);         // put digit back into the input stream
        double val;
        cin >> val;              // read a floating-point number
        return Token{ number, val };  // let '8' represent "a number"
    }
    default:
        if (isalpha(ch))
        {
            string s;
            s += ch;
            while ((cin.get(ch)) && (isalpha(ch) || isdigit(ch)))
                s += ch;
            cin.putback(ch);
            if (s == declkey)
                return Token{ let };
            return Token{ name,s };
        }
        error("Bad token");
    }
}

void Token_stream::ignore(char c)
// ������ � ������������ ������������� ������
{
    //������� ��������� �����:
    if (full && c == buffer.kind)
    {
        full = false;
        return;
    }
    full = false;

    // ������ ��������� ������� ������:
    char ch = 0;
    while (cin >> ch)
        if (ch = c) return;
}


class Variable
{
public:
    string name;
    double value;

    Variable(string n, double v):
        name{ n }, value{ v } {}
    double get_value(string s);
    void set_value(string s, double d);
};

vector<Variable> var_table;


double get_value(string s)
//���������� �������� ���������� � ������ s
{
    for (const Variable& v : var_table)
        if (v.name == s) return v.value;
    error("get: undefined name ", s);
}

void set_value(string s, double d)
// ����������� ������� s ���� Variable �������� d
{
    for (Variable& v : var_table)
        if (v.name == s)
        {
            v.value = d;
            return;
        }
    error("set: ������������� ���������� ", s);
}

bool is_declared(string var)
//���� �� ���������� var � ������� var_table?
{
    for (const Variable v : var_table)
        if (v.name == var)
            return true;
    return false;
}

double define_name(string var, double val)
// ��������� ���� (var,val) � ������ var_table
{
    if (is_declared(var)) error(var, " ��������� ����������11 ");
    var_table.push_back(Variable{ var, val });
    return val;
}

Token_stream ts;        // ������������� get() � putback()
double expression();    // ���������� ��� ������������� � primary()

/// deal with numbers and parentheses
double primary()
{
    Token t = ts.get();
    switch (t.kind)
    {
    case '(':          // handle '(' expression ')' 
    {
        double d = expression();
        t = ts.get();
        if (t.kind != ')')
            error("')' expected");
        return d;
    }
    case '{':
    {
        double d = expression();
        t = ts.get();
        if (t.kind != '}')
        {
            error("need '}' ");
        }
        return d;
    }
    case number:          // we use '8' to represent a number
        return t.value;
    case name:
        return get_value(t.name);
    case '-':
        return -primary();
    case '+':
        return primary();
    default:
        error("primary expected");
    }
}

/// deal with *, /, and %
double term()
{
    double left = primary();
    Token t = ts.get();    // get the next token from token stream

    while (true)
    {
        switch (t.kind)
        {
        case '*':
            left *= primary();
            t = ts.get();
            break;
        case '/':
        {
            double d = primary();
            if (d == 0) error("divide by zero");
            left /= d;
            t = ts.get();
            break;
        }
        //����� � ���, ����� ��������� �������� % ��� ���������� � ��������� ������ (������ ������� case)
        case '%':                                       //int i1=narrow_cast<ini>(left);
        {                                               //int i2=narrow_cast<ini>(primary());
            double d = primary();                       //if (i2==0) error("%: division by zero"); 
            if (d == 0) error("%: division by zero");   //left=i1%i2;
            left = fmod(left, d);                       //t=ts.get();
            t = ts.get();
            break;                                      //break;
        }
        default:
            ts.putback(t);     // put t back into the token stream
        return left;
        }
    }
}

/// deal with + and -
double expression()
{
    double left = term();  // read and evaluate a Term
    Token t = ts.get();    // get the next token from token stream

    while (true)
    {
        switch (t.kind)
        {
        case '+':
            left += term();    // evaluate Term and add
            t = ts.get();
            break;

        case '-':
            left -= term();    // evaluate Term and subtract
            t = ts.get();
            break;

        default:
            ts.putback(t);     // put t back into the token stream
            return left;       // finally: no more + or -: return the answer
        }
    }
}

double declaration()
// �������, ��� �� ��� ��������� ����� "let"
// ������������: ���=���������
// ���������� ���������� � ������ � ��������� ���������,
// �������� ����������
{
    Token t = ts.get();
    if (t.kind != name)
        error("� ���������� ��������� ��� ����������");
    string var_name = t.name;
    Token t2 = ts.get();
    if (t2.kind != '=')
        error("��������� ������ = � ����������", var_name);
    double d = expression();
    define_name(var_name, d);
    return d;
}

double statement()
{
    Token t = ts.get();
    switch (t.kind)
    {
    case let:
        return  declaration();
    default:
        ts.putback(t);
        return expression();
    }
}

void clean_up_mess() // ������� �������
{
    ts.ignore(print);
}

void calculate() //���� ��� ���������� ���������
{
    while (cin)
    try
    {
        cout << prompt;
        Token t = ts.get();
        while (t.kind == print)
            t = ts.get(); // ������������ ������ ������
        if (t.kind == quit) return;
        ts.putback(t);
        cout << result << statement() << '\n';
    }
    catch (exception& e)
    {
        cerr << e.what() << '\n'; // ����� ��������� �� ������
        clean_up_mess();
    }
}

int main()
try
{
    setlocale(LC_ALL, "Russian");
    //��������������� �����
    define_name("pi", 3.1415926535);
    define_name("e", 2.7182818284);

    calculate();

    //keep_window_open(); // ���������� ���������� ���� ��������
    return 0;
}
catch (runtime_error& e)   //exception
{
    cerr << e.what() << '\n';
    keep_window_open("~~");
    return 1;
}

catch (...)
{
    cerr << "exception \n";
    keep_window_open("~~");
    return 2;
}