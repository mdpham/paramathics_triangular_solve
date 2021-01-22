# paramathics_triangular_solve
Optimizing forward substitution for triangular solve using adjacency matrix and contributing columns

Steps:
- Unzip Matrix Market format https://sparse.tamu.edu/TSOPF/TSOPF_RS_b678_c2 and https://sparse.tamu.edu/Norris/torso1 into `data/TSOPF_RS_b678_c2` and `data/torso1` respectively (with associated RHSs)
- May need to change execution permissions `chmod a+x {run_examples.sh, run_tests.sh}`
- `make clean && make build`
- `./run_examples.sh` to make sure it works on small matrices
- `./run_tests.sh` to test optimization speed up on both systems

To run on a new matrix:
- `make test A_PATH=path/to/A.mtx B_PATH=path/to/b.mtx MODE={naive, sparse}` where program expects `MODE` to be either 'naive' or 'sparse' (see `src/main.cpp`)
or use commented template in `run_tests.sh`.
