#include <range/range.hpp>

#include <gtest/gtest.h>

#include <list>
#include <string>

using namespace testing;
using namespace rng;

namespace
{
	struct X{ std::string _name; };
	
	using list_t = std::list<X>;
	using iterator_t = list_t::iterator;
	
	struct RangeIteratorsTest : public Test
	{
		RangeIteratorsTest()
		{
			_list.push_back(X());
			_list.push_back(X());
			_list.push_back(X());
			_list.push_back(X());
			_list.push_back(X());
			
			for(size_t i = 0; i < 5; ++i)
			{
				_iterators[i] = std::next(_list.begin(), i);
				_iterators[i]->_name = std::string("v") + std::to_string(i);
			}
		}
		
		list_t _list;
		iterator_t _iterators[5];
	};
		
	TEST_F(RangeIteratorsTest, correct_static_overlapping_static_type_range) {
		
		using split_t = stat::Type<3, iterator_t>::split_t;
		
		std::array<split_t, 56> const expected
		{
			split_t{_iterators[0], _iterators[0], _iterators[0],},
			split_t{_iterators[0], _iterators[0], _iterators[1],},
			split_t{_iterators[0], _iterators[0], _iterators[2],},
			split_t{_iterators[0], _iterators[0], _iterators[3],},
			split_t{_iterators[0], _iterators[0], _iterators[4],},
			split_t{_iterators[0], _iterators[0], _list.end(),},
			split_t{_iterators[0], _iterators[1], _iterators[1],},
			split_t{_iterators[0], _iterators[1], _iterators[2],},
			split_t{_iterators[0], _iterators[1], _iterators[3],},
			split_t{_iterators[0], _iterators[1], _iterators[4],},
			split_t{_iterators[0], _iterators[1], _list.end(),},
			split_t{_iterators[0], _iterators[2], _iterators[2],},
			split_t{_iterators[0], _iterators[2], _iterators[3],},
			split_t{_iterators[0], _iterators[2], _iterators[4],},
			split_t{_iterators[0], _iterators[2], _list.end(),},
			split_t{_iterators[0], _iterators[3], _iterators[3],},
			split_t{_iterators[0], _iterators[3], _iterators[4],},
			split_t{_iterators[0], _iterators[3], _list.end(),},
			split_t{_iterators[0], _iterators[4], _iterators[4],},
			split_t{_iterators[0], _iterators[4], _list.end(),},
			split_t{_iterators[0], _list.end(), _list.end(),},
			split_t{_iterators[1], _iterators[1], _iterators[1],},
			split_t{_iterators[1], _iterators[1], _iterators[2],},
			split_t{_iterators[1], _iterators[1], _iterators[3],},
			split_t{_iterators[1], _iterators[1], _iterators[4],},
			split_t{_iterators[1], _iterators[1], _list.end(),},
			split_t{_iterators[1], _iterators[2], _iterators[2],},
			split_t{_iterators[1], _iterators[2], _iterators[3],},
			split_t{_iterators[1], _iterators[2], _iterators[4],},
			split_t{_iterators[1], _iterators[2], _list.end(),},
			split_t{_iterators[1], _iterators[3], _iterators[3],},
			split_t{_iterators[1], _iterators[3], _iterators[4],},
			split_t{_iterators[1], _iterators[3], _list.end(),},
			split_t{_iterators[1], _iterators[4], _iterators[4],},
			split_t{_iterators[1], _iterators[4], _list.end(),},
			split_t{_iterators[1], _list.end(), _list.end(),},
			split_t{_iterators[2], _iterators[2], _iterators[2],},
			split_t{_iterators[2], _iterators[2], _iterators[3],},
			split_t{_iterators[2], _iterators[2], _iterators[4],},
			split_t{_iterators[2], _iterators[2], _list.end(),},
			split_t{_iterators[2], _iterators[3], _iterators[3],},
			split_t{_iterators[2], _iterators[3], _iterators[4],},
			split_t{_iterators[2], _iterators[3], _list.end(),},
			split_t{_iterators[2], _iterators[4], _iterators[4],},
			split_t{_iterators[2], _iterators[4], _list.end(),},
			split_t{_iterators[2], _list.end(), _list.end(),},
			split_t{_iterators[3], _iterators[3], _iterators[3],},
			split_t{_iterators[3], _iterators[3], _iterators[4],},
			split_t{_iterators[3], _iterators[3], _list.end(),},
			split_t{_iterators[3], _iterators[4], _iterators[4],},
			split_t{_iterators[3], _iterators[4], _list.end(),},
			split_t{_iterators[3], _list.end(), _list.end(),},
			split_t{_iterators[4], _iterators[4], _iterators[4],},
			split_t{_iterators[4], _iterators[4], _list.end(),},
			split_t{_iterators[4], _list.end(), _list.end(),},
			split_t{_list.end(), _list.end(), _list.end(),},
		};
		
		range<iterator_t> const r(_list.begin(), _list.end());
		
		size_t index = 0;
		for(split_t const &comb : iterable<stat::Separate<false>, stat::Type<3, iterator_t>>(r))
		{
			EXPECT_TRUE(index < expected.size());
			EXPECT_EQ(comb, expected[index]);
			++index;
		}
		EXPECT_EQ(index, expected.size());
	}
	
