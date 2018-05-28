#include "sem/sem.h"
#include "sem/exception/sem_exception.h"
#include "ast/func/ast_func_head.h"

ast_func_head::ast_func_head(ast_id *id) : id(id), type(nullptr), ret_type({false}) {}

ast_func_head::~ast_func_head() {
    delete id;
    delete type;
    for (auto child : param_name_vec) {
        delete child;
    }
    for (auto child : param_type_vec) {
        delete child;
    }
}

const std::string &ast_func_head::get_name() const {
    return id->get_id();
}

int ast_func_head::get_param_num() const {
    return (int) param_name_vec.size();
}

const std::vector<ast_id *> &ast_func_head::get_param_name_node() const {
    return param_name_vec;
}

const std::vector<ast_type_node *> &ast_func_head::get_param_type_node() const {
    return param_type_vec;
}

const sem_type &ast_func_head::get_ret_type() const {
    return ret_type;
}

const func_sign &ast_func_head::get_func_sign() const {
    return sign;
}

void ast_func_head::add_param(ast_id *param_name, ast_type_node *param_type) {
    param_name_vec.emplace_back(param_name);
    param_type_vec.emplace_back(param_type);
}

void ast_func_head::set_ret_type_node(ast_type_node *type) {
    this->type = type;
}

bool ast_func_head::semantics_child() {
    if (!id->analyse(false)) {
        return false;
    }
    for (auto child : param_name_vec) {
        if (!child->analyse()) {
            return false;
        }
    }
    for (auto child : param_type_vec) {
        if (!child->analyse()) {
            return false;
        }
    }
    return type == nullptr || type->analyse();
}

bool ast_func_head::semantics_self() {
    try {
        for (auto child : param_type_vec) {
            sem::assert_is_type(child->get_type());
        }
        if (type != nullptr) {
            sem::assert_is_type(type->get_type());
        }

        // Set function signature and return type
        sign.id = id->get_id();
        for (auto child : param_type_vec) {
            sign.param_type_vec.emplace_back(child->get_type());
        }
        if (type == nullptr) {
            ret_type = built_in_type::VOID_TYPE;
        } else {
            ret_type = type->get_type();
        }

        return true;
    } catch (const sem_exception &e) {
        PRINT_ERROR_MSG(e);
        return false;
    }
}

void ast_func_head::explain_impl(std::string &res, int indent) const {
    id->explain_impl(res, indent);

    explain_indent(res, indent);
    res += "--- params ---\n";
    for (int i = 0; i < get_param_num(); i++) {
        param_name_vec[i]->explain_impl(res, indent);
        param_type_vec[i]->explain_impl(res, indent);
    }

    explain_indent(res, indent);
    res += "--- return type ---\n";
    if (type != nullptr) {
        type->explain_impl(res, indent);
    } else {
        explain_indent(res, indent);
        res += "no return type\n";
    }
}