#pragma once

#include <cstdint>
#include <array>
#include <type_traits>

namespace rng
{
	template<typename T>
	class range;
	
	template<bool unique, size_t N, typename T>
	class iterable;
	
	template<bool unique, size_t N, typename T>
	class iterator;
	
	////////////////////////////////////////////////////////////////
	
	template<bool unique, size_t N, typename T>
	class iterator
	{
	public:
		using value_t = std::array<T, N>;

	private:
		using range_t = range<T>;
		
	public:
		iterator(iterator &&other) = default;
		iterator &operator=(iterator &&other) = default;
	
		iterator &operator++();
		
        value_t const &operator*() const { return _array; }
		bool operator!=(iterator const &other) const { return _array != other._array; }
		
	private:
        iterator(range_t const &r, T const &v) : _range(&r) { _array.fill(v); }
		
	private:
		range_t const *_range{};
		value_t _array;
		
	private:
		template<bool, size_t, typename> friend class iterable;
	};
	
	template<typename T>
	class range
	{
	public:
		constexpr range(T begin, T end) : _begin(begin), _end(end) {}
		
	private:
		T _begin;
		T _end;
		
	private:
		template<bool, size_t, typename> friend class iterable;
		template<bool, size_t, typename> friend class iterator;
	};
	
	template<bool unique, size_t N, typename T>
	class iterable
	{
	public:
		using range_t = range<T>;
		using iterator_t = iterator<unique, N, T>;
		using value_t = typename iterator_t::value_t;
		
	public:
		constexpr iterable(range_t const &r) : _range(r) {}
		
		iterator_t begin() const;
		iterator_t end() const;
		
	private:
		range_t _range;
	};
}

namespace rng
{
	template<typename T, typename std::enable_if<std::is_integral<T>::value, int>::type = 0>
	auto rngdistance(T const &a, T const &b) { return b - a; }
	
	template<typename T, typename std::enable_if<!std::is_integral<T>::value, int>::type = 0>
	auto rngdistance(T const &a, T const &b) { using std::distance; return distance(a, b); }
	
	template<typename T, typename std::enable_if<std::is_integral<T>::value, int>::type = 0>
	void rngadvance(T &a, size_t const d) { a += d; }
	
	template<typename T, typename std::enable_if<!std::is_integral<T>::value, int>::type = 0>
	void rngadvance(T &a, size_t const d) { using std::advance; advance(a, d); }
	
	template<bool unique, size_t N, typename T>
	typename iterable<unique, N, T>::iterator_t iterable<unique, N, T>::begin() const
	{	
		if(!unique)
		{
			return iterator_t(_range, _range._begin);
		}
		
		if(rngdistance(_range._begin, _range._end) < N)
		{
			return end();
		}
		
		iterator_t res(_range, _range._begin);
		for(size_t i = 0; i < N; ++i)
		{
			rngadvance(res._array[i], i);
		}
		
		return res;
	}
	
	template<bool unique, size_t N, typename T>
	typename iterable<unique, N, T>::iterator_t iterable<unique, N, T>::end() const
	{
		iterator_t res(_range, _range._begin);
		res._array[0] = _range._end;
		return res;
	}
	
	template<bool unique, size_t N, typename T>
	iterator<unique, N, T> &iterator<unique, N, T>::operator++()
	{
		iterator &res = *this;
				
		for(size_t i = 1; i <= N; ++i)
		{
			rngadvance(res._array[N-i], size_t(1));
			if(res._array[N-i] == res._range->_end)
			{
				if(i == N)
				{
					res = iterable<unique, N, T>(*_range).end();
					return res;
				}
				continue;
			}
			
			if(unique && rngdistance(res._array[N-i], res._range->_end) < i)
			{
				if(i == N)
				{
					res = iterable<unique, N, T>(*_range).end();
					return res;
				}
				continue;
			}
			for(size_t j = N-i+1; j<N; ++j)
			{
				res._array[j] = res._array[j-1];
				if(unique)
				{
					rngadvance(res._array[j], size_t(1));
				}
			}
			break;
		}
		
		return res;
	}
}
