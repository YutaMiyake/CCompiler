#include "ast_node.h"
statement_list_node::statement_list_node(): ast_node(){
}
statement_list_node::statement_list_node(statement_node* child): ast_node(){
  this->children.push_back(child);
}
statement_list_node::~statement_list_node(){

}
void statement_list_node::clear(){
  for(int child = 0; child < this->children.size(); child++){
    if(this->children[child]!=NULL){
      this->children[child]->clear();
      delete this->children[child];
    }
  }
}
void statement_list_node::addStmt(statement_node* child){
  this->children.push_back(child);
}
std::vector<statement_node*> statement_list_node::getChildren() const{
  return this->children;
}
void statement_list_node::print(){
  visualizer.debug("statement_list");
  visualizer.addNode(this->id,"statement_list");
  visualizer.addEdge(this->pid,this->id);

  for(int child = 0; child < this->children.size(); child++){
    if(this->children[child]!=NULL){
      this->children[child]->setPID(this->id);
      this->children[child]->print();
    }
  }
}
std::string statement_list_node::generateCode(){
  for(int child = 0; child < this->children.size(); child++){
    if(this->children[child]!=NULL){
      this->children[child]->generateCode();
    }
  }
  return "";
}