# =====================================================================
# Makefile for CS509_2026CSM1031 (GEMM / BMM individual task)
# =====================================================================

CXX      := g++
CXXFLAGS := -std=c++17 -Wall -O2

# Include directories (quoted because "Assignment 1" has a space)
INCLUDES := \
    -I"Assignment 1" \
    -I"Assignment 2/include" \
    -I"Assignment 3/include" \
    -I"Assignment4/include"

# ---------------------------------------------------------------------
# Main executable sources
# ---------------------------------------------------------------------
MAIN_SRC := main.cpp

A1_SRC := \
    "Assignment 1/driver.cpp" \
    "Assignment 1/simple_gemm.cpp" \
    "Assignment 1/blocked_gemm.cpp"

# NOTE: src/driver.cpp (defines assignment2()) was missing before — that's
# what caused "undefined reference to assignment2()".
A2_SRC := \
    "Assignment 2/src/graph.cpp" \
    "Assignment 2/src/csr.cpp" \
    "Assignment 2/src/bellman_ford.cpp" \
    "Assignment 2/src/floyd_warshall.cpp" \
    "Assignment 2/src/driver.cpp"

# NOTE: Assignment 3 wasn't compiled in at all before — that's what caused
# "undefined reference to assignment3()". Its driver.cpp reaches into
# Assignment 2's headers via relative "../../Assignment 2/include/..."
# includes, so no extra -I flag is needed for that part.
A3_SRC := \
    "Assignment 3/src/driver.cpp" \
    "Assignment 3/src/mst.cpp"

A4_SRC := \
    "Assignment4/src/driver.cpp" \
    "Assignment4/src/csr_converter.cpp" \
    "Assignment4/src/vertex_coloring.cpp" \
    "Assignment4/src/pagerank.cpp"

SRC := $(MAIN_SRC) $(A1_SRC) $(A2_SRC) $(A3_SRC) $(A4_SRC)

TARGET := cs509

# ---------------------------------------------------------------------
# Standalone test-case generators (each has its own main())
# ---------------------------------------------------------------------
GENBF_SRC    := "Assignment 2/generator/generate_bellman_ford.cpp"
GENFW_SRC    := "Assignment 2/generator/generate_floyd_warshall.cpp"
GENMST_SRC   := "Assignment 3/generator_mst.cpp"
GENCOLOR_SRC := "Assignment4/generator/generate_coloring_graph.cpp"
GENPR_SRC    := "Assignment4/generator/generate_pagerank_graph.cpp"

GENBF_BIN    := genBF
GENFW_BIN    := genFW
GENMST_BIN   := generator_mst
GENCOLOR_BIN := colorgen
GENPR_BIN    := pagerankgen

# ---------------------------------------------------------------------
# Targets
# ---------------------------------------------------------------------
# NOTE: paths above contain spaces (e.g. "Assignment 1"), which makes them
# unsafe to use as normal Make *prerequisites* (Make splits on whitespace).
# So $(SRC) is only ever referenced inside recipes (shell command lines,
# where the quotes are honored), never on a target's dependency line.
# That means these targets always re-run their compile command rather than
# doing per-file incremental tracking — fine for a project this size.

.PHONY: all
all:
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(SRC) -o $(TARGET)

.PHONY: generators
generators:
	$(CXX) $(CXXFLAGS) -I"Assignment 2/include" $(GENBF_SRC) -o $(GENBF_BIN)
	$(CXX) $(CXXFLAGS) -I"Assignment 2/include" $(GENFW_SRC) -o $(GENFW_BIN)
	$(CXX) $(CXXFLAGS) -I"Assignment 3/include" $(GENMST_SRC) -o $(GENMST_BIN)
	$(CXX) $(CXXFLAGS) -I"Assignment4/include" $(GENCOLOR_SRC) -o $(GENCOLOR_BIN)
	$(CXX) $(CXXFLAGS) -I"Assignment4/include" $(GENPR_SRC) -o $(GENPR_BIN)

.PHONY: run
run: all
	./$(TARGET)

.PHONY: clean
clean:
	rm -f $(TARGET) $(GENBF_BIN) $(GENFW_BIN) $(GENMST_BIN) $(GENCOLOR_BIN) $(GENPR_BIN)

.PHONY: rebuild
rebuild: clean all