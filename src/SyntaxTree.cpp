#include "SyntaxTree.h"
#include <exception>


SyntaxTree::SyntaxTree(std::string str) {
  m_stree = parse_string(str);
  m_result = parse_tree(m_stree);
}

SyntaxTree::SyntaxTree(const SyntaxTree& other) {
  m_stree = copy_tree(other.m_stree);
  m_result = parse_tree(m_stree);
}

SyntaxTree::SyntaxTree(SyntaxTree&& other) {
  // Initialize new object
  m_stree = other.m_stree;
  m_result = parse_tree(m_stree);
  // Free old ebject
  other.m_stree = nullptr;
}

SyntaxTree::~SyntaxTree() { if(m_stree) delete m_stree; }


BTree<Token*>* SyntaxTree::copy_tree(BTree<Token*>* other) {
  if (!other) return nullptr;
  
  // Allocate memory for new node
  BTree<Token*>* new_tree = new BTree<Token*>(*other);

  // Copy left and right subtree recursively
  new_tree->left = copy_tree(other->left);
  new_tree->left = copy_tree(other->right);

  return new_tree;
}


BTree<Token*>* SyntaxTree::parse_string(std::string str) {
  // Validate input
  validate_str(str);
  // Check if string is wrapped by a pair of parentheses
  if (is_wrapped(str)) {
    // Generate tree recursively for subexpression
    return parse_string(str.substr(1, str.size()-2));
  }
  // Check if str contains operator. Traverse in increasing priority
  for(auto& pair : Operator::map) {
    int index = find_substr_util(str, pair.second.str());
    if (index != std::string::npos) { // If operator was found
      // Create tree node containg the op
      BTree<Token*>* tree = new BTree<Token*>(new Operator(pair.second));
      tree->left = parse_string(str.substr(0,index));
      tree->right = parse_string(str.substr(index+1,str.size()-index-1));
      return tree;
    }
  }
  // If no operator was found, create tree node as operand
  return new BTree<Token*>(new Operand(str));
}


Operand SyntaxTree::parse_tree(BTree<Token*>* tree) {
  // Base case: operand node
  if (auto operand = dynamic_cast<Operand*>(tree->data))
    return *operand;
  
  // Recursive calculation
  auto n1 = parse_tree(tree->left);
  auto n2 = parse_tree(tree->right);
  auto op = *dynamic_cast<Operator*>(tree->data);

  // Result
  return op(n1,n2);
}


int SyntaxTree::find_substr_util(std::string str, std::string substr) {
  //Track number of opened/closed parentheses while traversing the string
  int nested_pars = 0;
  for (int i = 0; i != str.size(); ++i) {
    // Update tracker of nested parentheses
    if(str[i] == '(') ++nested_pars;
    if(str[i] == ')') --nested_pars;
    // Search string only if outside any parentheses
    if(nested_pars == 0) {
      bool found = true;
      for (int j = 0; j != substr.size(); ++j) {
        if(substr[j] != str[i+j]) {
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


bool SyntaxTree::validate_str(std::string str) {
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
  return true;
}