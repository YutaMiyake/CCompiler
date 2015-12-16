#include "SymbolNode.h"
SymbolNode::SymbolNode(): initialized(false), defined(false){};
SymbolNode::SymbolNode(std::string name, Spec* specifier, int line, int col, bool defined){
  this->name = name;
  this->specifier = specifier;
  this->line = line;
  this->col = col;
  this->defined = defined;
}
SymbolNode::~SymbolNode(){
  if(this->specifier!=NULL){
    delete this->specifier;
  }
}
void SymbolNode::setName(std::string name){
  this->name = name;
}
void SymbolNode::setLine(int line){
  this->line = line;
}
void SymbolNode::setCol(int col){
  this->col = col;
}
void SymbolNode::setInitialized(bool initialized){
  this->initialized = initialized;
}
void SymbolNode::setDefined(bool defined){
  this->defined = defined;
}
// getters ------------------------------
std::string SymbolNode::getName() const{
  return this->name;
}
std::string SymbolNode::getSpecName() const{
  return this->specifier->toString();
}
int SymbolNode::getLine() const{
  return this->line;
}
int SymbolNode::getCol() const{
  return this->col;
}
void SymbolNode::setSpecifier(Spec* specifier){
  this->specifier = specifier;
}
Spec* SymbolNode::getSpecifier() const{
  return this->specifier;
}
bool SymbolNode::isInitialized() const{
  return this->initialized;
}
bool SymbolNode::isDefined() const{
  return this->defined;
}