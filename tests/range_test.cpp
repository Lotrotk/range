#include <range/range.hpp>

#include <gtest/gtest.h>

#include <iostream>

using namespace testing;
using namespace rng;

namespace
{
	TEST(PuzzleFactoryTest, ) {
		
		for(auto const &pair : iterable<3, int, true>(range<int>(0, 10)))
		{
			std::cout << '(' << pair[0] << ", " << pair[1] << ", " << pair[2] << ')' << std::endl;
		}
		
		EXPECT_EQ(1, 2);
	}
}
