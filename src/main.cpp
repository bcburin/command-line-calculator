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

  while(true) { 
    cout << ">> ";
    cin >> input;

    if(input == "")

    SyntaxTree stree(input);
    cout << "   " <<  stree.result()->value() << endl;

  }

  return 0;
}

