#ifndef SYNTAX_TREE_H
#define SYNTAX_TREE_H

#include "BTree.h"
#include "Token.h"
#include "Operand.h"
#include "Operator.h"
#include <string>
#include <utility>

class SyntaxTree {
  private:
    /* ----- DATA MEMBERS ----- */
    // Pointer to a binary tree of tokens that represent the syntactic structure of an expression
    BTree<Token*>* m_stree;
    // Reuslt obtained 
    Operand m_result;
    /* ----- PRIVATE RECURSIVE METHODS ----- */
    BTree<Token*>* copy_tree(BTree<Token*>* other);
    BTree<Token*>* parse_string(std::string str);
    Operand parse_tree(BTree<Token*>* tree);
    /* ----- PRIVATE NON-RECURSIVE METHODS ----- */
    /*  Finds index of a given substring OUTSIDE any paretheses in the given string
     *  Returns index if found; otherwise, returns std::string::npos;
     */
    int find_substr_util(std::string str, std::string substr);
    /* Finds wheter a string is wrapped by parentheses 
     * Receives validated string
     */
    bool is_wrapped(std::string str);
    /* Throws errors for unacceptable strings */
    bool validate_str(std::string str);
  public:
    SyntaxTree(std::string str);
    SyntaxTree(const SyntaxTree& other);
    SyntaxTree(SyntaxTree&& other);
    ~SyntaxTree();
    inline Operand result() const { return m_result; }
};


#endif