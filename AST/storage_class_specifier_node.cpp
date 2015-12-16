#include "ast_node.h"
storage_class_specifier_node::storage_class_specifier_node(): ast_node(){
}
storage_class_specifier_node::storage_class_specifier_node(SpecName::Storage storeType): ast_node(){
  this->storeType = storeType;
}
void storage_class_specifier_node::clear(){

}
void storage_class_specifier_node::print(){
  visualizer.debug("storage_class_specifier");
  Spec spec;
  spec.setStorage(this->storeType);
  visualizer.addNode(this->id,spec.getStorageClassStr());
  visualizer.addEdge(this->pid,this->id);
}
std::string storage_class_specifier_node::generateCode(){
  return "";
}
