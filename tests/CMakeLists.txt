
set(headers
)

set(sources
	range_test.cpp
)

add_executable(rangetest ${headers} ${sources})
target_link_libraries(rangetest range -lgtest -lgtest_main -lpthread)
add_test(AllTests rangetest)
