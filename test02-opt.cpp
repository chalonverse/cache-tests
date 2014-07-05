// Random access, optimized
// sizeof(TestStruct) == 64
#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>
#include <random>

const unsigned NUM_TESTS = 1000;
const unsigned PER_TEST = 10000;

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

void testFunc(TestStruct* array, std::vector<unsigned>& indices) {
  auto start = std::chrono::steady_clock::now();

  int sum = 0;
  bool test = true;
  // Test here
  for (unsigned i = 0; i < PER_TEST; i++) {
    int idx = indices[i];
    // reads
    sum += array[idx].a;
    sum += array[idx].b;
    sum += array[idx].c;
    sum += array[idx].d;
    test &= array[idx].b0;
    sum += array[idx].e;
    sum += array[idx].f;
    sum += array[idx].g;
    sum += array[idx].h;
    test &= array[idx].b1;
    sum += array[idx].i;
    sum += array[idx].j;
    sum += array[idx].k;
    sum += array[idx].l;
    test &= array[idx].b2;
    sum += array[idx].m;
    sum += array[idx].n;
    sum += array[idx].o;
    test &= array[idx].b3;

    // write so can't be optimized
    array[idx].o = sum;
    array[idx].b3 = test;
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

  // Vector used for randomization
  std::vector<unsigned> indices(PER_TEST);
  for (unsigned i = 0; i < PER_TEST; i++) {
    indices[i] = i;
  }
  
  for (unsigned i = 0; i < NUM_TESTS; i++) {
    std::shuffle(indices.begin(), indices.end(), std::random_device());
    testFunc(testArray[i], indices);
  }
  
  return 0;
}
