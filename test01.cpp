// Sequential access, unoptimized
// sizeof(TestStruct) == 76
#include <iostream>
#include <chrono>

const unsigned NUM_TESTS = 1000;
const unsigned PER_TEST = 10000;

struct TestStruct {
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

  // Test here
  for (unsigned i = 0; i < PER_TEST; i++) {
    array[i].a = i;
    array[i].b = i;
    array[i].c = i;
    array[i].d = i;
    array[i].b0 = true;
    array[i].e = i;
    array[i].f = i;
    array[i].g = i;
    array[i].h = i;
    array[i].b1 = false;
    array[i].i = i;
    array[i].j = i;
    array[i].k = i;
    array[i].l = i;
    array[i].b2 = true;
    array[i].m = i;
    array[i].n = i;
    array[i].o = i;
    array[i].b3 = true;
  }
  
  auto end = std::chrono::steady_clock::now();
  std::cout << (end - start).count() << std::endl;
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
