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

bool testCopyConstruct() // !!!!!!!!!!!!!!!!!!!!
{
  topit::Vector< int > v;
  v.pushBack(1);
  topit::Vector< int > yav = v;
  bool isAllEqual = v.getSize() == yav.getSize();
  for (size_t i = 0; i < v.getSize(); ++i)
  {

  }
  return isAllEqual;
}

bool testElementAssert()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  return v[0] == 1 && v[1] == 2;
}

int main()
{
  using test_t = bool(*)();
  using pair_t = std::pair< const char *, test_t >;
  pair_t tests[] =
  {
    {"Default vector is empety", testDefaultVector},
    {"Vector with any value is not empety", testVectorWithValue}
    {"3 ", testCopyConstruct},
    {"4 ", testElementAssert},
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
}
