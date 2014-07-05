# Makefile for tests

# Executable files
EXEC_FILES = test01.out

##
LLVM_ROOT = ..
CLANG = $(LLVM_ROOT)/bin/clang++
CLANG_FLAGS = -std=c++11 -O2
CLANG_BC_FLAGS = $(CLANG_FLAGS) -emit-llvm -c
DIS = $(LLVM_ROOT)/bin/llvm-dis

all: $(EXEC_FILES)

clean:
	rm -f *.out *.bc *.llc

%.out: %.cpp
	$(CLANG) $(CLANG_FLAGS) $(@:%.out=%.cpp) -o $@
	$(CLANG) $(CLANG_BC_FLAGS) $(@:%.out=%.cpp) -o $(@:%.out=%.bc)
	$(DIS) -f $(@:%.out=%.bc)
