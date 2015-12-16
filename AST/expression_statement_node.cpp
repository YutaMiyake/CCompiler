#include "ast_node.h"
expression_statement_node::expression_statement_node(): ast_node(){
  init();
}
expression_statement_node::expression_statement_node(expression_node* expr): ast_node(){
  init();
  this->expr = expr;
}
expression_statement_node::~expression_statement_node(){
}
void expression_statement_node::clear(){
  if(this->expr!=NULL){
    this->expr->clear();
    delete this->expr;
  }
}
void expression_statement_node::init(){
  this->expr = NULL;
}
void expression_statement_node::print(){
  visualizer.debug("expression_statement");
  if(this->expr != NULL){
    this->expr->setPID(this->pid);
    this->expr->print();
  }
}
std::string expression_statement_node::generateCode(){
  return this->expr->generateCode();
}