#include "Spec.h"
Spec::Spec(SpecName::TypeKind tk, SpecName::Storage sc,
  SpecName::Qualifier tq, SpecName::Sign sign){
  this->typekind = tk;
  this->storage = sc;
  this->qualifier = tq;
  this->sign = sign;
  this->baseType = SpecName::NoType;
  this->is_value = false; // assume it is an identifier
}
Spec::~Spec(){}
std::string Spec::toTypeString() const{
  return getTypeKindStr();
}
std::string Spec::toString() const{
  std::stringstream ss;
  ss << "TypeKind: "<< this->getTypeKindStr()
     << " Storage: "<< this->getStorageClassStr()
     << " Qualifier: "<< this->getTypeQualifierStr()
     << " Sign: "<< this->getSignStr();
  return ss.str();
}
// setters  -------------------------------------------
void Spec::setTypeKind(SpecName::TypeKind typekind){
  this->typekind = typekind;
}
void Spec::setStorage(SpecName::Storage storage){
  this->storage = storage;
}
void Spec::setQualifier(SpecName::Qualifier qualifier){
  this->qualifier = qualifier;
}
void Spec::setSign(SpecName::Sign sign){
  this->sign = sign;
}
void Spec::setValue(bool is_value){
  this->is_value = is_value;
}

// getters  -------------------------------------------
SpecName::BaseType Spec::getBaseType() const{
  return this->baseType;
}
SpecName::TypeKind Spec::getTypeKind() const{
  return this->typekind;
}
SpecName::Storage Spec::getStorage() const{
  return this->storage;
}
SpecName::Qualifier Spec::getQualifier() const{
  return this->qualifier;
}
SpecName::Sign Spec::getSign() const{
  return this->sign;
}

bool Spec::isTypeKind(SpecName::TypeKind type) const {
  return this->typekind == type;
}
bool Spec::isStorageClass(SpecName::Storage type) const {
  return this->storage == type;
}
bool Spec::isTypeQualifier(SpecName::Qualifier type) const {
  return this->qualifier == type;
}
bool Spec::isSign(SpecName::Sign type) const {
  return this->sign == type;
}
bool Spec::isValue() const{
  return this->is_value;
}

