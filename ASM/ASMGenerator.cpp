#include "ASMGenerator.h"

ASMGenerator::ASMGenerator(){
  this->isMain = false;
  this->param = 0;
  this->func_name = "";
}
void ASMGenerator::build(){
  readASM();
  makeDataSegment();
  AssignReg();
  //showLines(this->tacLines);
  //showLines(this->tempLines);
  buildASM();
  writeASM();
}
void ASMGenerator::makeDataSegment(){
  // make data segment:
  // 1. labeling .data
  // 2. declaring or initializing global variables at memory
  // 3. labeling .text

  int line;
  int space;
  std::stringstream ss;

  this->asmWriter.debug(".data\n");
  for(line = 0; line < this->tacLines.size(); line++){

    // split
    std::vector<std::string> linevec = split(this->tacLines[line]);

    if((linevec[1] == "Init:" || linevec[1] == "Decl:")){
      this->asmWriter.debug("#" + this->tacLines[line]);
      // array
      if(linevec[3] == "array"){
        if(linevec[1] == "Decl:"){
          space = stoi(linevec[4]) * typeToSize(linevec[5]);
          ss << linevec[2] << ": .space " << space;
        }
        else{
          ss << linevec[2] << ": .word " << linevec[6];
        }
      }
      // basic variable
      else{
        if(linevec[1] == "Decl:"){
          space = typeToSize(linevec[3]);
          ss << linevec[2] << ": .space " << space;
        }
        else{
          ss << linevec[2] << ": .word " << linevec[4];
        }
      }
      this->asmWriter.debug(ss.str()+"\n");
      ss.str("");
    } // end init/decl case
  } // end for loop
  this->asmWriter.debug("newline: .asciiz \"\\n\"\n");
  this->asmWriter.debug(".text\n");
}
void ASMGenerator::buildASM(){
  for(int line = 0; line < this->tempLines.size(); line++){
    //std::cout << this->tacLines[line] << std::endl;
    this->asmLines.push_back("#" + this->tacLines[line] + "\n"
                             + toASM(this->tempLines[line]) + "\n");
  }
}
std::string ASMGenerator::toASM(std::string aTacLine){
  std::stringstream ss;
  std::vector<std::string> linevec = split(aTacLine);

  //if(std::regex_match(linevec[1],std::regex("(_LABEL)([0-9]+):"))){
  if(linevec[1].substr(0,6) == "_LABEL"){
    ss << linevec[1];
  }
  else if(aTacLine.find("FuncCall") != std::string::npos){
    if(linevec[2] == "print_int"){
      // called with integer pushed on the stack
      /*
      ss << "li $v0, 1\n"
         << "lw $a0, 0($sp)\n"
         << "addiu $sp, $sp, 4\n"
         << "syscall\n";
      */
     // assume int is loaded into $a0
     ss << "li $v0, 1\n"
        << "syscall\n";

      ss << "li $v0, 4\n"
         << "la $a0, newline\n"
         << "syscall";
    }
    else{

      if(linevec[1] != "FuncCall"){
      ss << "jal " << linevec[4] << "\n"
         << "move " << linevec[1]  << ", $v0";
      }else{
        ss << "jal " << linevec[2];
      }

      // pop out parameters
      if(!this->isMain){
       for(int arg = param - 1; arg >= 0; arg--){
          ss << "\nlw $a" << arg << ", " << 0 << "($sp)\n"
             << "addiu $sp, $sp, 4";
        }
      }
    }
    // reset param
    param = 0;
  }
  else if(linevec[1] == "PushParam"){
    ss << "move $a" << param << ", " << linevec[2];
    param++;
  }
  else if(linevec[1] == "PopParam"){
    // pass
  }
  else if(linevec[1] == "goto"){
    ss << "j " << linevec[2];
  }
  else if(linevec[1] == "Function:"){
    this->func_name = linevec[2];
    if(this->func_name == "main"){
      this->isMain = true;
    }
    ss << this->func_name << ":";
  }
  else if(linevec[1] == "Decl:" || linevec[1] == "Init:"){
    // pass
  }
  else if(linevec[1] == "BeginFunc"){
    if(!this->isMain){
      ss << "sw $fp, -4($sp)\n"
         << "sw $ra, -8($sp)\n"
         << "la $fp, 0($sp)\n"
         << "la $sp, -8($sp)";

      // push parameters
      for(int arg = 0; arg < stoi(linevec[2])/4; arg++){
        ss << "\nsw $a" << arg << ", -" << 4 << "($sp)\n"
           << "la $sp, -4($sp)";
      }
    }
  }
  else if(linevec[1] == "EndFunc"){
    if(this->isMain){
      ss << "_end_" + this->func_name + ":\n"
         << "li $v0, 10     # set up for exit\n"
         << "syscall        # exit";
      this->isMain = false;
    }
    else{
      ss << "_end_" + this->func_name + ":\n"
         << "la $sp, 0($fp)\n"
         << "lw $ra, -8($sp)\n"
         << "lw $fp, -4($sp)\n";
      ss << "jr $ra   # return";
    }
  }
  else if(linevec[1] == "return"){
    if(linevec.size() >= 3){
      // return x
      ss << "move $v0, " << linevec[2] << "\n";
    }
    ss << "j _end_" + this->func_name;
  }
  else if(linevec[1] == "if"){
    std::string exp_1, op, exp_2, label, reg1, reg2;
    bool single_exp = false;

    if(linevec[3] == "<="){
       op = "ble ";
    }else if(linevec[3] == ">="){
       op = "bge ";
    }else if(linevec[3] == ">"){
       op = "bgt ";
    }else if(linevec[3] == "<"){
       op = "blt ";
    }else if(linevec[3] == "=="){
       op = "beq ";
    }else if(linevec[3] == "!="){
       op = "bne ";
    }else{
      // assume it is a single condition
       op = "beq ";
       single_exp = true;
    }

    if(single_exp){
      exp_1 = linevec[2]; exp_2 = "1"; label = linevec[4];
    }
    else{
      exp_1 = linevec[2]; exp_2 = linevec[4]; label = linevec[6];
    }

    if(is_number(exp_1)){
      reg1 = this->registers.getSavedTempReg();
      ss << "li " << reg1 << ", " << exp_1 << "\n";
      exp_1 = reg1;
    }
    else if(exp_1[0] != '$'){
      reg1 = this->registers.getSavedTempReg();
      ss << "la " << reg1 << ", " << exp_1 << "\n";
      ss << "lw " << reg1 << ", " <<  "(" << reg1 << ")" << "\n";
      exp_1 = reg1;
    }
    if(is_number(exp_2)){
      reg2 = this->registers.getSavedTempReg();
      ss << "li " << reg2 << ", " << exp_2 << "\n";
      exp_2 = reg2;
    }
    else if(exp_2[0] != '$'){
      reg2 = this->registers.getSavedTempReg();
      ss << "la " << reg2 << ", " <<  exp_2 << "\n";
      ss << "lw " << reg2 << ", " <<  "(" << reg2 << ")" << "\n";
      exp_2 = reg2;
    }

    ss << op << exp_1 << ", " << exp_2 << ", " << label;
    registers.freeRegister(reg1);
    registers.freeRegister(reg2);

  } // end if statement
  else if(linevec[2] == ":="){
    std::string dest, op1, op, op2;

    // simple assignment XXXX A := B unnecessary ...
    if(linevec.size() < 5){

      dest = linevec[1];
      op1 = linevec[3];
      ss << makeSimpleAssign(dest,op1);
    }
    else{
      dest = linevec[1];
      op1 = linevec[3];
      op = linevec[4];
      op2 = linevec[5];

      ss << makeOp(dest,op1,op,op2);
    }
  } // end assignment

  return ss.str();
}
std::string ASMGenerator::makeSimpleAssign(std::string dest, std::string op1){
  std::string reg1, reg2;
  std::stringstream ss;

  // integer (immediate)
  if(is_number(op1)){
    reg1 = this->registers.getSavedTempReg();
    ss << "li " << reg1 << ", " << op1 << "\n";
    op1 = reg1;
  }
  // dereference
  else if(op1[0] == '('){
    reg1 = this->registers.getSavedTempReg();
    ss << "lw " << reg1 << ", " <<  op1 << "\n";
    op1 = reg1;
  }
  // variable
  else if(op1[0] != '$'){
    reg1 = this->registers.getSavedTempReg();
    ss << "la " << reg1 << ", " <<  op1 << "\n";
    ss << "lw " << reg1 << ", " <<  "(" << reg1 << ")" << "\n";
    op1 = reg1;
  }

  if(dest[0] == '('){
    // ($temp)
    reg2 = this->registers.getSavedTempReg();
    ss << "move " << reg2 << ", " << op1;
    ss << "\n" << "sw " << reg2 << ", " << dest;
  }
  else if(dest[0] != '$'){
    // variable
    reg2 = this->registers.getSavedTempReg();
    ss << "move " << reg2 << ", " << op1;
    ss << "\n" << "sw " << reg2 << ", " << dest;
  }
  else{
    // register
    ss << "move " << dest << ", " << op1;
  }

  // free registers
  this->registers.freeRegister(reg1);
  this->registers.freeRegister(reg2);

  return ss.str();
}
std::string ASMGenerator::makeOp(std::string dest, std::string op1,
  std::string op, std::string op2){

  std::stringstream ss;
  std::string reg1, reg2, reg3;

  if(op == "*"){op = "mul";}
  else if(op == "/"){op = "div";}
  else if(op == "+"){op = "add";}
  else if(op == "-"){op = "sub";}

  // integer (immediate)
  if(is_number(op1)){
    // std::cout << op1 << std::endl;
    reg1 = this->registers.getSavedTempReg();
    ss << "li " << reg1 << ", " << op1 << "\n";
    op1 = reg1;
  }
  // dereference
  else if(op1[0] == '('){
    reg1 = this->registers.getSavedTempReg();
    ss << "lw " << reg1 << ", " <<  op1 << "\n";
    op1 = reg1;
  }
  // address
  else if(op1[0] == '&'){
    reg1 = this->registers.getSavedTempReg();
    op1.erase(0,1);
    ss << "la " << reg1 << ", " <<  op1 << "\n";
    op1 = reg1;
  }
  // variable
  else if(op1[0] != '$'){
    reg1 = this->registers.getSavedTempReg();
    ss << "la " << reg1 << ", " <<  op1 << "\n";
    ss << "lw " << reg1 << ", " <<  "(" << reg1 << ")" << "\n";
    op1 = reg1;
  }

  // integer (immediate)
  if(is_number(op2)){
    reg2 = this->registers.getSavedTempReg();
    ss << "li " << reg2 << ", " << op2 << "\n";
    op2 = reg2;
  }
  // dereference
  else if(op2[0] == '('){
    reg2 = this->registers.getSavedTempReg();
    ss << "lw " << reg2 << ", " <<  op2 << "\n";
    op2 = reg2;
  }
  // address
  else if(op2[0] == '&'){
    reg2 = this->registers.getSavedTempReg();
    op2.erase(0,1);
    ss << "la " << reg2 << ", " <<  op2 << "\n";
    op2 = reg2;
  }
  // variable
  else if(op2[0] != '$'){
    reg2 = this->registers.getSavedTempReg();
    ss << "la " << reg2 << ", " <<  op2 << "\n";
    ss << "lw " << reg2 << ", " <<  "(" << reg2 << ")" << "\n";
    op2 = reg2;
  }

  if(dest[0] == '('){
    // ($temp)
    reg3 = this->registers.getSavedTempReg();
    ss << op << " " << reg3 << ", " << op1 << ", " << op2;
    ss << "\n" << "sw " << reg3 << ", " << dest;
  }
  else if(dest[0] != '$'){
    // variable
    reg3 = this->registers.getSavedTempReg();
    ss << op << " " << reg3 << ", " << op1 << ", " << op2;
    ss << "\n" << "sw " << reg3 << ", " << dest;
  }
  else{
    // register
    ss << op << " " << dest << ", " << op1 << ", " << op2;
  }

  // free registers
  this->registers.freeRegister(reg1);
  this->registers.freeRegister(reg2);
  this->registers.freeRegister(reg3);

  return ss.str();
}
void ASMGenerator::readASM(){
  std::ifstream fin;
  std::string line;
  fin.open(this->tacFileName);
  while(fin.good()){
    getline(fin,line);
    if(line != ""){
      this->tacLines.push_back(line);
    }
  }
  fin.close();
}
void ASMGenerator::writeASM(){
  int asmIdx;
  for(asmIdx = 0; asmIdx < this->asmLines.size(); asmIdx++){
    this->asmWriter.debug(this->asmLines[asmIdx]);
  }
}
void ASMGenerator::setTACFileName(std::string filename){
  this->tacFileName = filename;
}
void ASMGenerator::setASMFileName(std::string filename){
  this->asmWriter.setFileName(filename);
  this->asmWriter.setDebug(true);
}
void ASMGenerator::showLines(std::vector<std::string> lines){
  int line;
  for (line = 0; line < lines.size(); line++){
    std::cout << lines[line] << std::endl;
  }
}
int ASMGenerator::typeToSize(std::string type){
  if(type == "int"){
    return 4;
  }
  return 0;
}
std::string ASMGenerator::vecToStr(std::vector<std::string> vec ){
  int tok;
  std::string result;
  for(tok = 0; tok < vec.size(); tok++){
    result += vec[tok];
  }
  return result;
}

