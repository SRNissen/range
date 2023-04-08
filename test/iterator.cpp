#include "../source/snrt_ranges_iterator.hpp"
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
    

    using FW = snrt::RangeIterator<int>;
    using RW = std::reverse_iterator<snrt::RangeIterator<int>>;

    {
        auto itrFW = FW{10};
        std::advance(itrFW, 5);
        assert(*itrFW == 15);
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
        
        auto itrRW = RW{10}; // if 10 is the end, this points to 9 (rbegin)
        std::advance(itrRW, 4); // so this "advances" 4 in the reverse direction
        assert(*itrRW == 5); //to 5
    }

    // Operator++
    {
        auto itr = FW{2};

        assert(*itr == 2);

        auto a = itr++;

        assert(*a == 2);
        assert(*itr == 3);

        auto b = ++itr;

        assert(*b == 4);
        assert(*itr == 4);

        auto itr2 = FW{4};
        assert(itr == itr2);

        itr2++;
        assert(itr != itr2);
    }

    {
        auto itr = FW{2};
        auto a = --itr;
        assert(*a == 1);

        auto b = itr--;
        assert(*b == 1);
        assert(*itr == 0);
    }

    {
        auto itr = FW{2};
        itr += 2;
        assert(*itr == 4);
        auto itr7 = itr + 3;
        assert(*itr7 == 7);
    }

    {
        auto itr = FW{7};
        itr -= 2;
        assert(*itr == 5);
        auto itr2 = itr - 3;
        assert(*itr2 == 2);
    }

    {
        auto itr = RW{2};
        auto a = --itr;
        assert(*a == 2);

        auto b = itr--;
        assert(*b == 2);
        assert(*itr == 3);
    }

    {
        auto itr = RW{10};
        itr += 2;
        assert(*itr == 7);
        auto itr4 = itr + 3;
        assert(*itr4 == 4);
    }

    {
        auto itr = RW{10};
        itr -= 2;
        assert(*itr == 11);
        auto itr14 = itr - 3;
        assert(*itr14 == 14);
    }


    {
        auto itrA = FW{2};
        auto itrB = FW{2};

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
        auto itr2 = FW{2};
        auto itr3 = FW{3};

        assert(itr2 < itr3);
        assert(itr2 <= itr3);

        assert(itr3 > itr2);
        assert(itr3 >= itr2);
    }

    {
        auto itr2 = FW{2};
        auto itr4 = itr2 + 2;
        assert(*itr4 == 4);
    }
}