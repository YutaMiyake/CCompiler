#include "ast_node.h"
initializer_list_node::initializer_list_node(): ast_node(){
}
initializer_list_node::initializer_list_node(initializer_node* child): ast_node(){
  this->children.push_back(child);
}
initializer_list_node::~initializer_list_node(){

}
void initializer_list_node::clear(){
  for(int child = 0; child < this->children.size(); child++){
    if(this->children[child]!=NULL){
      this->children[child]->clear();
      delete this->children[child];
    }
  }
}
void initializer_list_node::addInit(initializer_node* child){
  this->children.push_back(child);
}
std::vector<initializer_node*> initializer_list_node::getChildren() const{
  return this->children;
}
void initializer_list_node::print(){
  visualizer.debug("initializer_list");
  visualizer.addNode(this->id,"initializer_list");
  visualizer.addEdge(this->pid,this->id);
  for(int child = 0; child < this->children.size(); child++){
    if(this->children[child]!=NULL){
      this->children[child]->setPID(this->id);
      this->children[child]->print();
    }
  }
}
std::string initializer_list_node::generateCode(){
  std::string ret;
  for(int child = 0; child < this->children.size(); child++){
    if(this->children[child]!=NULL){
      if(ret == ""){
        ret = this->children[child]->generateCode();
      }
      else {
        ret += "," + this->children[child]->generateCode();
      }
    }
  }
  return ret;
}
