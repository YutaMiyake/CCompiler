#include "ast_node.h"
constant_node::constant_node(int ival): ast_node(){
  this->type = ConstType::INT;
  this->ival = ival;
}
constant_node::constant_node(char cval): ast_node(){
  this->type = ConstType::CHAR;
  this->cval = cval;
}
constant_node::constant_node(float fval): ast_node(){
  this->type = ConstType::FLOAT;
  this->fval = fval;
}
int constant_node::getIval() const{
  return this->ival;
}
char constant_node::getCval() const{
  return this->cval;
}
float constant_node::getFval() const{
  return this->fval;
}
void constant_node::setIval(int ival){
  this->ival = ival;
}
void constant_node::setCval(char cval){
  this->cval = cval;
}
void constant_node::setFval(float fval){
  this->fval = fval;
}
void constant_node::clear(){
}
void constant_node::print(){
  visualizer.debug("constant");
  std::stringstream ss;
  if(this->type == ConstType::INT){
      ss << this->ival;
      visualizer.addNode(this->id,ss.str());
      visualizer.addEdge(this->pid,this->id);
  }else if(this->type == ConstType::CHAR){
      ss << this->cval;
      visualizer.addNode(this->id,ss.str());
      visualizer.addEdge(this->pid,this->id);
  }else if(this->type == ConstType::FLOAT){
      ss << this->fval;
      visualizer.addNode(this->id,ss.str());
      visualizer.addEdge(this->pid,this->id);
  }else {
      error("[A] ERROR: Unknown constant type while print");
  }
}
Spec* constant_node::getSpec(){
  TypeBasic* typebasic = NULL;
  if(this->type == ConstType::INT){
      typebasic = new TypeBasic(SpecName::Int);
      typebasic->setValue(true);
    }else if(this->type == ConstType::CHAR){
      typebasic = new TypeBasic(SpecName::Char);
      typebasic->setValue(true);
    }else if(this->type == ConstType::FLOAT){
      typebasic = new TypeBasic(SpecName::Float);
      typebasic->setValue(true);
   }else {
      error("[A] ERROR: Unknown constant type while getSpec");
  }
  return typebasic;
}
std::string constant_node::generateCode(){
  return toStr();
  /*
  std::stringstream ss;
  switch(this->type){
    case ConstType::INT:
      ss << ast_node::getNewTempStr() << " := " << this->ival << ";\n";
      codeGenerator.debug(ss.str());
    break;
    case ConstType::CHAR:
      ss << ast_node::getNewTempStr() << " := " << this->cval << ";\n";
      codeGenerator.debug(ss.str());
    break;
    case ConstType::FLOAT:
      ss << ast_node::getNewTempStr() << " := " << this->fval << ";\n";
      codeGenerator.debug(ss.str());
    break;
    case ConstType::ENUM:
    break;
  }
  */
}
std::string constant_node::toStr(){
std::stringstream ss;
  switch(this->type){
    case ConstType::INT:
      ss << this->ival;
    break;
    case ConstType::CHAR:
      ss << this->cval;
    break;
    case ConstType::FLOAT:
      ss << this->fval;
    break;
    case ConstType::ENUM:
    break;
  }
  return ss.str();
}
