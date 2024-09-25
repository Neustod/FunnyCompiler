#include "Globals.h"
#include "LexicalAnalisys.h"
#include <string>
#include <regex>
#include <fstream>
#include <iostream>

using namespace std;


//Лескический анализ
int LexicalAnalysis(const char* codeFile, const char* lexFile)
{
    bool isErrorExists{ false };

    regex regexw(R"([a-z_A-Z_]+)"); //Слово
    regex regexd("([0-9]+)"); //Число
    regex regexi(R"(^[a-z_A-Z_]+[a-z_A-Z_0-9]*)"); //Идентификатор

    //Поток чтения исходного файла с кодом
    ifstream srcFile{ codeFile };
    //Поток записи файла с лексическим анализом
    ofstream destFile{ lexFile };

    if (!srcFile)
    {
        cout << "File error: Unable to open source file. Expected path: " << codeFile << endl;
        return 1;
    }

    //Накапливающая строка буфер
    string strBuff;

    //Текущий символ
    char sym;

    //Идентификатор лексемы
    int id;

    //Текущая строка
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
            if (regex_match(strBuff, regexd)) id = lex_const; // Если слово является константой
            else if (regex_match(strBuff, regexi)) { // Сравнение слова с ключевыми по регулярным выражениям
                if (strBuff == "Begin") id = lex_begin;
                else if (strBuff == "Var") id = lex_var;
                else if (strBuff == "Integer") id = lex_type;
                else if (strBuff == "End") id = lex_end;
                else id = lex_id; // Иначе слово явяется идентификатором
            }
            else id = lex_error; // Ошибка
        }
        else {
            strBuff += sym;

            switch (strBuff[0]) // Если встретился оператор
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
