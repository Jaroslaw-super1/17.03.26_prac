#include <iostream>
#include <iomanip>
#include "top-it-vector.hpp"

bool testDefaultVector()
{
  topit::Vector< int > v;
  return v.isEmpety();
}

bool testVectorWithValue()
{
  topit::Vector< int > v;
  v.pushBack(1);
  return !v.isEmpety();
}

int main()
{
  using test_t = bool(*)();
  using pair_t = std::pair< const char *, test_t >;
  pair_t tests[] =
  {
    {"Default vector is empety", testDefaultVector},
    {"Vector with any value is not empety", testVectorWithValue}
  };
  const size_t count = sizeof(tests) / sizeof(pair_t);
  std::cout << std::boolalpha;
  bool pass = true;

  for (size_t i = 0; i < count; i++)
  {
    bool res = tests[i].second();
    std::cout << tests[i].first << ' ' << res << '\n';
    pass = pass && res;
  }

  std::cout << pass << '\n';

//  std::cout << "testDefaultVector " << testDefaultVector() << '\n';
}
