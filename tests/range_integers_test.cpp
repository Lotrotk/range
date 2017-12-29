#include <range/range.hpp>

#include <gtest/gtest.h>

using namespace testing;
using namespace rng;

namespace
{
	range<int> const r(0, 5);
	
	TEST(RangeIntegersTest, correct_static_overlapping_static_type_range) {
		
		using split_t = stat::Type<3, int>::split_t;
		
		std::array<split_t, 56> const expected
		{
			split_t{0, 0, 0,},
			split_t{0, 0, 1,},
			split_t{0, 0, 2,},
			split_t{0, 0, 3,},
			split_t{0, 0, 4,},
			split_t{0, 0, 5,},
			split_t{0, 1, 1,},
			split_t{0, 1, 2,},
			split_t{0, 1, 3,},
			split_t{0, 1, 4,},
			split_t{0, 1, 5,},
			split_t{0, 2, 2,},
			split_t{0, 2, 3,},
			split_t{0, 2, 4,},
			split_t{0, 2, 5,},
			split_t{0, 3, 3,},
			split_t{0, 3, 4,},
			split_t{0, 3, 5,},
			split_t{0, 4, 4,},
			split_t{0, 4, 5,},
			split_t{0, 5, 5,},
			split_t{1, 1, 1,},
			split_t{1, 1, 2,},
			split_t{1, 1, 3,},
			split_t{1, 1, 4,},
			split_t{1, 1, 5,},
			split_t{1, 2, 2,},
			split_t{1, 2, 3,},
			split_t{1, 2, 4,},
			split_t{1, 2, 5,},
			split_t{1, 3, 3,},
			split_t{1, 3, 4,},
			split_t{1, 3, 5,},
			split_t{1, 4, 4,},
			split_t{1, 4, 5,},
			split_t{1, 5, 5,},
			split_t{2, 2, 2,},
			split_t{2, 2, 3,},
			split_t{2, 2, 4,},
			split_t{2, 2, 5,},
			split_t{2, 3, 3,},
			split_t{2, 3, 4,},
			split_t{2, 3, 5,},
			split_t{2, 4, 4,},
			split_t{2, 4, 5,},
			split_t{2, 5, 5,},
			split_t{3, 3, 3,},
			split_t{3, 3, 4,},
			split_t{3, 3, 5,},
			split_t{3, 4, 4,},
			split_t{3, 4, 5,},
			split_t{3, 5, 5,},
			split_t{4, 4, 4,},
			split_t{4, 4, 5,},
			split_t{4, 5, 5,},
			split_t{5, 5, 5,},
		};
		
		size_t index = 0;
		for(split_t const &comb : iterable<stat::Separate<false>, stat::Type<3, int>>(r))
		{
			EXPECT_TRUE(index < expected.size());
			EXPECT_EQ(comb, expected[index]);
			++index;
		}
		EXPECT_EQ(index, expected.size());
	}
	
	TEST(RangeIntegersTest, correct_dynamic_overlapping_static_type_range) {
		
		using split_t = stat::Type<3, int>::split_t;
		
		std::array<split_t, 56> const expected
		{
			split_t{0, 0, 0,},
			split_t{0, 0, 1,},
			split_t{0, 0, 2,},
			split_t{0, 0, 3,},
			split_t{0, 0, 4,},
			split_t{0, 0, 5,},
			split_t{0, 1, 1,},
			split_t{0, 1, 2,},
			split_t{0, 1, 3,},
			split_t{0, 1, 4,},
			split_t{0, 1, 5,},
			split_t{0, 2, 2,},
			split_t{0, 2, 3,},
			split_t{0, 2, 4,},
			split_t{0, 2, 5,},
			split_t{0, 3, 3,},
			split_t{0, 3, 4,},
			split_t{0, 3, 5,},
			split_t{0, 4, 4,},
			split_t{0, 4, 5,},
			split_t{0, 5, 5,},
			split_t{1, 1, 1,},
			split_t{1, 1, 2,},
			split_t{1, 1, 3,},
			split_t{1, 1, 4,},
			split_t{1, 1, 5,},
			split_t{1, 2, 2,},
			split_t{1, 2, 3,},
			split_t{1, 2, 4,},
			split_t{1, 2, 5,},
			split_t{1, 3, 3,},
			split_t{1, 3, 4,},
			split_t{1, 3, 5,},
			split_t{1, 4, 4,},
			split_t{1, 4, 5,},
			split_t{1, 5, 5,},
			split_t{2, 2, 2,},
			split_t{2, 2, 3,},
			split_t{2, 2, 4,},
			split_t{2, 2, 5,},
			split_t{2, 3, 3,},
			split_t{2, 3, 4,},
			split_t{2, 3, 5,},
			split_t{2, 4, 4,},
			split_t{2, 4, 5,},
			split_t{2, 5, 5,},
			split_t{3, 3, 3,},
			split_t{3, 3, 4,},
			split_t{3, 3, 5,},
			split_t{3, 4, 4,},
			split_t{3, 4, 5,},
			split_t{3, 5, 5,},
			split_t{4, 4, 4,},
			split_t{4, 4, 5,},
			split_t{4, 5, 5,},
			split_t{5, 5, 5,},
		};
		
		size_t index = 0;
		for(split_t const &comb : iterable<dyn::Separate, stat::Type<3, int>>(r, dyn::Separate(false)))
		{
			EXPECT_TRUE(index < expected.size());
			EXPECT_EQ(comb, expected[index]);
			++index;
		}
		EXPECT_EQ(index, expected.size());
	}
	
