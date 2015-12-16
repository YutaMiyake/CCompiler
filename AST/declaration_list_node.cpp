#include "ast_node.h"
declaration_list_node::declaration_list_node(){

}
declaration_list_node::declaration_list_node(declaration_node* child){
  this->children.push_back(child);
}
declaration_list_node::~declaration_list_node(){
}
void declaration_list_node::clear(){
  for(int child = 0; child < this->children.size(); child++){
    if(this->children[child]!=NULL){
      this->children[child]->clear();
      delete this->children[child];
    }
  }
}
void declaration_list_node::addDecl(declaration_node* child){
  this->children.push_back(child);
}
std::vector<declaration_node*> declaration_list_node::getChildren() const{
  return this->children;
}
void declaration_list_node::print(){
  visualizer.addNode(this->id,"declaration_list");
  visualizer.addEdge(this->pid,this->id);
  visualizer.debug("declaration_list");
  for(int child = 0; child < this->children.size(); child++){
    if(this->children[child]!=NULL){
      this->children[child]->setPID(this->id);
      this->children[child]->print();
    }
  }
}
std::string declaration_list_node::generateCode(){
  for(int child = 0; child < this->children.size(); child++){
    if(this->children[child]!=NULL){
      this->children[child]->generateCode();
    }
  }
  return "";
}