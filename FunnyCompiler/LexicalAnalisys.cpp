#include "Globals.h"
#include "LexicalAnalisys.h"
#include <string>
#include <regex>
#include <fstream>
#include <iostream>

using namespace std;


//����������� ������
int LexicalAnalysis(const char* codeFile, const char* lexFile)
{
    bool isErrorExists{ false };

    regex regexw(R"([a-z_A-Z_]+)"); //�����
    regex regexd("([0-9]+)"); //�����
    regex regexi(R"(^[a-z_A-Z_]+[a-z_A-Z_0-9]*)"); //�������������

    //����� ������ ��������� ����� � �����
    ifstream srcFile{ codeFile };
    //����� ������ ����� � ����������� ��������
    ofstream destFile{ lexFile };

    if (!srcFile)
    {
        cout << "File error: Unable to open source file. Expected path: " << codeFile << endl;
        return 1;
    }

    //������������� ������ �����
    string strBuff;

    //������� ������
    char sym;

    //������������� �������
    int id;

    //������� ������
    size_t currentString = 1;

    while (!srcFile.eof())
    {
        id = lex_error;
        strBuff = "";
        sym = srcFile.get();

        if (sym == ' ' || sym == '\n' || sym == '\t' || sym == EOF)
        {
            if (sym == '\n') currentString++;
            continue;
        }

        if (isalpha(sym) || isdigit(sym))
        {
            strBuff += sym;

            while (isalpha(srcFile.peek()) || isdigit(srcFile.peek()))
            {
                sym = srcFile.get();
                strBuff += sym;
            }
            if (regex_match(strBuff, regexd)) id = lex_const; // ���� ����� �������� ����������
            else if (regex_match(strBuff, regexi)) { // ��������� ����� � ��������� �� ���������� ����������
                if (strBuff == "Begin") id = lex_begin;
                else if (strBuff == "Var") id = lex_var;
                else if (strBuff == "Integer") id = lex_type;
                else if (strBuff == "End") id = lex_end;
                else id = lex_id; // ����� ����� ������� ���������������
            }
            else id = lex_error; // ������
        }
        else {
            strBuff += sym;

            switch (strBuff[0]) // ���� ���������� ��������
            {
            case '=':
                id = lex_equal;
                break;
            case '-':
                id = lex_minus;
                break;
            case '+':
                id = lex_plus;
                break;
            case '*':
                id = lex_multiply;
                break;
            case '/':
                id = lex_div;
                break;
            case '(':
                id = lex_lbracket;
                break;
            case ')':
                id = lex_rbracket;
                break;
            case ',':
                id = lex_comma;
                break;
            case '.':
                id = lex_dot;
                break;
            case ';':
                id = lex_semicol;
                break;
            case ':':
                id = lex_colon;
                break;
            default:
                id = lex_error;
                break;
            }
        }
        if (id == lex_error)
        {
            cout << "Lexical error: " << '\'' << strBuff << "\' " << " is undefined " << '\n';
            isErrorExists = true;
        }
        destFile << strBuff << " " << id << " " << currentString << '\n';

    }

    srcFile.close();
    destFile.close();

    return isErrorExists;
}
