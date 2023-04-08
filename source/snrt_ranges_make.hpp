#ifndef SNRT_RANGES_MAKE_HPP
#define SNRT_RANGES_MAKE_HPP

#include <type_traits>
#include "snrt_ranges_range.hpp"

namespace snrt
{
	template <char LowerBound, char UpperBound>
	constexpr auto make_range(auto const &lower_bound, auto const &upper_bound)
	{
		static_assert(std::is_same_v<decltype(lower_bound), decltype(upper_bound)>);
		
//		using T = decltype(lower_bound);

		if constexpr(LowerBound == '[' && UpperBound == ']')
		{
			return snrt::Range{snrt::Minimum{lower_bound}, snrt::Maximum{upper_bound}};
		}
	}
}

#endif