#include "ast_node.h"
function_definition_node::function_definition_node(): ast_node(){
}
function_definition_node::function_definition_node(declaration_specifiers_node* specifiers,
                         declarator_node* decl,
                         declaration_list_node* decList,
                         compound_statement_node* compStmt): ast_node(){
  this->specifiers = specifiers;
  this->decl = decl;
  this->decList = decList;
  this->compStmt = compStmt;
}
function_definition_node::~function_definition_node(){

}
void function_definition_node::clear(){
  if(this->specifiers!=NULL){
    this->specifiers->clear();
    delete this->specifiers;
  }
  if(this->decl!=NULL){
    this->decl->clear();
    delete this->decl;
  }
  if(this->decList!=NULL){
    this->decList->clear();
    delete this->decList;
  }
  if(this->compStmt!=NULL){
    this->compStmt->clear();
    delete this->compStmt;
  }
}
void function_definition_node::print(){
  visualizer.debug("function_definition");
  visualizer.addNode(this->id, "function_definition");
  visualizer.addEdge(this->pid, this->id);
  if(this->specifiers!=NULL){
    this->spec_id = ast_node::getUID();
    visualizer.addNode(this->spec_id, "specifier");
    visualizer.addEdge(this->id, this->spec_id);
    this->specifiers->setPID(this->spec_id);
    this->specifiers->print();
  }
  if(this->decl!=NULL){
    this->decl->setPID(this->id);
    this->decl->print();
  }
  if(this->decList!=NULL){
    this->decList->setPID(this->id);
    this->decList->print();
  }
  if(this->compStmt!=NULL){
    this->compStmt->setPID(this->id);
    this->compStmt->print();
  }
}
std::string function_definition_node::generateCode(){
  std::stringstream ss;
  std::string func_str = this->decl->generateCode();
  std::string tok, func_name;
  std::stringstream func_ss(func_str);
  std::vector<std::string> linevec;

  while(getline(func_ss, tok,' ')) {
      linevec.push_back(tok);
  }
  func_name = linevec[0];

  ss << "Function: " << func_name << "\n";
  codeGenerator.debug(ss.str());
  ss.str("");
  ss << "BeginFunc " << (linevec.size()-1)*4 << "\n";
  codeGenerator.debug(ss.str());

  for(int arg = linevec.size()-1; arg > 0; arg--){
    codeGenerator.debug("PopParam "+ linevec[arg] + "\n");
  }
  if(this->decList!=NULL){
    this->decList->generateCode();
  }
  if(this->compStmt!=NULL){
    this->compStmt->generateCode();
  }
  codeGenerator.debug("EndFunc\n");
  return "";
}