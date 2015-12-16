#include "ast_node.h"

enum_specifier_node::enum_specifier_node(): ast_node(){
}

enum_specifier_node::enum_specifier_node(identifier_node* identifier, enumerator_list_node* enm): ast_node(){
    this->enumList = enm;
    this->identifier = identifier;
}
void enum_specifier_node::clear(){
  if(this->identifier!=NULL){
    this->identifier->clear();
    delete this->identifier;
  }
  if(this->enumList!=NULL){
    this->enumList->clear();
    delete this->enumList;
  }
}
void enum_specifier_node::print(){
  visualizer.debug("enum_specifier");
  visualizer.addNode(this->id, "enum");
  visualizer.addEdge(this->pid, this->id);
  if(this->identifier!=NULL){
    this->identifier->setPID(this->id);
    this->identifier->print();
  }
  if(this->enumList!=NULL){
    this->enumList->setPID(this->id);
    this->enumList->print();
  }
}

std::string enum_specifier_node::generateCode(){
  return "";
}
