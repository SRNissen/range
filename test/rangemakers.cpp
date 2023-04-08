#include "../source/snrt_ranges_make.hpp"

#include <iostream>
#include <cassert>

void test();

int main()
{
    std::cout << "    " << __FILE__ << " compiled succesfully\n"
              << std::flush;
    test();
    std::cout << "    " << __FILE__ << " test ran to completion\n"
              << std::flush;
}

void test()
{
    auto two_three = snrt::make_range<'[', ']'>(2, 3);
    assert(!two_three.contains(1));
    assert(two_three.contains(2));
    assert(two_three.contains(3));
    assert(!two_three.contains(4));
}