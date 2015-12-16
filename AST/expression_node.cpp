#include "ast_node.h"
expression_node::expression_node(): ast_node(){
}
expression_node::expression_node(assignment_expression_node* child): ast_node(){
  this->children.push_back(child);
}
expression_node::~expression_node(){
}
void expression_node::clear(){
  for(int child = 0; child < this->children.size(); child++){
    if(this->children[child]!=NULL){
      this->children[child]->clear();
      delete this->children[child];
    }
  }
}
void expression_node::addAssignmentExpr(assignment_expression_node* child){
  this->children.push_back(child);
}
std::vector<assignment_expression_node*> expression_node::getChildren() const{
  return this->children;
}
void expression_node::print(){
  visualizer.debug("expression");
  for(int child = 0; child < this->children.size(); child++){
    if(this->children[child]!=NULL){
      this->children[child]->setPID(this->pid);
      this->children[child]->print();
      this->children[child]->getSpec();
    }
  }
}
Spec* expression_node::getSpec(){
// this is called only if there is one child?
  if(this->children[0]!=NULL){
    return this->children[0]->getSpec();
  }
  return NULL;
}
std::string expression_node::generateCode(){
  if(this->children.size() == 1){
    return this->children[0]->generateCode();
  }
  for(int child = 0; child < this->children.size(); child++){
    if(this->children[child]!=NULL){
      this->children[child]->generateCode();
    }
  }
  return "";
}