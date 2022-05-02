#ifndef OPERAND_H
#define OPERAND_H

#include <string>
#include <unordered_map>
#include "Token.h"


/* ABSTRACT CLASS: OPERAND */

struct Operand: public Token { 
  Operand(std::string str);
  virtual double value() const = 0;
  virtual Operand* clone() const = 0;
};


/* CLASS DOUBLE */

class Double: public Operand {
  private:
    double m_value;
  public:
    Double(std::string str);
    Double(double value);
    double value() const override;
    Operand* clone() const override;
};


/* CLASS VARIABLE */

class Variable: public Operand {
  public:
    Variable(std::string name);
    /* Returs value stored */
    double value() const override;
    /* Sets a value for the variabe in the storage */
    void set(const Operand* op) const;
    /* Alias to Token::str() */
    inline std::string name() const { return str(); }
    /* Clones object */
    Operand* clone() const override;
    /* Empties static storage */
    static void empty_storage();
    /* Add and remove variables to the storage */
    static void add(std::string name, double value);
    static void remove(std::string name);
  private:
    /* Stores variable values */
    static std::unordered_map<std::string, Operand*> storage;
    /* Checks if variable is in the storage */
    static bool is_in_storage(const std::string& name);
};


/* OVERLOADED OPERATORS */

bool operator!=(const Operand& op1, const Operand& op2);
bool operator==(const Operand& op1, const Operand& op2);
bool operator<(const Operand& op1, const Operand& op2);
bool operator>(const Operand& op1, const Operand& op2);
bool operator<=(const Operand& op1, const Operand& op2);
bool operator>=(const Operand& op1, const Operand& op2);

#endif