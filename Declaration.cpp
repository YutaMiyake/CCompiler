#include "Declaration.h"
Declaration::Declaration():mode(DeclMode::NoMode), level(0), argSize(0), hasType(false), hasInt(false), arraySizeAstNode(NULL){
}
Declaration::~Declaration(){}

// change states of declaration ***********************************************
void Declaration::pushID(std::string id){
  //std::cout << id << std::endl;
  this->ids.push_back(id);
}
void Declaration::pushLine(int line){
  this->lines.push_back(line);
}
void Declaration::pushCol(int col){
  this->cols.push_back(col);
}
void Declaration::pushKind(SpecName::TypeKind typekind){
  //std::cout << "Kind: " << typekind;
  if(typekind == SpecName::NoKind){
    this->kindsHolder.push_back(this->kinds);
    this->kinds.clear();
    //std::cout << " Size: " << this->kindsHolder.size();
  }
  else{
    if(this->kinds.empty()){
      this->kinds.push_back(typekind);
      //std::cout << " OK";
    }
    else if(typekind != this->kinds.back()){
      this->kinds.push_back(typekind);
      //std::cout << " OK";
    }
  }
  //std::cout << " " << std::endl;
}
void Declaration::pushBase(SpecName::BaseType basetype){
  //std::cout << "Base: " << basetype << std::endl;
  if(basetype == SpecName::NoType){
    this->basesHolder.push_back(this->bases);
    this->bases.clear();
  }
  else{
    this->bases.push_back(basetype);
  }
}
void Declaration::pushQualifier(SpecName::Qualifier qualifier){
  //std::cout << "Qualifier: " << qualifier << std::endl;
  if(qualifier == SpecName::NoQualifier){
    this->qualifiersHolder.push_back(this->qualifiers);
    this->qualifiers.clear();
  }
  else{
    this->qualifiers.push_back(qualifier);
  }
}
void Declaration::pushStorage(SpecName::Storage storage){
  //std::cout << storage << std::endl;
  if(storage == SpecName::NoStorage){
    this->storagesHolder.push_back(this->storages);
    this->storages.clear();
  }
  else{
    this->storages.push_back(storage);
  }
}
void Declaration::pushSign(SpecName::Sign sign){
  //std::cout << sign << std::endl;
  if(sign == SpecName::NoSign){
    this->signsHolder.push_back(this->signs);
    this->signs.clear();
    //std::cout << "-----"<< std::endl;
  }
  else{
    this->signs.push_back(sign);
  }
}
void Declaration::setNextPtr(){
  //std::cout << this->level;
  this->levels.push_back(this->level);
  this->level = 0;
}
void Declaration::incPtrLevel(){
  this->level++;
}
void Declaration::setNextArray(){
  //std::cout << this->arraySizes.size();
  this->dims.push_back(this->arraySizes);
  this->arraySizes.clear();
}
void Declaration::pushArraySize(int size){
  // std::cout << "SIZE" << size << std::endl;
  this->arraySizes.push_back(size);
}
void Declaration::pushArraySizeAstNode(constant_expression_node* arraySizeAstNode){
  // Eventually we want this so we can have multi-dimensional arrays
  //this->arraySizeAstNodes.push_back(arraySizeAstNode);

  this->arraySizeAstNode = arraySizeAstNode;
}

void Declaration::incArgSize(){
  this->argSize++;
}
void Declaration::setMode(DeclMode::Mode mode){
 this->mode = mode;
}
void Declaration::setHasType(){
  this->hasType = true;
}
// getters  ******************************************************
std::string Declaration::getID(int idx) const{
   return this->ids[idx];
 }
 bool Declaration::isMode(DeclMode::Mode mode) const{
  return this->mode == mode;
 }
int Declaration::getArgSize() const{
  return this->argSize;
 }
 std::vector<SymbolNode*> Declaration::getArgSymbolNodes() const{
  return this->argSymbolNodes;
 }
 int Declaration::getBasesNum() const{
   return this->bases.size();
 }
