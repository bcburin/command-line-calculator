#ifndef OPERAND_H
#define OPERAND_H

#include <string>
#include "Token.h"

class Operand: public Token {
  private:
    double m_value;
  public:
    Operand();
    Operand(std::string str);
    Operand(double value);
    inline double value() const { return m_value; }
    /* Overloaded operators */
    bool operator!=(const Operand& other);
    bool operator==(const Operand& other);
    bool operator<(const Operand& other);
    bool operator>(const Operand& other);
    bool operator<=(const Operand& other);
    bool operator>=(const Operand& other);
};

#endif