#include "ast_node.h"
pointer_node::pointer_node(type_qualifier_list_node* typeQualList, pointer_node* pointer): ast_node(){
  this->typeQualList = typeQualList;
  this->pointer = pointer;
}
pointer_node::~pointer_node(){

}
void pointer_node::clear(){
  if(this->typeQualList!=NULL){
    this->typeQualList->clear();
    delete this->typeQualList;
  }
  if(this->pointer!=NULL){
    this->pointer->clear();
    delete this->pointer;
  }
}
void pointer_node::print(){
  visualizer.debug("pointer");
  visualizer.addNode(this->id,"*");
  visualizer.addEdge(this->pid,this->id);
  if(this->typeQualList != NULL){
    this->typeQualList->setPID(this->id);
    this->typeQualList->print();
  }
  if(this->pointer != NULL){
    this->pointer->setPID(this->id);
    this->pointer->print();
  }
}
std::string pointer_node::generateCode(){
  std::string ret;
  return ret;
}