	TEST_F(RangeIteratorsTest, correct_dynamic_overlapping_static_type_range) {
		
		using split_t = stat::Type<3, iterator_t>::split_t;
		
		std::array<split_t, 56> const expected
		{
			split_t{_iterators[0], _iterators[0], _iterators[0],},
			split_t{_iterators[0], _iterators[0], _iterators[1],},
			split_t{_iterators[0], _iterators[0], _iterators[2],},
			split_t{_iterators[0], _iterators[0], _iterators[3],},
			split_t{_iterators[0], _iterators[0], _iterators[4],},
			split_t{_iterators[0], _iterators[0], _list.end(),},
			split_t{_iterators[0], _iterators[1], _iterators[1],},
			split_t{_iterators[0], _iterators[1], _iterators[2],},
			split_t{_iterators[0], _iterators[1], _iterators[3],},
			split_t{_iterators[0], _iterators[1], _iterators[4],},
			split_t{_iterators[0], _iterators[1], _list.end(),},
			split_t{_iterators[0], _iterators[2], _iterators[2],},
			split_t{_iterators[0], _iterators[2], _iterators[3],},
			split_t{_iterators[0], _iterators[2], _iterators[4],},
			split_t{_iterators[0], _iterators[2], _list.end(),},
			split_t{_iterators[0], _iterators[3], _iterators[3],},
			split_t{_iterators[0], _iterators[3], _iterators[4],},
			split_t{_iterators[0], _iterators[3], _list.end(),},
			split_t{_iterators[0], _iterators[4], _iterators[4],},
			split_t{_iterators[0], _iterators[4], _list.end(),},
			split_t{_iterators[0], _list.end(), _list.end(),},
			split_t{_iterators[1], _iterators[1], _iterators[1],},
			split_t{_iterators[1], _iterators[1], _iterators[2],},
			split_t{_iterators[1], _iterators[1], _iterators[3],},
			split_t{_iterators[1], _iterators[1], _iterators[4],},
			split_t{_iterators[1], _iterators[1], _list.end(),},
			split_t{_iterators[1], _iterators[2], _iterators[2],},
			split_t{_iterators[1], _iterators[2], _iterators[3],},
			split_t{_iterators[1], _iterators[2], _iterators[4],},
			split_t{_iterators[1], _iterators[2], _list.end(),},
			split_t{_iterators[1], _iterators[3], _iterators[3],},
			split_t{_iterators[1], _iterators[3], _iterators[4],},
			split_t{_iterators[1], _iterators[3], _list.end(),},
			split_t{_iterators[1], _iterators[4], _iterators[4],},
			split_t{_iterators[1], _iterators[4], _list.end(),},
			split_t{_iterators[1], _list.end(), _list.end(),},
			split_t{_iterators[2], _iterators[2], _iterators[2],},
			split_t{_iterators[2], _iterators[2], _iterators[3],},
			split_t{_iterators[2], _iterators[2], _iterators[4],},
			split_t{_iterators[2], _iterators[2], _list.end(),},
			split_t{_iterators[2], _iterators[3], _iterators[3],},
			split_t{_iterators[2], _iterators[3], _iterators[4],},
			split_t{_iterators[2], _iterators[3], _list.end(),},
			split_t{_iterators[2], _iterators[4], _iterators[4],},
			split_t{_iterators[2], _iterators[4], _list.end(),},
			split_t{_iterators[2], _list.end(), _list.end(),},
			split_t{_iterators[3], _iterators[3], _iterators[3],},
			split_t{_iterators[3], _iterators[3], _iterators[4],},
			split_t{_iterators[3], _iterators[3], _list.end(),},
			split_t{_iterators[3], _iterators[4], _iterators[4],},
			split_t{_iterators[3], _iterators[4], _list.end(),},
			split_t{_iterators[3], _list.end(), _list.end(),},
			split_t{_iterators[4], _iterators[4], _iterators[4],},
			split_t{_iterators[4], _iterators[4], _list.end(),},
			split_t{_iterators[4], _list.end(), _list.end(),},
			split_t{_list.end(), _list.end(), _list.end(),},
		};
		
		range<iterator_t> const r(_list.begin(), _list.end());
		
		size_t index = 0;
		for(split_t const &comb : iterable<dyn::Separate, stat::Type<3, iterator_t>>(r, dyn::Separate(false)))
		{
			EXPECT_TRUE(index < expected.size());
			EXPECT_EQ(comb, expected[index]);
			++index;
		}
		EXPECT_EQ(index, expected.size());
	}
	