	TEST(RangeIntegersTest, correct_static_overlapping_dynamic_type_range) {
		
		using split_t = dyn::Type<int>::split_t;
		
		std::array<split_t, 56> const expected
		{
			split_t{0, 0, 0,},
			split_t{0, 0, 1,},
			split_t{0, 0, 2,},
			split_t{0, 0, 3,},
			split_t{0, 0, 4,},
			split_t{0, 0, 5,},
			split_t{0, 1, 1,},
			split_t{0, 1, 2,},
			split_t{0, 1, 3,},
			split_t{0, 1, 4,},
			split_t{0, 1, 5,},
			split_t{0, 2, 2,},
			split_t{0, 2, 3,},
			split_t{0, 2, 4,},
			split_t{0, 2, 5,},
			split_t{0, 3, 3,},
			split_t{0, 3, 4,},
			split_t{0, 3, 5,},
			split_t{0, 4, 4,},
			split_t{0, 4, 5,},
			split_t{0, 5, 5,},
			split_t{1, 1, 1,},
			split_t{1, 1, 2,},
			split_t{1, 1, 3,},
			split_t{1, 1, 4,},
			split_t{1, 1, 5,},
			split_t{1, 2, 2,},
			split_t{1, 2, 3,},
			split_t{1, 2, 4,},
			split_t{1, 2, 5,},
			split_t{1, 3, 3,},
			split_t{1, 3, 4,},
			split_t{1, 3, 5,},
			split_t{1, 4, 4,},
			split_t{1, 4, 5,},
			split_t{1, 5, 5,},
			split_t{2, 2, 2,},
			split_t{2, 2, 3,},
			split_t{2, 2, 4,},
			split_t{2, 2, 5,},
			split_t{2, 3, 3,},
			split_t{2, 3, 4,},
			split_t{2, 3, 5,},
			split_t{2, 4, 4,},
			split_t{2, 4, 5,},
			split_t{2, 5, 5,},
			split_t{3, 3, 3,},
			split_t{3, 3, 4,},
			split_t{3, 3, 5,},
			split_t{3, 4, 4,},
			split_t{3, 4, 5,},
			split_t{3, 5, 5,},
			split_t{4, 4, 4,},
			split_t{4, 4, 5,},
			split_t{4, 5, 5,},
			split_t{5, 5, 5,},
		};
		
		size_t index = 0;
		for(split_t const &comb : iterable<stat::Separate<false>, dyn::Type<int>>(r, dyn::Type<int>(3)))
		{
			EXPECT_TRUE(index < expected.size());
			EXPECT_EQ(comb, expected[index]);
			++index;
		}
		EXPECT_EQ(index, expected.size());
	}
	
