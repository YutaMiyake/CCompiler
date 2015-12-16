#include "ast_node.h"
shift_expression_node::shift_expression_node(additive_expression_node* addExpr): ast_node(){
  init();
  this->addExpr = addExpr;
  mode = 0;
}
shift_expression_node::shift_expression_node(shift_expression_node* shiftExpr, OpType::Type op, additive_expression_node* addExpr): ast_node(){
  init();
  this->shiftExpr = shiftExpr;
  this->op = op;
  this->addExpr = addExpr;
  mode = 1;
}
shift_expression_node::~shift_expression_node(){
}
void shift_expression_node::clear(){
  if(this->shiftExpr!=NULL){
    this->shiftExpr->clear();
    delete this->shiftExpr;
  }
  if(this->addExpr!=NULL){
    this->addExpr->clear();
    delete this->addExpr;
  }
}
void shift_expression_node::init(){
  this->shiftExpr = NULL;
  this->op = OpType::NONE;
  this->addExpr = NULL;
  mode = -1;
}
void shift_expression_node::print(){
  visualizer.debug("shift_expression");
    switch(this->mode){
      case 0:
        if(this->addExpr!=NULL){
          this->addExpr->setPID(this->pid);
          this->addExpr->print();
        }
      break;
      case 1:
        if(this->op == OpType::LEFT_OP){
          visualizer.addNode(this->id,"<<");
        }else{
          visualizer.addNode(this->id,">>");
        }
        visualizer.addEdge(this->pid,this->id);

        if(this->shiftExpr!=NULL){
          this->shiftExpr->setPID(this->id);
          this->shiftExpr->print();
        }
        if(this->addExpr!=NULL){
          this->addExpr->setPID(this->id);
          this->addExpr->print();
        }
      break;
      default:
        std::cout << "ERROR: unknown shift expression type" << std::endl;
      break;
    }
  }
Spec* shift_expression_node::getSpec(){
// fow now
  switch(this->mode){
    case 0:
      return this->addExpr->getSpec();
    case 1:
      return this->shiftExpr->getSpec();
  }
  return NULL;
}
std::string shift_expression_node::generateCode(){
  switch(this->mode){
    case 0:
      return this->addExpr->generateCode();
    case 1:
      return this->shiftExpr->generateCode();
  }
}