	TEST_F(RangeIteratorsTest, correct_static_overlapping_dynamic_type_range) {
		
		using split_t = dyn::Type<iterator_t>::split_t;
		
		std::array<split_t, 56> const expected
		{
			split_t{_iterators[0], _iterators[0], _iterators[0],},
			split_t{_iterators[0], _iterators[0], _iterators[1],},
			split_t{_iterators[0], _iterators[0], _iterators[2],},
			split_t{_iterators[0], _iterators[0], _iterators[3],},
			split_t{_iterators[0], _iterators[0], _iterators[4],},
			split_t{_iterators[0], _iterators[0], _list.end(),},
			split_t{_iterators[0], _iterators[1], _iterators[1],},
			split_t{_iterators[0], _iterators[1], _iterators[2],},
			split_t{_iterators[0], _iterators[1], _iterators[3],},
			split_t{_iterators[0], _iterators[1], _iterators[4],},
			split_t{_iterators[0], _iterators[1], _list.end(),},
			split_t{_iterators[0], _iterators[2], _iterators[2],},
			split_t{_iterators[0], _iterators[2], _iterators[3],},
			split_t{_iterators[0], _iterators[2], _iterators[4],},
			split_t{_iterators[0], _iterators[2], _list.end(),},
			split_t{_iterators[0], _iterators[3], _iterators[3],},
			split_t{_iterators[0], _iterators[3], _iterators[4],},
			split_t{_iterators[0], _iterators[3], _list.end(),},
			split_t{_iterators[0], _iterators[4], _iterators[4],},
			split_t{_iterators[0], _iterators[4], _list.end(),},
			split_t{_iterators[0], _list.end(), _list.end(),},
			split_t{_iterators[1], _iterators[1], _iterators[1],},
			split_t{_iterators[1], _iterators[1], _iterators[2],},
			split_t{_iterators[1], _iterators[1], _iterators[3],},
			split_t{_iterators[1], _iterators[1], _iterators[4],},
			split_t{_iterators[1], _iterators[1], _list.end(),},
			split_t{_iterators[1], _iterators[2], _iterators[2],},
			split_t{_iterators[1], _iterators[2], _iterators[3],},
			split_t{_iterators[1], _iterators[2], _iterators[4],},
			split_t{_iterators[1], _iterators[2], _list.end(),},
			split_t{_iterators[1], _iterators[3], _iterators[3],},
			split_t{_iterators[1], _iterators[3], _iterators[4],},
			split_t{_iterators[1], _iterators[3], _list.end(),},
			split_t{_iterators[1], _iterators[4], _iterators[4],},
			split_t{_iterators[1], _iterators[4], _list.end(),},
			split_t{_iterators[1], _list.end(), _list.end(),},
			split_t{_iterators[2], _iterators[2], _iterators[2],},
			split_t{_iterators[2], _iterators[2], _iterators[3],},
			split_t{_iterators[2], _iterators[2], _iterators[4],},
			split_t{_iterators[2], _iterators[2], _list.end(),},
			split_t{_iterators[2], _iterators[3], _iterators[3],},
			split_t{_iterators[2], _iterators[3], _iterators[4],},
			split_t{_iterators[2], _iterators[3], _list.end(),},
			split_t{_iterators[2], _iterators[4], _iterators[4],},
			split_t{_iterators[2], _iterators[4], _list.end(),},
			split_t{_iterators[2], _list.end(), _list.end(),},
			split_t{_iterators[3], _iterators[3], _iterators[3],},
			split_t{_iterators[3], _iterators[3], _iterators[4],},
			split_t{_iterators[3], _iterators[3], _list.end(),},
			split_t{_iterators[3], _iterators[4], _iterators[4],},
			split_t{_iterators[3], _iterators[4], _list.end(),},
			split_t{_iterators[3], _list.end(), _list.end(),},
			split_t{_iterators[4], _iterators[4], _iterators[4],},
			split_t{_iterators[4], _iterators[4], _list.end(),},
			split_t{_iterators[4], _list.end(), _list.end(),},
			split_t{_list.end(), _list.end(), _list.end(),},
		};
		
		range<iterator_t> const r(_list.begin(), _list.end());
		
		size_t index = 0;
		for(split_t const &comb : iterable<stat::Separate<false>, dyn::Type<iterator_t>>(r, dyn::Type<iterator_t>(3)))
		{
			EXPECT_TRUE(index < expected.size());
			EXPECT_EQ(comb, expected[index]);
			++index;
		}
		EXPECT_EQ(index, expected.size());
	}
	
