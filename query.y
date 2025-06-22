%{
    #include <stdio.h>
    #include <stdlib.h>
    extern char* yytext;
    extern int yydebug;
    void yyerror(const char* s);
    int yylex(void);
%}

%union {
    char* str;
}

%left PIPE_T
%left PLUS_T MINUS_T STAR_T

%token <str> STRING_T WORD_T

%token QUERY_T EXEC_T IF_T BEGIN_T END_T FOR_T IN_T RES_T EMPTY_T URL_T NOT_EMPTY_T
%token PLUSPLUS_T MINUSMINUS_T STARSTAR_T
%token PLUS_T MINUS_T STAR_T PIPE_T EQ_T COLON_T SEMI_T COMMA_T
%token LT_T GT_T LBRACK_T RBRACK_T LPAREN_T RPAREN_T

%start program
%debug

%%

program:
      declarations commands
    | declarations
    ;

declarations:
      declarations declaration
    | declaration
    ;

declaration:
      QUERY_T WORD_T EQ_T query SEMI_T
    | QUERY_T WORD_T EQ_T list_of_queries SEMI_T
    | RES_T WORD_T SEMI_T
    ;

commands:
      commands command
    | command
    ;

command:
      EXEC_T WORD_T SEMI_T
    | IF_T condition BEGIN_T commands END_T
    | FOR_T WORD_T IN_T list_of_queries BEGIN_T commands END_T
    | assign_command SEMI_T
    ;

assign_command:
      WORD_T EQ_T EXEC_T WORD_T
    | WORD_T EQ_T WORD_T set_operator WORD_T
    ;

condition:
      EMPTY_T LPAREN_T WORD_T RPAREN_T
    | NOT_EMPTY_T LPAREN_T WORD_T RPAREN_T
    | URL_T LPAREN_T WORD_T COMMA_T STRING_T RPAREN_T
    ;

query:
    LT_T terms GT_T
    ;

list_of_queries:
    LBRACK_T query_list RBRACK_T
    ;

query_list:
      query_list COMMA_T LT_T terms GT_T
    | query_list COMMA_T WORD_T
    | LT_T terms GT_T
    | WORD_T
;

terms:
      terms term
    | term
    ;

term:
      WORD_T
    | STRING_T
    | directive
    | operator term
    | term PIPE_T term
    | LPAREN_T term RPAREN_T
    ;

directive:
      WORD_T COLON_T WORD_T
    | WORD_T COLON_T STRING_T
    ;

operator:
      PLUS_T
    | MINUS_T
    | STAR_T
    ;

set_operator:
      PLUSPLUS_T
    | MINUSMINUS_T
    | STARSTAR_T
    ;

%%

void yyerror(const char* s) {
    fprintf(stderr, "Syntax error: %s\n", s);
}

int main() {
    return yyparse();
}
