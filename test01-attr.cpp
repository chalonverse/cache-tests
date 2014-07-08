// Sequential access, unoptimized
// Using autoarrange attribute
// sizeof(TestStruct) == 64 w/ autoarrange
#include <iostream>
#include <chrono>

const unsigned NUM_TESTS = 1000;
const unsigned PER_TEST = 10000;

struct [[clang::autoarrange]] TestStruct {
  int a;
  int b;
  int c;
  int d;
  bool b0;
  int e;
  int f;
  int g;
  int h;
  bool b1;
  int i;
  int j;
  int k;
  int l;
  bool b2;
  int m;
  int n;
  int o;
  bool b3;
};

void testFunc(TestStruct* array) {
  auto start = std::chrono::steady_clock::now();

  int sum = 0;
  bool test = true;
  // Test here
  for (unsigned i = 0; i < PER_TEST; i++) {
    // reads
    sum += array[i].a;
    sum += array[i].b;
    sum += array[i].c;
    sum += array[i].d;
    test &= array[i].b0;
    sum += array[i].e;
    sum += array[i].f;
    sum += array[i].g;
    sum += array[i].h;
    test &= array[i].b1;
    sum += array[i].i;
    sum += array[i].j;
    sum += array[i].k;
    sum += array[i].l;
    test &= array[i].b2;
    sum += array[i].m;
    sum += array[i].n;
    sum += array[i].o;
    test &= array[i].b3;

    // write so can't be optimized
    array[i].o = sum;
    array[i].b3 = test;
  }
  
  auto end = std::chrono::steady_clock::now();
#ifdef SHOW_OUTPUT
  std::cout << (end - start).count() << std::endl;
#endif
}

int main() {
  // Allocate test arrays here, so they don't get optimized out
  TestStruct* testArray[NUM_TESTS];
  for (unsigned i = 0; i < NUM_TESTS; i++) {
    testArray[i] = new TestStruct[PER_TEST];
  }

  for (unsigned i = 0; i < NUM_TESTS; i++) {
    testFunc(testArray[i]);
  }
  
  return 0;
}
