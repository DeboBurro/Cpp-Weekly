# Instruction
1. Build the benchmark library inside of this repo.
2. Run the code by `g++ understanding-myPair-StdPair.cpp -std=c++11 -isystem benchmark/include -Lbenchmark/build/src -lbenchmark -lpthread -o myPair-StdPair-benchmark`.
3. Run `./myPair-StdPair-benchmark`