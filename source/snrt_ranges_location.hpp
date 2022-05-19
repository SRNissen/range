#ifndef SNRT_RANGES_LOCATION_HPP
#define SNRT_RANGES_LOCATION_HPP

namespace snrt
{
    enum class Location
    {
        below_range  = -1, in_range = 0, above_range = 1
    };

    inline constexpr Location below_range = Location::below_range;
    inline constexpr Location in_range = Location::in_range;
    inline constexpr Location above_range = Location::above_range;
}

#endif // header guard