#ifndef __AST_NODE__H__
#define __AST_NODE__H__
#include <string>
#include <iostream>
#include <cstdlib>
#include <vector>
#include "../SymbolTable.h"
#include "../SymbolNode.h"
#include "../SymDumper.h"
#include "../graph.h"
#include "../CodeDumper.h"

extern Graph visualizer;
extern CodeDumper codeGenerator;
extern SymDumper symDumper;

// forward declaration
class ast_node;
class translation_unit_node;
class external_declaration_node;
class function_definition_node;
class declaration_node;
class declaration_list_node;
class init_declarator_node;
class init_declarator_list_node;
class declaration_specifiers_node;
class storage_class_specifier_node;
class type_specifier_node;
class type_qualifier_node;
class type_qualifier_list_node;
class union_specifier_node;
class struct_or_union_node;
class struct_declaration_list_node;
class struct_declaration_node;
class struct_declarator_list_node;
class struct_declarator_node;
class specifier_qualifier_list_node;
class qualifier_list_node;
class declarator_list_node;
class struct_declarator_node;
class enum_specifier_node;
class enumerator_list_node;
class enumerator_node;
class declarator_node;
class direct_declarator_node;
class pointer_node;
class parameter_type_list_node;
class parameter_list_node;
class parameter_declaration_node;
class identifier_list_node;
class initializer_node;
class initializer_list_node;
class type_name_node;
class abstract_declarator_node;
class direct_abstract_declarator_node;
class statement_node;
class labeled_statement_node;
class expression_statement_node;
class compound_statement_node;
class statement_list_node;
class selection_statement_node;
class iteration_statement_node;
class jump_statement_node;
class expression_node;
class assignment_expression_node;
class assignment_operator_node;
class conditional_expression_node;
class constant_expression_node;

// Grouping this off to note that they are all binary operations,
// which we may want to collapse all into something like a binary_operation_node
class logical_or_expression_node;
class logical_and_expression_node;
class inclusive_or_expression_node;
class exclusive_or_expression_node;
class and_expression_node;
class equality_expression_node;
class relational_expression_node;
class shift_expression_node;
class additive_expression_node;
class multiplicative_expression_node;

class cast_expression_node;
class unary_expression_node;
class unary_operator_node;
class postfix_expression_node;
class array_node;
class primary_expression_node;
class argument_expression_list_node;
class constant_node;
class string_node;
class identifier_node;

namespace DirectType{
  enum Type{NONE, ARRAY, FUNCTION, FUNCTION_CALL};
}
//could be enum for type_specifiers but should also includes struct and union (extra credit)
namespace TypeSpecifier{
  enum Type{VOID, CHAR, SHORT, INT, LONG, FLOAT, DOUBLE, SIGNED,
            UNSIGNED, TYPEDEF_NAME};
}
namespace ConstType{
  enum Type {INT,CHAR,FLOAT,ENUM};
}
namespace StructUnion{
  enum Type {NONE, STRUCT, UNION};
}
namespace OpType{
  enum Type{NONE, PERIOD,PTR_OP,
            INC, DEC, SIZEOF,
            MUL, DIV, PLUS, MINUS,
            ASTERISK, MOD, PIPE,
            AND, UP_CARROT, TILDE, BANG,
            LEFT_OP, RIGHT_OP, QUESTION,
            L, G, GE, LE, EQ, NE, AND_OP, OR_OP
          };
}
namespace JumpType{
  enum Type{NONE, RETURN, BREAK, CONTINUE};
}
namespace IterType{
  enum Type{NONE, WHILE, DO, FOR};
}
namespace SelecType{
  enum Type{NONE, IF, SWITCH};
}
namespace LabelType{
  enum Type{NONE, CASE, DEFAULT};
}

class ast_node {
  public:
    ast_node();
    virtual ~ast_node();
    virtual void clear()=0;
    virtual void print()=0;
    virtual std::string generateCode()=0;

    static int getTempNum();
    static int getLabelNum();
    static void incrTempNum();
    static void incrLabelNum();
    static std::string getTempStr();
    static std::string getNewTempStr();
    static std::string getLastTempStr();
    static std::string getNewLabelStr();
    static std::string getLabelStr();
    static int getUID();

