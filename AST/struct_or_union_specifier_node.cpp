#include "ast_node.h"
struct_or_union_specifier_node::struct_or_union_specifier_node(
  struct_or_union_node* structUnion,std::string identifier,
  struct_declaration_list_node* structDecl): ast_node(){

  this->structUnion = structUnion;
  this->identifier = identifier;
  this->structDecl = structDecl;
}
void struct_or_union_specifier_node::clear(){
  if(this->structUnion!=NULL){
    this->structUnion->clear();
    delete this->structUnion;
  }
  if(this->structDecl!=NULL){
    this->structDecl->clear();
    delete this->structDecl;
  }
}
void struct_or_union_specifier_node::print(){
  visualizer.debug("struct_or_union_specifier");
  this->structDecl->setPID(this->pid); // assume structUnion is valid
  this->structUnion->print();

  if(this->identifier != ""){
    int identifier_id = ast_node::getUID();
    visualizer.addNode(identifier_id,this->identifier);
    visualizer.addEdge(this->structUnion->getID(),identifier_id);
  }
  if(this->structDecl != NULL){
    this->structDecl->setPID(this->structUnion->getID());
    this->structDecl->print();
  }
}
std::string  struct_or_union_specifier_node::generateCode(){
  return "";
}