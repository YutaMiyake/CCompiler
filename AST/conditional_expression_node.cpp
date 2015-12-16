#include "ast_node.h"
conditional_expression_node::conditional_expression_node(
  logical_or_expression_node* logOrExpr): ast_node(){
  init();
  this->logOrExpr = logOrExpr;
  this->mode = 0;
}
conditional_expression_node::conditional_expression_node(
  logical_or_expression_node* logOrExpr, expression_node* expr,
  conditional_expression_node* condExpr): ast_node(){
  init();
  this->condExpr = condExpr;
  this->expr = expr;
  this->logOrExpr = logOrExpr;
  this->mode = 1;
}
conditional_expression_node::~conditional_expression_node(){
}
void conditional_expression_node::clear(){
  if(this->logOrExpr!=NULL){
    this->logOrExpr->clear();
    delete this->logOrExpr;
  }
  if(this->condExpr!=NULL){
    this->condExpr->clear();
    delete this->condExpr;
  }
  if(this->expr!=NULL){
    this->expr->clear();
    delete this->expr;
  }
}
void conditional_expression_node::init(){
  this->condExpr = NULL;
  this->logOrExpr = NULL;
  this->expr = NULL;
  this->mode = -1;
}
void conditional_expression_node::print(){
  visualizer.debug("conditional_expression");
  switch(this->mode){
    case 0:
      if(this->logOrExpr!=NULL){
        this->logOrExpr->setPID(this->pid);
        this->logOrExpr->print();
      }
    break;
    case 1:
      visualizer.addNode(this->id,"conditional_expression"); // for now
      visualizer.addEdge(this->pid,this->id);

      if(this->logOrExpr!=NULL){
        this->logOrExpr->setPID(this->id);
        this->logOrExpr->print();
      }
      if(this->expr!=NULL){
        this->expr->setPID(this->id);
        this->expr->print();
      }
      if(this->condExpr!=NULL){
        this->condExpr->setPID(this->id);
        this->condExpr->print();
      }

    break;
    default:
      std::cout << "ERROR: unknown conditional expression type" << std::endl;
    break;
  }
}
Spec* conditional_expression_node::getSpec(){
// fow now
  switch(this->mode){
    case 0:
      return this->logOrExpr->getSpec();
    break;
    case 1:
      return this->condExpr->getSpec();
    break;
  }
  return NULL;
}
std::string conditional_expression_node::generateCode(){
  switch(this->mode){
    case 0:
      return this->logOrExpr->generateCode();

    case 1:
      if(this->logOrExpr!=NULL){
        this->logOrExpr->generateCode();
      }
      if(this->expr!=NULL){
        this->expr->generateCode();
      }
      if(this->condExpr!=NULL){
        this->condExpr->generateCode();
      }
    break;
  }
  return "";
}