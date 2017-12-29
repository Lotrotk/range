#include <range/range.hpp>

#include <gtest/gtest.h>

#include <array>

using namespace testing;
using namespace rng;

namespace
{
	range<int> const r(0, 5);
	
	using value_t = value<3, int>;
	
	TEST(RangeIntegersTest, CorrectOverlappingRange) {
		
		std::array<value_t, 56> const expected
		{
			value_t{0, 0, 0,},
			value_t{0, 0, 1,},
			value_t{0, 0, 2,},
			value_t{0, 0, 3,},
			value_t{0, 0, 4,},
			value_t{0, 0, 5,},
			value_t{0, 1, 1,},
			value_t{0, 1, 2,},
			value_t{0, 1, 3,},
			value_t{0, 1, 4,},
			value_t{0, 1, 5,},
			value_t{0, 2, 2,},
			value_t{0, 2, 3,},
			value_t{0, 2, 4,},
			value_t{0, 2, 5,},
			value_t{0, 3, 3,},
			value_t{0, 3, 4,},
			value_t{0, 3, 5,},
			value_t{0, 4, 4,},
			value_t{0, 4, 5,},
			value_t{0, 5, 5,},
			value_t{1, 1, 1,},
			value_t{1, 1, 2,},
			value_t{1, 1, 3,},
			value_t{1, 1, 4,},
			value_t{1, 1, 5,},
			value_t{1, 2, 2,},
			value_t{1, 2, 3,},
			value_t{1, 2, 4,},
			value_t{1, 2, 5,},
			value_t{1, 3, 3,},
			value_t{1, 3, 4,},
			value_t{1, 3, 5,},
			value_t{1, 4, 4,},
			value_t{1, 4, 5,},
			value_t{1, 5, 5,},
			value_t{2, 2, 2,},
			value_t{2, 2, 3,},
			value_t{2, 2, 4,},
			value_t{2, 2, 5,},
			value_t{2, 3, 3,},
			value_t{2, 3, 4,},
			value_t{2, 3, 5,},
			value_t{2, 4, 4,},
			value_t{2, 4, 5,},
			value_t{2, 5, 5,},
			value_t{3, 3, 3,},
			value_t{3, 3, 4,},
			value_t{3, 3, 5,},
			value_t{3, 4, 4,},
			value_t{3, 4, 5,},
			value_t{3, 5, 5,},
			value_t{4, 4, 4,},
			value_t{4, 4, 5,},
			value_t{4, 5, 5,},
			value_t{5, 5, 5,},
		};
		
		size_t index = 0;
		for(value_t const &comb : iterable<false, 3, int>(r))
		{
			EXPECT_TRUE(index < expected.size());
			EXPECT_EQ(comb, expected[index]);
			++index;
		}
		EXPECT_EQ(index, expected.size());
	}

	TEST(RangeIntegersTest, CorrectRange) {
		
		std::array<value_t, 15> const expected
		{
			value_t{1, 2, 3,},
			value_t{1, 2, 4,},
			value_t{1, 2, 5,},
			value_t{1, 3, 4,},
			value_t{1, 3, 5,},
			value_t{1, 4, 5,},
			value_t{1, 5, 5,},
			value_t{2, 3, 4,},
			value_t{2, 3, 5,},
			value_t{2, 4, 5,},
			value_t{2, 5, 5,},
			value_t{3, 4, 5,},
			value_t{3, 5, 5,},
			value_t{4, 5, 5,},
			value_t{5, 5, 5,},
		};
		
		size_t index = 0;
		for(value_t const &comb : iterable<true, 3, int>(r))
		{
			EXPECT_TRUE(index < expected.size());
			EXPECT_EQ(comb, expected[index]);
			++index;
		}
		EXPECT_EQ(index, expected.size());
	}
	
	TEST(RangeIntegersTest, has_empty_range) {
		
		std::array<std::pair<value_t, bool>, 56> const values
		{
			std::make_pair(value_t{0, 0, 0,}, true),
			std::make_pair(value_t{0, 0, 1,}, true),
			std::make_pair(value_t{0, 0, 2,}, true),
			std::make_pair(value_t{0, 0, 3,}, true),
			std::make_pair(value_t{0, 0, 4,}, true),
			std::make_pair(value_t{0, 0, 5,}, true),
			std::make_pair(value_t{0, 1, 1,}, true),
			std::make_pair(value_t{0, 1, 2,}, true),
			std::make_pair(value_t{0, 1, 3,}, true),
			std::make_pair(value_t{0, 1, 4,}, true),
			std::make_pair(value_t{0, 1, 5,}, true),
			std::make_pair(value_t{0, 2, 2,}, true),
			std::make_pair(value_t{0, 2, 3,}, true),
			std::make_pair(value_t{0, 2, 4,}, true),
			std::make_pair(value_t{0, 2, 5,}, true),
			std::make_pair(value_t{0, 3, 3,}, true),
			std::make_pair(value_t{0, 3, 4,}, true),
			std::make_pair(value_t{0, 3, 5,}, true),
			std::make_pair(value_t{0, 4, 4,}, true),
			std::make_pair(value_t{0, 4, 5,}, true),
			std::make_pair(value_t{0, 5, 5,}, true),
			std::make_pair(value_t{1, 1, 1,}, true),
			std::make_pair(value_t{1, 1, 2,}, true),
			std::make_pair(value_t{1, 1, 3,}, true),
			std::make_pair(value_t{1, 1, 4,}, true),
			std::make_pair(value_t{1, 1, 5,}, true),
			std::make_pair(value_t{1, 2, 2,}, true),
			std::make_pair(value_t{1, 2, 3,}, false),
			std::make_pair(value_t{1, 2, 4,}, false),
			std::make_pair(value_t{1, 2, 5,}, true),
			std::make_pair(value_t{1, 3, 3,}, true),
			std::make_pair(value_t{1, 3, 4,}, false),
			std::make_pair(value_t{1, 3, 5,}, true),
			std::make_pair(value_t{1, 4, 4,}, true),
			std::make_pair(value_t{1, 4, 5,}, true),
			std::make_pair(value_t{1, 5, 5,}, true),
			std::make_pair(value_t{2, 2, 2,}, true),
			std::make_pair(value_t{2, 2, 3,}, true),
			std::make_pair(value_t{2, 2, 4,}, true),
			std::make_pair(value_t{2, 2, 5,}, true),
			std::make_pair(value_t{2, 3, 3,}, true),
			std::make_pair(value_t{2, 3, 4,}, false),
			std::make_pair(value_t{2, 3, 5,}, true),
			std::make_pair(value_t{2, 4, 4,}, true),
			std::make_pair(value_t{2, 4, 5,}, true),
			std::make_pair(value_t{2, 5, 5,}, true),
			std::make_pair(value_t{3, 3, 3,}, true),
			std::make_pair(value_t{3, 3, 4,}, true),
			std::make_pair(value_t{3, 3, 5,}, true),
			std::make_pair(value_t{3, 4, 4,}, true),
			std::make_pair(value_t{3, 4, 5,}, true),
			std::make_pair(value_t{3, 5, 5,}, true),
			std::make_pair(value_t{4, 4, 4,}, true),
			std::make_pair(value_t{4, 4, 5,}, true),
			std::make_pair(value_t{4, 5, 5,}, true),
			std::make_pair(value_t{5, 5, 5,}, true),
		};

		for(auto const &pair : values)
		{
			EXPECT_EQ(has_empty_range(pair.first, r), pair.second);
		}
	}
}
