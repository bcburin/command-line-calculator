#include "Operand.h"
#include <execution>

// Operand::Operand(): Operand(0) {}


Operand::Operand(std::string str): Token(str) {
  try { m_value = std::stod(str); }
  catch(...) { throw std::invalid_argument("Operand not conversible to double."); }
}


Operand::Operand(double value): Token(std::to_string(value)), m_value(value) {}


bool Operand::operator==(const Operand& other) { return value() == other.value(); }
bool Operand::operator!=(const Operand& other) { return !(*this == other); }
bool Operand::operator<(const Operand& other) { return value() < other.value(); }
bool Operand::operator>(const Operand& other) { return value() > other.value(); }
bool Operand::operator<=(const Operand& other) { return *this < other || *this == other; }
bool Operand::operator>=(const Operand& other) { return *this > other || *this == other; }