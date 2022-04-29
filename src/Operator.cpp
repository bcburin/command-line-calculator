#include "Operator.h"

std::set<Operator> Operator::set = {
  {Operator("+", 0, [](double x, double y){ return x+y; })},
  {Operator("-", 1, [](double x, double y){ return x-y; })},
  {Operator("*", 2, [](double x, double y){ return x*y; })},
  {Operator("/", 3, [](double x, double y){ return x/y; })}
};


// bool Operator::is_operator(std::string op) { return map.find(op) != map.end(); }



Operator::Operator(): Token("") {}


Operator::Operator(std::string str, int priority, std::function<double(double, double)> apply)
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


Operand Operator::operator()(const Operand& operand1, const Operand& operand2) {
  return Operand(m_apply(operand1.value(), operand2.value()));
}


bool operator<(const Operator& op1, const Operator& op2) { return op1.priority() < op2.priority(); }