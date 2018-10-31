#include "literals.hpp"

IntLiteral::IntLiteral(const char *x) {
  value = atoi(x);
}

CharLiteral::CharLiteral(const char *x) {
  value = x[0];
}

BoolLiteral::BoolLiteral(const char *x) {
  value = x[0] == 't';
}

StringLiteral::StringLiteral(const char *x) {
  value = string(x);
}

int IntLiteral::print() {
  printText(value);
  return pidcount;
}

int CharLiteral::print() {
  printText(value);
  return pidcount;
}

int BoolLiteral::print() {
  printText(value ? "true" : "false");
  return pidcount;
}

int StringLiteral::print() {
  printText(value);
  return pidcount;
}

Type IntLiteral::get_type() {
  return Type::_int;
}

Type CharLiteral::get_type() {
  return Type::_int;
}

Type BoolLiteral::get_type() {
  return Type::_boolean;
}

Type StringLiteral::get_type() {
  return Type::_int;
}
