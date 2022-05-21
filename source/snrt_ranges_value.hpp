#ifndef SNRT_RANGES_VALUE_HPP
#define SNRT_RANGES_VALUE_HPP

#include "snrt_ranges_location.hpp"
#include "snrt_ranges_range.hpp"


namespace snrt
{
    template<typename T>
    class Value
    {
    public:

        T value;
        [[nodiscard]] constexpr operator T const& () const { return value; }
        [[nodiscard]] constexpr operator T & () { return value; }

        [[nodiscard]] constexpr bool is_in_range(auto const& range) const { return range.contains(value); }
        [[nodiscard]] constexpr bool is_below_range(auto const& range) const { return locate_compared_to_range(range) == Location::below_range; }
        [[nodiscard]] constexpr bool is_above_range(auto const& range) const { return locate_compared_to_range(range) == Location::above_range; }
        
        [[nodiscard]] constexpr Location locate_compared_to_range(auto const& range) const { return range.locate(value); }
    };
}

#endif // header guard