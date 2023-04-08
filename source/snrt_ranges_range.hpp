#ifndef SNRT_RANGES_RANGE_HPP
#define SNRT_RANGES_RANGE_HPP

#include <type_traits>
#include "snrt_ranges_bounds.hpp"
#include "snrt_ranges_exceptions.hpp"
#include "snrt_ranges_location.hpp"
#include "snrt_ranges_iterator.hpp"

namespace snrt
{

	template <typename T, template <typename> class LowerBound, template <typename> class UpperBound>
	class Range
	{
	public:
		Range() = delete;

		Range(LowerBound<T>, UpperBound<T>);

		[[nodiscard]] constexpr bool contains(T const &value) const;

		[[nodiscard]] constexpr Location locate(T const &value) const;

		constexpr RangeIterator<T> cbegin() const
		{
			if constexpr (std::is_same_v<decltype(lower_bound_), Minimum<T>>)
			{
				return {lower_bound_.value};
			}
			else if constexpr (std::is_same_v<decltype(lower_bound_), GreaterThan<T>>)
			{
				return {lower_bound_.value + 1};
			}
		}

		constexpr RangeIterator<T> begin() const
		{
			return cbegin();
		}

		constexpr RangeIterator<T> cend() const
		{
			if constexpr (std::is_same_v<decltype(upper_bound_), LessThan<T>>)
			{
				return {upper_bound_.value};
			}
			else if (std::is_same_v<decltype(upper_bound_), Maximum<T>>)
			{
				return {upper_bound_.value + 1};
			}
		}

		constexpr RangeIterator<T> end() const
		{
			return cend();
		}

		constexpr auto crbegin() const
		{
			return std::reverse_iterator{cend()};
		}

		constexpr auto rbegin() const
		{
			return crbegin();
		}

		constexpr auto crend() const
		{
			return std::reverse_iterator{cbegin()};
		}

		constexpr auto rend() const
		{
			return crend();
		}

		constexpr T back() const
		{
			return *crbegin();
		}
		
		constexpr T front() const
		{
			return *begin();
		}
		

	private:
		LowerBound<T> lower_bound_;
		UpperBound<T> upper_bound_;
	};

	template <typename T, template <typename> class LowerBound, template <typename> class UpperBound>
	Range<T, LowerBound, UpperBound>::Range(LowerBound<T> lb, UpperBound<T> ub) : lower_bound_(lb), upper_bound_(ub)
	{
		static_assert(LowerBound<T>::is_lower_bound == true);
		static_assert(UpperBound<T>::is_upper_bound == true);

		if (upper_bound_.value < lower_bound_.value)
			throw snrt::exception::InvertedRange{};
	}

	template <typename T, template <typename> class LowerBound, template <typename> class UpperBound>
	[[nodiscard]] constexpr bool Range<T, LowerBound, UpperBound>::contains(T const &value) const
	{
		return lower_bound_.is_satisfied(value) && upper_bound_.is_satisfied(value);
	}

	template <typename T, template <typename> class LowerBound, template <typename> class UpperBound>
	[[nodiscard]] constexpr Location Range<T, LowerBound, UpperBound>::locate(T const &value) const
	{
		if (!lower_bound_.is_satisfied(value))
			return Location::below_range;

		else if (!upper_bound_.is_satisfied(value))
			return Location::above_range;

		else
			return Location::in_range;
	}

} // namespace

#endif // header guard