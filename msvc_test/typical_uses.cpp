#include "CppUnitTest.h"

#include <string>

#include "snrt_ranges.hpp"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace typical_use_A
{
	TEST_CLASS(Constructing_an_snrt_Range_that_is)
	{
		TEST_METHOD(inclusive_inclusive)
		{
			auto const lower_bound = snrt::Minimum{ 'b' };
			auto const upper_bound = snrt::Maximum{ 'd' };

			auto const char_range = snrt::Range{ lower_bound, upper_bound };

			Assert::IsFalse(char_range.contains('a'));

			Assert::IsTrue(char_range.contains('b'));
			Assert::IsTrue(char_range.contains('c'));
			Assert::IsTrue(char_range.contains('d'));

			Assert::IsFalse(char_range.contains('e'));
		}

		TEST_METHOD(inclusive_exclusive)
		{
			auto const lower_bound = snrt::Minimum{ 200 };
			auto const upper_bound = snrt::LessThan{ 204 };

			auto const int_range = snrt::Range{ lower_bound, upper_bound };

			Assert::IsFalse(int_range.contains(199));

			Assert::IsTrue(int_range.contains(201));
			Assert::IsTrue(int_range.contains(202));
			Assert::IsTrue(int_range.contains(203));

			Assert::IsFalse(int_range.contains(204));
		}

		TEST_METHOD(exclusive_inclusive)
		{
			auto const lower_bound = snrt::GreaterThan{ 10.0 };
			auto const upper_bound = snrt::Maximum{ 11.0 };

			auto const double_range = snrt::Range{ lower_bound, upper_bound };

			auto constexpr epsilon = 1.0 / 10000000.0;

			Assert::IsFalse(double_range.contains(10.0));

			Assert::IsTrue(double_range.contains(10.0 + epsilon));
			Assert::IsTrue(double_range.contains(10.5));
			Assert::IsTrue(double_range.contains(11.0));

			Assert::IsFalse(double_range.contains(11.0 + epsilon));
		}

		TEST_METHOD(exclusive_exclusive)
		{
			auto const lower_bound = snrt::GreaterThan{ std::string{"Jules"} };
			auto const upper_bound = snrt::LessThan{ std::string{"Mike"} };

			auto const string_range = snrt::Range{ lower_bound, upper_bound };

			Assert::IsFalse(string_range.contains("Jules"));

			Assert::IsTrue(string_range.contains("Kim"));

			Assert::IsFalse(string_range.contains("Mike"));
		}
	};
}

namespace typical_use_B
{
	TEST_CLASS(Using_an_snrt_Range_to)
	{
		TEST_METHOD(Determine_whether_a_value_is_contained_by_a_range)
		{
			auto const range = snrt::Range{ snrt::GreaterThan{2}, snrt::LessThan{4} };

			if (range.contains(3))
				Assert::IsTrue(true);
			else
				Assert::Fail();
		}

		TEST_METHOD(Locate_a_value_compared_to_the_range)
		{
			auto const range = snrt::Range{ snrt::GreaterThan{2}, snrt::LessThan{4} };
			auto constexpr value = 3;

			switch (range.locate(value))
			{
			case snrt::below_range:
			{
				Assert::Fail();
				break;
			}
			case snrt::above_range:
			{
				Assert::Fail();
				break;
			}
			case snrt::in_range:
			{
				Assert::IsTrue(range.contains(value));
				break;
			}
			}
		}
	};
}

namespace typical_use_C
{
	TEST_CLASS(Using_an_snrt_Value_to)
	{
		TEST_METHOD(Determine_whether_a_value_is_in_a_range)
		{
			auto const value = snrt::Value{ 2.5 };

			auto const range = snrt::Range{ snrt::Minimum{2.0}, snrt::Maximum{3.0} };

			if (value.is_in_range(range))
				Assert::IsTrue(range.locate(value) == snrt::in_range);
			else
				Assert::Fail();
		}

		TEST_METHOD(Determine_whether_a_value_is_below_a_range)
		{
			auto const value = snrt::Value{ 1.5 };

			auto const range = snrt::Range{ snrt::Minimum{2.0}, snrt::Maximum{3.0} };

			if (value.is_below_range(range))
				Assert::IsTrue(range.locate(value) == snrt::below_range);
			else
				Assert::Fail();
		}

		TEST_METHOD(Determine_whether_a_value_is_above_a_range)
		{
			auto const value = snrt::Value{ 3.5 };

			auto const range = snrt::Range{ snrt::Minimum{2.0}, snrt::Maximum{3.0} };

			if (value.is_above_range(range))
				Assert::IsTrue(range.locate(value) == snrt::above_range);
			else
				Assert::Fail();
		}

		TEST_METHOD(Locate_a_value_compared_to_the_range)
		{
			auto const value = snrt::Value{ 1.5 };
			auto const range = snrt::Range{ snrt::Minimum{2.0}, snrt::Maximum{3.0} };

			switch (value.locate_compared_to_range(range))
			{
			case snrt::below_range:
				Assert::IsTrue(range.locate(value) == snrt::below_range);
				break;
			default:
				Assert::Fail();
			}
		}
	};
}