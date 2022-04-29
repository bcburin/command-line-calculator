#ifndef OPERATOR_H
#define OPERATOR_H

#include <string>
#include <initializer_list>
#include <functional>
#include <set>
#include "Token.h"
#include "Operand.h"

class Operator: public Token {
  private:
    int m_priority;
    std::function<double(double, double)> m_apply;
  public:
    static std::set<Operator> set;
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
    // bool operator<(const Operator& other);
    bool operator>(const Operator& other);
    bool operator<=(const Operator& other);
    bool operator>=(const Operator& other);
    /* Return new Operand, result of the operation on two Operand inputs */
    Operand operator()(const Operand& operand1, const Operand& operand2);
};

/* Sorting struct to allow construction of sets (and other STL containers) of Operator objects */
// struct SortOperators final { bool operator()(const Operator&, const Operator&) const; };

bool operator<(const Operator&, const Operator&);

#endif