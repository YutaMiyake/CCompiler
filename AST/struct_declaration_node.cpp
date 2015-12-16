#include "ast_node.h"
struct_declaration_node::struct_declaration_node(specifier_qualifier_list_node* spqlist,
  struct_declarator_list_node* strDeclList):ast_node(){
  this->spqlist = spqlist;
  this->strDeclList = strDeclList;
}
void struct_declaration_node::clear(){
  if(this->spqlist != NULL){
    this->spqlist->clear();
    delete this->spqlist;
  }
  if(this->strDeclList != NULL){
    this->strDeclList->clear();
    delete this->strDeclList;
  }
}
void struct_declaration_node::print(){
  visualizer.debug("struct_declaration");
  visualizer.addNode(this->id,"struct_declaration");
  visualizer.addEdge(this->pid,this->id);
  if(this->spqlist!=NULL){
    this->spqlist->setPID(this->id);
    this->spqlist->print();
  }
  if(this->strDeclList!=NULL){
    this->strDeclList->setPID(this->id);
    this->strDeclList->print();
  }
}
std::string  struct_declaration_node::generateCode(){
  return "";
}