#include "ast_node.h"
identifier_node::identifier_node(std::string name, SymbolNode* symnode, int line, int col): ast_node(){
  this->id_name = name;
  this->id_symnode = symnode;
  this->line = line;
  this->col = col;
}
identifier_node::~identifier_node(){
}
void identifier_node::clear(){
  if(this->id_symnode!=NULL){
    symDumper.addSymToDump(this->id_symnode);
  }
}
void identifier_node::setSymNode(SymbolNode* sym){
  this->id_symnode = sym;
}
int identifier_node::getLine() const{
  return this->line;
}
int identifier_node::getCol() const{
  return this->col;
}
std::string identifier_node::getName() const{
  return this->id_name;
}
SymbolNode* identifier_node::getSymNode() const{
  return this->id_symnode;
}
void identifier_node::print(){
  visualizer.debug("identifier");
  visualizer.addNode(this->id,this->id_name);
  visualizer.addEdge(this->pid,this->id);
}
Spec* identifier_node::getSpec(){
  if(this->id_symnode!=NULL){
    return this->id_symnode->getSpecifier();
  }
  return NULL;
}
std::string identifier_node::generateCode(){
  return this->id_name;
}