#include "ast_node.h"
labeled_statement_node::labeled_statement_node(std::string identifier, statement_node* statement): ast_node(){
  init();
  this->identifier = identifier;
  this->statement = statement;
}
labeled_statement_node::labeled_statement_node(LabelType::Type label_type, constant_expression_node* constExpr, statement_node* statement): ast_node(){
  init();
  this->label_type = label_type;
  this->constExpr = constExpr;
  this->statement = statement;
}
labeled_statement_node::~labeled_statement_node(){
}
void labeled_statement_node::clear(){
  if(this->statement!=NULL){
    this->statement->clear();
    delete this->statement;
  }
  if(this->constExpr!=NULL){
    this->constExpr->clear();
    delete this->constExpr;
  }
}
void labeled_statement_node::init(){
  this->label_type = LabelType::NONE;
  this->identifier = "";
  this->constExpr = NULL;
  this->statement = NULL;
}
void labeled_statement_node::print(){
  visualizer.debug("labeled_statement");
  if(this->label_type == LabelType::NONE){
    std::stringstream ss;
    ss << this->identifier << ":";
    visualizer.addNode(this->id,ss.str());
    visualizer.addEdge(this->pid,this->id);
    if(this->statement != NULL){
      this->statement->setPID(this->id);
      this->statement->print();
    }
  }
  else if(this->label_type == LabelType::CASE){
    visualizer.addNode(this->id,"case");
    visualizer.addEdge(this->pid,this->id);
    if(this->constExpr != NULL){
      this->constExpr->setPID(this->id);
      this->constExpr->print();
    }
    if(this->statement != NULL){
      this->statement->setPID(this->id);
      this->statement->print();
    }
  }
  else if(this->label_type == LabelType::DEFAULT){
    visualizer.addNode(this->id,"default:");
    visualizer.addEdge(this->pid,this->id);
    if(this->statement != NULL){
      this->statement->setPID(this->id);
      this->statement->print();
    }
  }
}
std::string labeled_statement_node::generateCode(){
  if(this->label_type == LabelType::NONE){
    if(this->statement != NULL){
      return this->statement->generateCode();
    }
  }
  else if(this->label_type == LabelType::CASE){
    if(this->constExpr != NULL){
      return this->constExpr->generateCode();
    }
    if(this->statement != NULL){
      return this->statement->generateCode();
    }
  }
  else if(this->label_type == LabelType::DEFAULT){
    if(this->statement != NULL){
      return this->statement->generateCode();
    }
  }
  return "";
}
