#include "ast_node.h"

enumerator_list_node::enumerator_list_node(): ast_node(){
}

enumerator_list_node::enumerator_list_node(enum_specifier_node* child): ast_node(){
  this->children.push_back(child);
}

void enumerator_list_node::addEnumSpec(enum_specifier_node* child){
  this->children.push_back(child);
}
void enumerator_list_node::clear(){
  for(int child = 0; child < this->children.size(); child++){
    if(this->children[child]!=NULL){
      this->children[child]->clear();
      delete this->children[child];
    }
  }
}
std::vector<enum_specifier_node*> enumerator_list_node::getChildren() const{
  return this->children;
}

void enumerator_list_node::print(){
  visualizer.debug("enumerator_list");
  visualizer.addNode(this->id,"{}");
  visualizer.addEdge(this->pid,this->id);
  for(int child = 0; child < this->children.size(); child++){
    if(this->children[child]!=NULL){
      this->children[child]->setPID(this->id);
      this->children[child]->print();
    }
  }
}

std::string enumerator_list_node::generateCode(){
  return "";
}