std::string Spec::getTypeKindStr() const{
  std::string result;
  if(this->typekind == SpecName::NoKind){
    // none
  }
  else if(this->typekind == SpecName::Basic){
    result = "basic";
  }
  else if(this->typekind == SpecName::Pointer){
    result = "pointer";
  }
  else if(this->typekind == SpecName::Array){
    result = "array";
  }
  else if(this->typekind == SpecName::Struct){
    result = "struct";
  }
  else if(this->typekind == SpecName::Union){
    result = "union";
  }
  else if(this->typekind == SpecName::Function){
    result = "function";
  }
  else if(this->typekind == SpecName::Enum){
    result = "enum";
  }
  else if(this->typekind == SpecName::TypeName){
    result = "typename";
  }
  else{
    std::cout << "Error: invalid type kind" << std::endl;
  }
  return result;
}
std::string Spec::getStorageClassStr() const{
  std::string result;
  if(this->storage == SpecName::NoStorage){
    // none
  }
  else if(this->storage == SpecName::Extern){
    result = "extern";
  }
  else if(this->storage == SpecName::Static){
    result = "static";
  }
  else if(this->storage == SpecName::Auto){
    result = "auto";
  }
  else if(this->storage == SpecName::Register){
    result = "register";
  }
  else if(this->storage == SpecName::Typedef){
    result = "typedef";
  }
  else if(this->storage == SpecName::NoStorage){}
  else{
    std::cout << "Error: invalid storage class" << std::endl;
  }
  return result;
}
std::string Spec::getTypeQualifierStr() const{
  std::string result;
  if(this->qualifier == SpecName::NoQualifier){
    // none
  }
  else if(this->qualifier == SpecName::Const){
    result = "const";
  }
  else if(this->qualifier == SpecName::Volatile){
    result = "volatile";
  }
  else if(this->qualifier == SpecName::ConstVolatile){
    result = "const volatile";
  }
  else{
    std::cout << "Error: invalid type qualifier" << std::endl;
  }
  return result;
}
std::string Spec::getSignStr() const{
  std::string result;
  if(this->sign == SpecName::NoSign){
    // none
  }
  else if(this->sign == SpecName::Signed){
    result = "signed";
  }
  else if(this->sign == SpecName::Unsigned){
    result = "unsigned";
  }
  else{
    std::cout << "Error: invalid sign" << std::endl;
  }
  return result;
}
// Basic -------------------------------------------------------------------
TypeBasic::TypeBasic(SpecName::BaseType baseType){
  this->typekind = SpecName::Basic;
  this->baseType = baseType;
}
TypeBasic::TypeBasic(SpecName::Storage sc,SpecName::Qualifier tq, SpecName::Sign sign){
  this->typekind = SpecName::Basic;
  this->storage = sc;
  this->qualifier = tq;
  this->sign = sign;
  this->baseType = SpecName::NoType;
}
TypeBasic::~TypeBasic(){}
std::string TypeBasic::toString() const{
  std::stringstream ss;
  std::string temp;
  temp = this->getTypeName();
  if(!temp.empty()){
    ss << temp;
  }
  temp = this->getStorageClassStr();
  if(!temp.empty()){
    ss << " " + temp;
  }
  return ss.str();
}
std::string TypeBasic::toTypeString() const{
  return getTypeName();
}
std::string TypeBasic::basetToStr(SpecName::BaseType basetype) const{
  std::string result;
  if(basetype == SpecName::Void){
    result = "void";
  }
  else if(basetype == SpecName::Char){
    result = "char";
  }
  else if(basetype == SpecName::Int){
    result = "int";
  }
  else if(basetype == SpecName::Short){
    result = "short";
  }
  else if(basetype == SpecName::Long){
    result = "long";
  }
  else if(basetype == SpecName::LLong){
    result = "long long";
  }
  else if(basetype == SpecName::Float){
    result = "float";
  }
  else if(basetype == SpecName::Double){
    result = "double";
  }
  else if(basetype == SpecName::LDouble){
    result = "long double";
  }
  else{
    std::cout << "Error: invalid base type" << std::endl;
  }
  return result;
}
std::string TypeBasic::getBaseTypeStr() const{
  return basetToStr(this->baseType);
}
std::string TypeBasic::getTypeName() const{
  std::string result = basetToStr(this->baseType);
  std::string temp;
  temp = this->getTypeQualifierStr();
  if(!temp.empty()){
    result =temp + " " + result;
  }
  temp = this->getSignStr();
  if(!temp.empty()){
    result = temp + " " + result;
  }
  return result;
}

SpecName::BaseType TypeBasic::getBaseType() const{
  return this->baseType;
}
void TypeBasic::setBaseType(SpecName::BaseType baseType){
  this->baseType = baseType;
}
bool TypeBasic::isBase(SpecName::BaseType baseType){
  return this->baseType == baseType;
}

// enum  ------------------------------------------------------------------
TypeEnum::TypeEnum(SpecName::Storage sc,SpecName::Qualifier tq, SpecName::Sign sign){
  this->typekind = SpecName::Enum;
  this->storage = sc;
  this->qualifier = tq;
  this->sign = sign;

  this->nextNumber = 0;
  this->enumName = "int";
}
std::string TypeEnum::toTypeString() const{
  return this->enumName;
}
std::string TypeEnum::toString() const{
  return "Enum"; //for now
}
int TypeEnum::getSize() const{
  return constants.size();
}
void TypeEnum::addConst(std::string name, int number){
  constants[name] = number;
  this->nextNumber = ++number;
}
int TypeEnum::getNextNumber() const{
  return this->nextNumber;
}

