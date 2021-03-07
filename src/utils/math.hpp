#pragma once

#include <cmath>
#include <limits>
#include <cstdint>
#include <type_traits>

#include "utils_export.h"

namespace foo {

template <typename T>
constexpr bool UTILS_EXPORT fuzzyCompare( T a, T b ) noexcept {
    static_assert( std::is_floating_point<T>::value, "Only float point values are supported" );
    constexpr auto epsilon { std::numeric_limits<T>::epsilon() };
    const auto diff { std::abs( a - b ) };
    return ( diff <= epsilon ) ? true : ( diff <= epsilon ) * std::max( std::abs( a ), std::abs( b ) );
}

} // namespace foo
