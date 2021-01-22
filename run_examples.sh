#!/usr/bin/env bash
# make clean
# make build

# Sanity checks on smaller matrices
###############

#   Example 3.7 Section 3.4 of https://www-users.cs.umn.edu/~saad/IterMethBook_2ndEd.pdf with ones vector RHS
#   Used for testing reading into compressed column format
make test \
  A_PATH=data/example/example_A.mtx \
  B_PATH=data/example/example_b.mtx \
  MODE=naive
make test \
  A_PATH=data/example/example_A.mtx \
  B_PATH=data/example/example_b.mtx \
  MODE=sparse

#   Sympiler Figure 1
#   Used for testing DFS algo on adjacency graph to compute reach set
make test \
  A_PATH=data/example/sympiler_L.mtx \
  B_PATH=data/example/sympiler_b.mtx \
  MODE=naive
make test \
  A_PATH=data/example/sympiler_L.mtx \
  B_PATH=data/example/sympiler_b.mtx \
  MODE=sparse