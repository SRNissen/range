#include "CppUnitTest.h"

#include "snrt_ranges.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace typical_use
{
	TEST_CLASS(wine_type_classification)
	{
	public:

		enum class WineType
		{
			unknown, water, wine, fortified_wine
		};

		TEST_METHOD(Fortified_wine)
		{
		//Arrange

			// alcoholic range of wine from wikipedia article
			auto min_alcoholic_content = snrt::bounds::Minimum{ 0.06 };
			auto max_alcoholic_content = snrt::bounds::LessThan{ 0.22 };
			auto range_of_alcoholic_content_in_wine = snrt::Range{min_alcoholic_content, max_alcoholic_content};

			// a strong fortified wine
			double actual_alcoholic_content = max_alcoholic_content.value + 1.0;

			// but we don't know that yet because we haven't classified it
			auto actual_wine_type = WineType::unknown;


		//Act

			switch (range_of_alcoholic_content_in_wine.locate(actual_alcoholic_content))
			{
			case snrt::Location::below_range:
				actual_wine_type = WineType::water;
				break;
			case snrt::Location::in_range:
				actual_wine_type = WineType::wine;
				break;
			case snrt::Location::above_range:
				actual_wine_type = WineType::fortified_wine;
				break;
			}


		//Assert
			Assert::IsTrue(WineType::fortified_wine == actual_wine_type);
		}
	};
}
