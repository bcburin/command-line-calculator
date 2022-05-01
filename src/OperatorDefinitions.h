#ifndef OPERATORS_H
#define OPERATORS_H

#include "Operand.h"
#include <functional>
#include <exception>
#include <cmath>

using operator_function = std::function<Operand*(const Operand*, const Operand*)>;

operator_function __sum__ = [](const Operand* x, const Operand* y){
  if(!y) throw std::invalid_argument("Expected expression after + operator.");
  if(!x) return new Double(y->value());
  return new Double(x->value()+y->value()); 
};

operator_function __sub__ = [](const Operand* x, const Operand* y){ 
  if(!y) throw std::invalid_argument("Expected expression after - operator.");
  if(!x) return new Double(-y->value());
  return new Double(x->value()-y->value()); 
};

operator_function __mul__ = [](const Operand* x, const Operand* y){ 
  if(!y) throw std::invalid_argument("Expected expression after * operator.");
  if(!x) throw std::invalid_argument("Expected expression before * operator.");
  return new Double(x->value()*y->value());
};

operator_function __div__ = [](const Operand* x, const Operand* y){ 
  if(!y) throw std::invalid_argument("Expected expression after / operator.");
  if(!x) throw std::invalid_argument("Expected expression before / operator.");
  if(y->value() == 0) throw std::invalid_argument("Division by zero");
  return new Double(x->value()/y->value()); 
};

operator_function __trunc__ = [](const Operand* x, const Operand* y){ 
  if(!y) throw std::invalid_argument("Expected expression after // operator.");
  if(!x) throw std::invalid_argument("Expected expression before // operator.");
  if(y->value() == 0) throw std::invalid_argument("Division by zero");
  return new Double((int)(x->value()/y->value())); 
};

operator_function __mod__ = [](const Operand* x, const Operand* y){ 
  if(!y) throw std::invalid_argument("Expected expression after / operator.");
  if(!x) throw std::invalid_argument("Expected expression before / operator.");
  if(y->value() == 0) throw std::invalid_argument("Division by zero");
  return new Double(std::fmod(x->value(),y->value())); 
};

operator_function __pow__ = [](const Operand* x, const Operand* y){ 
  if(!y) throw std::invalid_argument("Expected expression after ^ operator.");
  if(!x) throw std::invalid_argument("Expected expression before ^ operator.");
  if(x->value() == 0 && y->value() == 0) throw std::invalid_argument("Power 0^0 undefined.");
  return new Double(std::pow(x->value(),y->value()));
};

operator_function __assing__ = [](const Operand* lhs, const Operand* rhs){ 
  if(!rhs) throw std::invalid_argument("Expected expression after = operator.");
  if(!lhs) throw std::invalid_argument("Expected variable before = operator.");
  // Check if left hand side operator is variable
  auto var = dynamic_cast<const Variable*>(lhs);
  if(!var) { 
    throw std::invalid_argument("Left hand side of assignment operator (" + lhs->str() + ") must be a variable."); 
  }
  var->set(rhs);
  return new Double(rhs->value());
};

operator_function operator_assign(std::string op_name, operator_function& __op__) {
  return [op_name, &__op__](const Operand* lhs, const Operand* rhs){ 
    if(!rhs) throw std::invalid_argument("Expected expression after " + op_name + " operator.");
    if(!lhs) throw std::invalid_argument("Expected variable before " + op_name + " operator.");
    // Check if left hand side operator is variable
    auto var = dynamic_cast<const Variable*>(lhs);
    if(!var) { 
      throw std::invalid_argument("Left hand side of assignment operator (" + lhs->str() + ") must be a variable."); 
    }
    // Create new operand
    Double* result = static_cast<Double*>(__op__(var,rhs));
    var->set(result);
    return result;
  };
}

operator_function __assign_sum__ = operator_assign("+=", __sum__);

operator_function __assign_sub__ = operator_assign("-=", __sub__);

operator_function __assign_mul__ = operator_assign("*=", __mul__);

operator_function __assign_div__ = operator_assign("/=", __div__);

operator_function __assign_pow__ = operator_assign("/=", __pow__);

operator_function __assign_mod__ = operator_assign("%=", __mod__);

operator_function __assign_trunc__ = operator_assign("//=", __trunc__);

#endif