    void setID();
    int getID();
    int getPID();
    void setPID(int pid);
    void setSource(std::string source);
    std::string getSource();
    Spec* getSpec();

    void error(const std::string& message);
    void warning(const std::string& message);

  private:
    std::string name;
    ast_node* parent;

    // for 3AC
    static int tempNum;   // 0
    static int labelNum;  // 0

    // for graphviz
    static int unique_id;  // 0

  protected:
    int id;
    int pid;
    Spec* spec;
    std::string source;
};

class translation_unit_node : public ast_node {
  public:
    translation_unit_node();
    translation_unit_node(external_declaration_node* child);
    ~translation_unit_node();
    void addExternDecl(external_declaration_node* child);
    std::vector<external_declaration_node*> getChildren() const;
    void clear();
    void print();
    std::string generateCode();
  private:
    std::vector<external_declaration_node*> children;
};

class external_declaration_node : public ast_node {
  public:
    external_declaration_node();
    external_declaration_node(function_definition_node* child);
    external_declaration_node(declaration_node* child);
    ~external_declaration_node();
    void clear();
    void print();
    std::string generateCode();
  private:
    function_definition_node* functionChild;
    declaration_node* declChild;
};

class function_definition_node : public ast_node {
  public:
    function_definition_node();
    function_definition_node(declaration_specifiers_node* specifiers,
                            declarator_node* decl,
                            declaration_list_node* decList,
                            compound_statement_node* compStmt);
    ~function_definition_node();
    void clear();
    void print();
    std::string generateCode();
  private:
    int spec_id;
    declaration_specifiers_node* specifiers;
    declarator_node* decl;
    declaration_list_node* decList;
    compound_statement_node* compStmt;
};

class declaration_node : public ast_node {
  public:
    declaration_node();
    declaration_node(declaration_specifiers_node* specifier, init_declarator_list_node* decList);
    ~declaration_node();
    void clear();
    void print();
    std::string generateCode();
  private:
    declaration_specifiers_node* specifier;
    init_declarator_list_node* decList;
    int spec_id;
};

class declaration_list_node : public ast_node {
  public:
    declaration_list_node();
    declaration_list_node(declaration_node* child);
    ~declaration_list_node();
    void addDecl(declaration_node* child);
    std::vector<declaration_node*> getChildren() const;
    void clear();
    void print();
    std::string generateCode();
  private:
    std::vector<declaration_node*> children;
};

class init_declarator_node : public ast_node {
  public:
    init_declarator_node(declarator_node* declarator, initializer_node* initializer);
    ~init_declarator_node();
    Spec* getSpec();
    void init();
    void clear();
    void print();
    std::string generateCode();
  private:
    int equal_id;
    declarator_node* declarator;
    initializer_node* initializer;
};

class init_declarator_list_node : public ast_node {
public:
  init_declarator_list_node();
  init_declarator_list_node(init_declarator_node* child);
  ~init_declarator_list_node();
  void addInitDecl(init_declarator_node* child);
  std::vector<init_declarator_node*> getChildren() const;
  void clear();
  void print();
  std::string generateCode();
private:
  std::vector<init_declarator_node*> children;
};

class declaration_specifiers_node : public ast_node {
  public:
    declaration_specifiers_node(storage_class_specifier_node* storage, declaration_specifiers_node* declSpec);
    declaration_specifiers_node(type_specifier_node* typeSpec, declaration_specifiers_node* declSpec);
    declaration_specifiers_node(type_qualifier_node* qualifier, declaration_specifiers_node* declSpec);
    ~declaration_specifiers_node();
    void init();
    void clear();
    void print();
    std::string generateCode();
  private:
    storage_class_specifier_node* storage;
    type_specifier_node* typeSpec;
    type_qualifier_node* qualifier;
    declaration_specifiers_node* declSpec;
};

class storage_class_specifier_node : public ast_node {
  public:
    storage_class_specifier_node();
    storage_class_specifier_node(SpecName::Storage storeType);
    void clear();
    void print();
    std::string generateCode();
  private:
    SpecName::Storage storeType;
};

class type_specifier_node : public ast_node {
  public:
    type_specifier_node();
    type_specifier_node(TypeSpecifier::Type type);
    void clear();
    void print();
    std::string generateCode();
  private:
    TypeSpecifier::Type type;
};

