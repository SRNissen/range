#ifndef SNRT_RANGE_HPP
#define SNRT_RANGE_HPP

namespace snrt
{
    enum class Location
    {
        below_range, in_range, above_range
    };

    template<typename T>
    class LessThan
    {
    public:
        T value;
        bool is_satisfied(T const& t) { return t < value; }
    };

    template<typename T>
    class GreaterThan
    {
    public:
        T value;
        bool is_satisfied(T const& t) { return t > value; }
    };

    template<typename T>
    class Maximum
    {
    public:
        T value;
        bool is_satisfied(T const& t) { return t <= value; }
    };

    template<typename T>
    class Minimum
    {
    public:
        T value;
        bool is_satisfied(T const& t) { return t >= value; }
    };

    template<typename T>
    class Value
    {
    public:
        T value;
        bool is_within_range(auto const & range) { return range.contains(value); }
        bool is_below_range(auto const& range) { return range.locate(value) == Location::below_range; }
        bool is_above_range(auto const& range) { return range.locate(value) == Location::above_range; }
    };

    template<typename T, template<typename> class LowerBound, template<typename> class UpperBound>
    class Range
    {
    public:

        Range() = delete;

        Range(LowerBound<T>, UpperBound<T>);

        bool contains(T const& value);

        Location locate(T const& value);

    private:
        LowerBound<T> lower_bound;
        UpperBound<T> upper_bound;
    };

    template<typename T, template<typename> class LowerBound, template<typename> class UpperBound>
    Range<T, LowerBound, UpperBound>::Range(LowerBound<T> lb, UpperBound<T> ub) : lower_bound(lb), upper_bound(ub)
    {}

    template<typename T, template<typename> class LowerBound, template<typename> class UpperBound>
    bool Range<T, LowerBound, UpperBound>::contains(T const& value)
    {
        return lower_bound.is_satisfied(value) && upper_bound.is_satisfied(value);
    }

    template<typename T, template<typename> class LowerBound, template<typename> class UpperBound>
    Location Range<T, LowerBound, UpperBound>::locate(T const& value)
    {
        if      (!lower_bound.is_satisfied(value))  return Location::below_range;
        else if (!upper_bound.is_satisfied(value))  return Location::above_range;
        else                                        return Location::in_range;
    }


    
} //namespace

#endif //header guard