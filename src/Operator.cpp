#include "Operator.h"
#include "OperatorDefinitions.h"

std::set<Operator> Operator::set = {
  Operator("=", 7, __assing__),
  Operator("+", 8, __sum__),
  Operator("-", 16, __sub__),
  Operator("*", 24, __mul__),
  Operator("%", 30, __mod__),
  Operator("//", 31, __trunc__),
  Operator("/", 32, __div__),
  Operator("^", 40, __pow__),
  Operator("+=", 0, __assing_sum__),
  Operator("-=", 1, __assing_sub__),
  Operator("*=", 2, __assing_mul__),
  Operator("/=", 3, __assing_div__),
  Operator("^=", 4, __assing_pow__)
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