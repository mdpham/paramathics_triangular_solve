#!/usr/bin/env bash
# make clean
# make build

# https://sparse.tamu.edu/Norris/torso1
make test \
  A_PATH=data/torso1/torso1.mtx \
  B_PATH=data/torso1/b_for_torso1.mtx \
  MODE=naive
make test \
  A_PATH=data/torso1/torso1.mtx \
  B_PATH=data/torso1/b_for_torso1.mtx \
  MODE=sparse

# # https://sparse.tamu.edu/TSOPF/TSOPF_RS_b678_c2
make test \
  A_PATH=data/TSOPF_RS_b678_c2/TSOPF_RS_b678_c2.mtx \
  B_PATH=data/TSOPF_RS_b678_c2/b_for_TSOPF_RS_b678_c2_b.mtx \
  MODE=naive
make test \
  A_PATH=data/TSOPF_RS_b678_c2/TSOPF_RS_b678_c2.mtx \
  B_PATH=data/TSOPF_RS_b678_c2/b_for_TSOPF_RS_b678_c2_b.mtx \
  MODE=sparse

# Validate using third matrix by passing paths
# make test \
#   A_PATH=path/to/matrix.mtx \
#   B_PATH=path/to/vector.mtx \
#   MODE=naive
# make test \
#   A_PATH=path/to/matrix.mtx \
#   B_PATH=path/to/vector.mtx \
#   MODE=sparse