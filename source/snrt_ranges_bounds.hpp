#ifndef SNRT_RANGES_BOUNDS_HPP
#define SNRT_RANGES_BOUNDS_HPP

namespace snrt::bounds
{
    template<typename T>
    class Minimum
    {
    public:
        bool is_satisfied(T const& t) { return t >= value; }

        T value;

        const static bool is_lower_bound = true;
    };

    template<typename T>
    class GreaterThan
    {
    public:
        bool is_satisfied(T const& t) { return t > value; }

        T value;

        const static bool is_lower_bound = true;
    };

    template<typename T>
    class Maximum
    {
    public:
        bool is_satisfied(T const& t) { return t <= value; }

        T value;

        const static bool is_upper_bound = true;
    };

    template<typename T>
    class LessThan
    {
    public:
        bool is_satisfied(T const& t) { return t < value; }
        
        T value;
        
        const static bool is_upper_bound = true;
    };

} //namespace

#endif //header guard