#include "ast_node.h"
postfix_expression_node::postfix_expression_node(): ast_node(){}
postfix_expression_node::postfix_expression_node(primary_expression_node* primayExpr): ast_node(){
  init();
  this->primayExpr = primayExpr;
  this->mode = 0;
  this->identifierNode = getIdentifier();
}
postfix_expression_node::postfix_expression_node(postfix_expression_node* postExpr, expression_node* expr): ast_node(){
  init();
  this->postExpr = postExpr;
  this->expr = expr;
  this->mode = 1;
  this->identifierNode = getIdentifier();
}
postfix_expression_node::postfix_expression_node(postfix_expression_node* postExpr): ast_node(){
  init();
  this->postExpr = postExpr;
  this->mode = 2;
  this->identifierNode = getIdentifier();
}
postfix_expression_node::postfix_expression_node(postfix_expression_node* postExpr, argument_expression_list_node* argExpr): ast_node(){
  init();
  this->postExpr = postExpr;
  this->argExpr = argExpr;
  this->mode = 3;
  this->identifierNode = getIdentifier();
}
postfix_expression_node::postfix_expression_node(postfix_expression_node* postExpr, OpType::Type op, std::string identifier): ast_node(){
  init();
  this->postExpr = postExpr;
  this->op = op;
  this->identifier = identifier;
  this->mode = 4;
  this->identifierNode = getIdentifier();
}
postfix_expression_node::postfix_expression_node(postfix_expression_node* postExpr, OpType::Type op): ast_node(){
  init();
  this->postExpr = postExpr;
  this->op = op;
  this->mode = 5;
  this->identifierNode = getIdentifier();
}
postfix_expression_node::~postfix_expression_node(){
}
void postfix_expression_node::clear(){
  if(this->primayExpr!=NULL){
    this->primayExpr->clear();
    delete this->primayExpr;
  }
  if(this->postExpr!=NULL){
    this->postExpr->clear();
    delete this->postExpr;
  }
  if(this->expr!=NULL){
    this->expr->clear();
    delete this->expr;
  }
  if(this->argExpr!=NULL){
    this->argExpr->clear();
    delete this->argExpr;
  }
}
void postfix_expression_node::init(){
  this->identifierNode = NULL;
  this->primayExpr = NULL;
  this->postExpr = NULL;
  this->expr = NULL;
  this->argExpr = NULL;
  this->op = OpType::NONE;
  this->identifier ="";
}
void postfix_expression_node::print(){
  visualizer.debug("postfix_expression");
  switch(this->mode){
    case 0:
      if(primayExpr!=NULL){
        primayExpr->setPID(this->pid);
        primayExpr->print();
      }
    break;
    case 1:
      printArray();
    break;
    case 2:
    case 3:
      printFunction();
    break;
    case 4:
      if(this->op == OpType::PERIOD){
        printStructUnion();
      }
      else{
        if(postExpr!=NULL){
          postExpr->setPID(this->pid);
          postExpr->print();
        }
      }
    break;
    case 5:
      this->op_node_id = ast_node::getUID();
      if(this->op == OpType::INC){
        visualizer.addNode(this->op_node_id,"++");
      }
      else{
        visualizer.addNode(this->op_node_id,"--");
      }
      visualizer.addEdge(this->pid,this->op_node_id);

      if(postExpr!=NULL){
        postExpr->setPID(this->op_node_id);
        postExpr->print();
      }
    break;
    default:
      error("[A] ERROR: unknown postfix expression type while print");
    break;
  }
}
Spec* postfix_expression_node::getSpec(){
  switch(this->mode){
    case 0:
      return this->primayExpr->getSpec();
    case 1:
      return getArraySpec();
    case 2:
    case 3:
       return getFunctionSpec();
    case 4:
      if(this->op == OpType::PERIOD){
        return getStructUnionSpec();
      }
    case 5:
      if(this->postExpr!=NULL){
        return this->postExpr->getSpec();
      }
      return NULL;

    default:
      return NULL;
  }
}
identifier_node* postfix_expression_node::getIdentifier() const{
  primary_expression_node* primayExpr = getPrimaryExpr();
  if(primayExpr->isIdentifier()){
      return primayExpr->getIdentifier();
    }
  return NULL;
}
primary_expression_node* postfix_expression_node::getPrimaryExpr() const{
  if(this->primayExpr==NULL){
    return this->postExpr->getPrimaryExpr();
  }
  return this->primayExpr;
}
void postfix_expression_node::printArray(){
  visualizer.addNode(this->id,"array");
  visualizer.addEdge(this->pid,this->id);
  if(postExpr!=NULL){
    postExpr->setPID(this->id);
    postExpr->print();
  }
  if(expr!=NULL){
    expr->setPID(this->id);
    expr->print();
  }
}
Spec* postfix_expression_node::getArraySpec(){
  std::stringstream ss;
  SymbolNode* sym = this->identifierNode->getSymNode();
  Spec* spec = sym->getSpecifier();
  std::string type = spec->toTypeString();

  // is array?
  if(!spec->isTypeKind(SpecName::Array)){
    ss << "[A] ERROR: called object type "
       << type
       << " is not an array or array pointer"
       << ", @" << this->identifierNode->getLine() << ":" << this->identifierNode->getCol();
    error(ss.str());
  }

  // check if the size is int
  if(this->expr!=NULL){
    if(this->expr->getSpec()->getBaseType() != SpecName::Int){
      ss << "[A] ERROR: array size must be integer";
      ss << ", @" << this->identifierNode->getLine() << ":" << this->identifierNode->getCol();
      error(ss.str());
    }
  }
  if(this->postExpr!=NULL){
    return this->postExpr->getSpec();
  }
  return NULL;
}
void postfix_expression_node::printFunction(){
  visualizer.addNode(this->id,"function");
  visualizer.addEdge(this->pid,this->id);
  if(postExpr!=NULL){
    postExpr->setPID(this->id);
    postExpr->print();
  }
  if(argExpr!=NULL){
    argExpr->setPID(this->id);
    argExpr->print();
  }
}
Spec* postfix_expression_node::getFunctionSpec(){
  std::stringstream ss;

  // redundant way now -- should be modified later!!
  if(this->argExpr == NULL){
    SymbolNode* sym = this->identifierNode->getSymNode();
    Spec* spec = sym->getSpecifier();
    int argSize;

    // is function?
    if(!spec->isTypeKind(SpecName::Function)){
      ss << "[A] ERROR: called object type "
         << this->spec->toTypeString()
         << " is not a function or function pointer"
         << ", @" << this->identifierNode->getLine() << ":" << this->identifierNode->getCol();
      error(ss.str());
    }
    argSize = dynamic_cast<TypeFunction*>(spec)->getArgSize();

    // few argument?
    if(0 < argSize){
      ss << "[A] ERROR: too few arguments to function call, expected ";
      if(argSize == 1){
        ss << "single argument";
      }else{
        ss << argSize << " arguments";
      }
      ss << ", have no arguments";
      ss << ", @" << this->identifierNode->getLine() << ":" << this->identifierNode->getCol();
      error(ss.str());
    }
  }

  else{
    std::vector<assignment_expression_node*> args = this->argExpr->getChildren();
    SymbolNode* sym = this->identifierNode->getSymNode();
    Spec* spec = sym->getSpecifier();
    int argSize;

    // is function?
    if(!spec->isTypeKind(SpecName::Function)){
      ss << "[A] ERROR: called object type " << this->spec->toTypeString() << " is not a function or function pointer";
      ss << ", @" << this->identifierNode->getLine() << ":" << this->identifierNode->getCol();
      error(ss.str());
    }
    argSize = dynamic_cast<TypeFunction*>(spec)->getArgSize();

    // check arg size
    if(args.size() > argSize){
      if(argSize == 0){
        ss << "[A] WARNING: too many arguments in call to "+this->identifierNode->getName();
        ss << ", @" << this->identifierNode->getLine() << ":" << this->identifierNode->getCol();
        warning(ss.str());
      }
      else{
        ss << "[A] ERROR: too many arguments to function call, expected ";
        if(argSize == 1){
          ss << "single argument";
        }else{
          ss << argSize << " arguments";
        }
        ss << ", have " << args.size() << " arguments";
        ss << ", @" << this->identifierNode->getLine() << ":" << this->identifierNode->getCol();
        error(ss.str());
      }
    }else if(args.size() < argSize){
      ss << "[A] ERROR: too few arguments to function call, expected ";
      if(argSize == 1){
        ss << "single argument";
      }else{
        ss << argSize << " arguments";
      }
      ss << ", have " << args.size() << " arguments";
      ss << ", @" << this->identifierNode->getLine() << ":" << this->identifierNode->getCol();
      error(ss.str());
    }
    // check param type
    /*
    for(int arg = 0; arg < args.size(); arg++){
      if(args[arg]->getSpec()->getBaseType()!= dynamic_cast<TypeFunction*>(spec)->getArgSpec(arg)->getBaseType()){
      }
    }
    */
  }

  if(this->postExpr!=NULL){
    return this->postExpr->getSpec();
  }
  return NULL;
}
void postfix_expression_node::printStructUnion(){
  visualizer.addNode(this->id,".");
  visualizer.addEdge(this->pid,this->id);
  if(postExpr!=NULL){
    postExpr->setPID(this->id);
    postExpr->print();
  }
  int structUnion_id = ast_node::getUID();
  visualizer.addNode(structUnion_id,this->identifier);
  visualizer.addEdge(this->id,structUnion_id);
}
Spec* postfix_expression_node::getStructUnionSpec(){
  /*std::stringstream ss;
  SymbolNode* sym = this->identifierNode->getSymNode();
  Spec* spec = sym->getSpecifier();
  std::string name = this->identifierNode->getName();

  // check identifier
  //ss << "no member named \'" << this->identifier << "\'in \'struct" << name <<"\'";
  */

  return NULL;
}
std::string postfix_expression_node::generateCode(){
  switch(this->mode){
    case 0:
      return primayExpr->generateCode();
    case 1:
      return generateArrayCode();
    case 2:
    case 3:
      return generateFunctionCode();
    case 4:
      return postExpr->generateCode();
    case 5:
      return generatePostfixedCode();
  }
  return "";
}
std::string postfix_expression_node::generateArrayCode(){
  std::string name = this->identifierNode->getName();
  SymbolNode* sym = this->identifierNode->getSymNode();
  TypeArray* array = (TypeArray*) sym->getSpecifier();
  std::vector<int> sizes = array->getSizes();
  std::vector<std::string> blocks;
  int dims = sizes.size();
  int tmp;
  std::stringstream ss;
  std::string temp, temp2, temp3, num;
  std::vector<expression_node*> exprs;

  blocks.push_back("1");
  for(int dim = 1; dim < dims; dim++){
    tmp = 1;
    for(int idx = 0; idx < dim; idx++){
      tmp *= sizes[idx];
    }
    ss << tmp;
    blocks.push_back(ss.str());
    ss.str("");
  }

  getExprs(exprs);
  temp2 = "0";

  for(int dim = 0; dim < dims; dim++){
    num = exprs[dims-1-dim]->generateCode();
    temp = ast_node::getNewTempStr();
    temp3 = ast_node::getNewTempStr();
    codeGenerator.debug(temp + " := " + num +" * " +blocks[dim]+ "\n");
    codeGenerator.debug(temp3 + " := " + temp +" + " +temp2+ "\n");
    temp2 = temp3;
  }

  temp = ast_node::getNewTempStr();
  temp3 = ast_node::getNewTempStr();
  codeGenerator.debug(temp + " := " + "4" + "\n"); // for now - only int
  codeGenerator.debug(temp3 + " := " + temp +" * " +temp2+ "\n");
  temp = ast_node::getNewTempStr();
  codeGenerator.debug(temp + " := " + temp3 +" + &" +name+ "\n");

  //result = ast_node::getNewTempStr();
  //codeGenerator.debug(result + " := " +"("+temp+")"+ "\n");

  return "("+temp+")";
}
void postfix_expression_node::getExprs(std::vector<expression_node*>& exprs){
  if(this->primayExpr==NULL){
    exprs.push_back(this->expr);
    this->postExpr->getExprs(exprs);
  }
}
std::string postfix_expression_node::generateFunctionCode(){
  std::string name = this->identifierNode->getName();
  SymbolNode* sym = this->identifierNode->getSymNode();
  TypeFunction* function = (TypeFunction*) sym->getSpecifier();
  Spec* returnSpec = function->getReturnSpec();
  std::string result;
  std::stringstream ss;
  int argSpace = 0;

  if(this->argExpr != NULL){
    std::vector<std::string> args;
    std::string temps = argExpr->generateCode();
    std::string arg;
    std::stringstream ssin(temps);
    while (ssin.good()){
      ssin >> arg;
      args.push_back(arg);
    }

    for(int arg = 0; arg < args.size(); arg++){
      std::string argtemp = ast_node::getNewTempStr();
      codeGenerator.debug(argtemp + " := " + args[arg] + "\n");
      argSpace += 4; // only integer
      codeGenerator.debug("PushParam " + argtemp + "\n");
    }
  }
  if(returnSpec->toTypeString() != "void"){
    ss.str("");
    result = ast_node::getNewTempStr();
    ss << result + " := ";
  }

  ss << "FuncCall " << name << " " << argSpace << "\n";
  codeGenerator.debug(ss.str());

  return result;
}
std::string postfix_expression_node::generatePostfixedCode(){
  std::string result, temp;
  std::stringstream ss;
  temp = this->postExpr->generateCode();
  result = ast_node::getNewTempStr();
  ss << result << " := " << temp << "\n";
  codeGenerator.debug(ss.str());
  ss.str("");

  ss << temp << " := ";

  if(this->op == OpType::INC){
    ss << temp << " + 1";
  }
  else{
    ss << temp << " - 1";
  }
  ss << "\n";
  codeGenerator.debug(ss.str());

  return result;
}