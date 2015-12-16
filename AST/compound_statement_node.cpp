#include "ast_node.h"
compound_statement_node::compound_statement_node(
  declaration_list_node* declList, statement_list_node* stateList): ast_node(){
  init();
  this->declList = declList;
  this->stateList = stateList;
}
compound_statement_node::~compound_statement_node(){
}
void compound_statement_node::clear(){
  if(this->declList!=NULL){
    this->declList->clear();
    delete this->declList;
  }
  if(this->stateList!=NULL){
    this->stateList->clear();
    delete this->stateList;
  }
}

void compound_statement_node::init(){
  this->declList = NULL;
  this->stateList = NULL;
}
void compound_statement_node::print(){
  visualizer.debug("compound_statement");
  visualizer.addNode(this->id, "{}");
  visualizer.addEdge(this->pid, this->id);
  if(this->declList!=NULL){
    this->declList->setPID(this->id);
    this->declList->print();
  }
  if(this->stateList!=NULL){
    this->stateList->setPID(this->id);
    this->stateList->print();
  }
}
std::string compound_statement_node::generateCode(){
  if(this->declList!=NULL){
    this->declList->generateCode();
  }
  if(this->stateList!=NULL){
    this->stateList->generateCode();
  }
  return "";
}