	TEST_F(RangeIteratorsTest, correct_dynamic_overlapping_dynamic_type_range) {
		
		using split_t = dyn::Type<iterator_t>::split_t;
		
		std::array<split_t, 56> const expected
		{
			split_t{_iterators[0], _iterators[0], _iterators[0],},
			split_t{_iterators[0], _iterators[0], _iterators[1],},
			split_t{_iterators[0], _iterators[0], _iterators[2],},
			split_t{_iterators[0], _iterators[0], _iterators[3],},
			split_t{_iterators[0], _iterators[0], _iterators[4],},
			split_t{_iterators[0], _iterators[0], _list.end(),},
			split_t{_iterators[0], _iterators[1], _iterators[1],},
			split_t{_iterators[0], _iterators[1], _iterators[2],},
			split_t{_iterators[0], _iterators[1], _iterators[3],},
			split_t{_iterators[0], _iterators[1], _iterators[4],},
			split_t{_iterators[0], _iterators[1], _list.end(),},
			split_t{_iterators[0], _iterators[2], _iterators[2],},
			split_t{_iterators[0], _iterators[2], _iterators[3],},
			split_t{_iterators[0], _iterators[2], _iterators[4],},
			split_t{_iterators[0], _iterators[2], _list.end(),},
			split_t{_iterators[0], _iterators[3], _iterators[3],},
			split_t{_iterators[0], _iterators[3], _iterators[4],},
			split_t{_iterators[0], _iterators[3], _list.end(),},
			split_t{_iterators[0], _iterators[4], _iterators[4],},
			split_t{_iterators[0], _iterators[4], _list.end(),},
			split_t{_iterators[0], _list.end(), _list.end(),},
			split_t{_iterators[1], _iterators[1], _iterators[1],},
			split_t{_iterators[1], _iterators[1], _iterators[2],},
			split_t{_iterators[1], _iterators[1], _iterators[3],},
			split_t{_iterators[1], _iterators[1], _iterators[4],},
			split_t{_iterators[1], _iterators[1], _list.end(),},
			split_t{_iterators[1], _iterators[2], _iterators[2],},
			split_t{_iterators[1], _iterators[2], _iterators[3],},
			split_t{_iterators[1], _iterators[2], _iterators[4],},
			split_t{_iterators[1], _iterators[2], _list.end(),},
			split_t{_iterators[1], _iterators[3], _iterators[3],},
			split_t{_iterators[1], _iterators[3], _iterators[4],},
			split_t{_iterators[1], _iterators[3], _list.end(),},
			split_t{_iterators[1], _iterators[4], _iterators[4],},
			split_t{_iterators[1], _iterators[4], _list.end(),},
			split_t{_iterators[1], _list.end(), _list.end(),},
			split_t{_iterators[2], _iterators[2], _iterators[2],},
			split_t{_iterators[2], _iterators[2], _iterators[3],},
			split_t{_iterators[2], _iterators[2], _iterators[4],},
			split_t{_iterators[2], _iterators[2], _list.end(),},
			split_t{_iterators[2], _iterators[3], _iterators[3],},
			split_t{_iterators[2], _iterators[3], _iterators[4],},
			split_t{_iterators[2], _iterators[3], _list.end(),},
			split_t{_iterators[2], _iterators[4], _iterators[4],},
			split_t{_iterators[2], _iterators[4], _list.end(),},
			split_t{_iterators[2], _list.end(), _list.end(),},
			split_t{_iterators[3], _iterators[3], _iterators[3],},
			split_t{_iterators[3], _iterators[3], _iterators[4],},
			split_t{_iterators[3], _iterators[3], _list.end(),},
			split_t{_iterators[3], _iterators[4], _iterators[4],},
			split_t{_iterators[3], _iterators[4], _list.end(),},
			split_t{_iterators[3], _list.end(), _list.end(),},
			split_t{_iterators[4], _iterators[4], _iterators[4],},
			split_t{_iterators[4], _iterators[4], _list.end(),},
			split_t{_iterators[4], _list.end(), _list.end(),},
			split_t{_list.end(), _list.end(), _list.end(),},
		};
		
		range<iterator_t> const r(_list.begin(), _list.end());
		
		size_t index = 0;
		for(split_t const &comb : iterable<dyn::Separate, dyn::Type<iterator_t>>(r, dyn::Separate(false), dyn::Type<iterator_t>(3)))
		{
			EXPECT_TRUE(index < expected.size());
			EXPECT_EQ(comb, expected[index]);
			++index;
		}
		EXPECT_EQ(index, expected.size());
	}