class type_qualifier_node : public ast_node {
  public:
    type_qualifier_node();
    type_qualifier_node(SpecName::Qualifier qual);
    void clear();
    void print();
    std::string generateCode();
  private:
    SpecName::Qualifier qual;
};
class type_qualifier_list_node : public ast_node {
public:
  type_qualifier_list_node();
  type_qualifier_list_node(type_qualifier_node* child);
  ~type_qualifier_list_node();
  void addQual(type_qualifier_node* child);
  std::vector<type_qualifier_node*> getChildren() const;
  void clear();
  void print();
  std::string generateCode();
private:
  std::vector<type_qualifier_node*> children;
};

class struct_or_union_specifier_node : public ast_node {
  public:
     struct_or_union_specifier_node(struct_or_union_node* structUnion,std::string identifier, struct_declaration_list_node* structDecl);
     void clear();
     void print();
     std::string generateCode();
  private:
    struct_or_union_node* structUnion;
    std::string identifier;
    struct_declaration_list_node* structDecl;
};

class struct_or_union_node : public ast_node {
  public:
    struct_or_union_node(StructUnion::Type type);
    void clear();
    void print();
    std::string generateCode();
  private:
    StructUnion::Type type;
};

class struct_declaration_list_node : public ast_node {
public:
  struct_declaration_list_node();
  struct_declaration_list_node(struct_declaration_node* child);
  void addStrDecl(struct_declaration_node* child);
  std::vector<struct_declaration_node*> getChildren() const;
  void clear();
  void print();
  std::string generateCode();
private:
  std::vector<struct_declaration_node*> children;
};

class struct_declaration_node : public ast_node {
  public:
   struct_declaration_node(specifier_qualifier_list_node* spqlist, struct_declarator_list_node* strDeclList);
   void clear();
   void print();
   std::string generateCode();
  private:
    specifier_qualifier_list_node* spqlist;
    struct_declarator_list_node* strDeclList;
};

class struct_declarator_list_node : public ast_node {
public:
  struct_declarator_list_node();
  struct_declarator_list_node(struct_declarator_node* child);
  void addStrDecl(struct_declarator_node* child);
  std::vector<struct_declarator_node*> getChildren() const;
  void clear();
  void print();
  std::string generateCode();
private:
  std::vector<struct_declarator_node*> children;
};

class struct_declarator_node : public ast_node {
  public:
    struct_declarator_node(declarator_node* decl, constant_expression_node* constExpr);
    void clear();
    void print();
    std::string generateCode();
  private:
    declarator_node* decl;
    constant_expression_node* constExpr;
};

class specifier_qualifier_list_node : public ast_node {
  public:
    specifier_qualifier_list_node(type_specifier_node* spec, specifier_qualifier_list_node* sqlist);
    specifier_qualifier_list_node(type_qualifier_node* qual, specifier_qualifier_list_node* sqlist);
    ~specifier_qualifier_list_node();
    void init();
    Spec* getSpec();
    void clear();
    void print();
    std::string generateCode();
  private:
    specifier_qualifier_list_node* sqlist;
    type_specifier_node* spec;
    type_qualifier_node* qual;
};

class enum_specifier_node : public ast_node {
  public:
    enum_specifier_node();
    //init as null if not used
    enum_specifier_node(identifier_node* identifier, enumerator_list_node* enm);
    void clear();
    void print();
    std::string generateCode();
  private:
    enumerator_list_node* enumList;
    identifier_node* identifier;
};

class enumerator_list_node : public ast_node {
  public:
    enumerator_list_node();
    enumerator_list_node(enum_specifier_node* child);
    void addEnumSpec(enum_specifier_node* child);
    std::vector<enum_specifier_node*> getChildren() const;
    void clear();
    void print();
    std::string generateCode();
  private:
    std::vector<enum_specifier_node*> children;
};//

class enumerator_node : public ast_node {
  public:
    enumerator_node();
    enumerator_node(identifier_node* identifier, constant_expression_node* constExpr);
    void clear();
    void print();
    std::string generateCode();
  private:
    identifier_node* identifier;
    constant_expression_node* constExpr;
};

