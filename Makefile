# Makefile for tests

# Executable files
EXEC_FILES = test01.out test01-opt.out

##
LLVM_ROOT = ..
CLANG = $(LLVM_ROOT)/bin/clang++
CLANG_FLAGS = -std=c++11 -O2
CLANG_BC_FLAGS = $(CLANG_FLAGS) -emit-llvm -c
DIS = $(LLVM_ROOT)/bin/llvm-dis

all: $(EXEC_FILES)

clean:
	rm -f *.out *.bc *.ll *.txt *.stats

# First do output version for stats,
# then no output version for valgrind
%.out: %.cpp
	$(CLANG) $(CLANG_FLAGS) -D SHOW_OUTPUT $(@:%.out=%.cpp) -o $@
	./$@ > $(@:%.out=%.txt)
	$(CLANG) $(CLANG_FLAGS) $(@:%.out=%.cpp) -o $@
	$(CLANG) $(CLANG_BC_FLAGS) $(@:%.out=%.cpp) -o $(@:%.out=%.bc)
	$(DIS) -f $(@:%.out=%.bc)
	valgrind --tool=cachegrind --cachegrind-out-file=$(@:%.out=%.cg.stats) --log-file=$(@:%.out=%.cg.txt) ./$@