	TEST_F(RangeIteratorsTest, correct_static_not_overlapping_static_type_range) {
		
		using split_t = stat::Type<3, iterator_t>::split_t;
		
		std::array<split_t, 15> const expected
		{
			split_t{_iterators[1], _iterators[2], _iterators[3],},
			split_t{_iterators[1], _iterators[2], _iterators[4],},
			split_t{_iterators[1], _iterators[2], _list.end(),},
			split_t{_iterators[1], _iterators[3], _iterators[4],},
			split_t{_iterators[1], _iterators[3], _list.end(),},
			split_t{_iterators[1], _iterators[4], _list.end(),},
			split_t{_iterators[1], _list.end(), _list.end(),},
			split_t{_iterators[2], _iterators[3], _iterators[4],},
			split_t{_iterators[2], _iterators[3], _list.end(),},
			split_t{_iterators[2], _iterators[4], _list.end(),},
			split_t{_iterators[2], _list.end(), _list.end(),},
			split_t{_iterators[3], _iterators[4], _list.end(),},
			split_t{_iterators[3], _list.end(), _list.end(),},
			split_t{_iterators[4], _list.end(), _list.end(),},
			split_t{_list.end(), _list.end(), _list.end(),},
		};
		
		range<iterator_t> const r(_list.begin(), _list.end());
		
		size_t index = 0;
		for(split_t const &comb : iterable<stat::Separate<true>, stat::Type<3, iterator_t>>(r))
		{
			EXPECT_TRUE(index < expected.size());
			EXPECT_EQ(comb, expected[index]);
			++index;
		}
		EXPECT_EQ(index, expected.size());
	}
	
