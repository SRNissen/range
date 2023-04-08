#include "../source/snrt_ranges_range.hpp"
#include <iostream>
#include <cassert>


void test();

int main()
{
    std::cout << "    " << __FILE__ << " compiled succesfully\n" << std::flush;
    test();
    std::cout << "    " << __FILE__ << " test ran to completion\n" << std::flush; 
}

void test()
{
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
    
    // Back and front
    {
        auto const range = snrt::Range{snrt::Minimum{1}, snrt::Maximum{4}};
        assert(range.front() == 1);
        assert(range.back() == 4);
    }
}