# range
A little library to loop in ordered subranges

The idea was to quickly iterate different subranges : if the range is [0, 5[ and we want to split this into four,
then we need 3 variables that define the splits within this range. The variables must be ordered from smallest to largest.

The possible splits for 'not overlapping' 3 subranges are then:
* {1, 2, 3}
* {1, 2, 4}
* {1, 2, 5}
* {1, 3, 4}
* {1, 3, 5}
* {1, 4, 5}
* {1, 5, 5}
* {2, 3, 4}
* {2, 3, 5}
* {2, 4, 5}
* {2, 5, 5}
* {3, 4, 5}
* {3, 5, 5}
* {4, 5, 5}
* {5, 5, 5}

The first range implicitly goes from [0, first_split[ and the second from [first_split, second_split[, and so on.
That is why the first split can not be 0 if we don't want these ranges to overlap.
What is allowed however is that a range is empty, and two empty ranges are considered not to be overlapping.
An empty range is represented by the end of the range (5).

Similarly these are the splits when overlap is allowed:
* {0, 0, 0}
* {0, 0, 1}
* {0, 0, 2}
* {0, 0, 3}
* {0, 0, 4}
* {0, 0, 5}
* {0, 1, 1}
* {0, 1, 2}
* {0, 1, 3}
* {0, 1, 4}
* {0, 1, 5}
* {0, 2, 2}
* {0, 2, 3}
* {0, 2, 4}
* {0, 2, 5}
* {0, 3, 3}
* {0, 3, 4}
* {0, 3, 5}
* {0, 4, 4}
* {0, 4, 5}
* {0, 5, 5}
* {1, 1, 1}
* {1, 1, 2}
* {1, 1, 3}
* {1, 1, 4}
* {1, 1, 5}
* {1, 2, 2}
* {1, 2, 3}
* {1, 2, 4}
* {1, 2, 5}
* {1, 3, 3}
* {1, 3, 4}
* {1, 3, 5}
* {1, 4, 4}
* {1, 4, 5}
* {1, 5, 5}
* {2, 2, 2}
* {2, 2, 3}
* {2, 2, 4}
* {2, 2, 5}
* {2, 3, 3}
* {2, 3, 4}
* {2, 3, 5}
* {2, 4, 4}
* {2, 4, 5}
* {2, 5, 5}
* {3, 3, 3}
* {3, 3, 4}
* {3, 3, 5}
* {3, 4, 4}
* {3, 4, 5}
* {3, 5, 5}
* {4, 4, 4}
* {4, 4, 5}
* {4, 5, 5}
* {5, 5, 5}

There is also a function that can determine whether or not a split defines one or more empty ranges:
```c++
has_empty_range()
```

The best part of this library is that the splits can be iterated in a ranged for loop !
Whether or not overlap is allowed and the number of splits can be (independently) set at compile time or at runtime.

```c++
using namespace rng;

range<int> const r(0, 5);

//behavior completely defined at compile time
for(auto const &s : iterable<stat::Separate<false>, stat::Type<3, int>>(r))
{
	std::cout << '{' << s[0] << ", " << s[1] << ", " << s[2] << '}' << std::endl;
	if(has_empty_range(s, r))
	{
		//continue;
	}
	
	//do stuff
}

//behavior completely defined at runtime
for(auto const &s : iterable<dyn::Separate, dyn::Type<int>>(r, dyn::Separate(false), dyn::Type<int>(3)))
{
	std::cout << '{' << s[0] << ", " << s[1] << ", " << s[2] << '}' << std::endl;
	if(has_empty_range(s, r))
	{
		//continue;
	}
	
	//do stuff
}

```
