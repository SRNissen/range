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

		[[nodiscard]] constexpr auto contains(T const &value) const -> bool;
		[[nodiscard]] constexpr auto locate(T const &value) const -> Location;



		// Element access functions only available when static_assert(std::is_integral_v<T> == true);
		[[nodiscard]] constexpr auto front() const -> T;
		[[nodiscard]] constexpr auto back() const -> T;

		[[nodiscard]] constexpr auto cbegin() const -> RangeIterator<T>;
		[[nodiscard]] constexpr auto cend() const -> RangeIterator<T>;

		[[nodiscard]] constexpr auto begin() const -> RangeIterator<T>;
		[[nodiscard]] constexpr auto end() const -> RangeIterator<T>;

		[[nodiscard]] constexpr auto crbegin() const -> std::reverse_iterator<RangeIterator<T>>;
		[[nodiscard]] constexpr auto crend() const -> std::reverse_iterator<RangeIterator<T>>;

		[[nodiscard]] constexpr auto rbegin() const -> std::reverse_iterator<RangeIterator<T>>;
		[[nodiscard]] constexpr auto rend() const -> std::reverse_iterator<RangeIterator<T>>;

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

	template <typename T, template <typename> class LowerBound, template <typename> class UpperBound>
	[[nodiscard]] constexpr RangeIterator<T> Range<T, LowerBound, UpperBound>::cbegin() const
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

	template <typename T, template <typename> class LowerBound, template <typename> class UpperBound>
	[[nodiscard]] constexpr RangeIterator<T> Range<T, LowerBound, UpperBound>::cend() const
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

	template <typename T, template <typename> class LowerBound, template <typename> class UpperBound>
	[[nodiscard]] constexpr RangeIterator<T> Range<T, LowerBound, UpperBound>::begin() const
	{
		return cbegin();
	}

	template <typename T, template <typename> class LowerBound, template <typename> class UpperBound>
	[[nodiscard]] constexpr RangeIterator<T> Range<T, LowerBound, UpperBound>::end() const
	{
		return cend();
	}

	template <typename T, template <typename> class LowerBound, template <typename> class UpperBound>
	[[nodiscard]] constexpr std::reverse_iterator<RangeIterator<T>> Range<T, LowerBound, UpperBound>::crbegin() const
	{
		return std::reverse_iterator{cend()};
	}

	template <typename T, template <typename> class LowerBound, template <typename> class UpperBound>
	[[nodiscard]] constexpr std::reverse_iterator<RangeIterator<T>> Range<T, LowerBound, UpperBound>::crend() const
	{
		return std::reverse_iterator{cbegin()};
	}

	template <typename T, template <typename> class LowerBound, template <typename> class UpperBound>
	[[nodiscard]] constexpr std::reverse_iterator<RangeIterator<T>> Range<T, LowerBound, UpperBound>::rbegin() const
	{
		return crbegin();
	}

	template <typename T, template <typename> class LowerBound, template <typename> class UpperBound>
	[[nodiscard]] constexpr std::reverse_iterator<RangeIterator<T>> Range<T, LowerBound, UpperBound>::rend() const
	{
		return crend();
	}

	template <typename T, template <typename> class LowerBound, template <typename> class UpperBound>
	[[nodiscard]] constexpr T Range<T, LowerBound, UpperBound>::front() const
	{
		
		return *begin();
	}

	template <typename T, template <typename> class LowerBound, template <typename> class UpperBound>
	[[nodiscard]] constexpr T Range<T, LowerBound, UpperBound>::back() const
	{
		return *rbegin();
	}

} // namespace

#endif // header guard