// array -----------------------------------------------
TypeArray::TypeArray(SpecName::Storage sc,SpecName::Qualifier tq, SpecName::Sign sign){
  this->typekind = SpecName::Array;
  this->storage = sc;
  this->qualifier = tq;
  this->sign = sign;

  this->elemSpec = NULL;
}
std::string TypeArray::toTypeString() const{
  std::stringstream ss;
  ss << getElemTypeName();
  for(int dim = 0; dim < this->arraySizes.size(); dim++){
    ss << "[" << this->arraySizes[dim] << "]";
  }
  return ss.str();
}
std::string TypeArray::toString() const{
  std::stringstream ss;
  std::string temp;
  ss << toTypeString();
  temp = this->getStorageClassStr();
  if(!temp.empty()){
    ss << " " + temp;
  }
  return ss.str();
}
void TypeArray::setElemSpec(Spec* elemSpec){
  this->elemSpec = elemSpec;
}
void TypeArray::setArraySizes(std::vector<int>& arraySizes){
  this->arraySizes = arraySizes;
}
SpecName::BaseType TypeArray::getBaseType() const{
  return this->elemSpec->getBaseType();
}
std::string TypeArray::getElemTypeName() const{
  if(this->elemSpec!=NULL){
    return this->elemSpec->toString();
  }
  return "";
}
int TypeArray::getSize(int dim) const{
  return this->arraySizes[dim];
}
int TypeArray::getSpace() const{
  int result = 1;
  for(int dim = 0; dim < this->arraySizes.size(); dim++){
    result *= this->arraySizes[dim];
  }
  return result;
}
std::vector<int> TypeArray::getSizes() const{
  return this->arraySizes;
}
int TypeArray::getDim() const{
  return this->arraySizes.size();
}

