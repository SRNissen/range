#ifndef SNRT_RANGES_ITERATOR_HPP
#define SNRT_RANGES_ITERATOR_HPP

#include <cstddef>
#include <iterator>
#include <type_traits>

namespace snrt
{
	template <std::integral T>
	struct RangeIterator
	{
		using difference_type = std::ptrdiff_t;
		using value_type = std::remove_cv_t<T>;
		using pointer = T *;
		using reference = T &;
		using iterator_category = std::random_access_iterator_tag;

		RangeIterator(T initial_value) : t{initial_value} {}

		constexpr T operator*()
		{
			return t;
		}

		constexpr RangeIterator &operator+=(std::integral auto i)
		{
			t += i;
			return *this;
		}

		constexpr RangeIterator operator+(std::integral auto i) const
		{
			RangeIterator temp(*this);
			return temp += i;
		}

		constexpr RangeIterator &operator-=(std::integral auto i)
		{
			t -= i;
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
			t += 1;
			return temp;
		}

		constexpr RangeIterator &operator++()
		{
			t += 1;
			return *this;
		}

		constexpr RangeIterator operator--(int)
		{
			RangeIterator temp = *this;
			t -= 1;
			return temp;
		}

		constexpr RangeIterator &operator--()
		{
			t -= 1;
			return *this;
		}

		constexpr bool operator==(RangeIterator other) const
		{
			return t == other.t;
		}

		constexpr bool operator!=(RangeIterator other) const
		{
			return t != other.t;
		}

		constexpr bool operator<(RangeIterator other) const
		{
			return t < other.t;
		}

		constexpr bool operator<=(RangeIterator other) const
		{
			return (*this < other) || (*this == other);
		}

		constexpr bool operator>(RangeIterator other) const
		{
				return t > other.t;
		}

		constexpr bool operator>=(RangeIterator other) const
		{
			return (*this > other) || (*this == other);
		}

	private:
		T t;
	};
}

#endif