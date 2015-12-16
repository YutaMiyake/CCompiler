#include "ast_node.h"
abstract_declarator_node::abstract_declarator_node(pointer_node* pointer,direct_abstract_declarator_node* directAbs): ast_node(){
  this->pointer = pointer;
  this->directAbs = directAbs;
}
void abstract_declarator_node::clear(){
  if(this->pointer != NULL){
    this->pointer->clear();
    delete this->pointer;
  }
  if(this->directAbs != NULL){
    this->directAbs->clear();
    delete this->directAbs;
  }
}
void abstract_declarator_node::print(){
  visualizer.debug("abstract_declarator");
  if(this->pointer != NULL){
    this->pointer->setPID(this->pid);
    this->pointer->print();
  }
  if(this->directAbs != NULL){
    this->directAbs->setPID(this->pid);
    this->directAbs->print();
  }
}
std::string abstract_declarator_node::generateCode(){
  return "";
}