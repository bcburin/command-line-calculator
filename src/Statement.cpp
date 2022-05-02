#include "Statement.h"
#include "SyntaxTree.h"
#include "Helpers.h"

/* STATEMENT */

Statement::Statement(std::string str): m_str(str) {}


/* EXPRESSION */

Expression::Expression(std::string str): Statement(str), m_result(0) {}

void Expression::execute() {  m_result = evaluate(str()); }

double Expression::evaluate(std::string str) {
  SyntaxTree stree(str);
  return stree.result();
}


/* DELETE STATEMENT */

DeleteStatement::DeleteStatement(std::string str): Statement(str), m_variable(str.substr(7)) {}

void DeleteStatement::execute() { Variable::remove(m_variable); }


/* MULTILINE STATEMENT */

MultilineStatement::MultilineStatement(std::string str, std::vector<Statement*> nested_statements)
: Statement(str), m_nested_statements(nested_statements) {}


/* IF STATEMENT */

IfStatement::IfStatement(std::string str, std::vector<Statement*> nested_statements)
: MultilineStatement(str, nested_statements), m_condition(str.substr(3)) {}

void IfStatement::execute() {
  if( Expression::evaluate(m_condition) ) {
    for (const auto& statement : nested_statements() ) {
      statement->execute();
    }
  }
}


/* WHILE STATEMENT */

WhileStatement::WhileStatement(std::string str, std::vector<Statement*> nested_statements)
: MultilineStatement(str, nested_statements), m_condition(str.substr(6)) {}

void WhileStatement::execute() {
  while( Expression::evaluate(m_condition) ) {
    for (const auto& statement : nested_statements() ) {
      statement->execute();
    }
  }
}


/* FOR STATEMENT */

ForStatement::ForStatement(std::string str, std::vector<Statement*> nested_statements)
: MultilineStatement(str, nested_statements) {
  // Remove "for" keyword and trim result
  str = str.substr(4);
  str = trim(str);
  // Find first comma operator
  int index = str.find(",");
  // Throw error if not found
  if(index == std::string::npos) throw std::invalid_argument("Expected ',' separator in for loop.");
  // Build initializator string if found
  m_init = str.substr(0,index);
  // Find second comma operator
  str = str.substr(index+1);
  index = str.find(",");
  // Throw error if not found
  if(index == std::string::npos) throw std::invalid_argument("Expected second ',' separator in for loop.");
  // Build condition and increment strings if found
  m_condition = str.substr(0, index);
  m_increase = str.substr(index+1);
}

void ForStatement::execute() {
  Expression::evaluate(m_init);
  while( Expression::evaluate(m_condition) ) {
    for (const auto& statement : nested_statements() ) {
      statement->execute();
    }
    Expression::evaluate(m_increase);
  }
}


