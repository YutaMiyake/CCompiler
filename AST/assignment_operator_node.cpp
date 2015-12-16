#include "ast_node.h"
assignment_operator_node::assignment_operator_node(): ast_node(){}
assignment_operator_node::assignment_operator_node(AssignType::Type op): ast_node(){
  this->op = op;
}
void assignment_operator_node::clear(){

}
void assignment_operator_node::print(){
  visualizer.debug("assignment_operator");
  switch(this->op){
    case AssignType::EQUAL:
      visualizer.addNode(this->id,"=");
      visualizer.addEdge(this->pid,this->id);
    break;
    case AssignType::MUL_ASSIGN:
      visualizer.addNode(this->id,"*=");
      visualizer.addEdge(this->pid,this->id);
    break;
    case AssignType::DIV_ASSIGN:
      visualizer.addNode(this->id,"/=");
      visualizer.addEdge(this->pid,this->id);
    break;
    case AssignType::MOD_ASSIGN:
      visualizer.addNode(this->id,"%%=");
      visualizer.addEdge(this->pid,this->id);
    break;
    case AssignType::ADD_ASSIGN:
      visualizer.addNode(this->id,"+=");
      visualizer.addEdge(this->pid,this->id);
    break;
    case AssignType::SUB_ASSIGN:
      visualizer.addNode(this->id,"-=");
      visualizer.addEdge(this->pid,this->id);
    break;
    case AssignType::LEFT_ASSIGN:
      visualizer.addNode(this->id,"<<=");
      visualizer.addEdge(this->pid,this->id);
    break;
    case AssignType::RIGHT_ASSIGN:
      visualizer.addNode(this->id,">>=");
      visualizer.addEdge(this->pid,this->id);
    break;
    case AssignType::AND_ASSIGN:
      visualizer.addNode(this->id,"&=");
      visualizer.addEdge(this->pid,this->id);
    break;
    case AssignType::XOR_ASSIGN:
      visualizer.addNode(this->id,"^=");
      visualizer.addEdge(this->pid,this->id);
    break;
    case AssignType::OR_ASSIGN:
      visualizer.addNode(this->id,"|=");
      visualizer.addEdge(this->pid,this->id);
    break;
    default:
      std::cout << "ERROR Unknown assignment operator type";
    break;
  } // end switch
}
std::string assignment_operator_node::generateCode(){
  switch(this->op){
    case AssignType::EQUAL:
      return " := ";
    case AssignType::MUL_ASSIGN:
      return " :*= ";
    case AssignType::DIV_ASSIGN:
      return " :/= ";
    case AssignType::MOD_ASSIGN:
      return " :%%= ";
    case AssignType::ADD_ASSIGN:
      return " :+= ";
    case AssignType::SUB_ASSIGN:
      return " :-= ";
    case AssignType::LEFT_ASSIGN:
      return " :<<= ";
    case AssignType::RIGHT_ASSIGN:
      return " :>>= ";
    case AssignType::AND_ASSIGN:
      return " :&= ";
    case AssignType::XOR_ASSIGN:
      return " :^= ";
    case AssignType::OR_ASSIGN:
      return " :|= ";
  } // end switch
  return "";
}

