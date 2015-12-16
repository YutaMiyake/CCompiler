#include "ast_node.h"
logical_and_expression_node::logical_and_expression_node(
  inclusive_or_expression_node* iorExpr): ast_node(){
  init();
  this->iorExpr = iorExpr;
  this->mode = 0;
}
logical_and_expression_node::logical_and_expression_node(
  logical_and_expression_node* logAndExpr, OpType::Type op,
  inclusive_or_expression_node* iorExpr): ast_node(){
  init();
  this->logAndExpr = logAndExpr;
  this->op = op;
  this->iorExpr = iorExpr;
  this->mode = 1;
}
logical_and_expression_node::~logical_and_expression_node(){

}
void logical_and_expression_node::clear(){
  if(this->logAndExpr!=NULL){
    this->logAndExpr->clear();
    delete this->logAndExpr;
  }
  if(this->iorExpr!=NULL){
    this->iorExpr->clear();
    delete this->iorExpr;
  }
}
void logical_and_expression_node::init(){
  logAndExpr = NULL;
  iorExpr = NULL;
  op = OpType::NONE;
  mode = -1;
}
void logical_and_expression_node::print(){
  visualizer.debug("logical_and_expression");
  switch(this->mode){
    case 0:
      if(this->iorExpr!=NULL){
        this->iorExpr->setPID(this->pid);
        this->iorExpr->print();
      }
    break;
    case 1:
      visualizer.addNode(this->id,"&&");
      visualizer.addEdge(this->pid,this->id);

      if(this->logAndExpr!=NULL){
        this->logAndExpr->setPID(this->id);
        this->logAndExpr->print();
      }
      if(this->iorExpr!=NULL){
        this->iorExpr->setPID(this->id);
        this->iorExpr->print();
      }
    break;
    default:
      std::cout << "ERROR: unknown logical and expression type" << std::endl;
    break;
  }
}
Spec* logical_and_expression_node::getSpec(){
// fow now
  switch(this->mode){
    case 0:
      return this->iorExpr->getSpec();
    break;
    case 1:
      return this->logAndExpr->getSpec();
    break;
  }
  return NULL;
}
std::string logical_and_expression_node::generateCode(){
  switch(this->mode){
    case 0:
      return this->iorExpr->generateCode();
    break;
    case 1:
      codeGenerator.debug(" && ");

      if(this->logAndExpr!=NULL){
        this->logAndExpr->generateCode();
      }
      if(this->iorExpr!=NULL){
        this->iorExpr->generateCode();
      }
    break;
  }
  return "";
}