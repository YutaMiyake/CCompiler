#include "ast_node.h"
init_declarator_list_node::init_declarator_list_node(): ast_node(){
}
init_declarator_list_node::init_declarator_list_node(init_declarator_node* child): ast_node(){
  this->children.push_back(child);
}
init_declarator_list_node::~init_declarator_list_node(){

}
void init_declarator_list_node::clear(){
  for(int child = 0; child < this->children.size(); child++){
    if(this->children[child]!=NULL){
      this->children[child]->clear();
      delete this->children[child];
    }
  }
}
void init_declarator_list_node::addInitDecl(init_declarator_node* child){
  this->children.push_back(child);
}
std::vector<init_declarator_node*> init_declarator_list_node::getChildren() const{
  return this->children;
}
void init_declarator_list_node::print(){
  visualizer.debug("init_declarator_list");
  visualizer.addNode(this->id,"init_declarator_list");
  visualizer.addEdge(this->pid,this->id);

  for(int child = 0; child < this->children.size(); child++){
    if(this->children[child]!=NULL){
      this->children[child]->setPID(this->id);
      this->children[child]->print();
    }
  }
}
std::string init_declarator_list_node::generateCode(){
  for(int child = 0; child < this->children.size(); child++){
    if(this->children[child]!=NULL){
      this->children[child]->generateCode();
    }
  }
  return "";
}