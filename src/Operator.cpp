#include "Operator.h"

std::set<Operator> Operator::set = {
  Operator("+", 8, [](const Operand* x, const Operand* y){ return new Double(x->value()+y->value()); }),
  Operator("-", 16, [](const Operand* x, const Operand* y){ return new Double(x->value()-y->value()); }),
  Operator("*", 24, [](const Operand* x, const Operand* y){ return new Double(x->value()*y->value()); }),
  Operator("/", 32, [](const Operand* x, const Operand* y){ return new Double(x->value()/y->value()); }),
  /* Assignment operator */
  Operator("=", 0, [](const Operand* lhs, const Operand* rhs){ 
    auto var = dynamic_cast<const Variable*>(lhs);
    if(!var) { throw std::invalid_argument("Left hand side of assignment operator (" + lhs->str() + ") must be a variable."); }
    var->set(rhs);
    return new Double(rhs->value());
  })
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