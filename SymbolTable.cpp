#include "SymbolTable.h"
SymbolTable::SymbolTable(): levels(-1){
  /*default constructor*/
  this->debugger = new Debugger();
}
SymbolTable::~SymbolTable(){
  /*destructor*/
  delete this->debugger;
  debugger = NULL;
}
int SymbolTable::getLevel() const{
  /*return levels*/
  return this->levels;
}
void SymbolTable::pushTable(std::map<std::string,SymbolNode*> newSymTable){
  /*push a given table on top and increment levels*/
  this->levels++;
  this->symTables.push_back(newSymTable);
  this->debugger->debug("[S]: A new symbol table is pushed on ===========================================");
}

void SymbolTable::pushTable(){
  /*push a new table on top and increment levels*/
  std::map<std::string,SymbolNode*> newSymTable;
  this->levels++;
  this->symTables.push_back(newSymTable);
  this->debugger->debug("[S]: A new symbol table is pushed on ===========================================");
}

void SymbolTable::popTable(){
  /*pop the top table and decrement levels*/
  this->levels--;
  this->symTables.pop_back();
  this->debugger->debug("[S]: The top symbol table is popped off ========================================");
}
bool SymbolTable::empty() const{
  /* return true if the symbol table is empty*/
  if( this->symTables.size() <= 0){
    this->debugger->debug("[S]: No Symbol Table");
    return true;
  }
  return false;
}
bool SymbolTable::insertSymbol(const std::string& key, SymbolNode* val){
  /* insert a given symbol and returns true if there is no conflict with
  one in the same table; otherwise return false
  */
  if(empty()){
    return false;
  }
  // declarations/initializations
  SymbolNode* content = lookupTopTable(key);
  std::stringstream ss;

  this->symTables[this->levels][key] = val;
  if(content == NULL){
    content = lookUpShadowedSymbol(key);
    if(content == NULL){
      ss << "[S]: Symbol \'"+key+"\' is inserted at level #" << this->levels;
      this->debugger->debug(ss.str());
    }
    else{
      ss << "[S]: Symbol \'"+key+"\' shadows another in parent level #" << this->levels;
      this->debugger->debug(ss.str());
    }
    return true;
  }
  else{
    return false;
  }
}

SymbolNode* SymbolTable::lookupTopTable(const std::string& key)
/* looks up the top level and returns the content if the key is found;
otherwise, it returns NULL.
*/
{
  if(empty()){
    return NULL;
  }

  // declarations/initializations
  SymbolNode * val = NULL;

  if(this->symTables[this->levels].find(key) != this->symTables[this->levels].end()){
      val = this->symTables[this->levels][key];
    }
  if(val != NULL){
    this->debugger->debug("[S]: Symbol "+key+" is found at top level");
  }
  else{
    this->debugger->debug("[S]: Symbol "+key+" is not found at top level");
  }
  return val;
}
SymbolNode* SymbolTable::lookUpShadowedSymbol(const std::string& key)
/* looks up the parent levels and returns the content of the shadowed symbol if
it finds; otherwise, it returns NULL.
*/
{
  if(empty()){
    return NULL;
  }

  // declarations/initializations
  SymbolNode* val = NULL;
  bool found = false;
  int level;

  //ignore the top level -> start with level-1
  for(level = this->levels-1; level >= 0; --level){
    if(symTables[level].find(key) != symTables[level].end()){
      val = symTables[level][key];
      found = true;
    }
  }
  if(found){
    this->debugger->debug("[S]: Symbol "+key+" is found at level "+ std::to_string(level+1));
  }
  else{
    this->debugger->debug("[S]: Symbol "+key+" is not found at any parent level");
  }

  return val;
}
SymbolNode* SymbolTable::lookupSymbol(const std::string& key)
/* looks up the all levels and returns the content
if the key is found; otherwise, it returns NULL.
*/
{
  SymbolNode* val = NULL;
  if((val = lookupTopTable(key)) == NULL){
    val = lookUpShadowedSymbol(key);
  }
  return val;
}
void SymbolTable::writeFile(){
  /*dump a current symbol table to a file*/
  if(empty()){
    return;
  }
  // declarations/initializations
  std::ofstream fout;
  std::map<std::string,SymbolNode*>::iterator iter;

  fout.open(filename.c_str(), std::ofstream::app);
  fout << "Symbol Tables\n"
       << "====================================================" << std::endl;

  // dump symbol tables
  for(int level = this->levels; level >= 0; --level){
      fout << "[Symbol table #" << level << "]"<< std::endl;
      for(iter = this->symTables[level].begin(); iter != this->symTables[level].end(); ++iter){
        fout << "Symbol: " << iter->first << ", ";
        fout << (*iter->second).getSpecName() << " ";
        fout << "@" << (*iter->second).getLine() << ":" << (*iter->second).getCol();
        fout << "\n";
      }
      fout << "--------------------------------------------------" << std::endl;
    }
    fout << "====================================================\n\n" << std::endl;

  fout.close();
}
Debugger* SymbolTable::getDebugger() const{
  /*return a debugger*/
  return this->debugger;
}
void SymbolTable::setFileName(const std::string filename){
  /*set an ouput file name*/
  this->filename = filename;
}