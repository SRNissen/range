#ifndef SNRT_RANGES_ITERATOR_HPP
#define SNRT_RANGES_ITERATOR_HPP

#include <cstddef>
#include <iterator>
#include <type_traits>

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
		using pointer = T *;
		using reference = T &;
		using iterator_category = std::random_access_iterator_tag;

		static_assert(std::is_integral_v<T>);

		RangeIterator(T initial_value) : t{initial_value} {}

		constexpr T operator*()
		{
			return t;
		}

		constexpr RangeIterator &operator+=(std::integral auto i)
		{
			if constexpr (D == Direction::forward)
				t += i;
			else
				t -= i;

			return *this;
		}

		constexpr RangeIterator operator+(std::integral auto i) const
		{
			RangeIterator temp(*this);

			return temp += i;
		}

		constexpr RangeIterator &operator-=(std::integral auto i)
		{
			if constexpr (D == Direction::forward)
				t -= i;
			else
				t += i;

			return *this;
		}

		constexpr RangeIterator operator-(std::integral auto i) const
		{

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

		constexpr RangeIterator &operator++()
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

		constexpr RangeIterator &operator--()
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
}

#endif