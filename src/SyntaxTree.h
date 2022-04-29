#ifndef SYNTAX_TREE_H
#define SYNTAX_TREE_H

#include "BTree.h"
#include "Token.h"
#include "Operand.h"
#include "Operator.h"
#include <string>
#include <utility>

class SyntaxTree: protected BTree<Token*> {
  private:
    Operand m_result;
  public:
    SyntaxTree(std::string str);
    SyntaxTree(const SyntaxTree& other);
    SyntaxTree(SyntaxTree&& other);
    inline Operand result() const { return m_result; }

  private:
    /* ----- PRIVATE UTILITY METHODS ----- */

    /* Traverses tree recursively in post order to obtain its result
     * Called during instantiation
     */
    Operand parse();
    /*  Finds index of a given substring OUTSIDE any paretheses in the given string
     *  Returns index if found; otherwise, returns std::string::npos;
     */
    int find_operand(std::string str, std::string opstr);
    /* Finds whether a string is wrapped by parentheses 
     * Receives validated string
     */
    bool is_wrapped(std::string str);
    /*   Throws errors for unacceptable strings:
     * - Unmatched parentheses
     */
    bool validate_str(std::string str);
};


#endif