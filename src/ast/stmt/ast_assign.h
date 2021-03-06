#ifndef MPC_AST_ASSIGN_H
#define MPC_AST_ASSIGN_H

#include "ast/ast_node.h"
#include "ast/stmt/ast_stmt.h"
#include "ast/id/ast_id.h"

class ast_assign : public ast_node {
public:
    ast_assign(ast_value_node *lhs, ast_value_node *rhs);

    ~ast_assign() override;

    void explain_impl(std::string &res, int indent) const override;

protected:
    bool semantics_child() override;

    bool semantics_self() override;

    void codegen() override;

private:
    ast_value_node *lhs;
    ast_value_node *rhs;
};

#endif //MPC_AST_ASSIGN_H