class declarator_node : public ast_node {
  public:
    declarator_node(pointer_node* pointer, direct_declarator_node* directDecl);
    ~declarator_node();
    Spec* getSpec();
    void clear();
    void print();
    std::string generateCode();
  private:
    direct_declarator_node* directDecl;
    pointer_node* pointer;
};

class direct_declarator_node : public ast_node {
  public:
    direct_declarator_node(identifier_node* identifier);
    direct_declarator_node(DirectType::Type direct_type, direct_declarator_node* direct_declarator, constant_expression_node* constExpr);
    direct_declarator_node(DirectType::Type direct_type, direct_declarator_node* direct_declarator);
    direct_declarator_node(DirectType::Type direct_type, direct_declarator_node* direct_declarator, parameter_type_list_node* paramList);
    direct_declarator_node(DirectType::Type direct_type, direct_declarator_node* direct_declarator, identifier_list_node* idList);
    ~direct_declarator_node();
    void init();

    Spec* getSpec();
    void clear();
    void print();
    std::string generateCode();
    std::string generateArrayCode();
    std::string getName();

  private:
    identifier_node* identifier;
    declarator_node* declarator;
    direct_declarator_node* direct_declarator;
    constant_expression_node* constExpr;
    parameter_type_list_node* paramList;
    identifier_list_node* idList;
    DirectType::Type direct_type;
    int mode;
};

class pointer_node : public ast_node {
  public:
    pointer_node(type_qualifier_list_node* typeQualList, pointer_node* pointer);
    ~pointer_node();
    void clear();
    void print();
    std::string generateCode();

  private:
    type_qualifier_list_node* typeQualList;
    pointer_node* pointer;
};

class parameter_type_list_node : public ast_node {
  public:
    parameter_type_list_node(parameter_list_node* paramList);
    ~parameter_type_list_node();
    void clear();
    void print();
    std::string generateCode();
  private:
    parameter_list_node* paramList;
};

class parameter_list_node : public ast_node {
public:
  parameter_list_node();
  parameter_list_node(parameter_declaration_node* child);
  ~parameter_list_node();
  void addParamDecl(parameter_declaration_node* child);
  std::vector<parameter_declaration_node*> getChildren() const;
  void clear();
  void print();
  std::string generateCode();
private:
  std::vector<parameter_declaration_node*> children;
};

class parameter_declaration_node : public ast_node {
  public:
    parameter_declaration_node(declaration_specifiers_node* declSpec);
    parameter_declaration_node(declaration_specifiers_node* declSpec, declarator_node* decl);
    parameter_declaration_node(declaration_specifiers_node* declSpec, abstract_declarator_node* absDecl);
    ~parameter_declaration_node();
    void clear();
    void print();
    void init();
    std::string generateCode();
  private:
    declaration_specifiers_node* declSpec;
    declarator_node* decl;
    abstract_declarator_node* absDecl;
};

class identifier_list_node : public ast_node {
public:
  identifier_list_node();
  identifier_list_node(std::string child);
  ~identifier_list_node();
  void addIdentifier(std::string child);
  std::vector<std::string> getChildren() const;
  void clear();
  void print();
  std::string generateCode();
private:
  std::vector<std::string> children;
};

class initializer_node : public ast_node {
  public:
    initializer_node(assignment_expression_node* assignExpr);
    initializer_node(initializer_list_node* initList);
    ~initializer_node();
    void init();
    std::vector<Spec*> getSpecs();
    Spec* getSpec();
    void clear();
    void print();
    std::string generateCode();

  private:
    assignment_expression_node* assignExpr;
    initializer_list_node* initList;
};

class initializer_list_node : public ast_node {
 public:
   initializer_list_node();
   initializer_list_node(initializer_node* child);
   ~initializer_list_node();
   void addInit(initializer_node* child);
   std::vector<initializer_node*> getChildren() const;

   Spec* getSpec();
   std::vector<Spec*> getSpecs();
   void clear();
   void print();
   std::string generateCode();
 private:
   std::vector<initializer_node*> children;
};

class type_name_node : public ast_node {
  public:
    type_name_node(specifier_qualifier_list_node* specQualList, abstract_declarator_node* absDecl);
    void clear();
    void print();
    std::string generateCode();
  private:
    specifier_qualifier_list_node* specQualList;
    abstract_declarator_node* absDecl;
};

