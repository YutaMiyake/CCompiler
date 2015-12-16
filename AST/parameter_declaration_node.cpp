#include "ast_node.h"
parameter_declaration_node::parameter_declaration_node(declaration_specifiers_node* declSpec): ast_node(){
  init();
  this->declSpec = declSpec;
}
parameter_declaration_node::parameter_declaration_node(declaration_specifiers_node* declSpec, declarator_node* decl): ast_node(){
  init();
  this->declSpec = declSpec;
  this->decl = decl;
}
parameter_declaration_node::parameter_declaration_node(declaration_specifiers_node* declSpec, abstract_declarator_node* absDecl): ast_node(){
  init();
  this->declSpec = declSpec;
  this->absDecl = absDecl;
}
void parameter_declaration_node::init(){
  this->declSpec = NULL;
  this->decl = NULL;
  this->absDecl = NULL;
}
parameter_declaration_node::~parameter_declaration_node(){

}
void parameter_declaration_node::clear(){
  if(this->declSpec!=NULL){
    this->declSpec->clear();
    delete this->declSpec;
  }
  if(this->decl!=NULL){
    this->decl->clear();
    delete this->decl;
  }
  if(this->absDecl!=NULL){
    this->absDecl->clear();
    delete this->absDecl;
  }
}
void parameter_declaration_node::print(){
  visualizer.debug("parameter_declaration");
  visualizer.addNode(this->id,"param");
  visualizer.addEdge(this->pid,this->id);

  if(this->declSpec != NULL){
    this->declSpec->setPID(this->id);
    this->declSpec->print();
  }

  if(this->decl != NULL){
    this->decl->setPID(this->id);
    this->decl->print();
  }
  else if(this->absDecl != NULL){
    this->absDecl->setPID(this->id);
    this->absDecl->print();
  }
}
std::string parameter_declaration_node::generateCode(){
  std::string ret;
  /*if(this->declSpec != NULL){
    this->declSpec->generateCode();
  }
  */
  if(this->decl != NULL){
    ret = this->decl->generateCode();
  }
  else if(this->absDecl != NULL){
    ret = this->absDecl->generateCode();
  }
  return ret;
}
