#include "ast_node.h"
iteration_statement_node::iteration_statement_node(IterType::Type iter_type, expression_node* expr1,
  statement_node* statement): ast_node(){
  init();
  this->iter_type = iter_type;
  this->expr1 = expr1;
  this->statement = statement;
  this->mode = 0;
}
iteration_statement_node::iteration_statement_node(IterType::Type iter_type, expression_node* expr1,
  expression_node* expr2,expression_node* expr3,statement_node* statement): ast_node(){
  init();
  this->iter_type = iter_type;
  this->expr1 = expr1;
  this->expr2 = expr2;
  this->expr3 = expr3;
  this->statement = statement;
  this->mode = 1;
}
iteration_statement_node::~iteration_statement_node(){

}
void iteration_statement_node::clear(){
  if(this->expr1!=NULL){
    this->expr1->clear();
    delete this->expr1;
  }
  if(this->expr2!=NULL){
    this->expr2->clear();
    delete this->expr2;
  }
  if(this->expr3!=NULL){
    this->expr3->clear();
    delete this->expr3;
  }
  if(this->statement!=NULL){
    this->statement->clear();
    delete this->statement;
  }
}
void iteration_statement_node::init(){
  this->iter_type = IterType::NONE;
  this->expr1 = NULL;
  this->expr2 = NULL;
  this->expr3 = NULL;
  this->statement = NULL;
  this->mode = -1;
}
void iteration_statement_node::print(){
  visualizer.debug("iteration_statement");
  switch(this->mode){
    case 0:
      if(this->iter_type == IterType::WHILE){
        visualizer.addNode(this->id,"while");
        visualizer.addEdge(this->pid,this->id);
        if(this->expr1 != NULL){
          this->expr1->setPID(this->id);
          this->expr1->print();
        }
        if(this->statement != NULL){
          this->statement->setPID(this->id);
          this->statement->print();
        }
      }
      else if(this->iter_type == IterType::DO){
        visualizer.addNode(this->id,"do");
        visualizer.addEdge(this->pid,this->id);
        if(this->statement != NULL){
          this->statement->setPID(this->id);
          this->statement->print();
        }
        if(this->expr1 != NULL){
          this->expr1->setPID(this->id);
          this->expr1->print();
        }
      }
    break;
    case 1:
      visualizer.addNode(this->id,"for");
      visualizer.addEdge(this->pid,this->id);
      if(this->expr1 != NULL){
        this->expr1->setPID(this->id);
        this->expr1->print();
      }
      if(this->expr2 != NULL){
        this->expr2->setPID(this->id);
        this->expr2->print();
      }
      if(this->expr3 != NULL){
        this->expr3->setPID(this->id);
        this->expr3->print();
      }
      if(this->statement != NULL){
        this->statement->setPID(this->id);
        this->statement->print();
      }
    break;
    default:
      std::cout << "ERROR: unknown iteration statement type" << std::endl;
    break;
  }
}
std::string iteration_statement_node::generateCode(){
  std::string cond, label1, label2, label3, label4;
  switch(this->mode){
    case 0:
      if(this->iter_type == IterType::WHILE){
        label1 = ast_node::getNewLabelStr();
        label2 = ast_node::getNewLabelStr();
        label3 = ast_node::getNewLabelStr();
        codeGenerator.debug(label1+":\n");
        cond = this->expr1->generateCode();
        codeGenerator.debug("if "+cond+" goto "+label2+"\n");
        codeGenerator.debug("goto "+label3+"\n");
        codeGenerator.debug(label2+":\n");
        this->statement->generateCode();
        codeGenerator.debug("goto "+label1+"\n");
        codeGenerator.debug(label3+":\n");
      }
      else if(this->iter_type == IterType::DO){
       label1 = ast_node::getNewLabelStr();
       label2 = ast_node::getNewLabelStr();
       codeGenerator.debug(label1+":\n");
       this->statement->generateCode();
       cond = this->expr1->generateCode();
       codeGenerator.debug("if "+cond+" goto "+label1+"\n");
       codeGenerator.debug("goto "+label2+"\n");
       codeGenerator.debug(label2+":\n");
      }
    break;
    case 1:
      label1 = ast_node::getNewLabelStr();
      label2 = ast_node::getNewLabelStr();
      label3 = ast_node::getNewLabelStr();
      label4 = ast_node::getNewLabelStr();

      if(this->expr1 != NULL){
        this->expr1->generateCode();
      }

      codeGenerator.debug(label1+":\n");  // label1
      if(this->expr2 != NULL){
        cond = this->expr2->generateCode();
        codeGenerator.debug("if "+cond+" goto "+label2+"\n");
      }
      codeGenerator.debug("goto "+label3+"\n");

      codeGenerator.debug(label4+":\n");  // label4
      if(this->expr3 != NULL){
        this->expr3->generateCode();
      }
      codeGenerator.debug("goto "+label1+"\n");

      codeGenerator.debug(label2+":\n"); // label2
      if(this->statement != NULL){
        this->statement->generateCode();
      }
      codeGenerator.debug("goto "+label4+"\n");

      codeGenerator.debug(label3+":\n");  // label3
    break;
  }
  return "";
}