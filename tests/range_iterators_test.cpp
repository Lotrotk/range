#include <range/range.hpp>

#include <gtest/gtest.h>

#include <array>
#include <list>
#include <ostream>
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
	
	using split_t = split<3, iterator_t>;
	
	TEST_F(RangeIteratorsTest, CorrectOverlappingRange) {
		
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
		for(split_t const &comb : iterable<false, 3, iterator_t>(r))
		{
			EXPECT_TRUE(index < expected.size());
			EXPECT_EQ(comb, expected[index]);
			++index;
		}
		EXPECT_EQ(index, expected.size());
	}
	
	TEST_F(RangeIteratorsTest, CorrectRange) {
		
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
		for(split_t const &comb : iterable<true, 3, iterator_t>(r))
		{
			EXPECT_TRUE(index < expected.size());
			EXPECT_EQ(comb, expected[index]);
			++index;
		}
		EXPECT_EQ(index, expected.size());
	}
	
	TEST_F(RangeIteratorsTest, has_empty_range) {
		
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
