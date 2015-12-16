#include "ast_node.h"

enumerator_node::enumerator_node(): ast_node(){
}

enumerator_node::enumerator_node(identifier_node* identifier, constant_expression_node* constExpr): ast_node(){
    this->identifier = identifier;
    this->constExpr = constExpr;
}
void enumerator_node::clear(){
  if(this->identifier!=NULL){
    this->identifier->clear();
    delete this->identifier;
  }
  if(this->constExpr!=NULL){
    this->constExpr->clear();
    delete this->constExpr;
  }
}
void enumerator_node::print(){
  visualizer.debug("enumerator");
  visualizer.addNode(this->id, "{}");
  visualizer.addEdge(this->pid, this->id);

  if(this->constExpr!=NULL){
    this->constExpr->setPID(this->id);
    this->constExpr->print();
  }

}

std::string enumerator_node::generateCode(){
  return "";
}
