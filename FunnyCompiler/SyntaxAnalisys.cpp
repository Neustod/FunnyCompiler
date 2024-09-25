#include "Globals.h"
#include "SyntaxAnalisys.h"
#include <string>
#include <fstream>
#include <iostream>

using namespace std;


//���������� ����������
ifstream lexFile;

size_t currentString, preLine;
string currentLexeme;
int currentId;


//���������� �������

//������������
int W();

//���������� ����������
int S();


//�����������


//��������������� ����������
// Z -> BW | e
int Z()
{
    if (currentId == lex_plus || currentId == lex_minus || currentId == lex_multiply || currentId == lex_div)
    {
        lexFile >> currentLexeme >> currentId >> currentString;

        return W();
    }
    return 0;
}


//���������
int E()
{
    if (currentId == lex_minus)
    {
        lexFile >> currentLexeme >> currentId >> currentString;
    }
    return W();
}


//������������
// W -> (E)Z | OZ
int W()
{
    preLine = currentString;

    if (currentId == lex_lbracket)
    {
        lexFile >> currentLexeme >> currentId >> currentString;

        if (E() != 0)
        {
            return 1;
        }

        if (currentId == lex_rbracket)
        {
            lexFile >> currentLexeme >> currentId >> currentString;

            return Z();
        }
        else {
            cout << "Syntax error: expected \')\', but " << currentLexeme << " encountered at line " << currentString << endl;
            return 1;
        }
    }
    else if (currentId == lex_id || currentId == lex_const)
    {
        lexFile >> currentLexeme >> currentId >> currentString;

        return Z();
    }
    else {
        cout << "Syntax error: expected \'operator\', but " << currentLexeme << " encountered at line " << currentString << endl;
        return 1;
    }
}


//������������ (+ ������������)
// A -> I=E;
int A()
{
    if (currentId != lex_id) {
        cout << "Syntax error: expected \'identificator\', but " << currentLexeme << " encountered at line " << currentString << endl;
        return 1;
    }

    lexFile >> currentLexeme >> currentId >> currentString;

    if (currentId != lex_equal)
    {
        cout << "Syntax error: expected \'=\', but " << currentLexeme << " encountered at line " << currentString << endl;
        return 1;
    }

    lexFile >> currentLexeme >> currentId >> currentString;

    if (E() != 0) return 1;

    if (currentId != lex_semicol)
    {
        cout << "Syntax error: expected \';\', but " << currentLexeme << " encountered at line " << preLine << endl;

        return 1;
    }

    return 0;
}


//��� ���������
int F()
{
    bool bError = false;

    lexFile >> currentLexeme >> currentId >> currentString;

    while (currentId != lex_end && !lexFile.eof())
    {
        if (A() != 0)
        {
            bError = true;

            while (currentId != lex_semicol && currentId != lex_end && !lexFile.eof())
            {
                lexFile >> currentLexeme >> currentId >> currentString;
            }
        }

        lexFile >> currentLexeme >> currentId >> currentString;
    }
    return bError;
}


//���� ���� (begin F end.)
int D()
{
    lexFile >> currentLexeme >> currentId >> currentString;

    if (currentId != lex_begin) {
        cout << "Syntax error: expected \'Begin\', but " << currentLexeme << " encountered at line " << currentString << endl;
        return 1;
    }

    if (F() != 0) {
        return 1;
    }

    if (currentId != lex_end) {
        cout << "Syntax error: expected \'End\', but " << currentLexeme << " encountered at line " << currentString << endl;
        return 1;
    }

    lexFile >> currentLexeme >> currentId >> currentString;

    if (currentId != lex_dot) {
        cout << "Syntax error: expected \'.\', but " << currentLexeme << " encountered at line " << currentString << endl;
        return 1;
    }

    return 0;
}


//���������� ���� � ���������
int T()
{
    lexFile >> currentLexeme >> currentId >> currentString;

    if (currentId != lex_type) {
        cout << "Syntax error: expected \'Integer\', but " << currentLexeme << " encountered at line " << currentString << endl;
        return 1;
    }

    lexFile >> currentLexeme >> currentId >> currentString;

    if (currentId != lex_semicol) {
        cout << "Syntax error: expected \';\', but " << currentLexeme << " encountered at line " << currentString << endl;
        return 1;
    }

    return D();
}


//������ ���������� ��� ���������� ����
int X()
{
    lexFile >> currentLexeme >> currentId >> currentString;

    if (currentId == lex_comma)
        return S();
    else if (currentId == lex_colon)
        return T();
    else
    {
        cout << "Syntax error: expected \':\', but " << currentLexeme << " encountered at line " << currentString << endl;
        return 1;
    }
}


//���������� ����������
int S()
{
    lexFile >> currentLexeme >> currentId >> currentString;

    if (currentId == lex_id)
        return X();
    else
    {
        cout << "Syntax error: expected \'identificator\', but " << currentLexeme << " encountered at line " << currentString << endl;
        return 1;
    }
}


//�������������� ������
int SyntaxAnalysis(const char* szLexFile)
{
    lexFile.open(szLexFile);

    //�������� ������ ��� ������ ����� ������������ �������
    if (!lexFile)
    {
        cout << "File error: Unable to open source file. Expected path: " << szLexFile << endl;
        return 1;
    }

    lexFile >> currentLexeme >> currentId >> currentString;

    if (currentId == lex_var)
    {
        return S();
    }
    else
    {
        cout << "Syntax error: expected \'Var\', but " << currentLexeme << " encountered at line " << currentString << endl;
        return 1;
    }
}