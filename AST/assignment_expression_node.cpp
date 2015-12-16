#include "ast_node.h"
assignment_expression_node::assignment_expression_node(
  conditional_expression_node* cond_expr): ast_node(){
  init();
  this->cond_expr = cond_expr;
  this->mode = 0;
}
assignment_expression_node::assignment_expression_node(
  unary_expression_node* unary_expr, assignment_operator_node* assign_op,
  assignment_expression_node* assign_expr): ast_node(){
  init();
  this->unary_expr = unary_expr;
  this->assign_op = assign_op;
  this->assign_expr = assign_expr;
  this->mode = 1;
}
assignment_expression_node::~assignment_expression_node(){
}
void assignment_expression_node::clear(){
  if(this->unary_expr!=NULL){
    this->unary_expr->clear();
    delete this->unary_expr;
  }
  if(this->assign_expr!=NULL){
    this->assign_expr->clear();
    delete this->assign_expr;
  }
  if(this->cond_expr!=NULL){
    this->cond_expr->clear();
    delete this->cond_expr;
  }
  if(this->assign_op!=NULL){
    this->assign_op->clear();
    delete this->assign_op;
  }
}
void assignment_expression_node::init(){
  this->cond_expr = NULL;
  this->unary_expr = NULL;
  this->assign_op = NULL;
  this->assign_expr = NULL;
  this->mode = -1;
}
void assignment_expression_node::print(){
  visualizer.debug("assignment_expression");
  switch(this->mode){
    case 0:
      if(this->cond_expr!=NULL){
        this->cond_expr->setPID(this->pid);
        this->cond_expr->print();
      }
    break;
    case 1:
      if(this->assign_op!=NULL){
        this->assign_op->setPID(this->pid);
        this->assign_op->print();
      }
      if(this->unary_expr!=NULL){
        this->unary_expr->setPID(this->assign_op->getID());
        this->unary_expr->print();
      }
      if(this->assign_expr!=NULL){
        this->assign_expr->setPID(this->assign_op->getID());
        this->assign_expr->print();
      }
    break;
    default:
      error("[A] ERROR: unknown assignment expression type while print");
    break;
  }
}
Spec* assignment_expression_node::getSpec(){
SpecName::BaseType left = SpecName::NoType;
SpecName::BaseType right = SpecName::NoType;
Spec *leftSpec, *rightSpec;

// fow now
  switch(this->mode){
    case 0:
      return this->cond_expr->getSpec();

    case 1:
      if(this->unary_expr!=NULL && this->assign_expr != NULL){
        leftSpec = this->unary_expr->getSpec();
        rightSpec = this->assign_expr->getSpec();

        if(leftSpec!= NULL && rightSpec!= NULL){
          left = leftSpec->getBaseType();
          right = rightSpec->getBaseType();

          // std::cout << left << " " << right << std::endl;

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
    } // end switch
  return NULL;
}
std::string assignment_expression_node::generateCode(){
  std::string temp1,temp2,result;
  std::stringstream ss;
  switch(this->mode){
    case 0:
      return this->cond_expr->generateCode();

    case 1:
      temp1 = this->unary_expr->generateCode();
      temp2 = this->assign_expr->generateCode();
      ss << temp1 << this->assign_op->generateCode() << temp2 << "\n";
      codeGenerator.debug(ss.str());

      return temp1;
  }
  return "";
}