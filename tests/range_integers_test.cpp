#include <range/range.hpp>

#include <gtest/gtest.h>

#include <array>

using namespace testing;
using namespace rng;

namespace
{
	range<int> const r(0, 5);
	
	using value_t = std::array<int, 3>;
	
	TEST(RangeIntegersTest, CorrectOverlappingRange) {
		
		std::array<value_t, 35> const expected
		{
			value_t{0, 0, 0,},
			value_t{0, 0, 1,},
			value_t{0, 0, 2,},
			value_t{0, 0, 3,},
			value_t{0, 0, 4,},
			value_t{0, 1, 1,},
			value_t{0, 1, 2,},
			value_t{0, 1, 3,},
			value_t{0, 1, 4,},
			value_t{0, 2, 2,},
			value_t{0, 2, 3,},
			value_t{0, 2, 4,},
			value_t{0, 3, 3,},
			value_t{0, 3, 4,},
			value_t{0, 4, 4,},
			value_t{1, 1, 1,},
			value_t{1, 1, 2,},
			value_t{1, 1, 3,},
			value_t{1, 1, 4,},
			value_t{1, 2, 2,},
			value_t{1, 2, 3,},
			value_t{1, 2, 4,},
			value_t{1, 3, 3,},
			value_t{1, 3, 4,},
			value_t{1, 4, 4,},
			value_t{2, 2, 2,},
			value_t{2, 2, 3,},
			value_t{2, 2, 4,},
			value_t{2, 3, 3,},
			value_t{2, 3, 4,},
			value_t{2, 4, 4,},
			value_t{3, 3, 3,},
			value_t{3, 3, 4,},
			value_t{3, 4, 4,},
			value_t{4, 4, 4,},
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
		
		std::array<value_t, 10> const expected
		{
			value_t{0, 1, 2,},
			value_t{0, 1, 3,},
			value_t{0, 1, 4,},
			value_t{0, 2, 3,},
			value_t{0, 2, 4,},
			value_t{0, 3, 4,},
			value_t{1, 2, 3,},
			value_t{1, 2, 4,},
			value_t{1, 3, 4,},
			value_t{2, 3, 4,},
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
}
