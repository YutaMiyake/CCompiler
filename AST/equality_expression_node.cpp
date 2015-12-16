#include "ast_node.h"
equality_expression_node::equality_expression_node(relational_expression_node* relExpr): ast_node(){
  init();
  this->relExpr = relExpr;
  this->mode = 0;
}
equality_expression_node::equality_expression_node(
  equality_expression_node* equalExpr, OpType::Type op,
  relational_expression_node* relExpr): ast_node(){
  init();
  this->equalExpr = equalExpr;
  this->op = op;
  this->relExpr = relExpr;
  this->mode = 1;
}
equality_expression_node::~equality_expression_node(){
}
void equality_expression_node::clear(){
  if(this->equalExpr!=NULL){
    this->equalExpr->clear();
    delete this->equalExpr;
  }
  if(this->relExpr!=NULL){
    this->relExpr->clear();
    delete this->relExpr;
  }
}
void equality_expression_node::init(){
  equalExpr = NULL;
  relExpr = NULL;
  op = OpType::NONE;
  mode = -1;
}
void equality_expression_node::print(){
  visualizer.debug("equality_expression");
  switch(this->mode){
    case 0:
      if(this->relExpr!=NULL){
        this->relExpr->setPID(this->pid);
        this->relExpr->print();
      }
    break;
    case 1:
      if(this->op == OpType::EQ){
        visualizer.addNode(this->id,"==");
      }else{ // NE
        visualizer.addNode(this->id,"!=");
      }
      visualizer.addEdge(this->pid,this->id);

      if(this->equalExpr!=NULL){
        this->equalExpr->setPID(this->id);
        this->equalExpr->print();
      }
      if(this->relExpr!=NULL){
        this->relExpr->setPID(this->id);
        this->relExpr->print();
      }
    break;
    default:
      error("[A] ERROR: unknown equality expression type while print");
    break;
  }
}
Spec* equality_expression_node::getSpec(){
// fow now
  switch(this->mode){
    case 0:
      return this->relExpr->getSpec();
    case 1:
      return this->equalExpr->getSpec();
  }
  return NULL;
}
std::string equality_expression_node::generateCode(){
  std::string result, temp1, temp2;
  switch(this->mode){
    case 0:
      return this->relExpr->generateCode();

    case 1:
      temp1 = this->equalExpr->generateCode();
      temp2 = this->relExpr->generateCode();
      result = ast_node::getNewTempStr();

      codeGenerator.debug(result);
      codeGenerator.debug(" := ");
      codeGenerator.debug(temp1);
      if(this->op == OpType::EQ){
        codeGenerator.debug(" == ");
      }else{ // NE
        codeGenerator.debug(" != ");
      }
      codeGenerator.debug(temp2);
      codeGenerator.debug("\n");
    return result;
  }
  return "";
}