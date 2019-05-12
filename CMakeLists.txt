# Copyright 2019 Mike Dev
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt
#
# NOTE: CMake support for Boost.Chrono is currently experimental at best
#       and the interface is likely to change in the future

cmake_minimum_required( VERSION 3.5 )
project( BoostChrono LANGUAGES CXX)

add_library( boost_chrono
    src/chrono.cpp
    src/process_cpu_clocks.cpp
    src/thread_clock.cpp
)
add_library( Boost::chrono ALIAS boost_chrono )

target_include_directories( boost_chrono PUBLIC include )

target_link_libraries( boost_chrono
    PUBLIC
        Boost::assert
        Boost::config
        Boost::core
        Boost::integer
        Boost::move
        Boost::mpl
        Boost::predef
        Boost::ratio
        Boost::static_assert
        Boost::system
        Boost::throw_exception
        Boost::type_traits
        Boost::typeof
        Boost::utility
     PRIVATE
        $<$<STREQUAL:Windows,$<PLATFORM_ID>>:Boost::winapi>
)
