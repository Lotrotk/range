# range
A little library to loop in ordered subranges

The idea was to quickly iterate different subranges : if the range is [0, 5[ then the possible values for 'unique' 3 subranges are (0, 1, 2), (0, 1, 3), (0, 1, 4), (0, 2, 3), (0, 2, 4), (0, 3, 4), (1, 2, 3), (1, 2, 4), (1, 3, 4), (2, 3, 3).

Similarly there are 35 triplets in case the subranges may overlap (an index may appear more than once in a triplet).

This C++ library can do that by iterators, and can therefore be used in a ranged for loop.
See tests for examples.
