#include <tbb/tbb.h>
#include <vector>
#include <numeric>
#include <chrono>
#include <iostream>
#include <cstdlib>

template <typename Func>
long long timeFunc(Func f)
{
  auto begin = std::chrono::steady_clock::now();
  f();
  auto end = std::chrono::steady_clock::now();
  return std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
}

void TBBPFor(unsigned long long _size)
{
  std::vector<int> numbers(_size);
  std::iota(std::begin(numbers), std::end(numbers), 0);

  auto begin = std::chrono::steady_clock::now();

  tbb::parallel_for(tbb::blocked_range<size_t>(0, 16),
                    [&numbers](tbb::blocked_range<size_t> &r)
                    {
                      for (size_t i = r.begin(); i != r.end(); ++i)
                        numbers[i] += 1;
                    });
  auto end = std::chrono::steady_clock::now();
  std::cout << "TBB update took " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " uS ";
}

void NormalFor(unsigned long long _size)
{
  std::vector<int> numbers(_size);
  std::iota(std::begin(numbers), std::end(numbers), 0);

  auto begin = std::chrono::steady_clock::now();

  std::for_each(std::begin(numbers), std::end(numbers),
                [](int &n)
                { n += 1; });
  auto end = std::chrono::steady_clock::now();
  std::cout << "Normal For update took " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " uS ";
}

auto main() -> int
{
  unsigned long long size = 1 << 30; //(1024*1024)*60;
  std::cout << "Data Size is " << size << '\n';

  auto time = timeFunc([&]()
                       { NormalFor(size); });
  std::cout << "Total Time " << time << " uS\n";

  time = timeFunc([&]()
                  { TBBPFor(size); });
  std::cout << "Total Time " << time << " uS\n";
  return EXIT_SUCCESS;
}
