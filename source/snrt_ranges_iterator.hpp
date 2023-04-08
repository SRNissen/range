#ifndef SNRT_RANGES_ITERATOR_HPP
#define SNRT_RANGES_ITERATOR_HPP

#include <cstddef>
#include <iterator>
#include <type_traits>

namespace snrt
{
	template <typename T>
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

		static_assert(std::is_integral_v<T>,
					  "\n"
					  "\n###################################"
					  "\n# If you are seeing this compiler #"
					  "\n# error, you tried to call one of #"
					  "\n#                                 #"
					  "\n# - front,                        #"
					  "\n# - back,                         #"
					  "\n# - begin, (or c- or r-begin)     #"
					  "\n# - end,   (or c- or r-end)       #"
					  "\n#                                 #"
					  "\n# on an snrt::Range<T,L,U> where  #"
					  "\n# T was not an integral type.     #"
					  "\n# Unfortunately, those calls      #"
					  "\n# only work when T is integral    #"
					  "\n###################################");

	private:
		T t;
	};
}

#endif