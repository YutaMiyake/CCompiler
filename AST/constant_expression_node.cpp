#include "ast_node.h"
constant_expression_node::constant_expression_node(conditional_expression_node* condExpr): ast_node(){
  init();
  this->condExpr = condExpr;
}
constant_expression_node::~constant_expression_node(){
  if(this->condExpr!=NULL){
    delete this->condExpr;
  }
}
void constant_expression_node::clear(){
  if(this->condExpr!=NULL){
    this->condExpr->clear();
    delete this->condExpr;
  }
}
void constant_expression_node::init(){
  this->condExpr = NULL;
}
void constant_expression_node::print(){
  visualizer.debug("constant_expression");
  if(this->condExpr!=NULL){
    this->condExpr->setPID(this->pid);
    this->condExpr->print();
  }
}
Spec* constant_expression_node::getSpec(){
// fow now
  if(this->condExpr != NULL){
    return this->condExpr->getSpec();
  }
  return NULL;
}
std::string constant_expression_node::generateCode(){
  if(this->condExpr!=NULL){
    return this->condExpr->generateCode();
  }
  return "";
}
