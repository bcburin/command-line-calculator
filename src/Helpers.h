#ifndef HELPERS_H
#define HELPERS_H

#include <vector>
#include <string>

/* Find index of a given element in vector;
 * Equality must be defined for type T 
 * return -1 if not found.
 */
template<typename T>
int find_in_vector(const std::vector<T>& vec, const T& key);

// Find index within specified range [start,end)
template<typename T>
int find_in_vector_range(const std::vector<T>& vec, const T& key, int start, int end);

/* Creates sliced copy of the vector in the range [start,end)
 * end defaults to -1, in which case the vector will be sliced to its end
 */
template <typename T>
std::vector<T> slice(std::vector<T> const& v, int start, int end = -1);

/* Trims whitespace at end and start of string */
std::string trim(std::string str);


/* TEMPLATE FUNCTION DEFINITIONS */

template<typename T>
int find_in_vector(const T& key, const std::vector<T>& vec) {
  return find_in_vector_range(key, vec, 0, vec.size());
}

template<typename T>
int find_in_vector_range(const T& key, const std::vector<T>& vec, int start, int end) {
  // Linear search
  for (int i = start; i != end; i++)
    if(key == vec[i]) return i;
  // Key not found
  return -1;
}

template <typename T>
std::vector<T> slice(std::vector<T> const& v, int start, int end) {
  // Begin and End iterator
  auto first = v.begin() + start;
  auto last = end == -1 ? v.end() : v.begin() + end;
  // Copy the element
  std::vector<T> vector(first, last);
  // Return the results
  return vector;
}

#endif