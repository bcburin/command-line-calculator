#include "Operator.h"
#include "OperatorDefinitions.h"

std::set<Operator> Operator::set = {
  Operator("==", 0, __eq__),
  Operator("!=", 1, __ne__),
  Operator(">", 2, __gt__),
  Operator("<", 3, __lt__),
  Operator(">=", 4, __ge__),
  Operator("<=", 5, __le__),
  Operator("+=", 8, __assign_sum__),
  Operator("-=", 9, __assign_sub__),
  Operator("*=", 10, __assign_mul__),
  Operator("%=", 11, __assign_mod__),
  Operator("//=", 12, __assign_trunc__),
  Operator("/=", 13, __assign_div__),
  Operator("^=", 14, __assign_pow__),
  Operator("=", 16, __assing__),
  Operator("+", 24, __sum__),
  Operator("-", 32, __sub__),
  Operator("*", 40, __mul__),
  Operator("%", 46, __mod__),
  Operator("//", 47, __trunc__),
  Operator("/", 48, __div__),
  Operator("^", 56, __pow__)
};


Operator::Operator(): Token("") {}


Operator::Operator(std::string str, int priority, std::function<Operand*(const Operand*, const Operand*)> apply)
: Token(str), m_priority(priority), m_apply(apply) {}


Operator::Operator(const Operator& other)
: Token(other.str()), m_priority(other.m_priority), m_apply(other.m_apply) {}


Operator::Operator(const Operator&& other)
: Token(other.str()), m_priority(other.m_priority), m_apply(other.m_apply) {}


Operator Operator::operator=(const Operator& other) { return Operator(other); }
Operator Operator::operator=(const Operator&& other) { return Operator(other); }


bool Operator::operator==(const Operator& other) { return str() == other.str() && priority() == other.priority(); }
bool Operator::operator!=(const Operator& other) { return !(*this == other); }
// bool Operator::operator<(const Operator& other) { return priority() < other.priority(); }
bool Operator::operator>(const Operator& other) { return priority() > other.priority(); }
bool Operator::operator<=(const Operator& other) { return *this < other || *this == other; }
bool Operator::operator>=(const Operator& other) { return *this > other || *this == other; }


Operand* Operator::operator()(const Operand* operand1, const Operand* operand2) {
  return m_apply(operand1, operand2);
}


bool operator<(const Operator& op1, const Operator& op2) { return op1.priority() < op2.priority(); }