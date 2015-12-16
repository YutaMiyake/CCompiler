#include "ast_node.h"
type_qualifier_list_node::type_qualifier_list_node(): ast_node(){
}
type_qualifier_list_node::type_qualifier_list_node(type_qualifier_node* child): ast_node(){
  this->children.push_back(child);
}
type_qualifier_list_node::~type_qualifier_list_node(){
}
void type_qualifier_list_node::clear(){
  for(int child = 0; child < this->children.size(); child++){
    if(this->children[child]!=NULL){
      this->children[child]->clear();
      delete this->children[child];
    }
  }
}
void type_qualifier_list_node::addQual(type_qualifier_node* child){
  this->children.push_back(child);
}
std::vector<type_qualifier_node*> type_qualifier_list_node::getChildren() const{
  return this->children;
}
void type_qualifier_list_node::print(){
  visualizer.debug("type_qualifier_list");
  visualizer.addNode(this->id,"type_qualifier_list");
  visualizer.addEdge(this->pid,this->id);
  for(int child = 0; child < this->children.size(); child++){
    if(this->children[child]!=NULL){
      this->children[child]->setPID(this->id);
      this->children[child]->print();
    }
  }
}

std::string  type_qualifier_list_node::generateCode(){
  return "";
}
