#ifndef HELPERS_H
#define HELPERS_H

#include <vector>

/* Find index of a given element in vector;
 * Equality must be defined for type T 
 * return -1 if not found.
 */
template<typename T>
int find_in_vector(const std::vector<T>& vec, const T& key);

// Find index within specified range [start,end)
template<typename T>
int find_in_vector_range(const std::vector<T>& vec, const T& key, int start, int end);


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


#endif