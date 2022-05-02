#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include "SyntaxTree.h"
#include "Operator.h"
#include "Statement.h"


std::vector<Statement*> read_statemets(std::istream* is = &std::cin, std::ostream* os = &std::cout, bool run=true);


int main(int argc, char **argv) {

  // Define starting variables
  Variable::add("PI", 3.14159);
  Variable::add("E", 2.71828);

  // Define variable to hold last result
  Variable::add("_",0);

  // Initialize interpreter
  read_statemets();

  // Free memory allocated for dynamic storage
  Variable::empty_storage();

  return 0;
}


std::vector<Statement*> read_statemets(std::istream* is, std::ostream* os,  bool run) {
  std::vector<Statement*> statement_list = {};
  std::string line;
  // If an ostream was given, output the '>>'  indicator
  if(os) *os << ">> ";
  // Read input from istream until reaching eof or specified "end" line
  while ( std::getline(*is, line) && trim(line) != "end" ) {
    try {
      // Trim line
      line = trim(line);
      // Check for trailing semicolon and set whether to display result
      bool display_result = true;
      if(line.back()==';') {
        line = line.substr(0,line.size()-1);
        display_result = false;
      }
      // Check for if statement
      if(line.find("if ")==0) {
        // Read nested statements
        std::vector<Statement*> nested_statements = read_statemets(is, os, false);
        // Create IfStatement object
        auto statement = new IfStatement(line, nested_statements);
        // Execute if in run mode
        if (run) statement->execute();
        // Save statement if not in run mode
        if (!run) statement_list.push_back(statement);
      } else 
      // Check for while statement
      if(line.find("while ")==0) {
        // Read nested statements
        std::vector<Statement*> nested_statements = read_statemets(is, os, false);
        // Create WhileStatement object
        auto statement = new WhileStatement(line, nested_statements);
        // Execute if in run mode
        if (run) statement->execute();
        // Save statement if not in run mode
        if (!run) statement_list.push_back(statement);
      } else 
      // Check for "for" operator
      if(line.find("for ")==0) {
        // Read nested statements
        std::vector<Statement*> nested_statements = read_statemets(is, os, false);
        // Create ForStatement object
        auto statement = new ForStatement(line, nested_statements);
        // Execute if in run mode
        if (run) statement->execute();
        // Save statement if not in run mode
        if (!run) statement_list.push_back(statement);
      } else
      // Check for delete statement
      if(line.find("delete ")==0) {
        // Create object
        auto statement = new DeleteStatement(line);
        // Execute if in run mode
        if (run) statement->execute();
        // Save statement if not in run mode
        if (!run) statement_list.push_back(statement);
      } else
      // In the default case, the statement is interpreted as expression
      {
        auto exp = new Expression(line);
        statement_list.push_back(exp);
        // If in run mode, evaluate expression and output result in the given ostream
        if(run) { 
          exp->execute();
          if(os && display_result) *os << "   " << exp->result() << std::endl;
        }
      }
    } catch (const std::invalid_argument& error) {
      if(os) *os << "   " << error.what() << std::endl;
    }
    // If ostream was given, output ">>" indicator for next line
    if(os) *os << ">> ";
  }

  return statement_list;
}