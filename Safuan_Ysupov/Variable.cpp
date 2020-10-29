#include "Variable.h"

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