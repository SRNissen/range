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
        bool is_within_range(auto const& range) { return range.contains(value); }
        bool is_below_range(auto const& range) { return location_in_range(range) == Location::below_range; }
        bool is_above_range(auto const& range) { return location_in_range(range) == Location::above_range; }
        Location locate_compared_to_range(auto const& range) { return range.locate(value); }
    };
}

#endif // header guard