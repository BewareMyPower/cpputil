# cpputil's installed directory
CPPUTIL_DIR = ../cpputil

CXX = g++
CXX_FLAGS = -O2 -std=c++11 -pthread -I$(CPPUTIL_DIR)/include
LD_FLAGS = -L$(CPPUTIL_DIR)/lib
LIBS = -lcpputil

SOURCES = atomic_vs_lock.cc string_buffer_performance.cc
TARGETS = $(SOURCES:.cc=.out)

all: $(TARGETS)
	@echo "Build targets: $(TARGETS)"

%.out: %.cc
	$(CXX) -o $@ $< $(CXX_FLAGS) $(LD_FLAGS) $(LIBS)

.Phony:
clean:
	rm -f $(TARGETS)