	TEST_F(RangeIteratorsTest, dynamic_not_overlapping_static_type_range) {
		
		using split_t = stat::Type<3, iterator_t>::split_t;
		
		std::array<split_t, 15> const expected
		{
			split_t{_iterators[1], _iterators[2], _iterators[3],},
			split_t{_iterators[1], _iterators[2], _iterators[4],},
			split_t{_iterators[1], _iterators[2], _list.end(),},
			split_t{_iterators[1], _iterators[3], _iterators[4],},
			split_t{_iterators[1], _iterators[3], _list.end(),},
			split_t{_iterators[1], _iterators[4], _list.end(),},
			split_t{_iterators[1], _list.end(), _list.end(),},
			split_t{_iterators[2], _iterators[3], _iterators[4],},
			split_t{_iterators[2], _iterators[3], _list.end(),},
			split_t{_iterators[2], _iterators[4], _list.end(),},
			split_t{_iterators[2], _list.end(), _list.end(),},
			split_t{_iterators[3], _iterators[4], _list.end(),},
			split_t{_iterators[3], _list.end(), _list.end(),},
			split_t{_iterators[4], _list.end(), _list.end(),},
			split_t{_list.end(), _list.end(), _list.end(),},
		};
		
		range<iterator_t> const r(_list.begin(), _list.end());
		
		size_t index = 0;
		for(split_t const &comb : iterable<dyn::Separate, stat::Type<3, iterator_t>>(r, dyn::Separate(true)))
		{
			EXPECT_TRUE(index < expected.size());
			EXPECT_EQ(comb, expected[index]);
			++index;
		}
		EXPECT_EQ(index, expected.size());
	}
	
	TEST_F(RangeIteratorsTest, has_empty_range_static_type) {
		
		using split_t = stat::Type<3, iterator_t>::split_t;
		
		std::array<std::pair<split_t, bool>, 56> const splits
		{
			std::make_pair(split_t{_iterators[0], _iterators[0], _iterators[0],}, true),
			std::make_pair(split_t{_iterators[0], _iterators[0], _iterators[1],}, true),
			std::make_pair(split_t{_iterators[0], _iterators[0], _iterators[2],}, true),
			std::make_pair(split_t{_iterators[0], _iterators[0], _iterators[3],}, true),
			std::make_pair(split_t{_iterators[0], _iterators[0], _iterators[4],}, true),
			std::make_pair(split_t{_iterators[0], _iterators[0], _list.end(),}, true),
			std::make_pair(split_t{_iterators[0], _iterators[1], _iterators[1],}, true),
			std::make_pair(split_t{_iterators[0], _iterators[1], _iterators[2],}, true),
			std::make_pair(split_t{_iterators[0], _iterators[1], _iterators[3],}, true),
			std::make_pair(split_t{_iterators[0], _iterators[1], _iterators[4],}, true),
			std::make_pair(split_t{_iterators[0], _iterators[1], _list.end(),}, true),
			std::make_pair(split_t{_iterators[0], _iterators[2], _iterators[2],}, true),
			std::make_pair(split_t{_iterators[0], _iterators[2], _iterators[3],}, true),
			std::make_pair(split_t{_iterators[0], _iterators[2], _iterators[4],}, true),
			std::make_pair(split_t{_iterators[0], _iterators[2], _list.end(),}, true),
			std::make_pair(split_t{_iterators[0], _iterators[3], _iterators[3],}, true),
			std::make_pair(split_t{_iterators[0], _iterators[3], _iterators[4],}, true),
			std::make_pair(split_t{_iterators[0], _iterators[3], _list.end(),}, true),
			std::make_pair(split_t{_iterators[0], _iterators[4], _iterators[4],}, true),
			std::make_pair(split_t{_iterators[0], _iterators[4], _list.end(),}, true),
			std::make_pair(split_t{_iterators[0], _list.end(), _list.end(),}, true),
			std::make_pair(split_t{_iterators[1], _iterators[1], _iterators[1],}, true),
			std::make_pair(split_t{_iterators[1], _iterators[1], _iterators[2],}, true),
			std::make_pair(split_t{_iterators[1], _iterators[1], _iterators[3],}, true),
			std::make_pair(split_t{_iterators[1], _iterators[1], _iterators[4],}, true),
			std::make_pair(split_t{_iterators[1], _iterators[1], _list.end(),}, true),
			std::make_pair(split_t{_iterators[1], _iterators[2], _iterators[2],}, true),
			std::make_pair(split_t{_iterators[1], _iterators[2], _iterators[3],}, false),
			std::make_pair(split_t{_iterators[1], _iterators[2], _iterators[4],}, false),
			std::make_pair(split_t{_iterators[1], _iterators[2], _list.end(),}, true),
			std::make_pair(split_t{_iterators[1], _iterators[3], _iterators[3],}, true),
			std::make_pair(split_t{_iterators[1], _iterators[3], _iterators[4],}, false),
			std::make_pair(split_t{_iterators[1], _iterators[3], _list.end(),}, true),
			std::make_pair(split_t{_iterators[1], _iterators[4], _iterators[4],}, true),
			std::make_pair(split_t{_iterators[1], _iterators[4], _list.end(),}, true),
			std::make_pair(split_t{_iterators[1], _list.end(), _list.end(),}, true),
			std::make_pair(split_t{_iterators[2], _iterators[2], _iterators[2],}, true),
			std::make_pair(split_t{_iterators[2], _iterators[2], _iterators[3],}, true),
			std::make_pair(split_t{_iterators[2], _iterators[2], _iterators[4],}, true),
			std::make_pair(split_t{_iterators[2], _iterators[2], _list.end(),}, true),
			std::make_pair(split_t{_iterators[2], _iterators[3], _iterators[3],}, true),
			std::make_pair(split_t{_iterators[2], _iterators[3], _iterators[4],}, false),
			std::make_pair(split_t{_iterators[2], _iterators[3], _list.end(),}, true),
			std::make_pair(split_t{_iterators[2], _iterators[4], _iterators[4],}, true),
			std::make_pair(split_t{_iterators[2], _iterators[4], _list.end(),}, true),
			std::make_pair(split_t{_iterators[2], _list.end(), _list.end(),}, true),
			std::make_pair(split_t{_iterators[3], _iterators[3], _iterators[3],}, true),
			std::make_pair(split_t{_iterators[3], _iterators[3], _iterators[4],}, true),
			std::make_pair(split_t{_iterators[3], _iterators[3], _list.end(),}, true),
			std::make_pair(split_t{_iterators[3], _iterators[4], _iterators[4],}, true),
			std::make_pair(split_t{_iterators[3], _iterators[4], _list.end(),}, true),
			std::make_pair(split_t{_iterators[3], _list.end(), _list.end(),}, true),
			std::make_pair(split_t{_iterators[4], _iterators[4], _iterators[4],}, true),
			std::make_pair(split_t{_iterators[4], _iterators[4], _list.end(),}, true),
			std::make_pair(split_t{_iterators[4], _list.end(), _list.end(),}, true),
			std::make_pair(split_t{_list.end(), _list.end(), _list.end(),}, true),
		};
		
		range<iterator_t> const r(_list.begin(), _list.end());

		for(auto const &pair : splits)
		{
			EXPECT_EQ(has_empty_range(pair.first, r), pair.second);
		}
	}
	