	TEST(RangeIntegersTest, correct_dynamic_overlapping_dynamic_type_range) {
		
		using split_t = dyn::Type<int>::split_t;
		
		std::array<split_t, 56> const expected
		{
			split_t{0, 0, 0,},
			split_t{0, 0, 1,},
			split_t{0, 0, 2,},
			split_t{0, 0, 3,},
			split_t{0, 0, 4,},
			split_t{0, 0, 5,},
			split_t{0, 1, 1,},
			split_t{0, 1, 2,},
			split_t{0, 1, 3,},
			split_t{0, 1, 4,},
			split_t{0, 1, 5,},
			split_t{0, 2, 2,},
			split_t{0, 2, 3,},
			split_t{0, 2, 4,},
			split_t{0, 2, 5,},
			split_t{0, 3, 3,},
			split_t{0, 3, 4,},
			split_t{0, 3, 5,},
			split_t{0, 4, 4,},
			split_t{0, 4, 5,},
			split_t{0, 5, 5,},
			split_t{1, 1, 1,},
			split_t{1, 1, 2,},
			split_t{1, 1, 3,},
			split_t{1, 1, 4,},
			split_t{1, 1, 5,},
			split_t{1, 2, 2,},
			split_t{1, 2, 3,},
			split_t{1, 2, 4,},
			split_t{1, 2, 5,},
			split_t{1, 3, 3,},
			split_t{1, 3, 4,},
			split_t{1, 3, 5,},
			split_t{1, 4, 4,},
			split_t{1, 4, 5,},
			split_t{1, 5, 5,},
			split_t{2, 2, 2,},
			split_t{2, 2, 3,},
			split_t{2, 2, 4,},
			split_t{2, 2, 5,},
			split_t{2, 3, 3,},
			split_t{2, 3, 4,},
			split_t{2, 3, 5,},
			split_t{2, 4, 4,},
			split_t{2, 4, 5,},
			split_t{2, 5, 5,},
			split_t{3, 3, 3,},
			split_t{3, 3, 4,},
			split_t{3, 3, 5,},
			split_t{3, 4, 4,},
			split_t{3, 4, 5,},
			split_t{3, 5, 5,},
			split_t{4, 4, 4,},
			split_t{4, 4, 5,},
			split_t{4, 5, 5,},
			split_t{5, 5, 5,},
		};
		
		size_t index = 0;
		for(split_t const &comb : iterable<dyn::Separate, dyn::Type<int>>(r, dyn::Separate(false), dyn::Type<int>(3)))
		{
			EXPECT_TRUE(index < expected.size());
			EXPECT_EQ(comb, expected[index]);
			++index;
		}
		EXPECT_EQ(index, expected.size());
	}

	TEST(RangeIntegersTest, correct_static_not_overlapping_static_type_range) {
		
		using split_t = stat::Type<3, int>::split_t;
		
		std::array<split_t, 15> const expected
		{
			split_t{1, 2, 3,},
			split_t{1, 2, 4,},
			split_t{1, 2, 5,},
			split_t{1, 3, 4,},
			split_t{1, 3, 5,},
			split_t{1, 4, 5,},
			split_t{1, 5, 5,},
			split_t{2, 3, 4,},
			split_t{2, 3, 5,},
			split_t{2, 4, 5,},
			split_t{2, 5, 5,},
			split_t{3, 4, 5,},
			split_t{3, 5, 5,},
			split_t{4, 5, 5,},
			split_t{5, 5, 5,},
		};
		
		size_t index = 0;
		for(split_t const &comb : iterable<stat::Separate<true>, stat::Type<3, int>>(r))
		{
			EXPECT_TRUE(index < expected.size());
			EXPECT_EQ(comb, expected[index]);
			++index;
		}
		EXPECT_EQ(index, expected.size());
	}
	
	TEST(RangeIntegersTest, dynamic_not_overlapping_static_type_range) {
		
		using split_t = stat::Type<3, int>::split_t;
		
		std::array<split_t, 15> const expected
		{
			split_t{1, 2, 3,},
			split_t{1, 2, 4,},
			split_t{1, 2, 5,},
			split_t{1, 3, 4,},
			split_t{1, 3, 5,},
			split_t{1, 4, 5,},
			split_t{1, 5, 5,},
			split_t{2, 3, 4,},
			split_t{2, 3, 5,},
			split_t{2, 4, 5,},
			split_t{2, 5, 5,},
			split_t{3, 4, 5,},
			split_t{3, 5, 5,},
			split_t{4, 5, 5,},
			split_t{5, 5, 5,},
		};
		
		size_t index = 0;
		for(split_t const &comb : iterable<dyn::Separate, stat::Type<3, int>>(r, dyn::Separate(true)))
		{
			EXPECT_TRUE(index < expected.size());
			EXPECT_EQ(comb, expected[index]);
			++index;
		}
		EXPECT_EQ(index, expected.size());
	}
	
