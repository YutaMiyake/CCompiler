#include "ast_node.h"
type_specifier_node::type_specifier_node(): ast_node(){
}
type_specifier_node::type_specifier_node(TypeSpecifier::Type type): ast_node(){
  this->type = type;
}
void type_specifier_node::clear(){

}
void type_specifier_node::print(){
  visualizer.debug("type_specifier");
  std::string type;
  switch(this->type){
    case TypeSpecifier::VOID:
      type = "void";
    break;
    case TypeSpecifier::CHAR:
      type = "char";
    break;
    case TypeSpecifier::SHORT:
      type = "short";
    break;
    case TypeSpecifier::LONG:
      type = "long";
    break;
    case TypeSpecifier::INT:
      type = "int";
    break;
    case TypeSpecifier::FLOAT:
      type = "float";
    break;
    case TypeSpecifier::DOUBLE:
      type = "double";
    break;
    case TypeSpecifier::SIGNED:
      type = "signed";
    break;
    case TypeSpecifier::UNSIGNED:
      type = "unsigned";
    break;
    case TypeSpecifier::TYPEDEF_NAME:
      type = "type_name";
    break;
  }
  visualizer.addNode(this->id,type);
  visualizer.addEdge(this->pid,this->id);
}
std::string type_specifier_node::generateCode(){
  switch(this->type){
    case TypeSpecifier::VOID:
      codeGenerator.debug(" void ");
    break;
    case TypeSpecifier::CHAR:
      codeGenerator.debug(" char ");
    break;
    case TypeSpecifier::SHORT:
      codeGenerator.debug(" short ");
    break;
    case TypeSpecifier::LONG:
      codeGenerator.debug(" long ");
    break;
    case TypeSpecifier::INT:
      codeGenerator.debug(" int ");
    break;
    case TypeSpecifier::FLOAT:
      codeGenerator.debug(" float ");
    break;
    case TypeSpecifier::DOUBLE:
      codeGenerator.debug(" double ");
    break;
    case TypeSpecifier::SIGNED:
      codeGenerator.debug(" signed ");
    break;
    case TypeSpecifier::UNSIGNED:
      codeGenerator.debug(" unsigned ");
    break;
    case TypeSpecifier::TYPEDEF_NAME:
      codeGenerator.debug(" type_name ");
    break;
  }
  return "";
}