std::vector<std::string> ASMGenerator::split(std::string line){
  std::string tok;
  std::stringstream ss(line);
  std::vector<std::string> linevec;
  while(getline(ss, tok,' ')) {
      linevec.push_back(tok);
  }
  return linevec;
}
bool ASMGenerator::is_number(const std::string& str)
{
    std::string::const_iterator it = str.begin();
    while (it != str.end() && std::isdigit(*it)) ++it;
    return !str.empty() && it == str.end();
}
bool ASMGenerator::replace(std::string& str, const std::string& from, const std::string& to) {
    size_t pos = str.find(from);
    if(pos == std::string::npos)
        return false;
    str.replace(pos, from.length(), to);
    return true;
}

void ASMGenerator::AssignReg(){
  std::string reg, repStr, tempStr;
  std::vector<std::string> dump_regs;
  std::map<std::string,std::string> used_regs;
  std::map<std::string,std::string>::iterator iter;
  std::map<std::string,std::string> arg_regs;
  bool inLocal = false;
  int paramNum = 0;

  for(int line = 0; line < this->tacLines.size(); line++){
    std::string temp = this->tacLines[line];
    std::vector<std::string> linevec = split(temp);
    // std::cout << temp << std::endl;

    // replace argument with register
    if(linevec[1] == "PopParam"){
      std::string reg = "$a" + std::to_string(paramNum);
      paramNum++;
      arg_regs[linevec[2]] = reg;
      inLocal = true;
    }
    else if(linevec[1] == "EndFunc" && inLocal){
      paramNum = 0;
      inLocal = false;
    }

    for(int tok = 0; tok < linevec.size(); tok++){
      // temporaries
      if(linevec[tok].substr(0,6) == "(_TEMP" || linevec[tok].substr(0,5) == "_TEMP"){
        //if(std::regex_match(linevec[tok],std::regex("(\\(?)(_TEMP)([0-9]+)(\\)?)")))
        tempStr = linevec[tok];
        if(tempStr[0] == '('){
          tempStr.erase(tempStr.begin(), tempStr.begin()+1);
          tempStr.erase(tempStr.end()-1, tempStr.end());
        }
        iter = used_regs.find(tempStr);
        if (iter != used_regs.end()){
          repStr =  used_regs[tempStr];
          dump_regs.push_back(used_regs[tempStr]);
        }
        else{
          reg = this->registers.getRegister(); // hopefully get next register
          used_regs[tempStr] = reg;
          repStr = reg;
        }

        if(linevec[tok][0] == '('){
          repStr = "(" + repStr + ")";
        }
        replace(temp, linevec[tok], repStr);
      }
      else{
        if(inLocal){
          // if match with any argument, replace it with its register
          for(iter = arg_regs.begin(); iter != arg_regs.end(); ++iter){
            std::string key = iter->first;
            if(key == linevec[tok]){
              replace(temp, linevec[tok], arg_regs[key]);
            }
          }
        } // end argument replacement
      }
    } // end line

    // free registers
    for(int reg = 0; reg < dump_regs.size(); reg++){
      this->registers.freeRegister(dump_regs[reg]);
    }
    dump_regs.clear();

    // add new line
    this->tempLines.push_back(temp);
  } // end whole lines
}