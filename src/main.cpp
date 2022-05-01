#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include "SyntaxTree.h"
#include "Operator.h"

using namespace std;


int main(int argc, char **argv) {

  string input;

  // Define starting variables
  Variable::add("PI", 3.14159);
  Variable::add("E", 2.71828);
  // Define variable to hold last result
  Variable::add("_",0);

  while(true) { 
    bool show_output = true;
    cout << ">> ";
    std::getline(std::cin, input);

    if(input == "") continue;

    if(input.back() == ';') {
      input = input.substr(0, input.size()-1);
      show_output = false;
    }

    if(input == "exit()") break;
    
    try{ 
      SyntaxTree stree(input); 
      Variable::add("_", stree.result());
      if(show_output) cout << "   " <<  stree.result() << endl;
    } catch(const std::invalid_argument& error) { 
      cout << "   " << error.what() << endl;
    }

  }

  return 0;
}