// base type *****************************************************************
 bool Declaration::setBaseType(TypeBasic *base, SpecName::BaseType basetype){
  SpecName::BaseType currentBaseType = base->getBaseType();
  //std::cout << "?: "<< currentBaseType << "->" << basetype << std::endl;

  // sign check (no double and float)
  if(base->isSign(SpecName::Signed) || base->isSign(SpecName::Unsigned)){
    if(!checkSigned(basetype)){
      return false;
    }
  }
  // no type
  if(currentBaseType == SpecName::NoType){
    // otherwise
    base->setBaseType(basetype);
    if(basetype == SpecName::Int){
      this->hasInt = true;
    }
    return true;
  }
  // int check
  if(basetype == SpecName::Int){
    if(this->hasInt){
      error("[P]: ERROR: cannot combine with previous 'int' declaration specifier");
    }
    else{
      this->hasInt = true;
    }
    if(currentBaseType == SpecName::Short ||
       currentBaseType == SpecName::Long  ||
       currentBaseType == SpecName::LLong){
        // no change
        return true;
    }
    error("[P]: ERROR: \'"+base->getBaseTypeStr()+" "+base->basetToStr(basetype)+"\' is invalid");
    return false;
  }
  // short check
  else if(basetype == SpecName::Short){
    if(currentBaseType == SpecName::Int){
      base->setBaseType(basetype);
      return true;
    }
    error("[P]: ERROR: \'"+base->getBaseTypeStr()+" "+base->basetToStr(basetype)+"\' is invalid");
    return false;
  }
  // long check
  else if(basetype == SpecName::Long){
    if(currentBaseType == SpecName::Long){
      base->setBaseType(SpecName::LLong);
      return true;
    }
    else if(currentBaseType == SpecName::Int){
      base->setBaseType(SpecName::Long);
      return true;
    }
    else if(currentBaseType == SpecName::Double){
      base->setBaseType(SpecName::LDouble);
      return true;
    }
    error("[P]: ERROR: \'"+base->getBaseTypeStr()+" "+base->basetToStr(basetype)+"\' is invalid");
    return false;
  }
  // check double
  else if(basetype == SpecName::Double){
    if(currentBaseType == SpecName::Long){
      base->setBaseType(SpecName::LDouble);
      return true;
    }
  }
  // other invalid combination
  error("[P]: ERROR: \'"+base->getBaseTypeStr()+" "+base->basetToStr(basetype)+"\' is invalid");
  return false;
 }
bool Declaration::buildBase(Spec* spec, std::vector<SpecName::BaseType> bases){
  if(!bases.empty()){
    for(int base = 0; base < bases.size(); base++){
      if(!setBaseType((TypeBasic*) spec, bases[base])){
        return false;
      }
    }
  }
  return true;
}

 // sign ********************************************************************
 bool Declaration::setSign(Spec* spec, SpecName::Sign sign){
  if(spec->getSign() != SpecName::NoSign){
    error("[P]: ERROR: Sign already exists");
    return false;
  }
  spec->setSign(sign);
  return true;
 }
