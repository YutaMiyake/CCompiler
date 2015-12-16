#ifndef __SYMBOL_NODE__H__
#define __SYMBOL_NODE__H__
#include "Spec.h"
class SymbolNode{
public:
  SymbolNode();
  SymbolNode(std::string, Spec* specifier, int = -1, int = -1, bool = false);
  ~SymbolNode();

  // setter
  void setName(std::string);
  //void setSpecName(std::string);
  void setLine(int);
  void setCol(int);
  void setSpecifier(Spec*);
  void setInitialized(bool initialized);
  void setDefined(bool defined);

  // getters
  std::string getName() const;
  std::string getSpecName() const;
  Spec* getSpecifier() const;
  int getLine() const;
  int getCol() const;
  bool isInitialized() const;
  bool isDefined() const;

protected:
  std::string name;
  //std::string specname;
  Spec* specifier;
  int line;
  int col;

  bool initialized;
  bool defined;
};
#endif
