int main()
{
	auto liquid = snns::make_range(snns::inclusive_inclusive{}, 0.0, 100.0);

	auto liquid = snns::make_range_inclusive_inclusive(0.0, 100.0);

	auto liquid = snns::make_range(0.0, 100.0, snns::inclusive_inclusive{});

	template <typename T, typename L, typename U, typename D>
	snns::make_range(T lower_bound_value, T upper_bound_value, L lower_bound_comparator, U upper_bound_comparator, D default_comparator = std::less_equal);

	auto zero_nine = snns::make_range(0, 10, std::greater_equal, std::less);

	auto zero_nine = snns::make_range(std::greater_equal, 0, std::less, 10);

	auto zero_nine = snns::make_range(std::pair{std::greater_equal, 0}, std::pair{std::less, 10});

	auto zero_nine = snns::make_range(std::greater_equal, 0, std::less, 10);

	auto zero_nine = snns::Range{snns::Minimum{0}, snns::LessThan{10}};

	auto zero_nine = snns::Range{std::greater_equal, 0, std::less, 10};
	
	auto zero_nine = snns::Range{std::greater_equal, 0, std::less_equal, 9};
}