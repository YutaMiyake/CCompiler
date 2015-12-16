#include "ast_node.h"
struct_declarator_list_node::struct_declarator_list_node():ast_node(){
}
struct_declarator_list_node::struct_declarator_list_node(struct_declarator_node* child):ast_node(){
  addStrDecl(child);
}
void struct_declarator_list_node::addStrDecl(struct_declarator_node* child){
  this->children.push_back(child);
}
std::vector<struct_declarator_node*> struct_declarator_list_node::getChildren() const{
  return this->children;
}
void struct_declarator_list_node::clear(){
  for(int child = 0; child < this->children.size(); child++){
    if(this->children[child]!=NULL){
      this->children[child]->clear();
      delete this->children[child];
    }
  }
}
void struct_declarator_list_node::print(){
 visualizer.debug("struct_declaration_list");
  visualizer.addNode(this->id,"struct_declaration_list");
  visualizer.addEdge(this->pid,this->id);
  for(int child = 0; child < this->children.size(); child++){
    if(this->children[child]!=NULL){
      this->children[child]->setPID(this->id);
      this->children[child]->print();
    }
  }
}
std::string struct_declarator_list_node::generateCode(){
  return "";
}