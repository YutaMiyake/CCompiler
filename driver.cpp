#include "SymbolTable.h"
#include "SymDumper.h"
#include "Debugger.h"
#include "CodeDumper.h"
#include "graph.h"
#include "AST/ast_node.h"
#include "ASM/ASMGenerator.h"
#include <sstream>
#include <iostream>

extern "C"{
  int yyparse();
  int yylex();
}

extern FILE* yyin;

int ast_node::tempNum;
int ast_node::labelNum;
int ast_node::unique_id;

ASMGenerator asmGenerator;
SymbolTable symTable;
SymDumper symDumper;
Graph visualizer;
CodeDumper codeGenerator;
Debugger lexDebugger;
Debugger lexSymbolDebugger;
Debugger parseDebugger;
Debugger reductionDebugger;

int main(int argc, char** argv){

  // flags
  bool sdebug = false, ldebug = false, pdebug = false, genAST = false,
       gen3AC = false, genASM = false, compileAssemble = false;

  // filenames
  std::string lex_file, listFileName, logFile, symTableLogFile, ast_log_file;
  std::string ast_dot_file, ast_png_file, tac_file, asm_file;

  // arguments handling
  std::vector<std::string> args(argv, argv+argc);
  for (int arg = 1; arg < (int)args.size()-1; ++arg) {
       if (args[arg] == "-o"){
         logFile = args[arg+1];
       }
       else if (args[arg] == "-d"){
         if(args[arg+1].find("s") != std::string::npos){
          sdebug = true;
         }
         if(args[arg+1].find("l") != std::string::npos){
          ldebug = true;
         }
         if(args[arg+1].find("p") != std::string::npos){
          pdebug = true;
         }
       }
       else if (args[arg] == "-c"){
        printf("'-c' flag to compile and assemble not implemented\n");
       }
       else if (args[arg] == "-a"){
         genAST = true;
       }
       else if (args[arg] == "-q"){
         gen3AC = true;
       }
       else if (args[arg] == "-S"){
         gen3AC = true;
         genASM = true;
       }
   }

  // Get source code file
  std::stringstream sourceFileName(args[args.size()-1]);
  std::string cfilename;
  yyin = fopen(sourceFileName.str().c_str(), "r");

  // Make file names
  getline(sourceFileName, cfilename, '.');

  if(sdebug || ldebug || pdebug){
    logFile = cfilename + ".log";
    std::cout << logFile << std::endl;
    std::remove(logFile.c_str());
  }

  if(sdebug){
    symTableLogFile = cfilename + ".slog";
    std::cout << symTableLogFile << std::endl;
    std::remove(symTableLogFile.c_str());
  }
  if(ldebug){
    lex_file = cfilename + ".llog";
    std::cout << lex_file << std::endl;
    std::remove(lex_file.c_str());
  }
  if(pdebug){
    listFileName = cfilename + ".list";
    std::cout << listFileName << std::endl;
    std::remove(listFileName.c_str());
  }
  if(genAST){
    ast_log_file = cfilename + ".alog";
    ast_dot_file = cfilename + ".dot";
    ast_png_file = cfilename + ".png";
    std::cout << ast_log_file << std::endl;
    std::cout << ast_dot_file << std::endl;
    std::cout << ast_png_file << std::endl;
    std::remove(ast_log_file.c_str());
    std::remove(ast_dot_file.c_str());
    std::remove(ast_png_file.c_str());
  }
  if(gen3AC){
    tac_file = cfilename + ".tac";
    std::cout << tac_file << std::endl;
    std::remove(tac_file.c_str());
  }
  if(genASM){
    asm_file = cfilename + ".s";
    std::cout << asm_file << std::endl;
    std::remove(asm_file.c_str());
  }

  // set configurations
  lexDebugger.setFileName(lex_file);
  lexDebugger.setDebug(ldebug);
  lexSymbolDebugger.setFileName(logFile);
  lexSymbolDebugger.setDebug(ldebug);

  parseDebugger.setFileName(listFileName);
  parseDebugger.setDebug(pdebug);
  reductionDebugger.setFileName(logFile);
  reductionDebugger.setDebug(pdebug);

  symTable.setFileName(symTableLogFile);
  symTable.getDebugger()->setFileName(logFile);
  symTable.getDebugger()->setDebug(sdebug);

  visualizer.setVisualizer(genAST);
  visualizer.setGraphFileName(ast_dot_file);
  visualizer.setLogFileName(ast_log_file);
  visualizer.setDebug(genAST);
  visualizer.startBuild();

  codeGenerator.setFileName(tac_file);
  codeGenerator.setDebug(gen3AC);

  // global symbol table
  symTable.pushTable();

  // print_int
  TypeFunction * spec = new TypeFunction();
  TypeBasic *base = new TypeBasic();
  TypeBasic *voidtype = new TypeBasic();
  voidtype->setBaseType(SpecName::Void);
  base->setBaseType(SpecName::Int);
  spec->insertArg(base);
  spec->setReturnSpec(voidtype);
  SymbolNode *symNode = new SymbolNode("print_int", spec, -1, -1, true);
  symTable.insertSymbol("print_int", symNode);

  // syntax-directed translation
  // std::cout << "Start syntax-directed translation ..." << std::endl;
  yyparse();

  // create image
  visualizer.endBuild(ast_png_file);

  // assembly
  // std::cout << "Generating assembly ..." << std::endl;
  asmGenerator.setTACFileName(tac_file);
  asmGenerator.setASMFileName(asm_file);
  asmGenerator.build();

  // std::cout << "Success!" << std::endl;
  return 0;
}
