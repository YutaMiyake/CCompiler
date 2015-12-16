#ifndef __TYPE__H__
#define __TYPE__H__
#include <iostream>
#include <vector>
#include <map>
#include <sstream>

namespace SpecName{
  enum TypeKind{
    NoKind, Basic, Pointer, Array, Struct, Union, Function, Enum, TypeName
  };
  enum BaseType{
   NoType,
   Void,
   Char, //UChar, SChar,
   Int, //UInt,
   Short, //UShort,
   Long, //ULong,
   LLong, //ULLong,
   Float,
   Double,
   LDouble
  };
  enum Storage{
    NoStorage, Extern, Static, Auto, Register, Typedef
  };
  enum Qualifier{
    NoQualifier, Const, Volatile, ConstVolatile
  };
  enum Sign{
    NoSign, Signed, Unsigned
  };
};

class Spec{
public:
  Spec(SpecName::TypeKind = SpecName::NoKind, SpecName::Storage = SpecName::NoStorage,
    SpecName::Qualifier = SpecName::NoQualifier, SpecName::Sign = SpecName::NoSign);
  virtual ~Spec();
  virtual std::string toString() const;
  virtual std::string toTypeString() const;
  virtual SpecName::BaseType getBaseType() const;

  std::string getTypeKindStr() const;
  std::string getStorageClassStr() const;
  std::string getTypeQualifierStr() const;
  std::string getSignStr() const;

  SpecName::TypeKind getTypeKind() const;
  SpecName::Storage getStorage() const;
  SpecName::Qualifier getQualifier() const;
  SpecName::Sign getSign() const;

  void setTypeKind(SpecName::TypeKind typekind);
  void setStorage(SpecName::Storage storage);
  void setQualifier(SpecName::Qualifier qualifier);
  void setSign(SpecName::Sign sign);
  void setValue(bool is_value);

  bool isTypeKind(SpecName::TypeKind) const;
  bool isStorageClass(SpecName::Storage) const;
  bool isTypeQualifier(SpecName::Qualifier) const;
  bool isSign(SpecName::Sign) const;
  bool isValue() const;  // for constant value

protected:
  SpecName::TypeKind typekind;
  SpecName::Storage storage;
  SpecName::Qualifier qualifier;
  SpecName::Sign sign;
  SpecName::BaseType baseType;
  bool is_value; // for constant value
};

// basic -----------------------------------------------
class TypeBasic: public Spec{
 public:
  TypeBasic(SpecName::BaseType baseType);
  TypeBasic(SpecName::Storage = SpecName::NoStorage, SpecName::Qualifier = SpecName::NoQualifier, SpecName::Sign = SpecName::NoSign);
  ~TypeBasic();
  std::string toString() const;
  std::string toTypeString() const;

  std::string getTypeName() const;
  std::string getBaseTypeStr() const;
  SpecName::BaseType getBaseType() const;
  std::string basetToStr(SpecName::BaseType basetype) const;
  void setBaseType(SpecName::BaseType baseType);
  bool isBase(SpecName::BaseType baseType);
 private:
  SpecName::BaseType baseType;
};

// enum -----------------------------------------------
class TypeEnum: public Spec{
 public:
   TypeEnum(SpecName::Storage = SpecName::NoStorage,SpecName::Qualifier = SpecName::NoQualifier, SpecName::Sign = SpecName::NoSign);
   std::string toString() const;
   std::string toTypeString() const;

   int getSize() const;
   void addConst(std::string name, int number);
   int getNextNumber() const;

 private:
  int nextNumber;
  std::string enumName;
  std::map<std::string, int> constants;
};

// array -----------------------------------------------
class TypeArray: public Spec{
 public:
   TypeArray(SpecName::Storage = SpecName::NoStorage,SpecName::Qualifier = SpecName::NoQualifier, SpecName::Sign = SpecName::NoSign);
   std::string toString() const;
   std::string toTypeString() const;

   SpecName::BaseType getBaseType() const;
   std::string getElemTypeName() const;
   int getSize(int n) const;
   int getSpace() const;
   std::vector<int> getSizes() const;
   int getDim() const;
   void setElemSpec(Spec* elemSpec);
   void setArraySizes(std::vector<int> &arraysizes);

 private:
  //std::string elemType;
  Spec* elemSpec;
  std::vector<int> arraySizes;
};
// function -----------------------------------------------
class TypeFunction : public Spec{
public:
    TypeFunction(SpecName::Storage = SpecName::NoStorage,SpecName::Qualifier = SpecName::NoQualifier, SpecName::Sign = SpecName::NoSign);
    std::string toString() const;
    std::string toTypeString() const;

    void insertArg(Spec* argSpec);
    void setReturnSpec(Spec* returnSpec);

    SpecName::BaseType getBaseType() const;
    int getArgSize() const;
    std::string getArgTypeName(int nth) const;
    std::string getReturnSpecName() const;
    Spec* getReturnSpec() const;
    Spec* getArgSpec(int nth) const;

  private:
    Spec* returnSpec;
    std::vector<Spec*> argSpecs;
};
// TypeName -----------------------------------------------
class TypeTypeName: public Spec{
 public:
   TypeTypeName(SpecName::Storage = SpecName::NoStorage,SpecName::Qualifier = SpecName::NoQualifier, SpecName::Sign = SpecName::NoSign);
   std::string toString() const;
   std::string toTypeString() const;

   Spec* getBaseSpec() const;
   std::string getTypeName() const;
   void setBaseSpec(Spec* baseSpec);
   void setTypeName(std::string typeName);

 private:
  std::string typeName;
  Spec * baseSpec;
};

// pointer -----------------------------------------------
class TypePointer: public Spec{
 public:
   TypePointer(SpecName::Storage = SpecName::NoStorage,SpecName::Qualifier = SpecName::NoQualifier, SpecName::Sign = SpecName::NoSign);
   std::string toString() const;
   std::string toTypeString() const;

   SpecName::BaseType getBaseType() const;
   Spec* getTargetSpec() const;
   std::string getTargetTypeName() const;
   int getLevels() const;
   void setTargetSpec(Spec* targetSpec);
   void setLevels(int levels);
   void incLevel();

 private:
 Spec* targetSpec;
 int levels;
};
// struct -----------------------------------------------
// no need to separate struct and union?
class TypeStruct: public Spec{
 public:
  TypeStruct(SpecName::Storage = SpecName::NoStorage,SpecName::Qualifier = SpecName::NoQualifier, SpecName::Sign = SpecName::NoSign);
  std::string toString() const;
  std::string toTypeString() const;

  void addMember(std::string name, Spec* type);
  Spec* findMember(std::string name);

 private:
  std::vector<std::string> names;
  std::string structName;
  std::map<std::string, Spec*> members; // small symbol table
};
// union -----------------------------------------------
// no need to separate struct and union?
class TypeUnion: public Spec{
 public:
  TypeUnion(SpecName::Storage = SpecName::NoStorage,SpecName::Qualifier = SpecName::NoQualifier, SpecName::Sign = SpecName::NoSign);
  std::string toString() const;
  std::string toTypeString() const;

  void addMember(std::string name, Spec* type);
  Spec* findMember(std::string name);

 private:
  std::string unionName;
  std::map<std::string, Spec*> members; // small symbol table
};

#endif