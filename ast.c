#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

ASTNode* make_node(ASTNodeType type) {
    ASTNode* node = malloc(sizeof(ASTNode));
    if (!node) {
        fprintf(stderr, "Memory allocation failed for ASTNode\n");
        exit(1);
    }
    node->type = type;
    node->value = NULL;
    node->op = AST_OP_NONE;
    node->left = NULL;
    node->right = NULL;
    node->next = NULL;
    return node;
}

ASTNode* make_word_node(char* val) {
    ASTNode* node = make_node(AST_TERM_WORD);
    node->value = strdup(val);
    return node;
}

ASTNode* make_string_node(char* val) {
    ASTNode* node = make_node(AST_TERM_STRING);
    node->value = strdup(val);
    return node;
}

ASTNode* make_directive_node(char* left, char* right) {
    ASTNode* node = make_node(AST_TERM_DIRECTIVE);
    size_t len = strlen(left) + strlen(right) + 2;
    node->value = malloc(len);
    snprintf(node->value, len, "%s:%s", left, right);
    return node;
}

ASTNode* make_unary_node(ASTOperator op, ASTNode* child) {
    ASTNode* node = make_node(AST_TERM_UNARY);
    node->op = op;
    node->left = child;
    return node;
}

ASTNode* make_binary_node(ASTOperator op, ASTNode* left, ASTNode* right) {
    ASTNode* node = make_node(AST_TERM_BINARY);
    node->op = op;
    node->left = left;
    node->right = right;
    return node;
}

ASTNode* append_node(ASTNode* list, ASTNode* item) {
    if (!list) return item;
    ASTNode* current = list;
    while (current->next) current = current->next;
    current->next = item;
    return list;
}

// === NEW FUNCTIONS ===

ASTNode* make_program_node(ASTNode* decls, ASTNode* cmds) {
    ASTNode* node = make_node(AST_PROGRAM);
    node->left = decls;
    node->right = cmds;
    return node;
}

ASTNode* append_declaration(ASTNode* list, ASTNode* item) {
    return append_node(list, item);
}

ASTNode* make_declaration_list(ASTNode* item) {
    return item;
}

ASTNode* make_query_declaration(char* name, ASTNode* query) {
    ASTNode* node = make_node(AST_QUERY_DECL);
    node->value = strdup(name);
    node->left = query;
    return node;
}

ASTNode* make_query_list_declaration(char* name, ASTNode* queries) {
    ASTNode* node = make_node(AST_QUERY_LIST_DECL);
    node->value = strdup(name);
    node->left = queries;
    return node;
}

ASTNode* make_result_declaration(char* name) {
    ASTNode* node = make_node(AST_RESULT_DECL);
    node->value = strdup(name);
    return node;
}

ASTNode* append_command(ASTNode* list, ASTNode* item) {
    return append_node(list, item);
}

ASTNode* make_command_list(ASTNode* item) {
    return item;
}

ASTNode* make_exec_command(char* name) {
    ASTNode* node = make_node(AST_EXEC_CMD);
    node->value = strdup(name);
    return node;
}

ASTNode* make_if_command(ASTNode* cond, ASTNode* cmds) {
    ASTNode* node = make_node(AST_IF_CMD);
    node->left = cond;
    node->right = cmds;
    return node;
}

ASTNode* make_for_command(char* var, ASTNode* queries, ASTNode* cmds) {
    ASTNode* node = make_node(AST_FOR_CMD);
    node->value = strdup(var);
    node->left = queries;
    node->right = cmds;
    return node;
}

ASTNode* make_exec_assign_command(char* var, char* exec) {
    ASTNode* node = make_node(AST_ASSIGN_EXEC_CMD);
    node->value = strdup(var);
    node->left = make_word_node(exec);
    return node;
}

ASTNode* make_set_op_assign_command(char* var, char* lhs, ASTOperator op, char* rhs) {
    ASTNode* node = make_node(AST_ASSIGN_SET_CMD);
    node->value = strdup(var);
    node->left = make_binary_node(op, make_word_node(lhs), make_word_node(rhs));
    return node;
}

ASTNode* make_condition_node(const char* type, char* val1, char* val2) {
    ASTNode* node = make_node(AST_CONDITION);
    node->value = strdup(type);
    node->left = make_word_node(val1);
    if (val2) node->right = make_string_node(val2);
    return node;
}

ASTNode* make_query_node(ASTNode* terms) {
    ASTNode* node = make_node(AST_QUERY);
    node->left = terms;
    return node;
}

ASTNode* make_query_list(ASTNode* q, ASTNode* tail) {
    return append_node(q, tail);
}

ASTNode* append_query(ASTNode* list, ASTNode* item) {
    return append_node(list, item);
}

ASTNode* make_term_list(ASTNode* item) {
    return item;
}

ASTNode* append_term(ASTNode* list, ASTNode* item) {
    return append_node(list, item);
}

ASTNode* make_unary_term(ASTOperator op, ASTNode* child) {
    return make_unary_node(op, child);
}

ASTNode* make_binary_term(ASTOperator op, ASTNode* left, ASTNode* right) {
    return make_binary_node(op, left, right);
}
