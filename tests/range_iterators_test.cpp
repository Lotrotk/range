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
	
	using value_t = std::array<iterator_t, 3>;
	
	TEST_F(RangeIteratorsTest, CorrectNotUniqueRange) {
		
		std::array<value_t, 35> const expected
		{
			value_t{_iterators[0], _iterators[0], _iterators[0],},
			value_t{_iterators[0], _iterators[0], _iterators[1],},
			value_t{_iterators[0], _iterators[0], _iterators[2],},
			value_t{_iterators[0], _iterators[0], _iterators[3],},
			value_t{_iterators[0], _iterators[0], _iterators[4],},
			value_t{_iterators[0], _iterators[1], _iterators[1],},
			value_t{_iterators[0], _iterators[1], _iterators[2],},
			value_t{_iterators[0], _iterators[1], _iterators[3],},
			value_t{_iterators[0], _iterators[1], _iterators[4],},
			value_t{_iterators[0], _iterators[2], _iterators[2],},
			value_t{_iterators[0], _iterators[2], _iterators[3],},
			value_t{_iterators[0], _iterators[2], _iterators[4],},
			value_t{_iterators[0], _iterators[3], _iterators[3],},
			value_t{_iterators[0], _iterators[3], _iterators[4],},
			value_t{_iterators[0], _iterators[4], _iterators[4],},
			value_t{_iterators[1], _iterators[1], _iterators[1],},
			value_t{_iterators[1], _iterators[1], _iterators[2],},
			value_t{_iterators[1], _iterators[1], _iterators[3],},
			value_t{_iterators[1], _iterators[1], _iterators[4],},
			value_t{_iterators[1], _iterators[2], _iterators[2],},
			value_t{_iterators[1], _iterators[2], _iterators[3],},
			value_t{_iterators[1], _iterators[2], _iterators[4],},
			value_t{_iterators[1], _iterators[3], _iterators[3],},
			value_t{_iterators[1], _iterators[3], _iterators[4],},
			value_t{_iterators[1], _iterators[4], _iterators[4],},
			value_t{_iterators[2], _iterators[2], _iterators[2],},
			value_t{_iterators[2], _iterators[2], _iterators[3],},
			value_t{_iterators[2], _iterators[2], _iterators[4],},
			value_t{_iterators[2], _iterators[3], _iterators[3],},
			value_t{_iterators[2], _iterators[3], _iterators[4],},
			value_t{_iterators[2], _iterators[4], _iterators[4],},
			value_t{_iterators[3], _iterators[3], _iterators[3],},
			value_t{_iterators[3], _iterators[3], _iterators[4],},
			value_t{_iterators[3], _iterators[4], _iterators[4],},
			value_t{_iterators[4], _iterators[4], _iterators[4],},
		};
		
		range<iterator_t> const r(_list.begin(), _list.end());
		
        size_t index = 0;
        for(value_t const &comb : iterable<false, 3, iterator_t>(r))
        {
			EXPECT_TRUE(index < expected.size());
			EXPECT_EQ(comb, expected[index]);
			++index;
		}
		EXPECT_EQ(index, expected.size());
	}
	
	TEST_F(RangeIteratorsTest, CorrectUniqueRange) {
		
		std::array<value_t, 10> const expected
		{
			value_t{_iterators[0], _iterators[1], _iterators[2],},
			value_t{_iterators[0], _iterators[1], _iterators[3],},
			value_t{_iterators[0], _iterators[1], _iterators[4],},
			value_t{_iterators[0], _iterators[2], _iterators[3],},
			value_t{_iterators[0], _iterators[2], _iterators[4],},
			value_t{_iterators[0], _iterators[3], _iterators[4],},
			value_t{_iterators[1], _iterators[2], _iterators[3],},
			value_t{_iterators[1], _iterators[2], _iterators[4],},
			value_t{_iterators[1], _iterators[3], _iterators[4],},
			value_t{_iterators[2], _iterators[3], _iterators[4],},
		};
		
		range<iterator_t> const r(_list.begin(), _list.end());
		
		size_t index = 0;
		for(value_t const &comb : iterable<true, 3, iterator_t>(r))
		{
			EXPECT_TRUE(index < expected.size());
			EXPECT_EQ(comb, expected[index]);
			++index;
		}
		EXPECT_EQ(index, expected.size());
	}
}