bool Declaration::checkSigned(SpecName::BaseType type) const{
  if(type == SpecName::Double || type == SpecName::LDouble){
    error("[P]: ERROR: \'double\' cannot be signed or unsigned");
    return false;
  }
  else if(type == SpecName::Float){
    error("[P]: ERROR: \'float\' cannot be signed or unsigned");
    return false;
  }
  return true;
}
bool Declaration::buildSign(Spec* spec, std::vector<SpecName::Sign> signs){
  // set sign
  if(!signs.empty()){
    for(int sign = 0; sign < signs.size(); sign++){
      if(!setSign(spec, signs[sign])){
        return false;
      }
    } // end sign
  }
  return true;
}
 // storage ******************************************************************
 bool Declaration::setStorage(Spec* spec, SpecName::Storage storage){
  // double storage
  if(spec->getStorage() != SpecName::NoStorage){
    error("[P]: ERROR: Storage already exists");
    return false;
  }
  // function declarator
  else if(isMode(DeclMode::FunctionArg)){
    if(storage != SpecName::Register){
      error("[P]: ERROR: invalid storage class specifier in function declarator");
      return false;
    }
  }
  // file scope
  else if(symTable.getLevel() == 1){
    if(storage == SpecName::Auto || storage == SpecName::Register){
      error("[P]: ERROR: illegal storage class on file-scoped variable");
      return false;
    }
  }
  spec->setStorage(storage);
  return true;
 }
 bool Declaration::buildStorage(Spec* spec, std::vector<SpecName::Storage> storages){
   // local variable has auto by default
   if(spec->getStorage() == SpecName::NoStorage && symTable.getLevel() > 1){
     spec->setStorage(SpecName::Auto);
   }
   // check validness
   if(!storages.empty()){
    for(int storage = 0; storage < storages.size(); storage++){
      if(!setStorage(spec,storages[storage])){
        return false;
      }
    }
   }
   return true;
 }

 // qualifier *****************************************************************
 bool Declaration::setQualifier(Spec* spec, SpecName::Qualifier qualifier){
  SpecName::Qualifier currentQualifier = spec->getQualifier();
  if(currentQualifier != SpecName::NoQualifier){
    if( (qualifier == SpecName::Const && currentQualifier == SpecName::Volatile) ||
      (qualifier == SpecName::Volatile && currentQualifier == SpecName::Const)){
      spec->setQualifier(SpecName::ConstVolatile);
      return true;
    }
    return false;
  }
  spec->setQualifier(qualifier);
  return true;
 }
 bool Declaration::buildQualifier(Spec* spec, std::vector<SpecName::Qualifier> qualifiers){
  if(!qualifiers.empty()){
    for(int qualifier = 0; qualifier < qualifiers.size(); qualifier++){
      if(!setQualifier(spec,qualifiers[qualifier])){
        return false;
      }
    }
  }
   return true;
 }
// push to symbol table ****************************************************
bool Declaration::complete(){
  bool complete = false;
  std::string name = this->ids[0];
  //std::cout << "ID: \'" << name << "\'" << std::endl;
  //std::cout << "Mode: " << mode <<std::endl;

  if(isMode(DeclMode::Basic)){
    complete = pushBasic(name);
  }
  else if(isMode(DeclMode::Array)){
    this->kindsHolder[0].pop_back();
    complete = pushArray(name);
  }
  else if(isMode(DeclMode::Pointer)){
    complete = pushPointer(name);
  }
  else if(isMode(DeclMode::Enum)){

  }
  else if(isMode(DeclMode::Struct)){
    complete = pushStruct(name);
  }
  else if(isMode(DeclMode::Union)){

  }
  else if(isMode(DeclMode::Function)){
    this->kindsHolder.pop_back();
    complete = pushFunction(name);
  }
  else if(isMode(DeclMode::FunctionCall)){

  }
  lightClear();
  return complete;
}
void Declaration::lightClear(){
  this->kinds.clear();
  this->bases.clear();
  this->signs.clear();
  this->qualifiers.clear();
  this->storages.clear();
  this->ids.clear();
  this->lines.clear();
  this->cols.clear();
  this->dims.clear();
  this->levels.clear();
  this->arraySizes.clear();
  this->level = 0;
  this->hasInt = false;
}
void Declaration::clear(){
  //std::cout << "Clearing previous declaration information" << std::endl;
  lightClear();
  mode = DeclMode::NoMode;
  this->signsHolder.clear();
  this->storagesHolder.clear();
  this->qualifiersHolder.clear();
  this->basesHolder.clear();
  this->kindsHolder.clear();
  clearArgs();
}
void Declaration::clearArgs(){
  this->argSize = 0;
  this->hasType = false;
  this->argSymbolNodes.clear();
}

