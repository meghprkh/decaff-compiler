#include "calls.hpp"

MethodCall::MethodCall(const char *_fn, MethodArgsList* _args) {
  fn = string(_fn);
  args = _args;
}

Callout::Callout(const char *_fn, CalloutArgsList* _args) {
  fn = string(_fn);
  args = _args;
}

void MethodArgsList::add(Expr *_e) {
  list.push_front(_e);
}

void CalloutArgsList::add(Expr *_e) {
  list.push_front(make_pair(_e, (StringLiteral*) NULL));
}

void CalloutArgsList::add(StringLiteral *_s) {
  list.push_front(make_pair((Expr*) NULL, _s));
}

int MethodCall::print() {
  int _args = args->print();
  printText(fn);
  printRelation(_args);
  return pidcount;
}

int MethodArgsList::print() {
  printText("MethodArgsList");
  int p = pidcount;
  for (auto e: list) {
    int _e = e->print();
    printRelation(p, _e);
  }
  return p;
}

int Callout::print() {
  int _args = args->print();
  printText(fn + ":callout");
  printRelation(_args);
  return pidcount;
}

int CalloutArgsList::print() {
  printText("CalloutArgsList");
  int p = pidcount;
  for (auto etmp: list) {
    auto e = etmp.first ? etmp.first : etmp.second;
    int _e = e->print();
    printRelation(p, _e);
  }
  return p;
}

Type MethodCall::get_type() {
  auto cdt = context.lookup(fn);
  if (cdt.isVoid)
    errors.push_back(Error(6, cdt.id + " used in expr even though returns void"));
  return cdt.type;
}

void MethodArgsList::traverse() {
  throw runtime_error("MethodArgsList traverse called without vector type");
}

void MethodArgsList::traverse(string method_name, vector<Type> types) {
  int i = 0;
  if (list.size() != types.size())
    errors.push_back(Error(5, method_name + " call differs in number of params"));
  for (auto e: list) {
    e->traverse();
    if (e->get_type() != types[i])
      errors.push_back(Error(5, method_name + " call, type of param " +
                                to_string(i) + " shall be " + typeToString(types[i])
                              ));
  }
}

void MethodCall::traverse() {
  auto cdt = context.lookup(fn);
  args->traverse(cdt.id, cdt.method_args);
}

void CalloutArgsList::traverse() {
  for (auto e: list) {
    if (e.first) e.first->traverse();
    else e.second->traverse();
  }
}

void Callout::traverse() {
  args->traverse();
}
