//#define BOOST_CHRONO_PROVIDES_DEPRECATED_IO_SINCE_V2_0_0
#include <boost/chrono.hpp>
#include <boost/chrono/chrono_io.hpp>
#include <atomic>

void test()
{
  std::atomic<boost::chrono::milliseconds> ms; // error C2338: atomic<T> requires T to be trivially copyable.
}

int main() {
  test();
  return 1;
}
