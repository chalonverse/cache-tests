// Sequential access, optimized
// sizeof(TestStruct) == 64
#include <iostream>
#include <chrono>

const unsigned NUM_TESTS = 1000;
const unsigned PER_TEST = 10001;

struct TestStruct {
  int a;
  int b;
  int c;
  int d;
  int e;
  int f;
  int g;
  int h;
  int i;
  int j;
  int k;
  int l;
  int m;
  int n;
  int o;
  bool b0, b1, b2, b3;
};

void testFunc(TestStruct* array) {
  auto start = std::chrono::steady_clock::now();

  // Test here (read/write)
  for (unsigned i = 0; i < PER_TEST - 1; i++) {
    array[i + 1].a = array[i].a;
    array[i + 1].b = array[i].b;
    array[i + 1].c = array[i].c;
    array[i + 1].d = array[i].d;
    array[i + 1].b0 = array[i].b0;
    array[i + 1].e = array[i].e;
    array[i + 1].f = array[i].f;
    array[i + 1].g = array[i].g;
    array[i + 1].h = array[i].h;
    array[i + 1].b1 = array[i].b1;
    array[i + 1].i = array[i].i;
    array[i + 1].j = array[i].j;
    array[i + 1].k = array[i].k;
    array[i + 1].l = array[i].l;
    array[i + 1].b2 = array[i].b2;
    array[i + 1].m = array[i].m;
    array[i + 1].n = array[i].n;
    array[i + 1].o = array[i].o;
    array[i + 1].b3 = array[i].b3;
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
