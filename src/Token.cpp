#include "Token.h"

Token::Token(std::string str): m_str(str) {}

bool Token::operator==(const Token& other) { return str() == other.str(); }

bool Token::operator!=(const Token& other) { return str() != other.str(); }

std::ostream& operator<<(std::ostream& os, const Token& token) {
  return os << token.str();
}