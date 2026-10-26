//===----------------------------------------------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//  Adaptation to Boost of the libcxx
//  Copyright 2010 Vicente J. Botet Escriba
//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

#include <boost/chrono/chrono.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <boost/cstdint.hpp>
#include <limits>
#ifdef BOOST_NO_CXX11_CONSTEXPR
#define BOOST_CONSTEXPR_ASSERT(C) BOOST_TEST(C)
#else
#include <boost/static_assert.hpp>
#define BOOST_CONSTEXPR_ASSERT(C) BOOST_STATIC_ASSERT(C)
#endif

int main()
{
  // Subtract after converting to the common duration, not by negating rhs first.
  {
    typedef boost::chrono::system_clock Clock;
    typedef boost::chrono::duration<boost::int64_t, boost::nano> Nanoseconds;
    typedef boost::chrono::duration<boost::uint32_t, boost::micro> UnsignedMicroseconds;
    typedef boost::chrono::time_point<Clock, Nanoseconds> Point;
    BOOST_CONSTEXPR Point epoch(Nanoseconds(0));
    BOOST_CONSTEXPR Point earlier = epoch - UnsignedMicroseconds(1);
    BOOST_CONSTEXPR_ASSERT(earlier.time_since_epoch() == Nanoseconds(-1000));
    BOOST_TEST((Point(Nanoseconds(5000)) - UnsignedMicroseconds(1)).time_since_epoch()
               == Nanoseconds(4000));
    BOOST_TEST((epoch - UnsignedMicroseconds(0)).time_since_epoch() == Nanoseconds(0));
    BOOST_TEST((epoch - UnsignedMicroseconds((std::numeric_limits<boost::uint32_t>::max)()))
               .time_since_epoch() == Nanoseconds(-4294967295000LL));
  }
  {
    typedef boost::chrono::system_clock Clock;
    typedef boost::chrono::duration<boost::int64_t> WideDuration;
    typedef boost::chrono::duration<boost::int32_t> NarrowDuration;
    typedef boost::chrono::time_point<Clock, WideDuration> Point;
    BOOST_CONSTEXPR Point epoch(WideDuration(0));
    BOOST_CONSTEXPR Point later = epoch - NarrowDuration((std::numeric_limits<boost::int32_t>::min)());
    BOOST_CONSTEXPR_ASSERT(later.time_since_epoch() == WideDuration(2147483648LL));
  }
  {
    typedef boost::chrono::system_clock Clock;
    typedef boost::chrono::duration<double> FloatingDuration;
    typedef boost::chrono::duration<boost::uint32_t> UnsignedDuration;
    typedef boost::chrono::time_point<Clock, FloatingDuration> Point;
    BOOST_TEST((Point(FloatingDuration(0)) - UnsignedDuration(1)).time_since_epoch()
               == FloatingDuration(-1));
  }

  {
    typedef boost::chrono::system_clock Clock;
    typedef boost::chrono::milliseconds Duration;
    boost::chrono::time_point<Clock, Duration> t(Duration(3));
    t += Duration(2);
    BOOST_TEST(t.time_since_epoch() == Duration(5));
  }
  {
    typedef boost::chrono::system_clock Clock;
    typedef boost::chrono::milliseconds Duration;
    boost::chrono::time_point<Clock, Duration> t(Duration(3));
    t -= Duration(2);
    BOOST_TEST(t.time_since_epoch() == Duration(1));
  }
  {
    typedef boost::chrono::system_clock Clock;
    typedef boost::chrono::milliseconds Duration1;
    typedef boost::chrono::microseconds Duration2;
    boost::chrono::time_point<Clock, Duration1> t1(Duration1(3));
    boost::chrono::time_point<Clock, Duration2> t2 = t1 - Duration2(5);
    BOOST_TEST(t2.time_since_epoch() == Duration2(2995));
  }
  {
    typedef boost::chrono::system_clock Clock;
    typedef boost::chrono::milliseconds Duration1;
    typedef boost::chrono::microseconds Duration2;
    BOOST_CONSTEXPR boost::chrono::time_point<Clock, Duration1> t1(Duration1(3));
    BOOST_CONSTEXPR boost::chrono::time_point<Clock, Duration2> t2 = t1 - Duration2(5);
    BOOST_CONSTEXPR_ASSERT(t2.time_since_epoch() == Duration2(2995));
  }
  {
    typedef boost::chrono::system_clock Clock;
    typedef boost::chrono::milliseconds Duration1;
    typedef boost::chrono::microseconds Duration2;
    boost::chrono::time_point<Clock, Duration1> t1(Duration1(3));
    boost::chrono::time_point<Clock, Duration2> t2(Duration2(5));
    BOOST_TEST( (t1 - t2) == Duration2(2995));
  }
  {
    typedef boost::chrono::system_clock Clock;
    typedef boost::chrono::milliseconds Duration1;
    typedef boost::chrono::microseconds Duration2;
    BOOST_CONSTEXPR boost::chrono::time_point<Clock, Duration1> t1(Duration1(3));
    BOOST_CONSTEXPR boost::chrono::time_point<Clock, Duration2> t2(Duration2(5));
    BOOST_CONSTEXPR_ASSERT( (t1 - t2) == Duration2(2995));
  }
  {
    typedef boost::chrono::system_clock Clock;
    typedef boost::chrono::milliseconds Duration1;
    typedef boost::chrono::microseconds Duration2;
    boost::chrono::time_point<Clock, Duration1> t1(Duration1(3));
    boost::chrono::time_point<Clock, Duration2> t2 = t1 + Duration2(5);
    BOOST_TEST(t2.time_since_epoch() == Duration2(3005));
    t2 = Duration2(6) + t1;
    BOOST_TEST(t2.time_since_epoch() == Duration2(3006));
  }
  {
    typedef boost::chrono::system_clock Clock;
    typedef boost::chrono::milliseconds Duration1;
    typedef boost::chrono::microseconds Duration2;
    BOOST_CONSTEXPR boost::chrono::time_point<Clock, Duration1> t1(Duration1(3));
    BOOST_CONSTEXPR boost::chrono::time_point<Clock, Duration2> t2 = t1 + Duration2(5);
    BOOST_CONSTEXPR_ASSERT(t2.time_since_epoch() == Duration2(3005));
    BOOST_CONSTEXPR boost::chrono::time_point<Clock, Duration2> t3 = Duration2(6) + t1;
    BOOST_CONSTEXPR_ASSERT(t3.time_since_epoch() == Duration2(3006));
  }
#ifdef BOOST_CHRONO_EXTENSIONS
  {
    typedef boost::chrono::system_clock Clock;
    typedef boost::chrono::milliseconds Duration;
    boost::chrono::time_point<Clock, Duration> t(Duration(3));
    t += 2;
    BOOST_TEST(t.time_since_epoch() == Duration(5));
  }
  {
    typedef boost::chrono::system_clock Clock;
    typedef boost::chrono::milliseconds Duration;
    boost::chrono::time_point<Clock, Duration> t(Duration(3));
    t++;
    BOOST_TEST(t.time_since_epoch() == Duration(4));
  }
  {
    typedef boost::chrono::system_clock Clock;
    typedef boost::chrono::milliseconds Duration;
    boost::chrono::time_point<Clock, Duration> t(Duration(3));
    ++t;
    BOOST_TEST(t.time_since_epoch() == Duration(4));
  }
  {
    typedef boost::chrono::system_clock Clock;
    typedef boost::chrono::milliseconds Duration;
    boost::chrono::time_point<Clock, Duration> t(Duration(3));
    t -= 2;
    BOOST_TEST(t.time_since_epoch() == Duration(1));
  }
#if 0
  {
    typedef boost::chrono::system_clock Clock;
    typedef boost::chrono::milliseconds Duration1;
    typedef boost::chrono::microseconds Duration2;
    boost::chrono::time_point<Clock, Duration1> t1(Duration1(3));
    boost::chrono::time_point<Clock, Duration2> t2 = t1 - Duration2(5);
    BOOST_TEST(t2.time_since_epoch() == Duration2(2995));
  }
  {
    typedef boost::chrono::system_clock Clock;
    typedef boost::chrono::milliseconds Duration1;
    typedef boost::chrono::microseconds Duration2;
    boost::chrono::time_point<Clock, Duration1> t1(Duration1(3));
    boost::chrono::time_point<Clock, Duration2> t2(Duration2(5));
    BOOST_TEST((t1 - t2) == Duration2(2995));
  }
  {
    typedef boost::chrono::system_clock Clock;
    typedef boost::chrono::milliseconds Duration1;
    typedef boost::chrono::microseconds Duration2;
    boost::chrono::time_point<Clock, Duration1> t1(Duration1(3));
    boost::chrono::time_point<Clock, Duration2> t2 = t1 + Duration2(5);
    BOOST_TEST(t2.time_since_epoch() == Duration2(3005));
    t2 = Duration2(6) + t1;
    BOOST_TEST(t2.time_since_epoch() == Duration2(3006));
  }
#endif
#endif

  return boost::report_errors();
}