TypeBasic* Declaration::makeBasicType(std::vector<SpecName::BaseType> bases, std::vector<SpecName::Sign>signs,
  std::vector<SpecName::Qualifier> qualifiers){
  //std::cout << "Building Basic Type ..." << std::endl;
  Spec spec;
  if(!buildSign(&spec,signs)){
    return NULL;
  }
  if(!buildQualifier(&spec, qualifiers)){
    return NULL;
  }
  TypeBasic *basetype = new TypeBasic(SpecName::NoStorage,spec.getQualifier(),spec.getSign());

  if(!buildBase(basetype, bases)){
    return NULL;
  }

  //std::cout << "Basic type: \'" << basetype->toTypeString() << "\' is created"<< std::endl;
  return basetype;
}
TypeBasic* Declaration::makeBasicVar(std::vector<SpecName::BaseType> bases,
  std::vector<SpecName::Sign>signs, std::vector<SpecName::Storage> storages,
   std::vector<SpecName::Qualifier> qualifiers){

  TypeBasic *base = makeBasicType(bases,signs,qualifiers);
  if(base == NULL){
    return NULL;
  }
  if(!buildStorage(base,storages)){
    return NULL;
  }
  if(base->getBaseType() == SpecName::Void){
    if(isMode(DeclMode::FunctionArg) && this->argSize > 1){
      error("[P]: ERROR: \'void\' must be the first and only parameter if specified");
    }
    else if(!isMode(DeclMode::Function) && !isMode(DeclMode::FunctionArg)){
      error("[P]: ERROR: variable has incomplete type \'void\'");
    }
  }
  return base;
}
bool Declaration::pushBasic(std::string name){
  TypeBasic* base = makeBasicVar(this->basesHolder[0],this->signsHolder[0],this->storagesHolder[0],this->qualifiersHolder[0]);
  SymbolNode *val = new SymbolNode(name,base,this->lines[0],this->cols[0],true);
  return insertSymbol(name,val,this->lines[0], this->cols[0]);
}
bool Declaration::pushArray(std::string name){
  Spec spec;
  // check array size

  if(!buildStorage(&spec,this->storagesHolder[0])){
    return false;
  }
  if(!buildQualifier(&spec, this->qualifiersHolder[0])){
    return false;
  }
  TypeArray *array = new TypeArray(spec.getStorage(),spec.getQualifier());
  int type = this->kindsHolder[0].size()-1;
  // basic type
  if(this->kindsHolder[0][type] == SpecName::Basic){
    TypeBasic *base = makeBasicType(this->basesHolder[0],this->signsHolder[0],this->qualifiersHolder[0]);
    if(base == NULL){
      return false;
    }
    array->setElemSpec(base);
  }
  // pointer
  else if(this->kindsHolder[0][type] == SpecName::Pointer){
    TypePointer* pointer = makePointerType(this->kindsHolder[0][type-1], this->basesHolder[0],this->signsHolder[0],this->qualifiersHolder[0]);
    array->setElemSpec(pointer);
  }

  array->setArraySizes(this->dims.front());
  this->dims.erase(this->dims.begin());

  // insert array
  SymbolNode *val = new SymbolNode(name,array,this->lines[0], this->cols[0],true);
  return insertSymbol(name, val,this->lines[0], this->cols[0]);
}
TypePointer* Declaration::makePointerType(SpecName::TypeKind typekind, std::vector<SpecName::BaseType> bases,
  std::vector<SpecName::Sign>signs, std::vector<SpecName::Qualifier> qualifiers){
    Spec spec;
    if(!buildQualifier(&spec, qualifiers)){
      return NULL;
    }
    TypePointer *pointer = new TypePointer(SpecName::NoStorage,spec.getQualifier());
    pointer->setLevels(this->levels.front());
    this->levels.erase(this->levels.begin());

    // basic type -------------------------------
    if(typekind == SpecName::Basic){
      TypeBasic *base = makeBasicType(bases,signs,qualifiers);
      if(base == NULL){
        return NULL;
      }
      pointer->setTargetSpec(base);
    }
    // typedef
    return pointer;
}
TypePointer* Declaration::makePointerVar(SpecName::TypeKind typekind, std::vector<SpecName::BaseType> bases,
  std::vector<SpecName::Sign>signs, std::vector<SpecName::Storage> storages,
   std::vector<SpecName::Qualifier> qualifiers){
  Spec spec;
  TypePointer *pointer = makePointerType(typekind,bases,signs,qualifiers);
  if(!buildStorage(pointer,storages)){
    return NULL;
  }
  return pointer;
}

