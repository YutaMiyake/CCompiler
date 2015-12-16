#include "ast_node.h"
string_node::string_node(): ast_node(){};
string_node::string_node(std::string string_literal): ast_node(){
  this->string_literal = string_literal;
}
std::string string_node::getStringLiteral(){
  return string_literal;
}
void string_node::clear(){

}
void string_node::setStringLiteral(std::string string_literal){
  this->string_literal = string_literal;
}
void string_node::print(){
  visualizer.debug("string");
  visualizer.addNode(this->id,this->string_literal);
  visualizer.addEdge(this->pid,this->id);
}
std::string string_node::generateCode(){
  return "";
}
