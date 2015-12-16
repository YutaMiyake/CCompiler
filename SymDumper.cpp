#include "SymDumper.h"
#include <algorithm>

void SymDumper::addSymToDump(SymbolNode* sym){
  std::vector<SymbolNode*>::iterator iter;
  iter = find (this->symDump.begin(), this->symDump.end(), sym);
    if (iter == this->symDump.end()){
      this->symDump.push_back(sym);
    }
}
void SymDumper::clearSymDump(){
  std::vector<SymbolNode*>::iterator iter;
  for(iter = this->symDump.begin(); iter != this->symDump.end(); ++iter){
    //std::cout << (*iter)->getName() << " is freed" << std::endl;
    delete *iter;
  }
}
