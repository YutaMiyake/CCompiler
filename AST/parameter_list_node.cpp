#include "ast_node.h"
parameter_list_node::parameter_list_node(): ast_node(){
}
parameter_list_node::parameter_list_node(parameter_declaration_node* child): ast_node(){
  this->children.push_back(child);
}
parameter_list_node::~parameter_list_node(){

}
void parameter_list_node::clear(){
  for(int child = 0; child < this->children.size(); child++){
    if(this->children[child]!=NULL){
      this->children[child]->clear();
      delete this->children[child];
    }
  }
}
void parameter_list_node::addParamDecl(parameter_declaration_node* child){
  this->children.push_back(child);
}
std::vector<parameter_declaration_node*> parameter_list_node::getChildren() const{
  return this->children;
}
void parameter_list_node::print(){
  visualizer.debug("parameter_list");
  visualizer.addNode(this->id,"parameter_list");
  visualizer.addEdge(this->pid,this->id);
  for(int child = 0; child < this->children.size(); child++){
    if(this->children[child]!=NULL){
      this->children[child]->setPID(this->id);
      this->children[child]->print();
    }
  }
}
std::string parameter_list_node::generateCode(){
  std::string ret;
  for(int child = 0; child < this->children.size(); child++){
    if(this->children[child]!=NULL){
      ret = ret + this->children[child]->generateCode() + " ";
    }
  }
  return ret;
}
