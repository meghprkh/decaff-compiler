#include "base.hpp"
#include "statements.hpp"

class MethodDeclArg: public Base {
public:
  MethodDeclArg(Type _type, const char *_id);
  int print();
  void traverse();
private:
  Type type;
  string id;
};

class MethodDeclArgs: public Base {
public:
  MethodDeclArgs() {};
  void add(MethodDeclArg* arg);
  int print();
  void traverse();
private:
  deque<MethodDeclArg*> args;
};

class MethodDecl: public Base {
public:
  MethodDecl(Type _type, const char *_id, MethodDeclArgs* _args, Block* _block);
  MethodDecl(const char *_id, MethodDeclArgs* _args, Block* _block);
  int print();
  void traverse();
private:
  bool isVoid = true;
  Type type;
  string id;
  MethodDeclArgs* args;
  Block *block;
};

class MethodDecls: public Base {
public:
  MethodDecls() {};
  void add(MethodDecl* method_decl);
  int print();
  void traverse();
private:
  deque<MethodDecl*> list;
};
