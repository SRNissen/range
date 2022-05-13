#ifndef SNRT_RANGES_RANGE_HPP
#define SNRT_RANGES_RANGE_HPP

#include "snrt_ranges_bounds.hpp"
#include "snrt_ranges_exceptions.hpp"
#include "snrt_ranges_location.hpp"

namespace snrt
{

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
	{
		static_assert(LowerBound<T>::is_lower_bound == true);
		static_assert(UpperBound<T>::is_upper_bound == true);

		if (upper_bound.value < lower_bound.value)
			throw snrt::exception::InvertedRange{};
	}

	template<typename T, template<typename> class LowerBound, template<typename> class UpperBound>
	bool Range<T, LowerBound, UpperBound>::contains(T const& value)
	{
		return lower_bound.is_satisfied(value) && upper_bound.is_satisfied(value);
	}

	template<typename T, template<typename> class LowerBound, template<typename> class UpperBound>
	Location Range<T, LowerBound, UpperBound>::locate(T const& value)
	{
		if (!lower_bound.is_satisfied(value))
			return Location::below_range;

		else if (!upper_bound.is_satisfied(value))
			return Location::above_range;

		else
			return Location::in_range;
	}

} //namespace

#endif //header guard