#include "ast_node.h"
  cast_expression_node::cast_expression_node(
    unary_expression_node* unaryExpr): ast_node(){
    this->unaryExpr = unaryExpr;
  }
  void cast_expression_node::print(){
    visualizer.debug("cast_expression");
    if(this->unaryExpr!=NULL){
      this->unaryExpr->setPID(this->pid);
      this->unaryExpr->print();
    }
  }
  cast_expression_node::~cast_expression_node(){
  }
  void cast_expression_node::clear(){
    if(this->unaryExpr!=NULL){
      this->unaryExpr->clear();
      delete this->unaryExpr;
    }
  }
  Spec* cast_expression_node::getSpec(){
    if(this->unaryExpr!=NULL){
      return this->unaryExpr->getSpec();
    }
    return NULL;
  }
  std::string cast_expression_node::generateCode(){
    return this->unaryExpr->generateCode();
  }