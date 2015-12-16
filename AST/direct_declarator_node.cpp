#include "ast_node.h"
  direct_declarator_node::direct_declarator_node(identifier_node* identifier): ast_node(){
    init();
    this->identifier = identifier;
    this->mode = 0;
  }

  direct_declarator_node::direct_declarator_node(DirectType::Type direct_type,
    direct_declarator_node* direct_declarator,
    constant_expression_node* constExpr): ast_node(){
    init();
    this->direct_type = direct_type;
    this->direct_declarator = direct_declarator;
    this->constExpr = constExpr;
    this->mode = 1;
  }

  direct_declarator_node::direct_declarator_node(DirectType::Type direct_type,
    direct_declarator_node* direct_declarator): ast_node(){
    init();
    this->direct_type = direct_type;
    this->direct_declarator = direct_declarator;
    this->mode = 2;
  }

  direct_declarator_node::direct_declarator_node(DirectType::Type direct_type,
    direct_declarator_node* direct_declarator, parameter_type_list_node* paramList): ast_node(){
    init();
    this->direct_type = direct_type;
    this->direct_declarator = direct_declarator;
    this->paramList = paramList;
    this->mode = 3;
  }

  direct_declarator_node::direct_declarator_node(DirectType::Type direct_type,
    direct_declarator_node* direct_declarator, identifier_list_node* idList): ast_node(){
    init();
    this->direct_type = direct_type;
    this->direct_declarator = direct_declarator;
    this->idList = idList;
    this->mode = 4;
  }

  direct_declarator_node::~direct_declarator_node(){
  }

  void direct_declarator_node::clear(){
    if(this->identifier!=NULL){
      this->identifier->clear();
      delete this->identifier;
    }
    if(this->declarator!=NULL){
      this->declarator->clear();
      delete this->declarator;
    }
    if(this->direct_declarator!=NULL){
      this->direct_declarator->clear();
      delete this->direct_declarator;
    }
    if(this->constExpr!=NULL){
      this->constExpr->clear();
      //delete this->constExpr; // ERROR: pointer being freed was not allocated
    }
    if(this->paramList!=NULL){
      this->paramList->clear();
      delete this->paramList;
    }
    if(this->idList!=NULL){
      this->idList->clear();
      delete this->idList;
    }
  }

  void direct_declarator_node::init(){
    this->identifier = NULL;
    this->declarator = NULL;
    this->direct_declarator = NULL;
    this->constExpr = NULL;
    this->paramList = NULL;
    this->idList = NULL;
    this->direct_type = DirectType::NONE;
    this->mode = -1;
  }

  void direct_declarator_node::print(){
    visualizer.debug("direct_declarator");
    switch(this->direct_type){
      case DirectType::NONE:
      if(this->identifier!=NULL){
        visualizer.addNode(this->id,this->identifier->getName());
        visualizer.addEdge(this->pid,this->id);
      }
      break;
      case DirectType::ARRAY:
        visualizer.addNode(this->id,"array");
        visualizer.addEdge(this->pid,this->id);

        if(this->direct_declarator!= NULL){
          this->direct_declarator->setPID(this->id);
          this->direct_declarator->print();
        }
        if(this->constExpr!= NULL){
          this->constExpr->setPID(this->id);
          this->constExpr->print();
        }
        else{
          // used to display only
          int size_id = ast_node::getUID();
          visualizer.addNode(size_id,"1");
          visualizer.addEdge(this->id,size_id);
        }
      break;
      case DirectType::FUNCTION:
        visualizer.addNode(this->id,"function");
        visualizer.addEdge(this->pid,this->id);

        if(this->direct_declarator!= NULL){
          this->direct_declarator->setPID(this->id);
          this->direct_declarator->print();
        }
        if(this->paramList!= NULL){
          this->paramList->setPID(this->id);
          this->paramList->print();
        }
      break;
      case DirectType::FUNCTION_CALL:
        visualizer.addNode(this->id,"function_call");
        visualizer.addEdge(this->pid,this->id);

        if(this->direct_declarator!= NULL){
          this->direct_declarator->setPID(this->id);
          this->direct_declarator->print();
        }
        if(this->idList!= NULL){
          this->idList->setPID(this->id);
          this->idList->print();
        }
      break;
    } // end switch
  }
Spec* direct_declarator_node::getSpec(){
  Spec * spec = NULL;

  if(this->mode == 0){
      if(this->identifier!=NULL){
        spec = this->identifier->getSpec();
      }
      return spec;
  }

  spec = this->direct_declarator->getSpec();

  if(this->direct_type == DirectType::ARRAY){
    if(this->constExpr!=NULL){
      if(this->constExpr->getSpec()->getBaseType() != SpecName::Int){
        error("[A] ERROR: array size must be integer");
      }
    }
    spec->setTypeKind(SpecName::Array);
  }
  else if(this->direct_type == DirectType::FUNCTION){
  }
  else if(this->direct_type == DirectType::FUNCTION_CALL){
  }
  return spec;
}
std::string direct_declarator_node::generateCode(){
  std::string ret;
  switch(this->direct_type){
    case DirectType::NONE:
      return this->identifier->generateCode();
    case DirectType::ARRAY:
      return generateArrayCode();
    case DirectType::FUNCTION:
      ret = this->direct_declarator->generateCode();
      if(this->paramList!=NULL){
        ret = ret + " " + this->paramList->generateCode();
      }
      return ret;
    case DirectType::FUNCTION_CALL:
    return this->direct_declarator->generateCode();
  } // end switch
}
std::string direct_declarator_node::generateArrayCode(){
  /*
  std::string offset;
  if(this->constExpr!= NULL){
    offset = this->constExpr->generateCode();
  }
  codeGenerator.debug(ast_node::getNewTempStr() + " := " + offset +";\n");
  */
  return this->direct_declarator->generateCode();
}
std::string direct_declarator_node::getName(){
  if(this->identifier!=NULL){
    return this->identifier->getName();
  }
  return this->direct_declarator->getName();
}
