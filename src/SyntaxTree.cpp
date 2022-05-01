#include "SyntaxTree.h"
#include <exception>

SyntaxTree::SyntaxTree(std::string str): BTree(nullptr), m_result(nullptr) {
  // Trim string
  str = trim(str);
  // Check for empty expression
  if (str == "") return;
  // Validate input
  validate_str(str);
  // Check if string is wrapped by a pair of parentheses; remove them if affirmative; repeat until not wrapped
  while (is_wrapped(str)) str = str.substr(1, str.size()-2);
  // Check if str contains operator; traverse operators in increasing priority
  bool is_operator = false;
  for(auto& op : Operator::set) {
    int index = find_operand(str, op.str());
    if (index != std::string::npos) { // If operator was found
      is_operator = true;
      // Create tree node containg the op
      data = new Operator(op);
      left = new SyntaxTree(str.substr(0,index));
      right = new SyntaxTree(str.substr(index+op.str().size(),str.size()-index-op.str().size()));
      break;
    }
  }

  if(!is_operator) {
    try{
      // If no operator was found, try to create tree node as double
      data = new Double(str);
    } catch(const std::invalid_argument& error) {
      // If it is not a double, initialize it as a variable
      data = new Variable(str);
    }
  }
  
  // Parse tree
  parse();
}


SyntaxTree::SyntaxTree(const SyntaxTree& other): BTree<Token*>(other), m_result(other.m_result) {}

SyntaxTree::SyntaxTree(SyntaxTree&& other): BTree<Token*>(std::move(other)), m_result(std::move(m_result)) {}

SyntaxTree::~SyntaxTree() { delete m_result; /* left and right destroyed in BTree destructor */ }


Operand* SyntaxTree::parse() {
  // Base case: operand node
  if (auto operand = dynamic_cast<Operand*>(data)) 
    return m_result = operand;

  // Base case: empty tree
  if(is_empty()) return nullptr;
  
  // If it is not an operand node, it is an operator node
  auto l_tree = static_cast<SyntaxTree*>(left);
  auto r_tree = static_cast<SyntaxTree*>(right);
  auto op = *static_cast<Operator*>(data);

  // Recursive calculation
  return m_result = op(l_tree->parse(),r_tree->parse());
}


int SyntaxTree::find_operand(std::string str, std::string opstr) {
  //Track number of opened/closed parentheses while traversing the string
  int nested_pars = 0;
  for (int i = 0; i != str.size(); ++i) {
    // Update tracker of nested parentheses
    if(str[i] == '(') ++nested_pars;
    if(str[i] == ')') --nested_pars;
    // Search string only if outside any parentheses
    if(nested_pars == 0) {
      bool found = true;
      for (int j = 0; j != opstr.size(); ++j) {
        if(opstr[j] != str[i+j]) {
          found = false;
          break;
        }
      }
      if (found) return i;
    }
  }
  return std::string::npos;
}


bool SyntaxTree::is_wrapped(std::string str) {
  // Check if first char is an open parenthesis
  if(str[0] != '(') return false;
  // Determine end of first expression wrapped by parentheses
  int open_pars = 1;
  int i;
  for (i = 1; i != str.size() && open_pars != 0 ; ++i) {
    if (str[i] == '(') ++open_pars;
    if (str[i] == ')') --open_pars;
  }
  // Return true if intial open parenthesis is closed at the end of string
  return i == str.size();
}


void SyntaxTree::validate_str(std::string str) {
  // Validate parentheses
  int open_pars = 0;
  for (const auto& ch : str) {
    if (ch == '(') ++open_pars;
    if (ch == ')') --open_pars;
    // Check for closing of unopened parentheses
    if (open_pars < 0) throw std::invalid_argument("Closed unopened parentheses.");
  }
  // Check for unclosed parentheses
  if (open_pars > 0) throw std::invalid_argument("Unclosed parentheses.");
}