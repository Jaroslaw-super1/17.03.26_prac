#include <iostream>
#include <initializer_list>
#include "top-it-vector.hpp"

topit::Vector< int > make()
{
  return {1, 2, 3, 4};
}

int main()
{
  std::initializer_list< int > il = {1, 2, 3, 4, 5, 6};

  topit::Vector< int > v = {1, 2, 3, 4, 5};
}

