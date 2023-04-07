#include "../source/snrt_ranges_range.hpp"
#include <iostream>
#include <cassert>

int main()
{
    {
        auto itr = snrt::RangeIterator<int, snrt::Direction::forward>{2};

        assert(*itr == 2);

        auto a = itr++;

        assert(*a == 2);
        assert(*itr == 3);

        auto b = ++itr;

        assert(*b == 4);
        assert(*itr == 4);

        auto itr2 = snrt::RangeIterator<int, snrt::Direction::forward>{4};
        assert(itr == itr2);

        itr2++;
        assert(itr != itr2);
    }

    {
        auto const lower_bound = snrt::Minimum{200};
        auto const upper_bound = snrt::LessThan{204};
        auto const int_range = snrt::Range{lower_bound, upper_bound};

        auto cbegin = int_range.cbegin();
        assert(*cbegin == 200);
    }
    
    {
        auto const lower_bound = snrt::GreaterThan{200};
        auto const upper_bound = snrt::LessThan{204};
        auto const int_range = snrt::Range{lower_bound, upper_bound};

        auto cbegin = int_range.cbegin();
        assert(*cbegin == 201);
    }
}