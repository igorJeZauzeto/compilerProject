#ifndef AST_H
#define AST_H

typedef enum {
    AST_PROGRAM,
    AST_DECLARATIONS,
    AST_COMMANDS,
    AST_QUERY_DECL,
    AST_QUERY_LIST_DECL,
    AST_RESULT_DECL,
    AST_EXEC_CMD,
    AST_IF_CMD,
    AST_FOR_CMD,
    AST_ASSIGN_EXEC_CMD,
    AST_ASSIGN_SET_CMD,
    AST_CONDITION,
    AST_QUERY,
    AST_QUERY_LIST,
    AST_TERM_LIST,
    AST_TERM_WORD,
    AST_TERM_STRING,
    AST_TERM_DIRECTIVE,
    AST_TERM_UNARY,
    AST_TERM_BINARY
} ASTNodeType;

typedef enum {
    AST_OP_PLUS,
    AST_OP_MINUS,
    AST_OP_STAR,
    AST_OP_PIPE,
    AST_OP_NONE
} ASTOperator;

typedef struct ASTNode {
    ASTNodeType type;
    char* value;
    ASTOperator op;
    struct ASTNode* left;
    struct ASTNode* right;
    struct ASTNode* next;
} ASTNode;

// Constructors
ASTNode* make_node(ASTNodeType type);
ASTNode* make_word_node(char* val);
ASTNode* make_string_node(char* val);
ASTNode* make_directive_node(char* left, char* right);
ASTNode* make_unary_node(ASTOperator op, ASTNode* child);
ASTNode* make_binary_node(ASTOperator op, ASTNode* left, ASTNode* right);
ASTNode* append_node(ASTNode* list, ASTNode* item);

// AST builder functions used in parser
ASTNode* make_program_node(ASTNode* decls, ASTNode* cmds);
ASTNode* append_declaration(ASTNode* list, ASTNode* item);
ASTNode* make_declaration_list(ASTNode* item);
ASTNode* make_query_declaration(char* name, ASTNode* query);
ASTNode* make_query_list_declaration(char* name, ASTNode* queries);
ASTNode* make_result_declaration(char* name);
ASTNode* append_command(ASTNode* list, ASTNode* item);
ASTNode* make_command_list(ASTNode* item);
ASTNode* make_exec_command(char* name);
ASTNode* make_if_command(ASTNode* cond, ASTNode* cmds);
ASTNode* make_for_command(char* var, ASTNode* queries, ASTNode* cmds);
ASTNode* make_exec_assign_command(char* var, char* exec);
ASTNode* make_set_op_assign_command(char* var, char* lhs, ASTOperator op, char* rhs);
ASTNode* make_condition_node(const char* type, char* val1, char* val2);
ASTNode* make_query_node(ASTNode* terms);
ASTNode* make_query_list(ASTNode* q, ASTNode* tail);
ASTNode* append_query(ASTNode* list, ASTNode* item);
ASTNode* make_term_list(ASTNode* item);
ASTNode* append_term(ASTNode* list, ASTNode* item);
ASTNode* make_unary_term(ASTOperator op, ASTNode* child);
ASTNode* make_binary_term(ASTOperator op, ASTNode* left, ASTNode* right);

#endif
