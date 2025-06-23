%{
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define strdup _strdup
#include "query.tab.h"
%}

%%

"QUERY"            { return QUERY_T; }
"EXEC"             { return EXEC_T; }
"IF"               { return IF_T; }
"BEGIN"            { return BEGIN_T; }
"END"              { return END_T; }
"FOR"              { return FOR_T; }
"IN"               { return IN_T; }
"RESULT_OF_QUERY"  { return RES_T; }
"EMPTY"            { return EMPTY_T; }
"URL_EXISTS"       { return URL_T; }
"NOT_EMPTY"        { return NOT_EMPTY_T; }

"++"               { return PLUSPLUS_T; }
"--"               { return MINUSMINUS_T; }
"**"               { return STARSTAR_T; }

"+"                { return PLUS_T; }
"-"                { return MINUS_T; }
"*"                { return STAR_T; }
"|"                { return PIPE_T; }
"="                { return EQ_T; }
":"                { return COLON_T; }
";"                { return SEMI_T; }
","                { return COMMA_T; }

"<"                { return LT_T; }
">"                { return GT_T; }
"["                { return LBRACK_T; }
"]"                { return RBRACK_T; }
"("                { return LPAREN_T; }
")"                { return RPAREN_T; }

\"([^\\\"]|\\.)*\" {
    yylval.str = strdup(yytext);
    return STRING_T;
}

[a-zA-Z_][a-zA-Z0-9_]* {
    yylval.str = strdup(yytext);
    return WORD_T;
}

[ \t\r\n]+         { /* ignore whitespace */ }

. {
    fprintf(stderr, "Unknown token: %s\n", yytext);
    exit(1);
}

%%

int yywrap() {
    return 1;
}
