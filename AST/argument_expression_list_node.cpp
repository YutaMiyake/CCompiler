#include "ast_node.h"
argument_expression_list_node::argument_expression_list_node(): ast_node(){
}
argument_expression_list_node::argument_expression_list_node(assignment_expression_node* child): ast_node(){
  this->children.push_back(child);
}
void argument_expression_list_node::addAssignmentExpr(assignment_expression_node* child){
  this->children.push_back(child);
}
argument_expression_list_node::~argument_expression_list_node(){
}
void argument_expression_list_node::clear(){
  for(int child = 0; child < this->children.size(); child++){
    if(this->children[child]!=NULL){
      this->children[child]->clear();
      delete this->children[child];
    }
  }
}
std::vector<assignment_expression_node*> argument_expression_list_node::getChildren() const{
  return this->children;
}
void argument_expression_list_node::print(){
  visualizer.debug("argument_expression_list");
  visualizer.addNode(this->id,"argument_expression_list");
  visualizer.addEdge(this->pid,this->id);
  for(int child = 0; child < this->children.size(); child++){
    if(this->children[child]!=NULL){
      this->children[child]->setPID(this->id);
      this->children[child]->print();
    }
  }
}
std::string argument_expression_list_node::generateCode(){
  std::string result;
  for(int child = 0; child < this->children.size(); child++){
    if(this->children[child]!=NULL){
      result = result + " " + this->children[child]->generateCode();
    }
  }
  return result;
}