class abstract_declarator_node : public ast_node {
  public:
    abstract_declarator_node(pointer_node* pointer,direct_abstract_declarator_node* directAbs);
    void clear();
    void print();
    std::string generateCode();
  private:
    pointer_node* pointer;
    direct_abstract_declarator_node* directAbs;
};

class direct_abstract_declarator_node: public ast_node{
public:
  direct_abstract_declarator_node();
  ~direct_abstract_declarator_node();
  void clear();
  void print();
  std::string generateCode();
private:
};

class statement_node : public ast_node {
  public:
    statement_node(labeled_statement_node* labelStmt);
    statement_node(compound_statement_node* compStmt);
    statement_node(expression_statement_node* exprStmt);
    statement_node(selection_statement_node* selectStmt);
    statement_node(iteration_statement_node* iterStmt);
    statement_node(jump_statement_node* jumpStmt);
    ~statement_node();
    void init();
    void clear();
    void print();
    std::string generateCode();
  private:
    labeled_statement_node* labelStmt;
    compound_statement_node* compStmt;
    expression_statement_node* exprStmt;
    selection_statement_node* selectStmt;
    iteration_statement_node* iterStmt;
    jump_statement_node* jumpStmt;
    int mode;
};


class labeled_statement_node : public ast_node {
  public:
    labeled_statement_node(std::string identifier, statement_node* statement);
    labeled_statement_node(LabelType::Type label_type, constant_expression_node* constExpr, statement_node* statement);
    ~labeled_statement_node();
    void init();
    void clear();
    void print();
    std::string generateCode();
  private:
    LabelType::Type label_type;
    std::string identifier;
    constant_expression_node* constExpr;
    statement_node* statement;
};

class expression_statement_node : public ast_node {
  public:
    expression_statement_node();
    expression_statement_node(expression_node* expr);
    ~expression_statement_node();
    void init();
    void clear();
    void print();
    std::string generateCode();
  private:
    expression_node* expr;
};

class compound_statement_node : public ast_node {
  public:
    compound_statement_node(declaration_list_node* declList, statement_list_node* stateList);
    ~compound_statement_node();
    void init();
    void clear();
    void print();
    std::string generateCode();
  private:
    statement_list_node* stateList;
    declaration_list_node* declList;
};

class statement_list_node : public ast_node {
 public:
   statement_list_node();
   statement_list_node(statement_node* child);
   ~statement_list_node();
   void addStmt(statement_node* child);
   std::vector<statement_node*> getChildren() const;
   void clear();
   void print();
   std::string generateCode();
 private:
   std::vector<statement_node*> children;
};

class selection_statement_node : public ast_node {
  public:
    selection_statement_node(SelecType::Type selec_type, expression_node* expr,
      statement_node* statement1,statement_node* statement2);
    ~selection_statement_node();
    void init();
    void clear();
    void print();
    std::string generateCode();

  private:
    SelecType::Type selec_type;
    expression_node* expr;
    statement_node *statement1, *statement2;
    int else_id;
};

class iteration_statement_node : public ast_node {
  public:
    iteration_statement_node(IterType::Type iter_type, expression_node* expr1,
      statement_node* statement);
    iteration_statement_node(IterType::Type iter_type, expression_node* expr1,
      expression_node* expr2,expression_node* expr3,statement_node* statement);
    ~iteration_statement_node();
    void init();
    void clear();
    void print();
    std::string generateCode();

  private:
    IterType::Type iter_type;
    expression_node *expr1, *expr2, *expr3;
    statement_node* statement;
    int mode;
};

class jump_statement_node : public ast_node {
  public:
    jump_statement_node(std::string identifier);
    jump_statement_node(JumpType::Type jump_type);
    jump_statement_node(expression_node* expr);
    ~jump_statement_node();
    void init();
    void clear();
    void print();
    std::string generateCode();
  private:
    std::string identifier;
    expression_node* expr;
    JumpType::Type jump_type;
    int mode;
    int label_id;
};

class expression_node: public ast_node {
public:
  expression_node();
  expression_node(assignment_expression_node* child);
  ~expression_node();
  void addAssignmentExpr(assignment_expression_node* child);
  std::vector<assignment_expression_node*> getChildren() const;

