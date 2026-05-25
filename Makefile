CXX = g++
CXXFLAGS = -O3 -std=c++2b -Wall -Wextra

SRCS = $(wildcard *.cpp)
HEADERS = $(wildcard algorithms/*.h)

ifeq ($(OS),Windows_NT)
    # Dynamically detect absolute system Python path and safely quote it to prevent space issues
    PYTHON ?= "$(shell py -c "import sys; print(sys.executable, end='')" 2>nul || echo python)"
else
    PYTHON ?= "$(shell which python3 2>/dev/null || which python 2>/dev/null || echo python3)"
endif

ifeq ($(OS),Windows_NT)
	TARGETS = $(SRCS:.cpp=.exe)
	CLEAN_CMD = if exist *.exe del /Q /F *.exe
	CLEAN_DIR = if exist results rmdir /S /Q results
	CLEAN_OUT = if exist output.txt del /Q /F output.txt
else
	TARGETS = $(SRCS:.cpp=)
	CLEAN_CMD = rm -f $(TARGETS)
	CLEAN_DIR = rm -rf results
	CLEAN_OUT = rm -f output.txt
endif

all: $(TARGETS)

ifeq ($(OS),Windows_NT)
%.exe: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $@ $<
else
%: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $@ $<
endif

benchmark: $(TARGETS)
	$(PYTHON) benchmark.py

check:
	$(PYTHON) check_tests.py

compare:
	$(PYTHON) compare_std.py

analyze: benchmark check compare

clean:
	-$(CLEAN_CMD)
	-$(CLEAN_DIR)
	-$(CLEAN_OUT)
