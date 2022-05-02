#include <iostream>
#include <string>
#include <functional>
#include "SyntaxTree.h"
#include "Operator.h"
#include "Statement.h"
#include "Interface.h"


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