  Spec* getSpec();
  void clear();
  void print();
  std::string generateCode();
private:
  std::vector<assignment_expression_node*> children;
};

class assignment_expression_node : public ast_node {
  public:
    assignment_expression_node(conditional_expression_node* cond_expr);
    assignment_expression_node(unary_expression_node* unary_expr,
      assignment_operator_node* assign_op, assignment_expression_node* assign_expr);
    ~assignment_expression_node();
    void init();

    Spec* getSpec();
    void clear();
    void print();
    std::string generateCode();
  private:
    conditional_expression_node* cond_expr;
    unary_expression_node* unary_expr;
    assignment_operator_node* assign_op;
    assignment_expression_node* assign_expr;
    int mode;
};

namespace AssignType{
  enum Type{EQUAL,MUL_ASSIGN,DIV_ASSIGN,MOD_ASSIGN,ADD_ASSIGN,SUB_ASSIGN,
    LEFT_ASSIGN,RIGHT_ASSIGN,AND_ASSIGN,XOR_ASSIGN,OR_ASSIGN};
}

class assignment_operator_node : public ast_node {
  public:
    assignment_operator_node();
    assignment_operator_node(AssignType::Type op);
    void clear();
    void print();
    std::string generateCode();
  private:
    int op;
};

class constant_expression_node : public ast_node {
  public:
    constant_expression_node(conditional_expression_node* condExpr);
    ~constant_expression_node();
    void init();

    Spec* getSpec();
    void clear();
    void print();
    std::string generateCode();
  private:
    conditional_expression_node* condExpr;
};

class conditional_expression_node : public ast_node {
  public:
    conditional_expression_node(logical_or_expression_node* logOrExpr);
    conditional_expression_node(logical_or_expression_node* logOrExpr, expression_node* expr, conditional_expression_node* condExpr);
    ~conditional_expression_node();
    void init();

    Spec* getSpec();
    void clear();
    void print();
    std::string generateCode();
  private:
    conditional_expression_node* condExpr;
    expression_node* expr;
    logical_or_expression_node* logOrExpr;
    int mode;
};


//////////////////// Beginning of binary operations ////////////////////////////
class logical_or_expression_node : public ast_node {
  public:
    logical_or_expression_node(logical_and_expression_node* logAndExpr);
    logical_or_expression_node(logical_or_expression_node* logOrExpr,
            OpType::Type op, logical_and_expression_node* logAndExpr);
    ~logical_or_expression_node();
    void init();

    Spec* getSpec();
    void clear();
    void print();
    std::string generateCode();
  private:
    logical_and_expression_node* logAndExpr;
    logical_or_expression_node* logOrExpr;
    OpType::Type op;
    int mode;
};

class logical_and_expression_node : public ast_node {
  public:
    logical_and_expression_node(inclusive_or_expression_node* iorExpr);
    logical_and_expression_node(logical_and_expression_node* logAndExpr, OpType::Type op, inclusive_or_expression_node* iorExpr);
    ~logical_and_expression_node();
    void init();

    Spec* getSpec();
    void clear();
    void print();
    std::string generateCode();
  private:
    inclusive_or_expression_node* iorExpr;
    logical_and_expression_node* logAndExpr;
    OpType::Type op;
    int mode;
};

class inclusive_or_expression_node : public ast_node {
  public:
    inclusive_or_expression_node(exclusive_or_expression_node* exorExpr);
    inclusive_or_expression_node(inclusive_or_expression_node* iorExpr, OpType::Type op, exclusive_or_expression_node* exorExpr);
    ~inclusive_or_expression_node();
    void init();

    Spec* getSpec();
    void clear();
    void print();
    std::string generateCode();
  private:
    exclusive_or_expression_node* exorExpr;
    inclusive_or_expression_node* iorExpr;
    OpType::Type op;
    int mode;
};

class exclusive_or_expression_node : public ast_node {
  public:
    exclusive_or_expression_node(and_expression_node* andExpr);
    exclusive_or_expression_node(exclusive_or_expression_node* exorExpr, OpType::Type op, and_expression_node* andExpr);
    ~exclusive_or_expression_node();
    void init();

