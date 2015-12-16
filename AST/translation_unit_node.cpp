#include "ast_node.h"

translation_unit_node::translation_unit_node(): ast_node(){
}

translation_unit_node::translation_unit_node(external_declaration_node* child): ast_node(){
    this->children.push_back(child);
}
translation_unit_node::~translation_unit_node(){
}
void translation_unit_node::clear(){
  for(int child = 0; child < this->children.size(); child++){
    if(this->children[child]!=NULL){
      this->children[child]->clear();
      delete this->children[child];
    }
  }
}
//add more external declaration nodes as children
void translation_unit_node::addExternDecl(external_declaration_node* child){
    this->children.push_back(child);
}

//return all of the children of the node
std::vector<external_declaration_node*> translation_unit_node::getChildren() const{
    return this->children;
}

//print the name of this node followed by children (graphviz readable?)
void translation_unit_node::print(){
    visualizer.debug("translation_unit");
    visualizer.addNode(this->id,"translation_unit");
    for(int child = 0; child < this->children.size(); child++){
    this->children[child]->setPID(this->id);
    this->children[child]->print();
  }
}

//implemented later
std::string translation_unit_node::generateCode(){
  for(int child = 0; child < this->children.size(); child++){
    this->children[child]->generateCode();
  }
  return "";
}
