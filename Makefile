all: world

CXX?=g++
CXXFLAGS?=--std=c++17 -Wall -fPIC -g

OBJS:= \
	objs/main.o

KERNEL_DIR:=.
include throws/Makefile.inc
include common/Makefile.inc
include ./Makefile.inc

world: example

$(shell mkdir -p objs)

objs/main.o: main.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c -o $@ $<;

example: $(THROWS_OBJS) $(COMMON_OBJS) $(KERNEL_OBJS) $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@;

.PHONY: clean
clean:
	@rm -rf objs example
