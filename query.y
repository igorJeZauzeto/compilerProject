%{
    #include <stdio.h>
    #include <stdlib.h>

    void yyerror(const char* s);
    int yylex(void);
%}

%token QUERY_T EXEC_T IF_T BEGIN_T END_T FOR_T IN_T RES_T EMPTY_T URL_T NOT_EMPTY_T
%token PLUSPLUS_T MINUSMINUS_T STARSTAR_T
%token PLUS_T MINUS_T STAR_T PIPE_T EQ_T COLON_T SEMI_T COMMA_T
%token LT_T GT_T LBRACK_T RBRACK_T LPAREN_T RPAREN_T

%union {
    char* str;
}

%token <str> STRING_T WORD_T


%start program

%%

program:

%%

void yyerror(const char* s) {
    fprintf(stderr, "Syntax error: %s\n", s);
}