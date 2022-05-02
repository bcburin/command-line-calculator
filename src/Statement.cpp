#include "Statement.h"
#include "SyntaxTree.h"
#include "Helpers.h"
#include "Interface.h"

/* STATEMENT */

Statement::Statement(std::string str): m_str(str) {}


/* EXPRESSION */

Expression::Expression(std::string str, std::ostream* os, bool run_mode)
: Statement(str), m_result(0), os(os), run_mode(run_mode) {}

void Expression::execute() {
  bool display_result = true;
  std::string str = Expression::str();
  // Check for trailing semicolon and set whether to display result
  if(str.back()==';') {
    str = str.substr(0,str.size()-1);
    display_result = false;
  }
  // Parse string
  m_result = evaluate(str);
  // Add result to global variable "_" 
  if(os) Variable::add("_", m_result);
  // Display result
  if(os && run_mode && display_result) *os << "   " << m_result << std::endl;
}

double Expression::evaluate(std::string str) {
  SyntaxTree stree(str);
  return stree.result();
}


/* DELETE STATEMENT */

DeleteStatement::DeleteStatement(std::string str): Statement(str), m_variable(str.substr(7)) {}

void DeleteStatement::execute() { Variable::remove(m_variable); }

/* RUN STATEMENT */

RunStatement::RunStatement(std::string str): Statement(str), arguments() {
  int index = str.find(":");
  if (index==std::string::npos) {
    // If ":" was not found in statement
    filename = trim(str.substr(4));
  } else {
    // Get filename between "run" and ":"
    filename = trim(str.substr(4,index-4));
    // Delete string before ":" (inclusive)
    str = str.substr(index+1);
    // Get arguments
    while ( (index = str.find(",")) != std::string::npos) {
      arguments.push_back( str.substr(0,index) );
      str = str.substr(index+1);
    }
    // Get last argument
    arguments.push_back(str);
  }
  filename = "scripts/" + filename + ".txt";
}

void RunStatement::execute() {
  std::ifstream script(filename);
  if(!script.is_open()) throw std::invalid_argument("No such file: '" + filename + "'");
  // Execute arguments
  for (const auto& arg : arguments) { 
    if(trim(arg)!="") Expression::evaluate(arg);
  }
  // Read and execute script
  read_statemets(&script, nullptr, true, true);
  // Close file
  script.close();
}


/* PRINT STATEMENT */

PrintStatement::PrintStatement(std::string str, std::ostream* os)
: Statement(str), expression(str.substr(6)), os(os) {}

void PrintStatement::execute() { 
  if(os) *os << "   " << Expression::evaluate(expression) << std::endl;
}


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


