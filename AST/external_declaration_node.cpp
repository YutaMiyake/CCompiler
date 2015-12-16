#include "ast_node.h"

external_declaration_node::external_declaration_node(): ast_node(){
}

external_declaration_node::external_declaration_node(
  function_definition_node* child): ast_node(){
    this -> functionChild = child;
    this -> declChild = NULL;
}

//add a declaration node child
external_declaration_node::external_declaration_node(
  declaration_node* child): ast_node(){
    this -> functionChild = NULL;
    this -> declChild = child;
}

external_declaration_node::~external_declaration_node(){

}
void external_declaration_node::clear(){
  if(this->declChild!=NULL){
    this->declChild->clear();
    delete this->declChild;
  }
  if(this->functionChild!=NULL){
    this->functionChild->clear();
    delete this->functionChild;
  }
}

//print name and name of child
void external_declaration_node::print(){
    visualizer.debug("external_declaration");
    //print own info
    if (this->functionChild == NULL) {
        this->declChild->setPID(this->pid);
        this->declChild->print();
    }
    else{
      this->functionChild->setPID(this->pid);
      this->functionChild->print();
    }
}

//later
std::string external_declaration_node::generateCode(){
  if (this->functionChild == NULL) {
      return this->declChild->generateCode();
  }
  else{
    return this->functionChild->generateCode();
  }
}
