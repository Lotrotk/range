
set(headers
)

set(sources
	range_integers_test.cpp
	#range_iterators_test.cpp
)

add_executable(rangetest ${headers} ${sources})
target_link_libraries(rangetest range -lgtest -lgtest_main -lpthread)
add_test(AllTests rangetest)
