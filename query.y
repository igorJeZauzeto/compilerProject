%code requires {
    #include "ast.h"
}

%{
    #include <stdio.h>
    #include <stdlib.h>
    #include "ast.h"
    extern char* yytext;
    extern int yydebug;
    void yyerror(const char* s);
    int yylex(void);
    ASTNode* root = NULL;
%}

%union {
    char* str;
    ASTNode* node;
    ASTOperator op;
}

%type <node> program declarations declaration commands command assign_command condition query list_of_queries query_list terms term directive
%type <op> operator set_operator

%token <str> STRING_T WORD_T

%token QUERY_T EXEC_T IF_T BEGIN_T END_T FOR_T IN_T RES_T EMPTY_T URL_T NOT_EMPTY_T
%token PLUSPLUS_T MINUSMINUS_T STARSTAR_T
%token PLUS_T MINUS_T STAR_T PIPE_T EQ_T COLON_T SEMI_T COMMA_T
%token LT_T GT_T LBRACK_T RBRACK_T LPAREN_T RPAREN_T

%start program
%debug

%%

program:
      declarations commands { $$ = make_program_node($1, $2); root = $$;}
    ;

declarations:
      declarations declaration { $$ = append_declaration($1, $2); }
    | declaration              { $$ = make_declaration_list($1); }
    ;

declaration:
      QUERY_T WORD_T EQ_T query SEMI_T             { $$ = make_query_declaration($2, $4); }
    | QUERY_T WORD_T EQ_T list_of_queries SEMI_T   { $$ = make_query_list_declaration($2, $4); }
    | RES_T WORD_T SEMI_T                          { $$ = make_result_declaration($2); }
    ;

commands:
      commands command { $$ = append_command($1, $2); }
    | command           { $$ = make_command_list($1); }
    ;

command:
      EXEC_T WORD_T SEMI_T                                      { $$ = make_exec_command($2); }
    | IF_T condition BEGIN_T commands END_T                     { $$ = make_if_command($2, $4); }
    | FOR_T WORD_T IN_T list_of_queries BEGIN_T commands END_T  { $$ = make_for_command($2, $4, $6); }
    | assign_command SEMI_T                                     { $$ = $1; }
    ;

assign_command:
      WORD_T EQ_T EXEC_T WORD_T                   { $$ = make_exec_assign_command($1, $4); }
    | WORD_T EQ_T WORD_T set_operator WORD_T      { $$ = make_set_op_assign_command($1, $3, $4, $5); }
    ;

condition:
      EMPTY_T LPAREN_T WORD_T RPAREN_T                         { $$ = make_condition_node("EMPTY", $3, NULL); }
    | NOT_EMPTY_T LPAREN_T WORD_T RPAREN_T                    { $$ = make_condition_node("NOT_EMPTY", $3, NULL); }
    | URL_T LPAREN_T WORD_T COMMA_T STRING_T RPAREN_T         { $$ = make_condition_node("URL_EXISTS", $3, $5); }
    ;

query:
    LT_T terms GT_T  { $$ = make_query_node($2); }
    ;

list_of_queries:
    LBRACK_T query_list RBRACK_T { $$ = $2; }
    ;

query_list:
      query_list COMMA_T LT_T terms GT_T { $$ = append_query($1, make_query_node($4)); }
    | query_list COMMA_T WORD_T          { $$ = append_query($1, make_word_node($3)); }
    | LT_T terms GT_T                    { $$ = make_query_list(make_query_node($2), NULL); }
    | WORD_T                             { $$ = make_query_list(make_word_node($1), NULL); }
    ;

terms:
      terms term { $$ = append_term($1, $2); }
    | term       { $$ = make_term_list($1); }
    ;

term:
      WORD_T                  { $$ = make_word_node($1); }
    | STRING_T                { $$ = make_string_node($1); }
    | directive               { $$ = $1; }
    | operator term           { $$ = make_unary_term($1, $2); }
    | term PIPE_T term        { $$ = make_binary_term(AST_OP_PIPE, $1, $3); }
    | LPAREN_T term RPAREN_T { $$ = $2; }
    ;

directive:
      WORD_T COLON_T WORD_T   { $$ = make_directive_node($1, $3); }
    | WORD_T COLON_T STRING_T { $$ = make_directive_node($1, $3); }
    ;

operator:
      PLUS_T  { $$ = AST_OP_PLUS; }
    | MINUS_T { $$ = AST_OP_MINUS; }
    | STAR_T  { $$ = AST_OP_STAR; }
    ;

set_operator:
      PLUSPLUS_T   { $$ = AST_OP_PLUS; }
    | MINUSMINUS_T { $$ = AST_OP_MINUS; }
    | STARSTAR_T   { $$ = AST_OP_STAR; }
    ;

%%

void yyerror(const char* s) {
    fprintf(stderr, "Syntax error: %s\n", s);
}
