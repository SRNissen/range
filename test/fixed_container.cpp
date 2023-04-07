#include "../source/snrt_ranges_range.hpp"
#include <iostream>
#include <cassert>

int main()
{
    using FW = snrt::RangeIterator<int, snrt::Direction::forward>;
    using RW = snrt::RangeIterator<int, snrt::Direction::backward>;

    {
        auto itrFW = FW{10};
        std::advance(itrFW, 5);
        assert(*itrFW == 15);

        auto itrRW = RW{10};
        std::advance(itrRW, 4);
        assert(*itrRW == 6);
    }

    {
        // en.cppreference.com/w/cpp/iterator/reverse_iterator
        // > For a reverse iterator r constructed from an iterator i,
        // > the relationship
        // >
        // > &*r == &*(i - 1)
        // >
        // > is always true (as long as r is dereferenceable);
        // > thus a reverse iterator constructed from a one-past-the-end
        // > iterator dereferences to the last element in a sequence.

        auto i = FW{10};
        auto r = std::reverse_iterator{i};

        assert(*r == *(i - 1));
        r++;
        r++;
        assert(*r == *(i - 3));
    }

    // Operator++
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
        auto itr = snrt::RangeIterator<int, snrt::Direction::forward>{2};
        auto a = --itr;
        assert(*a == 1);

        auto b = itr--;
        assert(*b == 1);
        assert(*itr == 0);
    }

    {
        auto itr = snrt::RangeIterator<int, snrt::Direction::forward>{2};
        itr += 2;
        assert(*itr == 4);
        auto itr7 = itr + 3;
        assert(*itr7 == 7);
    }

    {
        auto itr = snrt::RangeIterator<int, snrt::Direction::forward>{7};
        itr -= 2;
        assert(*itr == 5);
        auto itr2 = itr - 3;
        assert(*itr2 == 2);
    }

    {
        auto itr = snrt::RangeIterator<int, snrt::Direction::backward>{2};
        auto a = --itr;
        assert(*a == 3);

        auto b = itr--;
        assert(*b == 3);
        assert(*itr == 4);
    }

    {
        auto itr = snrt::RangeIterator<int, snrt::Direction::backward>{10};
        itr += 2;
        assert(*itr == 8);
        auto itr5 = itr + 3;
        assert(*itr5 == 5);
    }

    {
        auto itr = snrt::RangeIterator<int, snrt::Direction::backward>{10};
        itr -= 2;
        assert(*itr == 12);
        auto itr15 = itr - 3;
        assert(*itr15 == 15);
    }

    // {
    //     auto itr = snrt::RangeIterator<int, snrt::Direction::forward>{2};

    //     std::advance(itr, 2);

    //     assert(*itr == 4);
    // }

    {
        auto itrA = snrt::RangeIterator<int, snrt::Direction::forward>{2};
        auto itrB = snrt::RangeIterator<int, snrt::Direction::forward>{2};

        assert(itrA == itrB);
        assert(itrA <= itrB);
        assert(itrA >= itrB);

        assert(itrB == itrA);
        assert(itrB <= itrA);
        assert(itrB >= itrA);

        itrB++;

        assert(itrA != itrB);
        assert(itrB != itrA);
    }

    {
        auto itr2 = snrt::RangeIterator<int, snrt::Direction::forward>{2};
        auto itr3 = snrt::RangeIterator<int, snrt::Direction::forward>{3};

        assert(itr2 < itr3);
        assert(itr2 <= itr3);

        assert(itr3 > itr2);
        assert(itr3 >= itr2);
    }

    {
        auto itr2 = snrt::RangeIterator<int, snrt::Direction::forward>{2};
        auto itr4 = itr2 + 2;
        assert(*itr4 == 4);
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

    {
        auto const range = snrt::Range{snrt::Minimum{0}, snrt::LessThan{10}};

        auto cbegin = range.cbegin();
        assert(*cbegin == 0);
        assert((*(++cbegin)) == 1);
    }

    {
        auto const range = snrt::Range{snrt::Minimum{0}, snrt::LessThan{10}};

        auto cend = range.cend();
        assert(*cend == 10);
    }

    {
        auto const range = snrt::Range{snrt::Minimum{0}, snrt::Maximum{10}};

        auto cend = range.cend();
        assert(*cend == 11);
    }

    // C++11 style Range-based for loop
    {
        int a = 0;
        auto const range = snrt::Range{snrt::Minimum{1}, snrt::Maximum{4}};

        for (auto val : range)
            a += val;

        assert(a == 1 + 2 + 3 + 4);
    }

    // Forward iteration from begin
    {
        int a = 0;
        auto const range = snrt::Range{snrt::Minimum{1}, snrt::Maximum{4}};

        for (auto itr = range.begin(); itr != range.end(); ++itr)
            a += *itr;

        assert(a == 1 + 2 + 3 + 4);
    }

    // Forward iteration from cbegin
    {
        int a = 0;
        auto const range = snrt::Range{snrt::Minimum{1}, snrt::Maximum{4}};

        for (auto itr = range.cbegin(); itr != range.cend(); ++itr)
            a += *itr;

        assert(a == 1 + 2 + 3 + 4);
    }

    // Forward iteration from rbegin
    {
        int a = 0;
        auto const range = snrt::Range{snrt::Minimum{1}, snrt::Maximum{4}};

        for (auto itr = range.rbegin(); itr != range.rend(); ++itr)
            a += *itr;

        assert(a == 1 + 2 + 3 + 4);
    }

    // Forward iteration from crbegin
    {
        int a = 0;
        auto const range = snrt::Range{snrt::Minimum{1}, snrt::Maximum{4}};

        for (auto itr = range.crbegin(); itr != range.crend(); ++itr)
            a += *itr;

        assert(a == 1 + 2 + 3 + 4);
    }

    // Reverse iteration to begin
    {
        int a = 0;
        auto const range = snrt::Range{snrt::Minimum{1}, snrt::Maximum{4}};

        for (auto itr = --(range.end()); itr >= range.begin(); --itr)
            a += *itr;

        assert(a == 1 + 2 + 3 + 4);
    }

    // Reverse iteration to cbegin
    {
        int a = 0;
        auto const range = snrt::Range{snrt::Minimum{1}, snrt::Maximum{4}};

        for (auto itr = --(range.cend()); itr >= range.cbegin(); --itr)
            a += *itr;

        assert(a == 1 + 2 + 3 + 4);
    }

    // Reverse iteration to rbegin
    {
        int a = 0;
        auto const range = snrt::Range{snrt::Minimum{1}, snrt::Maximum{4}};

        for (auto itr = --(range.rend()); itr >= range.rbegin(); --itr)
            a += *itr;

        assert(a == 1 + 2 + 3 + 4);
    }

    // Reverse iteration to crbegin
    {
        int a = 0;
        auto const range = snrt::Range{snrt::Minimum{1}, snrt::Maximum{4}};

        for (auto itr = --(range.crend()); itr >= range.crbegin(); --itr)
            a += *itr;

        assert(a == 1 + 2 + 3 + 4);
    }
}