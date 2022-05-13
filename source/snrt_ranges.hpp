#ifndef SNRT_RANGE_HPP
#define SNRT_RANGE_HPP


#include "snrt_ranges_range.hpp"
/*
*	Introduces class Range<T, LowerBound<T>, UpperBound<T>>
*
*	Constructed so:
*		auto my_range = snrt::Range<double, snrt::GreaterThan<1.0>, snrt::Maximum<100.0>>;
* 
*	Used so:
*		if( my_range.contains(my_value) )
* 
*	or so:
*		switch( my_range.locate(my_value) )
*			case below_range:
*			case above_range:
*			case in_range:
*/



#include "snrt_ranges_value.hpp"
/*
*	introduces class Value<T>
*	
*	constructed so:
*		auto my_value = Value(50.0);
* 
*	Used so:
*		if(my_value.is_within_range(my_range))
*
*	Or so:
*		if(my_value.is_below_range(my_range))
* 
*	Or so:
*		if(my_value.is_above_range(my_range))
* 
*	Or so:
*		auto location = my_value.location_in_range(my_range); //Location::above_range, Location::below_range or Location::in_range
*/


#endif //header guard