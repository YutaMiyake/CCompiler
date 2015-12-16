#ifndef __ASMGENERATOR__H__
#define __ASMGENERATOR__H__
#include "../Debugger.h"
#include "Registers.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
//#include <regex>
#include <map>

class ASMGenerator{
public:
  ASMGenerator();
  void build();
  void setTACFileName(std::string filename);
  void setASMFileName(std::string filename);

private:
  void readASM();
  void makeDataSegment();
  void AssignReg();
  void buildASM();
  std::string toASM(std::string aTacLine);
  std::string makeOp(std::string dest, std::string op1,
    std::string op, std::string op2);
  std::string makeSimpleAssign(std::string dest, std::string op1);
  void writeASM();
  void showLines(std::vector<std::string> lines);
  int typeToSize(std::string type);
  std::string vecToStr(std::vector<std::string> vec);
  std::vector<std::string> split(std::string line);
  bool is_number(const std::string& str);
  bool replace(std::string& str, const std::string& from, const std::string& to);

  bool isMain;
  int param;
  std::string func_name;
  Registers registers;
  Debugger asmWriter;
  std::string tacFileName;
  std::vector<std::string> tacLines;
  std::vector<std::string> tempLines;
  std::vector<std::string> asmLines;
};
#endif