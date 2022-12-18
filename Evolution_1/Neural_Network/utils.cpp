#include <vector>

template<typename T> int find_index(std::vector<T> v, T el){
  // returns index of element in vector. returns -1 if element not in vector.
  auto a = v.begin();
  auto b = v.end();
  int i = find(a,b,el) - a;
  if (i!= v.size()){
      return i;
    } else {
      return -1;
    }
}
