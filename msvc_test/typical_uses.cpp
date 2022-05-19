#include "CppUnitTest.h"

#include <string>

#include "snrt_ranges.hpp"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace typical_uses
{
	namespace scenario_A
	{
		TEST_CLASS(Constructing_an_snrt_Range)
		{
			TEST_METHOD(That_is_inclusive_inclusive)
			{
				auto lower_bound = snrt::bounds::Minimum{ 'b' };
				auto upper_bound = snrt::bounds::Maximum{ 'd' };

				auto char_range = snrt::Range{ lower_bound, upper_bound };

				Assert::IsFalse(char_range.contains('a'));

				Assert::IsTrue(char_range.contains('b'));
				Assert::IsTrue(char_range.contains('c'));
				Assert::IsTrue(char_range.contains('d'));
				
				Assert::IsFalse(char_range.contains('e'));
			}

			TEST_METHOD(That_is_inclusive_exclusive)
			{
				auto lower_bound = snrt::bounds::Minimum{ 200 };
				auto upper_bound = snrt::bounds::LessThan{ 204 };

				auto int_range = snrt::Range{ lower_bound, upper_bound };

				Assert::IsFalse(int_range.contains(199));

				Assert::IsTrue(int_range.contains(201));
				Assert::IsTrue(int_range.contains(202));
				Assert::IsTrue(int_range.contains(203));

				Assert::IsFalse(int_range.contains(204));
			}

			TEST_METHOD(That_is_exclusive_inclusive)
			{
				auto lower_bound = snrt::bounds::GreaterThan{ 10.0 };
				auto upper_bound = snrt::bounds::Maximum{ 11.0 };

				auto double_range = snrt::Range{ lower_bound, upper_bound };

				auto const epsilon = 1.0 / 10000000.0;

				Assert::IsFalse(double_range.contains(10.0));

				Assert::IsTrue(double_range.contains(10.0 + epsilon));
				Assert::IsTrue(double_range.contains(10.5));
				Assert::IsTrue(double_range.contains(11.0));

				Assert::IsFalse(double_range.contains(11.0 + epsilon));

			}

			TEST_METHOD(That_is_exclusive_exclusive)
			{
				auto lower_bound = snrt::bounds::GreaterThan{ std::string{"Jules"}};
				auto upper_bound = snrt::bounds::LessThan{ std::string{"Mike"}};

				auto string_range = snrt::Range{ lower_bound, upper_bound };

				Assert::IsFalse(string_range.contains("Jules"));

				Assert::IsTrue(string_range.contains("Kim"));

				Assert::IsFalse(string_range.contains("Mike"));


			}
		};
	}

	namespace scenario_B
	{

	}
}
