#ifndef MY_PASCAL_AST_BLOCK_H
#define MY_PASCAL_AST_BLOCK_H

#include <vector>

#include "ast/ast_node.h"

class ast_block_head : public ast_node {
public:
    ~ast_block_head() override;

    void add_node(ast_node* node);

    bool analyse() override;

    void explain_impl(std::string &res, int indent) const override;

private:
    std::vector<ast_node*> node_vec;
};

class ast_block : public ast_node {
public:
    ast_block(ast_block_head *head, ast_node *body);

    ~ast_block() override;

    bool analyse() override;

    void explain_impl(std::string &res, int indent) const override;

private:
    ast_block_head *head;
    ast_node *body;
};

#endif //MY_PASCAL_AST_BLOCK_H
