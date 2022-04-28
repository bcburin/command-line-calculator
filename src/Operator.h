#ifndef OPERATOR_H
#define OPERATOR_H

#include <string>
#include <initializer_list>
#include <functional>
#include <map>
#include "Token.h"
#include "Operand.h"

class Operator: public Token {
  private:
    int m_priority;
    std::function<double(double, double)> m_apply;
  public:
    static std::map<int, Operator> map;
    // static bool is_operator(std::string op);
    inline int priority() const { return m_priority; }
    Operator();
    Operator(const Operator& other);
    Operator(const Operator&& other);
    Operator(std::string str, int priority, std::function<double(double, double)> apply);
    /* Copy and move assignments */
    Operator operator=(const Operator& other);
    Operator operator=(const Operator&& other);
    /* Overloaded operators */
    bool operator==(const Operator& other);
    bool operator!=(const Operator& other);
    bool operator<(const Operator& other);
    bool operator>(const Operator& other);
    bool operator<=(const Operator& other);
    bool operator>=(const Operator& other);
    Operand operator()(const Operand& operand1, const Operand& operand2);
};

#endif