#include "ast_node.h"
init_declarator_node::init_declarator_node(declarator_node* declarator,
  initializer_node* initializer):ast_node(){
  init();
  this->declarator = declarator;
  this->initializer = initializer;
}
init_declarator_node::~init_declarator_node(){

}
void init_declarator_node::clear(){
  if(this->declarator!=NULL){
    this->declarator->clear();
    delete this->declarator;
  }
  if(this->initializer!=NULL){
    this->initializer->clear();
    delete this->initializer;
  }
}
void init_declarator_node::init(){
  this->declarator = NULL;
  this->initializer = NULL;
}
void init_declarator_node::print(){
  visualizer.debug("init_declarator");
  if(this->initializer != NULL){
    this->equal_id = ast_node::getUID();
    visualizer.addNode(this->equal_id,"=");
    visualizer.addEdge(this->pid, this->equal_id);
    if(this->declarator!= NULL){
      this->declarator->setPID(this->equal_id);
      this->declarator->print();
    }
    if(this->initializer!= NULL){
      this->initializer->setPID(this->equal_id);
      this->initializer->print();
    }
  }
  else{
    if(this->declarator!= NULL){
      this->declarator->setPID(this->pid);
      this->declarator->print();
    }
  }
  getSpec();
}
Spec* init_declarator_node::getSpec(){
  // declarations/initializations
  SpecName::BaseType left = SpecName::NoType;
  SpecName::BaseType right = SpecName::NoType;
  Spec *leftSpec, *rightSpec;

  if(this->declarator!= NULL && this->initializer != NULL){
    leftSpec = this->declarator->getSpec();
    rightSpec = this->initializer->getSpec();

    if(leftSpec!= NULL && rightSpec!= NULL){
      left = leftSpec->getBaseType();
      right = rightSpec->getBaseType();

      //std::cout << left << " " << right << std::endl;

      // check if assignable
      if(leftSpec->isValue()){
        error("[A] ERROR: expression is not assignable");
      }

      // type matched
      if(left == right){
        return leftSpec;
      }
      // implicit conversions
      else if(left == SpecName::Float && right == SpecName::Int){ // int to float
        warning("[A] WARNING: implicit conversion from 'int' to 'float'");
        return new TypeBasic(SpecName::Float);
      }
      else if(left == SpecName::Int && right == SpecName::Float){ // float to int
        warning("[A] WARNING: implicit conversion from 'float' to 'int'");
        return new TypeBasic(SpecName::Int);
      }
    }
  }
  return this->declarator->getSpec();
}
std::string init_declarator_node::generateCode(){
  std::stringstream ss;
  std::string temp1, temp2;
  Spec * spec = this->declarator->getSpec();
  SpecName::TypeKind typekind = SpecName::NoKind;

  if(spec != NULL){
    typekind = spec->getTypeKind();
  }

  if(this->initializer != NULL){
    temp2 = this->initializer->generateCode();
    temp1 = this->declarator->generateCode();

    if(typekind == SpecName::Basic){
      ss << "Init: " << temp1 << " " << spec->toTypeString() << " " <<  temp2 << "\n";
      codeGenerator.debug(ss.str());
    }
    else if(typekind == SpecName::Array){
      ss << "Init: " << temp1 << " array " << dynamic_cast<TypeArray*>(spec)->getSpace()
         << " " + dynamic_cast<TypeArray*>(spec)->getElemTypeName() << " " << temp2 << "\n";
      codeGenerator.debug(ss.str());
    }
    return temp1;
  }
  else{
    temp1 = this->declarator->generateCode();
    if(typekind == SpecName::Basic){
      codeGenerator.debug("Decl: " + temp1 + " " + spec->toTypeString() + +"\n");
    }
    else if(typekind == SpecName::Array){
      ss << "Decl: " << temp1 << " array " << dynamic_cast<TypeArray*>(spec)->getSpace()
         << " " + dynamic_cast<TypeArray*>(spec)->getElemTypeName() << "\n";
      codeGenerator.debug(ss.str());
    }
    return temp1;
  }
  return "";
}