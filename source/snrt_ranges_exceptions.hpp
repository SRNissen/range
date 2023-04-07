#ifndef SNRT_RANGES_EXCEPTIONS_HPP
#define SNRT_RANGES_EXCEPTIONS_HPP

#include <exception>

namespace snrt::exception
{
    class InvertedRange : public std::exception
    {
    };
}

#endif //header guard