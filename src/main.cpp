#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include "SyntaxTree.h"
#include "Operator.h"

using namespace std;


int main(int argc, char **argv) {

  string input;

  Variable::add("PI", 3.1415);

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