	TEST(RangeIntegersTest, has_empty_range_static_size) {
		
		using split_t = stat::Type<3, int>::split_t;
		
		std::array<std::pair<split_t, bool>, 56> const splits
		{
			std::make_pair(split_t{0, 0, 0,}, true),
			std::make_pair(split_t{0, 0, 1,}, true),
			std::make_pair(split_t{0, 0, 2,}, true),
			std::make_pair(split_t{0, 0, 3,}, true),
			std::make_pair(split_t{0, 0, 4,}, true),
			std::make_pair(split_t{0, 0, 5,}, true),
			std::make_pair(split_t{0, 1, 1,}, true),
			std::make_pair(split_t{0, 1, 2,}, true),
			std::make_pair(split_t{0, 1, 3,}, true),
			std::make_pair(split_t{0, 1, 4,}, true),
			std::make_pair(split_t{0, 1, 5,}, true),
			std::make_pair(split_t{0, 2, 2,}, true),
			std::make_pair(split_t{0, 2, 3,}, true),
			std::make_pair(split_t{0, 2, 4,}, true),
			std::make_pair(split_t{0, 2, 5,}, true),
			std::make_pair(split_t{0, 3, 3,}, true),
			std::make_pair(split_t{0, 3, 4,}, true),
			std::make_pair(split_t{0, 3, 5,}, true),
			std::make_pair(split_t{0, 4, 4,}, true),
			std::make_pair(split_t{0, 4, 5,}, true),
			std::make_pair(split_t{0, 5, 5,}, true),
			std::make_pair(split_t{1, 1, 1,}, true),
			std::make_pair(split_t{1, 1, 2,}, true),
			std::make_pair(split_t{1, 1, 3,}, true),
			std::make_pair(split_t{1, 1, 4,}, true),
			std::make_pair(split_t{1, 1, 5,}, true),
			std::make_pair(split_t{1, 2, 2,}, true),
			std::make_pair(split_t{1, 2, 3,}, false),
			std::make_pair(split_t{1, 2, 4,}, false),
			std::make_pair(split_t{1, 2, 5,}, true),
			std::make_pair(split_t{1, 3, 3,}, true),
			std::make_pair(split_t{1, 3, 4,}, false),
			std::make_pair(split_t{1, 3, 5,}, true),
			std::make_pair(split_t{1, 4, 4,}, true),
			std::make_pair(split_t{1, 4, 5,}, true),
			std::make_pair(split_t{1, 5, 5,}, true),
			std::make_pair(split_t{2, 2, 2,}, true),
			std::make_pair(split_t{2, 2, 3,}, true),
			std::make_pair(split_t{2, 2, 4,}, true),
			std::make_pair(split_t{2, 2, 5,}, true),
			std::make_pair(split_t{2, 3, 3,}, true),
			std::make_pair(split_t{2, 3, 4,}, false),
			std::make_pair(split_t{2, 3, 5,}, true),
			std::make_pair(split_t{2, 4, 4,}, true),
			std::make_pair(split_t{2, 4, 5,}, true),
			std::make_pair(split_t{2, 5, 5,}, true),
			std::make_pair(split_t{3, 3, 3,}, true),
			std::make_pair(split_t{3, 3, 4,}, true),
			std::make_pair(split_t{3, 3, 5,}, true),
			std::make_pair(split_t{3, 4, 4,}, true),
			std::make_pair(split_t{3, 4, 5,}, true),
			std::make_pair(split_t{3, 5, 5,}, true),
			std::make_pair(split_t{4, 4, 4,}, true),
			std::make_pair(split_t{4, 4, 5,}, true),
			std::make_pair(split_t{4, 5, 5,}, true),
			std::make_pair(split_t{5, 5, 5,}, true),
		};

		for(auto const &pair : splits)
		{
			EXPECT_EQ(has_empty_range(pair.first, r), pair.second);
		}
	}
}
