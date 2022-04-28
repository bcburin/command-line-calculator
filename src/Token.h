#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <ostream>

class Token {
  private:
    std::string m_str;
  public:
    Token(std::string str);
    inline std::string str() const { return m_str; }
    // Overload equality and inequality
    virtual bool operator==(const Token& other);
    virtual bool operator!=(const Token& other);
};

// Write to ostream
std::ostream& operator<<(std::ostream& os, const Token& token);

#endif