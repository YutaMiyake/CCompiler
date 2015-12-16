#include "ast_node.h"
unary_operator_node::unary_operator_node(OpType::Type op): ast_node(){
    this->op = op;
  }
void unary_operator_node::clear(){

}
void unary_operator_node::print(){
    visualizer.debug("unary_operator");
    switch(this->op){
      case OpType::AND:
        visualizer.addNode(this->id,"&");
        visualizer.addEdge(this->pid,this->id);
      break;
      case OpType::ASTERISK:
        visualizer.addNode(this->id,"*");
        visualizer.addEdge(this->pid,this->id);
      break;
      case OpType::PLUS:
        visualizer.addNode(this->id,"+");
        visualizer.addEdge(this->pid,this->id);
      break;
      case OpType::MINUS:
        visualizer.addNode(this->id,"-");
        visualizer.addEdge(this->pid,this->id);
      break;
      case OpType::TILDE:
        visualizer.addNode(this->id,"~");
        visualizer.addEdge(this->pid,this->id);
      break;
      case OpType::BANG:
        visualizer.addNode(this->id,"!");
        visualizer.addEdge(this->pid,this->id);
      break;
      default:
        std::cout << "ERROR: unknown unary operator type" <<std::endl;
      break;
    }
  }

std::string unary_operator_node::generateCode(){
    std::string ret;
    switch(this->op){
      case OpType::AND:
        codeGenerator.debug(" AND ");
      break;
      case OpType::ASTERISK:
        codeGenerator.debug(" MUL ");
      break;
      case OpType::PLUS:
        codeGenerator.debug(" PLUS ");
      break;
      case OpType::MINUS:
        codeGenerator.debug(" SUB ");
      break;
      case OpType::TILDE:
        codeGenerator.debug(" TILDE ");
      break;
      case OpType::BANG:
        codeGenerator.debug(" BANG ");
      break;
    }
    return ret;
  }
