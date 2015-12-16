#include "ast_node.h"
primary_expression_node::primary_expression_node(identifier_node* identifier): ast_node(){
  init();
  this->mode = 0;
  this->identifier = identifier;
}
primary_expression_node::primary_expression_node(constant_node* constant): ast_node(){
  init();
  this->mode = 1;
  this->constant = constant;
}
primary_expression_node::primary_expression_node(string_node* string): ast_node(){
  init();
  this->mode = 2;
  this->string = string;
}
primary_expression_node::primary_expression_node(expression_node* expr): ast_node(){
  init();
  this->mode = 3;
  this->expr = expr;
}
primary_expression_node::~primary_expression_node(){

}
void primary_expression_node::clear(){
  if(this->identifier!=NULL){
    this->identifier->clear();
    delete this->identifier;
  }
  if(this->constant!=NULL){
    this->constant->clear();
    delete this->constant;
  }
  if(this->expr!=NULL){
    this->expr->clear();
    delete this->expr;
  }
}
void primary_expression_node::init(){
  this->identifier = NULL;
  this->constant = NULL;
  this->string = NULL;
  this->expr = NULL;
  this->mode = -1;
}
bool primary_expression_node::isIdentifier() const{
  return this->identifier != NULL;
}
identifier_node* primary_expression_node::getIdentifier() const{
  return this->identifier;
}

void primary_expression_node::print(){
  visualizer.debug("primary_expression");
  switch(this->mode){
    case 0:
      if(this->identifier != NULL){
        this->identifier->setPID(this->pid);
        this->identifier->print();
      }
    break;
    case 1:
      if(this->constant != NULL){
        this->constant->setPID(this->pid);
        this->constant->print();
      }
    break;
    case 2:
      if(this->string != NULL){
        this->string->setPID(this->pid);
        this->string->print();
      }
    break;
    case 3:
      if(this->expr != NULL){
        this->expr->setPID(this->pid);
        this->expr->print();
      }
    break;
    default:
      error("[A] ERROR: unknown primary expression type while print");
    break;
  } // end switch
}
Spec* primary_expression_node::getSpec(){
  switch(this->mode){
    case 0:
      if(this->identifier != NULL){
        return this->identifier->getSpec();
      }
    case 1:
      if(this->constant != NULL){
        return this->constant->getSpec();
      }
    case 2:
      if(this->string != NULL){
        //return this->string->getSpec();
      }
    case 3:
      if(this->expr != NULL){
        return this->expr->getSpec();
      }
  } // end switch
  return NULL;
}
std::string primary_expression_node::generateCode(){
  switch(this->mode){
    case 0:
      return this->identifier->generateCode();
    case 1:
      return this->constant->generateCode();
    case 2:
      //return this->string->generateCode();
    case 3:
      return this->expr->generateCode();
  } // end switch
  return "";
}