// function ------------------------------------------------------------------
TypeFunction::TypeFunction(SpecName::Storage sc,SpecName::Qualifier tq, SpecName::Sign sign){
  this->typekind = SpecName::Function;
  this->storage = sc;
  this->qualifier = tq;
  this->sign = sign;

  this->returnSpec = NULL;
}
std::string TypeFunction::toTypeString() const{
  std::stringstream ss;
  std::string temp;
  ss << getReturnSpecName() + "(";
  for(int arg = 0; arg < this->argSpecs.size(); arg++){
    ss << getArgTypeName(arg);
    if(arg < this->argSpecs.size()-1){
      ss << ", ";
    }
  }
  ss << ")";
  return ss.str();
}
std::string TypeFunction::toString() const{
  std::stringstream ss;
  std::string temp;
  ss << toTypeString();
  temp = this->getStorageClassStr();
  if(!temp.empty()){
    ss << " " + temp;
  }
  return ss.str();
}
void TypeFunction::insertArg(Spec* argSpec){
  this->argSpecs.push_back(argSpec);
}
void TypeFunction::setReturnSpec(Spec*  returnSpec){
  this->returnSpec = returnSpec;
}
SpecName::BaseType TypeFunction::getBaseType() const{
  return this->returnSpec->getBaseType();
}
int TypeFunction::getArgSize() const{
  return this->argSpecs.size();
}
std::string TypeFunction::getArgTypeName(int nth) const{
  return this->argSpecs[nth]->toString();
}
std::string TypeFunction::getReturnSpecName() const{
  return this->returnSpec->toString();
}
Spec* TypeFunction::getArgSpec(int nth) const{
  return this->argSpecs[nth];
}
Spec* TypeFunction::getReturnSpec() const{
  return this->returnSpec;
}
// typename  ------------------------------------------------------------------
TypeTypeName::TypeTypeName(SpecName::Storage sc,SpecName::Qualifier tq, SpecName::Sign sign){
  this->typekind = SpecName::TypeName;
  this->storage = sc;
  this->qualifier = tq;
  this->sign = sign;

  this->baseSpec = NULL;
}
std::string TypeTypeName::toTypeString() const{
  return this->baseSpec->toTypeString();
}
std::string TypeTypeName::toString() const{
 std::stringstream ss;
 std::string temp;
 ss << "Typedef " << this->typeName << " " << toTypeString();
 return ss.str();
}
void TypeTypeName::setTypeName(std::string typeName){
  this->typeName = typeName;
}
void TypeTypeName::setBaseSpec(Spec* baseSpec){
  this->baseSpec = baseSpec;
}
Spec* TypeTypeName::getBaseSpec() const{
  return this->baseSpec;
}
// pointer ------------------------------------------------------------------
TypePointer::TypePointer(SpecName::Storage sc,SpecName::Qualifier tq, SpecName::Sign sign){
  this->typekind = SpecName::Pointer;
  this->storage = sc;
  this->qualifier = tq;
  this->sign = sign;
}
std::string TypePointer::toTypeString() const{
  std::stringstream ss;
  std::string temp;
  ss << getTargetTypeName();
  temp = this->getTypeQualifierStr();
  if(!temp.empty()){
    ss << " " + temp;
  }
  for(int level = 0; level < this->levels; level++){
    ss << "*";
  }
  return ss.str();
}
std::string TypePointer::toString() const{
  std::stringstream ss;
  std::string temp;
  ss << toTypeString();
  temp = this->getStorageClassStr();
  if(!temp.empty()){
    ss << " " + temp;
  }
  return ss.str();
}
SpecName::BaseType TypePointer::getBaseType() const{
  return this->targetSpec->getBaseType();
}
std::string TypePointer::getTargetTypeName() const{
  return this->targetSpec->toTypeString();
}
int TypePointer::getLevels() const{
  return this->levels;
}
void TypePointer::setTargetSpec(Spec* targetSpec){
  this->targetSpec = targetSpec;
}
void TypePointer::setLevels(int levels){
  this->levels = levels;
}
void TypePointer::incLevel(){
  this->levels++;
}
// Struct -------------------------------------------------------------------
TypeStruct::TypeStruct(SpecName::Storage sc,SpecName::Qualifier tq, SpecName::Sign sign){
  this->typekind = SpecName::Struct;
  this->storage = sc;
  this->qualifier = tq;
  this->sign = sign;
}
std::string TypeStruct::toString() const{
  std::stringstream ss;
  std::string temp;
  ss << toTypeString();
  temp = this->getStorageClassStr();
  if(!temp.empty()){
    ss << " " + temp;
  }
  ss << "{ ";
  for(int name = 0; name < this->names.size(); name++){
    ss << this->members.at(this->names[name])->toTypeString() << " ";
  }
  ss << "}";
  return ss.str();
}
std::string TypeStruct::toTypeString() const{
  std::stringstream ss;
  std::string temp;
  ss << "Struct";
  if(!this->structName.empty()){  // may be anonymous
    ss << " " + this->structName;
  }
  return ss.str();
}
void TypeStruct::addMember(std::string name, Spec* type){
    this->members[name] = type;
    this->names.push_back(name);
}
Spec* TypeStruct::findMember(std::string name){
  if(this->members.find(name) != this->members.end()){
     return this->members[name];
    }
    return NULL;
}
// Union ------------------------------------------------------------------
TypeUnion::TypeUnion(SpecName::Storage sc,SpecName::Qualifier tq, SpecName::Sign sign){
  this->typekind = SpecName::Union;
  this->storage = sc;
  this->qualifier = tq;
  this->sign = sign;
}
std::string TypeUnion::toString() const{
  std::stringstream ss;
  std::string temp;
  ss << toTypeString();
  temp = this->getStorageClassStr();
  if(!temp.empty()){
    ss << " " + temp;
  }
  return ss.str();
}
std::string TypeUnion::toTypeString() const{
  std::stringstream ss;
  std::string temp;
  ss << "Union";
  if(!this->unionName.empty()){  // may be anonymous
    ss << " " + this->unionName;
  }
  return ss.str();
}
void TypeUnion::addMember(std::string name, Spec* type){
    this->members[name] = type;
}
Spec* TypeUnion::findMember(std::string name){
  if(this->members.find(name) != this->members.end()){
     return this->members[name];
    }
    return NULL;
}