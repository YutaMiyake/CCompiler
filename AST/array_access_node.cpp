#include "ast_node.h"
array_access_node::
array_access_node(postfix_expression_node* postExpr,
                  expression_node* expr,
                  constant_expression_node* arraySizeNode)
    : postfix_expression_node(postExpr, expr) {

    this->arraySizeNode = arraySizeNode;
}
