#include <benchmark/benchmark.h>
static void stdPair(benchmark::State& state){
  for (auto _ : state){
    std::pair <std::string, std::string> p{"Hello", "World"};
    benchmark::DoNotOptimize(p);
  }
}

BENCHMARK(stdPair);

template<typename F, typename S>
struct Pair{
  F key;
  S value;
};

static void myPair(benchmark::State& state){
  for(auto _ : state){
    Pair<std::string, std::string> p{"Hello", "World"};
    benchmark::DoNotOptimize(p);
  }
}
BENCHMARK(myPair);
