#include "ast_node.h"
  struct_or_union_node::struct_or_union_node(StructUnion::Type type): ast_node(){
    this->type = type;
  }
  void struct_or_union_node::clear(){
  }
  void struct_or_union_node::print(){
    std::string label = (this->type == StructUnion::STRUCT)? "struct" : "union";
    visualizer.debug("struct_or_union");
    visualizer.addNode(this->id,label);
    visualizer.addEdge(this->pid, this->id);
  }
  std::string  struct_or_union_node::generateCode(){
    return "";
  }
