#include "ast_node.h"
ast_node::ast_node(){
  this->name = "";
  this->parent = NULL;
  this->source = "";
  setID();
};
ast_node::~ast_node(){}

int ast_node::getTempNum(){
 return tempNum;
}
int ast_node::getLabelNum(){
 return labelNum;
}
void ast_node::incrTempNum(){
  tempNum++;
}
void ast_node::incrLabelNum(){
  labelNum++;
}

std::string ast_node::getTempStr(){
   std::stringstream ss;
   ss << "_TEMP" << tempNum;
   return ss.str();
 }
std::string ast_node::getNewTempStr(){
   std::stringstream ss;
   ss << "_TEMP" << ++tempNum;
   return ss.str();
 }
std::string ast_node::getLastTempStr(){
   std::stringstream ss;
   ss << "_TEMP" << tempNum-1;
   return ss.str();
}
std::string ast_node::getNewLabelStr(){
   std::stringstream ss;
   ss << "_LABEL" << ++labelNum;
   return ss.str();
}
std::string ast_node::getLabelStr(){
   std::stringstream ss;
   ss << "_LABEL" << labelNum;
   return ss.str();
}
int ast_node::getUID(){
  return unique_id++;
}

void ast_node::setID(){
  this->id = getUID();
}
int ast_node::getID(){
  return this->id;
}
int ast_node::getPID(){
  return this->pid;
}
void ast_node::setPID(int pid){
   this->pid = pid;
}

void ast_node::setSource(std::string source) {
  this->source = source;
}
std::string ast_node::getSource() {
  return this->source;
}

void ast_node::error(const std::string& message) {
    std::cout << message << std::endl;
    exit(1);
}
void ast_node::warning(const std::string& message) {
    std::cout << message << std::endl;
}