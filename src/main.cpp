#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include "SyntaxTree.h"
#include "Operator.h"

using namespace std;

// function<string(Token*)> print_token = [](Token* token) { return token->str() + "  "; };

int main(int argc, char **argv) {

  // SyntaxTree stree(argv[1]);

  // cout << stree.result()->value();

  string input;

  Double pi(3.14);
  Variable var_pi("PI");
  var_pi.set(&pi);

  while(true) { 
    bool show_output = true;
    cout << ">> ";
    std::getline(std::cin, input);

    if(input.back() == ';') {
      input = input.substr(0, input.size()-1);
      show_output = false;
    }

    if(input == "exit()") break;

    SyntaxTree stree(input);

    if(show_output) cout << "   " <<  stree.result()->value() << endl;

  }

  return 0;
}

