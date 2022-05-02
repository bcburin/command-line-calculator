#include "Interface.h"
#include "Operand.h"

std::vector<Statement*> read_statemets(std::istream* is, std::ostream* os,  bool run, bool re_throw) {
  std::vector<Statement*> statement_list = {};
  std::string line;
  // If an ostream was given, output the '>>'  indicator
  if(os) *os << ">> ";
  // Read input from istream until reaching eof or specified "end" line
  while ( std::getline(*is, line) && trim(line) != "end" ) {
    try {
      // Trim line
      line = trim(line);
      // Determine statement
      Statement* statement = nullptr;
      // Check for null input
      if (line == "") {}
      // Check for if statement
      else if(line.find("if ")==0) {
        // Read nested statements
        std::vector<Statement*> nested_statements = read_statemets(is, os, false);
        // Create IfStatement object
        statement = new IfStatement(line, nested_statements);
      } 
      // Check for while statement
      else if(line.find("while ")==0) {
        // Read nested statements
        std::vector<Statement*> nested_statements = read_statemets(is, os, false);
        // Create WhileStatement object
        statement = new WhileStatement(line, nested_statements);
      }
      // Check for "for" operator
      else if(line.find("for ")==0) {
        // Read nested statements
        std::vector<Statement*> nested_statements = read_statemets(is, os, false);
        // Create ForStatement object
        statement = new ForStatement(line, nested_statements);
      }
      // Check for delete statement
      else if(line.find("delete ")==0) {
        statement = new DeleteStatement(line);
      }
      // Check for run statement
      else if(line.find("run ")==0) {
        statement = new RunStatement(line);
      }
      // Check for print statement
      else if(line.find("print ")==0) {
        statement = new PrintStatement(line,os);
      }
      // In the default case, the statement is interpreted as expression
      else {
        statement = new Expression(line, os, run);
      }

      // Execute if in run mode
      if (run) statement->execute();
      // Save statement if not in run mode
      if (!run) statement_list.push_back(statement);

    } catch (const std::invalid_argument& error) {
      if(os) *os << "   " << error.what() << std::endl;
      if(re_throw) throw error;
    }
    // If ostream was given, output ">>" indicator for next line
    if(os) *os << ">> ";
  }

  return statement_list;
}