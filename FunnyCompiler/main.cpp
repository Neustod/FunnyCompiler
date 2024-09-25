#include <iostream>
#include "Compiler.h"

#define CODE_FILEPATH "code.txt"
#define LEX_FILEPATH "lex.txt"

using namespace std;


int main()
{
    if (LexicalAnalysis(CODE_FILEPATH, LEX_FILEPATH) == 1)
    {
        cout << "Lexical analysis was unsuccessfull" << endl;
        return 1;
    }
    else 
    {
        cout << "Lexical analysis was successfull" << endl;
    }

    if (SyntaxAnalysis(LEX_FILEPATH)) 
    { 
        cout << "Syntax analysis was unsuccessfull" << endl;
        return 1; 
    }
    else 
    {
        cout << "Syntax analysis was successfull" << endl;
    }

    return 0;
}
