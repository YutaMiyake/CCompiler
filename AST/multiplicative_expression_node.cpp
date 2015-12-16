#include "ast_node.h"
multiplicative_expression_node::multiplicative_expression_node(
  cast_expression_node* castExpr): ast_node(){
  init();
  this->castExpr = castExpr;
  this->mode = 0;
}
multiplicative_expression_node::multiplicative_expression_node(
  multiplicative_expression_node* multiExpr, OpType::Type op,
  cast_expression_node* castExpr): ast_node(){
  init();
  this->multiExpr = multiExpr;
  this->op = op;
  this->castExpr = castExpr;
  this->mode = 1;
}
multiplicative_expression_node::~multiplicative_expression_node(){

}
void multiplicative_expression_node::clear(){
  if(this->castExpr!=NULL){
    this->castExpr->clear();
    delete this->castExpr;
  }
  if(this->multiExpr!=NULL){
    this->multiExpr->clear();
    delete this->multiExpr;
  }
}
void multiplicative_expression_node::init(){
  this->multiExpr = NULL;
  this->op = OpType::NONE;
  this->castExpr = NULL;
  this->mode = -1;
}
void multiplicative_expression_node::print(){
  visualizer.debug("multiplicative_expression");
  switch(this->mode){
    case 0:
      if(this->castExpr!=NULL){
        this->castExpr->setPID(this->pid);
        this->castExpr->print();
      }
    break;
    case 1:
      if(this->op == OpType::ASTERISK){
        visualizer.addNode(this->id,"*");
      }
      else if(this->op == OpType::DIV){
        visualizer.addNode(this->id,"/");
      }
      else{
        visualizer.addNode(this->id,"%%");
      }
      visualizer.addEdge(this->pid,this->id);

      if(this->multiExpr!=NULL){
        this->multiExpr->setPID(this->id);
        this->multiExpr->print();
      }
      if(this->castExpr!=NULL){
        this->castExpr->setPID(this->id);
        this->castExpr->print();
      }
    break;
    default:
      std::cout << "ERROR: unknown multiplicative expression type" << std::endl;
    break;
  }
}
Spec* multiplicative_expression_node::getSpec(){
  SpecName::BaseType left, right;
  switch(this->mode){
    case 0:
      if(this->castExpr!=NULL){
        return this->castExpr->getSpec();
      }
      return NULL;

    case 1:
      if(this->multiExpr!=NULL){
        left = this->multiExpr->getSpec()->getBaseType();
      }
      if(this->castExpr!=NULL){
        right = this->castExpr->getSpec()->getBaseType();
      }

      // start *
      if(this->op == OpType::ASTERISK){
        if(left != right){
          // implicit conversion to float
          if(left == SpecName::Float || right == SpecName::Float){
            warning("[A] WARNING: implicit conversion to 'float'");
            return new TypeBasic(SpecName::Float);
          }
        }
        return this->multiExpr->getSpec();
      } // end *

      // start /
      else if(this->op == OpType::DIV){
        if(left != right){
          // implicit conversion to float
          if(left == SpecName::Float || right == SpecName::Float){
            warning("[A] WARNING: implicit conversion to 'float'");
            return new TypeBasic(SpecName::Float);
          }
        }
        return this->multiExpr->getSpec();
      } // end /

      // start %
      else if(this->op == OpType::MOD){
        if(left != SpecName::Int || right != SpecName::Int){
          error("[a] ERROR: modulus division only work with integers");
        }
        return this->multiExpr->getSpec();
      } // end %

      return NULL;

    default:
      return NULL;
  }
}
std::string multiplicative_expression_node::generateCode(){
  std::string result, temp1, temp2;
  std::stringstream ss;
  switch(this->mode){
    case 0:
      return this->castExpr->generateCode();

    case 1:
      temp1 = this->multiExpr->generateCode();
      temp2 = this->castExpr->generateCode();
      result = ast_node::getNewTempStr();

      ss << result << " := " << temp1;
      if(this->op == OpType::ASTERISK){
        ss << " * ";
      }
      else if(this->op == OpType::DIV){
        ss << " / ";
      }
      else{
        ss << " %% ";
      }
      ss << temp2 << "\n";
      codeGenerator.debug(ss.str());
      return result;
  }
  return "";
}
