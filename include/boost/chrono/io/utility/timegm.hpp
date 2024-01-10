//  boost/chrono/utility/timegm.hpp
//
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#ifndef BOOST_CHRONO_UTILITY_TIMEGM_HPP
#define BOOST_CHRONO_UTILITY_TIMEGM_HPP

#include <ctime>
#include <locale>

#if  ( defined BOOST_WINDOWS && ! defined(__CYGWIN__) )  \
  || (defined(sun) || defined(__sun)) \
  || (defined __IBMCPP__) \
  || defined __ANDROID__ \
  || defined __QNXNTO__ \
  || (defined(_AIX) && defined __GNUC__)
#define  BOOST_CHRONO_INTERNAL_TIMEGM
#endif

namespace boost {
namespace chrono {

namespace detail {

inline int32_t is_leap(int32_t year) {
    if (year % 400 == 0) {
        return 1;
    }
    if (year % 100 == 0) {
        return 0;
    }
    if (year % 4 == 0) {
        return 1;
    }
    return 0;
}

#if defined BOOST_CHRONO_INTERNAL_TIMEGM

inline int32_t days_from_0(int32_t year) {
    --year;
    return 365 * year + (year / 400) - (year/100) + (year / 4);
}
inline int32_t days_from_1970(int32_t year) {
    static const int32_t days_from_0_to_1970 = days_from_0(1970);
    return days_from_0(year) - days_from_0_to_1970;
}
inline int32_t days_from_1jan(int32_t year, int32_t month, int32_t day) {
    static const int32_t days[2][12] = {
        { 0,31,59,90,120,151,181,212,243,273,304,334},
        { 0,31,60,91,121,152,182,213,244,274,305,335}
    };

    return days[is_leap(year)][month-1] + day - 1;
}
inline std::time_t internal_timegm(const std::tm* t) {
    int year = t->tm_year + 1900;
    int month = t->tm_mon;
    if (month > 11) {
        year += month/12;
        month %= 12;
    } else if (month < 0) {
        int years_diff = (-month + 11)/12;
        year -= years_diff;
        month += 12 * years_diff;
    }
    month++;
    int day = t->tm_mday;
    int day_of_year = days_from_1jan(year,month,day);
    int days_since_epoch = days_from_1970(year) + day_of_year ;

    std::time_t seconds_in_day = 3600 * 24;
    std::time_t result = seconds_in_day * days_since_epoch + 3600 * t->tm_hour + 60 * t->tm_min + t->tm_sec;

    return result;
}

#endif

} // detail

/**
 * This function translates tm time as if it were utc in time_t.
 * This function is inverse to gmtime from POSIX.
 */
inline std::time_t timegm_s(const std::tm* t) {
    #if defined BOOST_CHRONO_INTERNAL_TIMEGM
        #if defined BOOST_WINDOWS && ! defined(__CYGWIN__)
            #if BOOST_MSVC < 1900
                return detail::internal_timegm(t);
            #else
                std::tm temp_t = *t;
                return _mkgmtime(&temp_t);
            #endif
        #else
            return detail::internal_timegm(t);
        #endif
    #else
        std::tm temp_t = *t;
        return timegm(&temp_t);
    #endif
}


} // chrono
} // boost

#endif  // BOOST_CHRONO_UTILITY_TIMEGM_HPP