bool Declaration::pushPointer(std::string name){
  TypePointer* pointer = makePointerVar(this->kindsHolder[0][0], this->basesHolder[0],this->signsHolder[0],this->storagesHolder[0],this->qualifiersHolder[0]);
  SymbolNode *val = new SymbolNode(name,pointer,this->lines[0],this->cols[0]);
  return insertSymbol(name, val,this->lines[0], this->cols[0]);
}
bool Declaration::pushFunction(std::string name){
  Spec spec;
  bool arg_definition_mode = false;
  int arg = 0;
  int type = 0;
  int kind = 0;

  if(!buildStorage(&spec,this->storagesHolder[type])){
    return false;
  }
  if(!buildQualifier(&spec, this->qualifiersHolder[type])){
    return false;
  }
  TypeFunction *function = new TypeFunction(spec.getStorage(),spec.getQualifier());

  // return type  ===========================================================
  if(!this->hasType){
    warning("[P] WARNING: type specifier missing, defaults to \'int\'");
    TypeBasic* base = new TypeBasic();
    base->setBaseType(SpecName::Int);
    function->setReturnSpec(base);
  }
  else{
    Spec returnSpec;
    int num = this->kindsHolder[kind].size()-1;
    // basic ---------------------------------------------------
    if(this->kindsHolder[kind][num] == SpecName::Basic){
      TypeBasic* base = makeBasicType(this->basesHolder[num],this->signsHolder[type],this->qualifiersHolder[type]);
      if(base != NULL){
        function->setReturnSpec(base);
      }
    }
    // pointer -------------------------------------------------
    else if(this->kindsHolder[kind][num] == SpecName::Pointer){
      TypePointer* pointer = makePointerType(this->kindsHolder[kind][num-1],this->basesHolder[type],
        this->signsHolder[type],this->qualifiersHolder[type]);
      if(pointer != NULL){
        function->setReturnSpec(pointer);
      }
    }
  }

  // function arguments mode
  setMode(DeclMode::FunctionArg); // better to check if an arg exists

  // check if arg has id
  if(ids.size() == this->kindsHolder.size()){ // not quite right way ?
    arg_definition_mode = true;
    arg = 1;
  }

  // argment types ===========================================================
  for(kind++; kind < this->kindsHolder.size(); kind++){
    //std::cout << "Figuring out a new argment type ..." << std::endl;
      type++;

      int num = this->kindsHolder[kind].size()-1;
      // basic ---------------------------------------------------
      if(this->kindsHolder[kind][num] == SpecName::Basic){
        TypeBasic* base = makeBasicVar(this->basesHolder[type],this->signsHolder[type],this->storagesHolder[type],this->qualifiersHolder[type]);
        if(arg_definition_mode){
          this->argSymbolNodes.push_back(new SymbolNode(this->ids[arg], base, this->lines[arg],this->cols[arg],true));
          arg++;
        }
        function->insertArg(base);
      }
      // pointer ---------------------------------------------------
      else if(this->kindsHolder[kind][num] == SpecName::Pointer){
        TypePointer* pointer = makePointerVar(this->kindsHolder[kind][num-1], this->basesHolder[type],this->signsHolder[type],this->storagesHolder[type],this->qualifiersHolder[type]);
        if(arg_definition_mode){
          this->argSymbolNodes.push_back(new SymbolNode(this->ids[arg], pointer, this->lines[arg], this->cols[arg], true));
          arg++;
        }
        function->insertArg(pointer);
      }
      // array ----------------------------------------------------
      else if(this->kindsHolder[kind][num] == SpecName::Array){
         TypeArray *array = new TypeArray();
        // check array size
        for(int dim = 0; dim < this->dims.front().size(); dim++){
          if(this->dims.front().at(dim) < 0){
            error("[P]: ERROR: an array with a negative size");
            return false;
          }
        }
        if(!buildStorage(array,this->storagesHolder[kind])){
          return false;
        }
        if(!buildQualifier(array, this->qualifiersHolder[kind])){
          return false;
        }
        // basic type
        if(this->kindsHolder[kind][num-1] == SpecName::Basic){
          TypeBasic *base = makeBasicType(this->basesHolder[kind],this->signsHolder[kind],this->qualifiersHolder[kind]);
          if(base == NULL){
            return false;
          }
          array->setElemSpec(base);
        }
        array->setArraySizes(this->dims.front());
        this->dims.erase(this->dims.begin());

        if(arg_definition_mode){
          this->argSymbolNodes.push_back(new SymbolNode(this->ids[arg], array, this->lines[arg], this->cols[arg],true));
          arg++;
        }

        function->insertArg(array);
      }
  } // end argment types  ====================================================

  // insert function
  SymbolNode *val = new SymbolNode(name, function, this->lines[0], this->cols[0]);
  return insertSymbol(name, val,this->lines[0], this->cols[0]);
}
bool Declaration::insertSymbol(std::string name, SymbolNode* val, int line, int col){
  SymbolNode *sym = symTable.lookupTopTable(name);
  if(sym != NULL && sym->isDefined()){
    std::stringstream ss;
    ss << "[P]: ERROR: Redefinition of \'" << name << "\'" << ", line " << line << " col " << col;
    error(ss.str());
  }
  else if(symTable.lookUpShadowedSymbol(name)) {
    std::stringstream ss;
    ss << "[P]: WARNING: Symbol \'"+name+"\' shadows another" << ", line " << line << " col " << col;
    warning(ss.str());
  }
  return symTable.insertSymbol(name, val);
}


