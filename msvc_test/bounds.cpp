#include "CppUnitTest.h"
#include "snrt_ranges_bounds.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace snrt_test::bounds
{
	constexpr auto one = 1.0;
	constexpr auto a_lot = 1000000.0;
	constexpr auto epsilon = one / a_lot;
	
	constexpr auto bound_value = 10.0;


	namespace minimum
	{
		constexpr auto minimum = snrt::Minimum{ bound_value };

		TEST_CLASS(is_not_satisfied_by_values)
		{
		public:

			TEST_METHOD(one_below_the_bound)
			{
				Assert::IsFalse(minimum.is_satisfied(bound_value - one));
			}

			TEST_METHOD(epsilon_below_the_bound)
			{
				Assert::IsFalse(minimum.is_satisfied(bound_value - epsilon));
			}

			TEST_METHOD(a_lot_below_the_bound)
			{
				Assert::IsFalse(minimum.is_satisfied(bound_value - a_lot));
			}
		};

		TEST_CLASS(is_satisfied_by_values)
		{
			TEST_METHOD(zero_above_the_bound)
			{
				Assert::IsTrue(minimum.is_satisfied(bound_value));
			}

			TEST_METHOD(epsilon_above_the_bound)
			{
				Assert::IsTrue(minimum.is_satisfied(bound_value + epsilon));
			}

			TEST_METHOD(one_above_the_bound)
			{
				Assert::IsTrue(minimum.is_satisfied(bound_value + one));
			}

			TEST_METHOD(a_lot_above_the_bound)
			{
				Assert::IsTrue(minimum.is_satisfied(bound_value + a_lot));
			}
		};
	}

	namespace maximum
	{
		constexpr auto maximum = snrt::Maximum{ bound_value };

		TEST_CLASS(is_not_satisfied_by_values)
		{
		public:

			TEST_METHOD(one_above_the_bound)
			{
				Assert::IsFalse(maximum.is_satisfied(bound_value + one));
			}

			TEST_METHOD(epsilon_above_the_bound)
			{
				Assert::IsFalse(maximum.is_satisfied(bound_value + epsilon));
			}

			TEST_METHOD(a_lot_above_the_bound)
			{
				Assert::IsFalse(maximum.is_satisfied(bound_value + a_lot));
			}
		};

		TEST_CLASS(is_satisfied_by_values)
		{
			TEST_METHOD(zero_below_the_bound)
			{
				Assert::IsTrue(maximum.is_satisfied(bound_value));
			}

			TEST_METHOD(epsilon_below_the_bound)
			{
				Assert::IsTrue(maximum.is_satisfied(bound_value - epsilon));
			}

			TEST_METHOD(one_below_the_bound)
			{
				Assert::IsTrue(maximum.is_satisfied(bound_value - one));
			}

			TEST_METHOD(a_lot_below_the_bound)
			{
				Assert::IsTrue(maximum.is_satisfied(bound_value - a_lot));
			}
		};
	}

	namespace greater_than
	{
		constexpr auto greater_than = snrt::GreaterThan{ bound_value };

		TEST_CLASS(is_not_satisfied_by_values)
		{
		public:

			TEST_METHOD(one_below_the_bound)
			{
				Assert::IsFalse(greater_than.is_satisfied(bound_value - one));
			}

			TEST_METHOD(epsilon_below_the_bound)
			{
				Assert::IsFalse(greater_than.is_satisfied(bound_value - epsilon));
			}

			TEST_METHOD(a_lot_below_the_bound)
			{
				Assert::IsFalse(greater_than.is_satisfied(bound_value - a_lot));
			}

			TEST_METHOD(zero_below_the_bound)
			{
				Assert::IsFalse(greater_than.is_satisfied(bound_value));
			}
		};

		TEST_CLASS(is_satisfied_by_values)
		{
			TEST_METHOD(epsilon_above_the_bound)
			{
				Assert::IsTrue(greater_than.is_satisfied(bound_value + epsilon));
			}

			TEST_METHOD(one_above_the_bound)
			{
				Assert::IsTrue(greater_than.is_satisfied(bound_value + one));
			}

			TEST_METHOD(a_lot_above_the_bound)
			{
				Assert::IsTrue(greater_than.is_satisfied(bound_value + a_lot));
			}
		};
	}

	namespace less_than
	{
		constexpr auto less_than = snrt::LessThan{ bound_value };

		TEST_CLASS(is_not_satisfied_by_values)
		{
		public:

			TEST_METHOD(one_above_the_bound)
			{
				Assert::IsFalse(less_than.is_satisfied(bound_value + one));
			}

			TEST_METHOD(epsilon_above_the_bound)
			{
				Assert::IsFalse(less_than.is_satisfied(bound_value + epsilon));
			}

			TEST_METHOD(a_lot_above_the_bound)
			{
				Assert::IsFalse(less_than.is_satisfied(bound_value + a_lot));
			}

			TEST_METHOD(zero_above_the_bound)
			{
				Assert::IsFalse(less_than.is_satisfied(bound_value));
			}
		};

		TEST_CLASS(is_satisfied_by_values)
		{


			TEST_METHOD(epsilon_below_the_bound)
			{
				Assert::IsTrue(less_than.is_satisfied(bound_value - epsilon));
			}

			TEST_METHOD(one_below_the_bound)
			{
				Assert::IsTrue(less_than.is_satisfied(bound_value - one));
			}

			TEST_METHOD(a_lot_below_the_bound)
			{
				Assert::IsTrue(less_than.is_satisfied(bound_value - a_lot));
			}
		};
	}

	
}