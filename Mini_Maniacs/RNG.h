#pragma once
#include <random>
template<typename t = int>
class Random 
{
public:
  Random<t>(unsigned int s) : seed(s) { engine = std::mt19937_64(seed); };
  Random<t>() 
  {
    std::random_device r; 
    seed = r(); 
    engine = std::mt19937_64(seed);

  }

  t Next(void)
  {
    return static_cast<t>(engine());
  }

template<typename t>
  t Next(t lower, t upper)
  {
    float base = std::generate_canonical<float, 15>(engine);
    t run = base * upper + 1;
    run += lower;
    return run;
  }

private:
  
  unsigned int seed;
  std::mt19937_64 engine;
};

