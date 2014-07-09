// Functionality tests to make sure
// stuff isn't broken with autoarrange
#include <iostream>

struct [[clang::autoarrange]] TestStruct01 {
  bool bit;
  int array[4];
  TestStruct01() {
    bit = false;
    array[0] = 1;
    array[1] = 1;
    array[2] = 2;
    array[3] = 3;
  }
};

struct [[clang::autoarrange]] TestStruct02 {
  bool bit;
  int array[4];
  TestStruct02() {
    bit = false;
    array[0] = 5;
    array[1] = 10;
    array[2] = 15;
    array[3] = 20;
  }
  virtual ~TestStruct02() { }
};

int main() {
  std::cout << sizeof(TestStruct01) << std::endl;
  TestStruct01 test;
  for (int i = 0; i < 4; i++) {
    std::cout << test.array[i] << std::endl;
  }
  
  std::cout << sizeof(TestStruct02) << std::endl;
  TestStruct02 test2;
  for (int i = 0; i < 4; i++) {
    std::cout << test2.array[i] << std::endl;
  }
  return 0;
}
