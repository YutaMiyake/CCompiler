#ifndef __SYMDUMPER_H__
#define __SYMDUMPER_H__
#include "SymbolNode.h"
class SymDumper{
public:
  void addSymToDump(SymbolNode* sym);
  void clearSymDump();
private:
  std::vector<SymbolNode*> symDump;
};
#endif