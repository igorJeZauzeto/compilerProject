#include <stdio.h>
#include "query.tab.h"
#include "ast.h"

extern ASTNode* root;

int yyparse(void);


void print_ast(ASTNode* node, int indent) {
    if (!node) return;

    for (int i = 0; i < indent; i++) printf("  ");

    switch (node->type) {
        case AST_PROGRAM: printf("AST_PROGRAM\n"); break;
        case AST_DECLARATIONS: printf("AST_DECLARATIONS\n"); break;
        case AST_COMMANDS: printf("AST_COMMANDS\n"); break;
        case AST_QUERY_DECL: printf("AST_QUERY_DECL (%s)\n", node->value); break;
        case AST_QUERY_LIST_DECL: printf("AST_QUERY_LIST_DECL (%s)\n", node->value); break;
        case AST_RESULT_DECL: printf("AST_RESULT_DECL (%s)\n", node->value); break;
        case AST_EXEC_CMD: printf("AST_EXEC_CMD (%s)\n", node->value); break;
        case AST_IF_CMD: printf("AST_IF_CMD\n"); break;
        case AST_FOR_CMD: printf("AST_FOR_CMD (%s)\n", node->value); break;
        case AST_ASSIGN_EXEC_CMD: printf("AST_ASSIGN_EXEC_CMD (%s = exec %s)\n", node->value, node->right ? node->right->value : ""); break;
        case AST_ASSIGN_SET_CMD: printf("AST_ASSIGN_SET_CMD (%s = %s op %s)\n", node->value, node->left ? node->left->value : "", node->right ? node->right->value : ""); break;
        case AST_CONDITION: printf("AST_CONDITION (%s)\n", node->value); break;
        case AST_QUERY: printf("AST_QUERY\n"); break;
        case AST_QUERY_LIST: printf("AST_QUERY_LIST\n"); break;
        case AST_TERM_LIST: printf("AST_TERM_LIST\n"); break;
        case AST_TERM_WORD: printf("AST_TERM_WORD (%s)\n", node->value); break;
        case AST_TERM_STRING: printf("AST_TERM_STRING (%s)\n", node->value); break;
        case AST_TERM_DIRECTIVE: printf("AST_TERM_DIRECTIVE (%s)\n", node->value); break;
        case AST_TERM_UNARY:
            printf("AST_TERM_UNARY (op: %d)\n", node->op);
            break;
        case AST_TERM_BINARY:
            printf("AST_TERM_BINARY (op: %d)\n", node->op);
            break;
        default: printf("UNKNOWN NODE\n"); break;
    }

    if (node->left) print_ast(node->left, indent + 1);
    if (node->right) print_ast(node->right, indent + 1);
    if (node->next) print_ast(node->next, indent);
}

int main() {
    if (yyparse() == 0) {
        printf("Parse sucessfull.\n");
        print_ast(root, 0);
    } else {
        printf("Parse not sucessfull.\n");
    }
    return 0;
}