    Spec* getSpec();
    void clear();
    void print();
    std::string generateCode();
  private:
    and_expression_node* andExpr;
    exclusive_or_expression_node* exorExpr;
    OpType::Type op;
    int mode;
};
class and_expression_node : public ast_node {
  public:
    and_expression_node(equality_expression_node* equalExpr);
    and_expression_node(and_expression_node* andExpr, OpType::Type op, equality_expression_node* equalExpr);
    ~and_expression_node();
    void init();

    Spec* getSpec();
    void clear();
    void print();
    std::string generateCode();
  private:
    and_expression_node* andExpr;
    equality_expression_node* equalExpr;
    OpType::Type op;
    int mode;
};

class equality_expression_node : public ast_node {
  public:
    equality_expression_node(relational_expression_node* relExpr);
    equality_expression_node(equality_expression_node* equalExpr, OpType::Type op, relational_expression_node* relExpr);
    ~equality_expression_node();

    void init();

    Spec* getSpec();
    void clear();
    void print();
    std::string generateCode();
  private:
    equality_expression_node* equalExpr;
    relational_expression_node* relExpr;
    OpType::Type op;
    int mode;
};

class relational_expression_node : public ast_node {
  public:
    relational_expression_node(shift_expression_node* shiftExpr);
    relational_expression_node(relational_expression_node* relExpr, OpType::Type op, shift_expression_node* shiftExpr);
    ~relational_expression_node();
    void init();

    Spec* getSpec();
    void clear();
    void print();
    std::string generateCode();
  private:
    relational_expression_node* relExpr;
    shift_expression_node* shiftExpr;
    OpType::Type op;
    int mode;
};

class shift_expression_node : public ast_node {
  public:
    shift_expression_node(additive_expression_node* addExpr);
    shift_expression_node(shift_expression_node* shiftExpr, OpType::Type op, additive_expression_node* addExpr);
    ~shift_expression_node();
    void init();

    Spec* getSpec();
    void clear();
    void print();
    std::string generateCode();
  private:
    shift_expression_node* shiftExpr;
    additive_expression_node* addExpr;
    OpType::Type op;
    int mode;
};

class additive_expression_node : public ast_node {
  public:
    additive_expression_node(multiplicative_expression_node* multiExpr);
    additive_expression_node(additive_expression_node* addExpr, OpType::Type op, multiplicative_expression_node* multiExpr);
    ~additive_expression_node();
    void init();

    Spec* getSpec();
    void clear();
    void print();
    std::string generateCode();
  private:
    multiplicative_expression_node* multiExpr;
    additive_expression_node* addExpr;
    OpType::Type op;
    int mode;
};

class multiplicative_expression_node : public ast_node {
  public:
    multiplicative_expression_node(cast_expression_node* castExpr);
    multiplicative_expression_node(multiplicative_expression_node* multiExpr, OpType::Type op, cast_expression_node* castExpr);
    ~multiplicative_expression_node();
    void init();

    Spec* getSpec();
    void clear();
    void print();
    std::string generateCode();
  private:
    cast_expression_node* castExpr;
    multiplicative_expression_node* multiExpr;
    OpType::Type op;
    int mode;
};
////////////////////////////////////////////////////////////////////////////////


class cast_expression_node : public ast_node {
  public:
    cast_expression_node(unary_expression_node* unaryExpr);
    cast_expression_node(type_name_node* typeName, cast_expression_node* castExpr);
    ~cast_expression_node();
    Spec* getSpec();
    void clear();
    void print();
    std::string generateCode();
  private:
    unary_expression_node* unaryExpr;
    cast_expression_node* castExpr;
    type_name_node* typeName;
};

class unary_expression_node : public ast_node {
  public:
    unary_expression_node(postfix_expression_node* postExpr);
    unary_expression_node(OpType::Type op, unary_expression_node* unaryExpr);
    unary_expression_node(unary_operator_node* unaryOp, cast_expression_node* castExpr);
    ~unary_expression_node();
    std::string getOpStr() const;
    void init();

    Spec* getSpec();
    void clear();
    void print();
    std::string generateCode();
  private:
    postfix_expression_node* postExpr;
    OpType::Type op;
    unary_operator_node* unaryOp;
    unary_expression_node* unaryExpr;
    cast_expression_node* castExpr;
    int mode;
};