bool Declaration::pushStruct(std::string name){
  int kind;
  int memberSize = this->kindsHolder.size();
  bool isComplete = (memberSize > 0)? true: false;
  TypeStruct* structspec = new TypeStruct();
  symTable.pushTable();  // poor way

  // member types ===========================================================
  for(kind = 1; kind < memberSize; kind++){
      int num = this->kindsHolder[kind].size()-1;
      // basic ---------------------------------------------------
      if(this->kindsHolder[kind][num] == SpecName::Basic){
        TypeBasic* base = makeBasicVar(this->basesHolder[kind-1],this->signsHolder[kind-1],this->storagesHolder[kind-1],this->qualifiersHolder[kind-1]);
        insertSymbol(this->ids[kind], new SymbolNode(this->ids[kind], base, this->lines[kind],this->cols[kind],true),this->lines[kind], this->cols[kind]);
        structspec->addMember(ids[kind],base);
      }
  } // end member types  ====================================================
  symTable.popTable(); // poor way

  SymbolNode *val = new SymbolNode(name,structspec,this->lines[0],this->cols[0],isComplete);
  return insertSymbol(name, val,this->lines[0], this->cols[0]);
}
// debug ********************************************************************
void Declaration::showIDs() const{
   for(int id = 0;id < this->ids.size(); id++){
     std::cout << id << ": " << this->ids[id] << std::endl;
   }
}
void Declaration::showKinds() const{
    for(int n = 0; n < this->kindsHolder.size(); n++){
      for(int kind = 0; kind < this->kindsHolder[n].size(); kind++){
        std::cout << this->kindsHolder[n].at(kind) << std::endl;
      }
    }
  }
void Declaration::showSigns() const{
  for(int n = 0; n < this->signsHolder.size(); n++){
    for(int sign = 0; sign < this->signsHolder[n].size(); sign++){
      std::cout << this->signsHolder[n].at(sign) << std::endl;
    }
  }
}
void Declaration::showBases() const{
  for(int n = 0; n < this->basesHolder.size(); n++){
    for(int base = 0; base < this->basesHolder[n].size(); base++){
      std::cout << this->basesHolder[n].at(base) << std::endl;
    }
  }
}
void Declaration::showStorages() const{
  for(int n = 0; n < this->storagesHolder.size(); n++){
    for(int storage = 0; storage< this->storagesHolder[n].size(); storage++){
      std::cout << this->storagesHolder[n].at(storage) << std::endl;
    }
  }
}
void Declaration::showQualifiers() const{
  for(int n = 0; n < this->qualifiersHolder.size(); n++){
    for(int qualifier = 0; qualifier< this->qualifiersHolder[n].size(); qualifier++){
      std::cout << this->qualifiersHolder[n].at(qualifier) << std::endl;
    }
  }
}
