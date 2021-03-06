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
  BTree(const T& data);
  BTree(const BTree& other);
  BTree(BTree&& other);
  ~BTree();
  /* Build methods */
  static BTree<T>* build_util(const std::vector<T>& in, const std::vector<T>& post, int in_start, int in_end, int post_start, int post_end);
  static BTree<T>* build_tree(const std::vector<T>& in, const std::vector<T>& post);
};

/* TEMPLATE FUNCTION DEFINITIONS */

template <typename T>
BTree<T>::BTree(const T& data): data(data), left(nullptr), right(nullptr) {}


template <typename T>
BTree<T>::BTree(const BTree<T>& other): data(other.data), left(nullptr), right(nullptr)  {
  if (other.left) left = new BTree<T>(*other.left);
  if (other.right) right = new BTree<T>(*other.right);
}


template <typename T>
BTree<T>::BTree(BTree&& other): data(std::move(data)), left(other.left), right(other.right) {}


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

#endif