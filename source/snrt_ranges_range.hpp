#ifndef SNRT_RANGES_RANGE_HPP
#define SNRT_RANGES_RANGE_HPP

#include <type_traits>
#include <cstddef>
#include <iterator>
#include "snrt_ranges_bounds.hpp"
#include "snrt_ranges_exceptions.hpp"
#include "snrt_ranges_location.hpp"

namespace snrt
{
	enum class Direction
	{
		forward,
		backward
	};

	template <typename T, Direction D>
	struct RangeIterator
	{
		using difference_type = std::ptrdiff_t;
		using value_type = std::remove_cv_t<T>;
		using pointer = T*;
		using reference = T&;
		using iterator_category = std::random_access_iterator_tag;
		
		static_assert(std::is_integral_v<T>);

		RangeIterator(T initial_value) : t{initial_value} {}

		constexpr T operator*()
		{
			return t;
		}

		template <typename I>
		constexpr RangeIterator& operator+=(I i)
		{
			static_assert(std::is_integral_v<I>);
			
			if constexpr(D == Direction::forward)
				t += i;
			else
				t -= i;

			return *this;
		}

		template <typename I>
		constexpr RangeIterator operator+(I i) const
		{
			static_assert(std::is_integral_v<I>);
			
			RangeIterator temp(*this);

			return temp += i;
		}
		
		template <typename I>
		constexpr RangeIterator& operator-=(I i)
		{
			static_assert(std::is_integral_v<I>);
			
			if constexpr (D == Direction::forward)
				t -= i;
			else
				t += i;

			return *this;
		}

		template <typename I>
		constexpr RangeIterator operator-(I i) const
		{
			static_assert(std::is_integral_v<I>);
			
			RangeIterator temp(*this);

			return temp -= i;
		}

		constexpr RangeIterator operator++(int)
		{
			RangeIterator temp = *this;
			
			if constexpr (D == Direction::forward)
				t += 1;
			else
				t -= 1;

			return temp;
		}

		constexpr RangeIterator& operator++()
		{
			if constexpr (D == Direction::forward)
				t += 1;
			else
				t -= 1;

			return *this;
		}

		constexpr RangeIterator operator--(int)
		{
			RangeIterator temp = *this;
			
			if constexpr (D == Direction::forward)
				t -= 1;
			else
				t += 1;

			return temp;
		}

		constexpr RangeIterator& operator--()
		{
			if constexpr (D == Direction::forward)
				t -= 1;
			else
				t += 1;

			return *this;
		}

		constexpr bool operator==(RangeIterator<T, D> other) const
		{
			return t == other.t;
		}

		constexpr bool operator!=(RangeIterator<T, D> other) const
		{
			return t != other.t;
		}

		constexpr bool operator<(RangeIterator<T, D> other) const
		{
			if constexpr (D == Direction::forward)
				return t < other.t;
			else
				return other.t < t;
		}

		constexpr bool operator<=(RangeIterator<T, D> other) const
		{
			return (*this < other) || (*this == other);
		}

		constexpr bool operator>(RangeIterator<T, D> other) const
		{
			if constexpr (D == Direction::forward)
				return t > other.t;
			else
				return other.t > t;
		}

		constexpr bool operator>=(RangeIterator<T, D> other) const
		{
			return (*this > other) || (*this == other);
		}

	private:
		T t;
	};

	template <typename T, template <typename> class LowerBound, template <typename> class UpperBound>
	class Range
	{
	public:
		Range() = delete;

		Range(LowerBound<T>, UpperBound<T>);

		[[nodiscard]] constexpr bool contains(T const &value) const;

		[[nodiscard]] constexpr Location locate(T const &value) const;

		constexpr RangeIterator<T, Direction::forward> cbegin() const
		{
			if constexpr (std::is_same_v<decltype(lower_bound), Minimum<T>>)
			{
				return {lower_bound.value};
			}
			else if constexpr (std::is_same_v<decltype(lower_bound), GreaterThan<T>>)
			{
				return {lower_bound.value + 1};
			}
		}

		constexpr RangeIterator<T, Direction::forward> begin() const
		{
			return cbegin();
		}

		constexpr RangeIterator<T, Direction::forward> cend() const
		{
			if constexpr (std::is_same_v<decltype(upper_bound), LessThan<T>>)
			{
				return {upper_bound.value};
			}
			else if (std::is_same_v<decltype(upper_bound), Maximum<T>>)
			{
				return {upper_bound.value + 1};
			}
		}

		constexpr RangeIterator<T, Direction::forward> end() const
		{
			return cend();
		}

		constexpr RangeIterator<T, Direction::backward> crbegin() const
		{
			if constexpr (std::is_same_v<decltype(upper_bound), LessThan<T>>)
			{
				return {upper_bound.value - 1};
			}
			else if (std::is_same_v<decltype(upper_bound), Maximum<T>>)
			{
				return {upper_bound.value};
			}
		}

		constexpr RangeIterator<T, Direction::backward> rbegin() const
		{
			return crbegin();
		}

		constexpr RangeIterator<T, Direction::backward> crend() const
		{
			if constexpr (std::is_same_v<decltype(lower_bound), Minimum<T>>)
			{
				return {lower_bound.value - 1};
			}
			else if constexpr (std::is_same_v<decltype(lower_bound), GreaterThan<T>>)
			{
				return {lower_bound.value};
			}
		}

		constexpr RangeIterator<T, Direction::backward> rend() const
		{
			return crend();
		}

		constexpr T back() const;
		constexpr T front() const;

	private:
		LowerBound<T> lower_bound;
		UpperBound<T> upper_bound;
	};

	template <typename T, template <typename> class LowerBound, template <typename> class UpperBound>
	Range<T, LowerBound, UpperBound>::Range(LowerBound<T> lb, UpperBound<T> ub) : lower_bound(lb), upper_bound(ub)
	{
		static_assert(LowerBound<T>::is_lower_bound == true);
		static_assert(UpperBound<T>::is_upper_bound == true);

		if (upper_bound.value < lower_bound.value)
			throw snrt::exception::InvertedRange{};
	}

	template <typename T, template <typename> class LowerBound, template <typename> class UpperBound>
	[[nodiscard]] constexpr bool Range<T, LowerBound, UpperBound>::contains(T const &value) const
	{
		return lower_bound.is_satisfied(value) && upper_bound.is_satisfied(value);
	}

	template <typename T, template <typename> class LowerBound, template <typename> class UpperBound>
	[[nodiscard]] constexpr Location Range<T, LowerBound, UpperBound>::locate(T const &value) const
	{
		if (!lower_bound.is_satisfied(value))
			return Location::below_range;

		else if (!upper_bound.is_satisfied(value))
			return Location::above_range;

		else
			return Location::in_range;
	}

} // namespace

#endif // header guard