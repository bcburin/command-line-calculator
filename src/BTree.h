#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <vector>
#include <string>
#include <functional>
#include <iostream>
#include <exception>
#include "Helpers.h"

template <typename T>
struct BTree {
  /* Data members */
  T data;
  BTree<T>* left;
  BTree<T>* right;
  /* Constructors and destructor */
  BTree();
  BTree(const T& data);
  ~BTree();
  /* Printing traversals */
  void print_inorder(std::function<std::string(T)>& print = nullptr);
  void print_postorder();
  void print_preorder();
  /* Build methods */
  static BTree<T>* build_util(const std::vector<T>& in, const std::vector<T>& post, int in_start, int in_end, int post_start, int post_end);
  static BTree<T>* build_tree(const std::vector<T>& in, const std::vector<T>& post);
};

/* TEMPLATE FUNCTION DEFINITIONS */

template <typename T>
BTree<T>::BTree(const T& data): data(data), left(nullptr), right(nullptr) {}

template <typename T>
BTree<T>::BTree(): BTree(0) {}

template <typename T>
BTree<T>::~BTree() {
  if(left) delete left;
  if(right) delete right;
}


template <typename T>
BTree<T>* BTree<T>::build_util(const std::vector<T>& in, const std::vector<T>& post, int in_start, int in_end, int post_start, int post_end) {
  // Base case
  if (in_start == in_end) return nullptr;

  // Find current node (last element in ranged post[])
  BTree<T>* curr = new BTree<T>(post[post_end-1]);

  // Find index of current node (last in ranged post[]) in ranged in[]
  int index = find_in_vector_range<T>(curr->data, in, in_start, in_end);

  // Generate left and right subtrees recursively
  curr->left = build_util(in, post, in_start, index, post_start, post_start-in_start+index);
  curr->right = build_util(in, post, index+1, in_end, post_start-in_start+index, post_end-1);

  // Return generated tree
  return curr;
}

template <typename T>
BTree<T>* BTree<T>::build_tree(const std::vector<T>& in, const std::vector<T>& post) {
  int in_size = in.size();
  int post_size = post.size();

  if(in_size != post_size) return nullptr;

  return build_util(in, post, 0, in_size, 0, post_size);
}

template <typename T>
void BTree<T>::print_inorder(std::function<std::string(T)>& print /*= {}*/) {
  if(left) left->print_inorder(print);
  if(print) std::cout << print(data);
  if(right) right->print_inorder(print);
}

template <typename T>
void BTree<T>::print_postorder() {
  if(left) left->print_postorder();
  if(right) right->print_postorder();
  std::cout << data;
}

template <typename T>
void BTree<T>::print_preorder() {
  std::cout << data;
  if(left) left->print_preorder();
  if(right) right->print_preorder();
}

#endif