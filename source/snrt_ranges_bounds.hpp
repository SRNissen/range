#ifndef SNRT_RANGES_BOUNDS_HPP
#define SNRT_RANGES_BOUNDS_HPP

namespace snrt
{
    template<typename T>
    class Minimum
    {
    public:
        [[nodiscard]] constexpr bool is_satisfied(T const& t) const { return t >= value; }

        T value;

        const static bool is_lower_bound = true;
    };

    template<typename T>
    class GreaterThan
    {
    public:
        [[nodiscard]] constexpr bool is_satisfied(T const& t) const { return t > value; }

        T value;

        const static bool is_lower_bound = true;
    };

    template<typename T>
    class Maximum
    {
    public:
        [[nodiscard]] constexpr bool is_satisfied(T const& t) const { return t <= value; }

        T value;

        const static bool is_upper_bound = true;
    };

    template<typename T>
    class LessThan
    {
    public:
        [[nodiscard]] constexpr bool is_satisfied(T const& t) const { return t < value; }
        
        T value;
        
        const static bool is_upper_bound = true;
    };

    template<typename T>
    using InclusiveMin = Minimum<T>;

    template<typename T>
    using ExclusiveMin = GreaterThan<T>;

    template<typename T>
    using InclusiveMax = Maximum<T>;

    template<typename T>
    using ExclusiveMax = LessThan<T>;

} //namespace

#endif //header guard