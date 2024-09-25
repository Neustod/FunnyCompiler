#pragma once

//Список лексем
enum Lexem {
    lex_error = -1,
    lex_begin = 1,
    lex_var,
    lex_type,
    lex_id,
    lex_const,
    lex_equal,
    lex_minus,
    lex_plus,
    lex_multiply,
    lex_div,
    lex_lbracket,
    lex_rbracket,
    lex_comma,
    lex_end,
    lex_dot,
    lex_colon,
    lex_semicol,
};