	TEST_F(RangeIteratorsTest, has_empty_range_dynamic_type) {
		
		using split_t = dyn::Type<iterator_t>::split_t;
		
		std::array<std::pair<split_t, bool>, 56> const splits
		{
			std::make_pair(split_t{_iterators[0], _iterators[0], _iterators[0],}, true),
			std::make_pair(split_t{_iterators[0], _iterators[0], _iterators[1],}, true),
			std::make_pair(split_t{_iterators[0], _iterators[0], _iterators[2],}, true),
			std::make_pair(split_t{_iterators[0], _iterators[0], _iterators[3],}, true),
			std::make_pair(split_t{_iterators[0], _iterators[0], _iterators[4],}, true),
			std::make_pair(split_t{_iterators[0], _iterators[0], _list.end(),}, true),
			std::make_pair(split_t{_iterators[0], _iterators[1], _iterators[1],}, true),
			std::make_pair(split_t{_iterators[0], _iterators[1], _iterators[2],}, true),
			std::make_pair(split_t{_iterators[0], _iterators[1], _iterators[3],}, true),
			std::make_pair(split_t{_iterators[0], _iterators[1], _iterators[4],}, true),
			std::make_pair(split_t{_iterators[0], _iterators[1], _list.end(),}, true),
			std::make_pair(split_t{_iterators[0], _iterators[2], _iterators[2],}, true),
			std::make_pair(split_t{_iterators[0], _iterators[2], _iterators[3],}, true),
			std::make_pair(split_t{_iterators[0], _iterators[2], _iterators[4],}, true),
			std::make_pair(split_t{_iterators[0], _iterators[2], _list.end(),}, true),
			std::make_pair(split_t{_iterators[0], _iterators[3], _iterators[3],}, true),
			std::make_pair(split_t{_iterators[0], _iterators[3], _iterators[4],}, true),
			std::make_pair(split_t{_iterators[0], _iterators[3], _list.end(),}, true),
			std::make_pair(split_t{_iterators[0], _iterators[4], _iterators[4],}, true),
			std::make_pair(split_t{_iterators[0], _iterators[4], _list.end(),}, true),
			std::make_pair(split_t{_iterators[0], _list.end(), _list.end(),}, true),
			std::make_pair(split_t{_iterators[1], _iterators[1], _iterators[1],}, true),
			std::make_pair(split_t{_iterators[1], _iterators[1], _iterators[2],}, true),
			std::make_pair(split_t{_iterators[1], _iterators[1], _iterators[3],}, true),
			std::make_pair(split_t{_iterators[1], _iterators[1], _iterators[4],}, true),
			std::make_pair(split_t{_iterators[1], _iterators[1], _list.end(),}, true),
			std::make_pair(split_t{_iterators[1], _iterators[2], _iterators[2],}, true),
			std::make_pair(split_t{_iterators[1], _iterators[2], _iterators[3],}, false),
			std::make_pair(split_t{_iterators[1], _iterators[2], _iterators[4],}, false),
			std::make_pair(split_t{_iterators[1], _iterators[2], _list.end(),}, true),
			std::make_pair(split_t{_iterators[1], _iterators[3], _iterators[3],}, true),
			std::make_pair(split_t{_iterators[1], _iterators[3], _iterators[4],}, false),
			std::make_pair(split_t{_iterators[1], _iterators[3], _list.end(),}, true),
			std::make_pair(split_t{_iterators[1], _iterators[4], _iterators[4],}, true),
			std::make_pair(split_t{_iterators[1], _iterators[4], _list.end(),}, true),
			std::make_pair(split_t{_iterators[1], _list.end(), _list.end(),}, true),
			std::make_pair(split_t{_iterators[2], _iterators[2], _iterators[2],}, true),
			std::make_pair(split_t{_iterators[2], _iterators[2], _iterators[3],}, true),
			std::make_pair(split_t{_iterators[2], _iterators[2], _iterators[4],}, true),
			std::make_pair(split_t{_iterators[2], _iterators[2], _list.end(),}, true),
			std::make_pair(split_t{_iterators[2], _iterators[3], _iterators[3],}, true),
			std::make_pair(split_t{_iterators[2], _iterators[3], _iterators[4],}, false),
			std::make_pair(split_t{_iterators[2], _iterators[3], _list.end(),}, true),
			std::make_pair(split_t{_iterators[2], _iterators[4], _iterators[4],}, true),
			std::make_pair(split_t{_iterators[2], _iterators[4], _list.end(),}, true),
			std::make_pair(split_t{_iterators[2], _list.end(), _list.end(),}, true),
			std::make_pair(split_t{_iterators[3], _iterators[3], _iterators[3],}, true),
			std::make_pair(split_t{_iterators[3], _iterators[3], _iterators[4],}, true),
			std::make_pair(split_t{_iterators[3], _iterators[3], _list.end(),}, true),
			std::make_pair(split_t{_iterators[3], _iterators[4], _iterators[4],}, true),
			std::make_pair(split_t{_iterators[3], _iterators[4], _list.end(),}, true),
			std::make_pair(split_t{_iterators[3], _list.end(), _list.end(),}, true),
			std::make_pair(split_t{_iterators[4], _iterators[4], _iterators[4],}, true),
			std::make_pair(split_t{_iterators[4], _iterators[4], _list.end(),}, true),
			std::make_pair(split_t{_iterators[4], _list.end(), _list.end(),}, true),
			std::make_pair(split_t{_list.end(), _list.end(), _list.end(),}, true),
		};
		
		range<iterator_t> const r(_list.begin(), _list.end());

		for(auto const &pair : splits)
		{
			EXPECT_EQ(has_empty_range(pair.first, r), pair.second);
		}
	}
}
