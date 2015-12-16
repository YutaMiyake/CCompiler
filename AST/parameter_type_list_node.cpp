#include "ast_node.h"
parameter_type_list_node::parameter_type_list_node(parameter_list_node* paramList){
  this->paramList = paramList;
}
parameter_type_list_node::~parameter_type_list_node(){

}
void parameter_type_list_node::clear(){
  if(this->paramList!=NULL){
    this->paramList->clear();
    delete this->paramList;
  }
}
void parameter_type_list_node::print(){
  visualizer.debug("parameter_type_list");
  if(this->paramList!=NULL){
    this->paramList->setPID(this->pid);
    this->paramList->print();
  }
}
std::string parameter_type_list_node::generateCode(){
  if(this->paramList!=NULL){
    return this->paramList->generateCode();
  }
}
