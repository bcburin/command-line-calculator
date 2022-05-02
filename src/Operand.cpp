#include "Operand.h"
#include <execution>

/* OPERAND (ABSTRACT CLASS) DEFINITIONS */

Operand::Operand(std::string str): Token(str) {}


/* DOUBLE DEFINITIONS */

Double::Double(std::string str): Operand(str) {
  try { m_value = std::stod(str); }
  catch(...) { throw std::invalid_argument("Operand not convertible to double."); }
}

Double::Double(double value): Operand(std::to_string(value)), m_value(value) {}

double Double::value() const { return m_value; }

Operand* Double::clone() const  { return new Double(*this); }


/* VARIABLE DEFINITIONS */

Variable::Variable(std::string name): Operand(name) {
  // Variable name must start with letter or _ character
  if (!isalpha(name[0]) && name[0] != '_') 
    throw std::invalid_argument("Invalid variable name: '" + name + "' (must start with a letter or _ character).");
  
  // Variable name must be made up by letters, numbers or the _ character
  for (const auto& ch : name)
    if(!isalnum(ch) && ch != '_')
      throw std::invalid_argument("Invalid variable name: '" + name + "' (must contain letters, numbers or the _ character only).");
}

double Variable::value() const {
  if (!is_in_storage(name())) throw std::invalid_argument("Undefined variable: '" + name() + "'");
  return storage[name()]->value();
}

void Variable::set(const Operand* op) const { storage[name()] = op->clone(); }

bool Variable::is_in_storage(const std::string& name) { return storage.find(name) != storage.end(); }

Operand* Variable::clone() const  { return new Variable(*this); }

std::unordered_map<std::string, Operand*> Variable::storage = {};

void Variable::empty_storage() { 
  for (const auto& pair : storage) delete pair.second;
  storage.clear(); 
}

void Variable::add(std::string name, double value) {
  Double val(value);
  Variable var(name);
  var.set(&val);
}

void Variable::remove(std::string name) {
  if (!is_in_storage(name)) throw std::invalid_argument("Undefined variable: '" + name + "'");
  delete storage[name];
  storage.erase(name);
}


/*  OVERLOADED OPERATORS FOR OPERANDS */

bool operator==(const Operand& op1, const Operand& op2) { return op1.value() == op2.value(); }
bool operator!=(const Operand& op1, const Operand& op2) { return !(op1 == op2); }
bool operator<(const Operand& op1, const Operand& op2) { return op1.value() < op2.value(); }
bool operator>(const Operand& op1, const Operand& op2) { return op1.value() > op2.value(); }
bool operator<=(const Operand& op1, const Operand& op2) { return op1 < op2 || op1 == op2; }
bool operator>=(const Operand& op1, const Operand& op2) { return op1 > op2 || op1 == op2; }