#ifndef SNRT_RANGE_HPP
#define SNRT_RANGE_HPP

namespace snrt
{

    template<typename T>
    struct Value
    {
        T value;
        
        bool is_in_range(auto range)
        {
            return range.contains(value);
        }
    };
    
    
    
    template<typename LowerLimit, typename UpperLimit>
    struct Range
    {
        Range() = delete;
        
        Range(LowerLimit, UpperLimit);
        
        bool contains(auto value);
        
        private:
        LowerLimit lower_limit;
        UpperLimit upper_limit;
    }
    
} //namespace

#endif //header guard