class unary_operator_node : public ast_node {
  public:
    unary_operator_node(OpType::Type op);

    Spec* getSpec();
    void clear();
    void print();
    std::string generateCode();
  private:
    OpType::Type op;
};

class postfix_expression_node : public ast_node {
  public:
    postfix_expression_node();
    postfix_expression_node(primary_expression_node* primayExpr);
    postfix_expression_node(postfix_expression_node* postExpr, expression_node* expr); // array
    postfix_expression_node(postfix_expression_node* postExpr); // array w/o expr
    postfix_expression_node(postfix_expression_node* postExpr, argument_expression_list_node* argExpr); // function call
    postfix_expression_node(postfix_expression_node* postExpr, OpType::Type op, std::string identifier); // ptr or dot
    postfix_expression_node(postfix_expression_node* postExpr, OpType::Type op); // inc or dec
    ~postfix_expression_node();
    void init();
    Spec* getSpec();
    Spec* getArraySpec();
    Spec* getFunctionSpec();
    Spec* getStructUnionSpec();
    identifier_node* getIdentifier() const;
    primary_expression_node* getPrimaryExpr() const;
    void getExprs(std::vector<expression_node*>& exprs);
    void print();
    void clear();
    void printStructUnion();
    void printFunction();
    void printArray();
    std::string generateCode();
    std::string generateArrayCode();
    std::string generateFunctionCode();
    std::string generatePostfixedCode();

  protected:
    int mode;
    identifier_node* identifierNode;
    primary_expression_node* primayExpr;
    postfix_expression_node* postExpr;
    expression_node* expr;
    argument_expression_list_node* argExpr;
    OpType::Type op;
    std::string identifier;
    int op_node_id;
};

// This class is specifically for array accesses
// Note that it is derived from postfix_expression_node
class array_access_node : public postfix_expression_node {
  public:
    array_access_node(postfix_expression_node* postExpr, expression_node* expr,
                      constant_expression_node* arraySizeNode);
  private:
    constant_expression_node* arraySizeNode;
};

class primary_expression_node: public ast_node {
  public:
    primary_expression_node(identifier_node* identifier);
    primary_expression_node(constant_node* constant);
    primary_expression_node(string_node* string);
    primary_expression_node(expression_node* expr);
    ~primary_expression_node();
    void init();
    bool isIdentifier() const;
    identifier_node* getIdentifier() const;
    Spec* getSpec();
    void clear();
    void print();
    std::string generateCode();
  private:
    identifier_node* identifier;
    constant_node* constant;
    string_node* string;
    expression_node* expr;
    int mode;
};

class argument_expression_list_node : public ast_node {
public:
  argument_expression_list_node();
  argument_expression_list_node(assignment_expression_node* child);
  ~argument_expression_list_node();
  void addAssignmentExpr(assignment_expression_node* child);
  std::vector<assignment_expression_node*> getChildren() const;

  Spec* getSpec();
  void clear();
  void print();
  std::string generateCode();
private:
  std::vector<assignment_expression_node*> children;
};

class constant_node : public ast_node {
public:
  constant_node(int ival);
  constant_node(char cval);
  constant_node(float fval);
  int getIval() const;
  char getCval() const;
  float getFval() const;
  void setIval(int ival);
  void setCval(char cval);
  void setFval(float fval);
  std::string toStr();
  Spec* getSpec();
  void clear();
  void print();
  std::string generateCode();

private:
  int ival;
  char cval;
  float fval;
  ConstType::Type type;
};

class string_node : public ast_node {
  public:
    string_node();
    string_node(std::string string_literal);
    std::string getStringLiteral();
    void setStringLiteral(std::string string_literal);
    Spec* getSpec();
    void clear();
    void print();
    std::string generateCode();

  private:
    std::string string_literal;
};

class identifier_node: public ast_node {
  public:
    identifier_node(std::string name, SymbolNode* symnode, int line, int col);
    ~identifier_node();
    void setSymNode(SymbolNode* sym);
    int getLine() const;
    int getCol() const;
    SymbolNode* getSymNode() const;
    std::string getName() const;
    Spec* getSpec();
    void clear();
    void print();
    std::string generateCode();
  private:
    std::string id_name;
    SymbolNode *id_symnode;
    int line;
    int col;
};
#endif
