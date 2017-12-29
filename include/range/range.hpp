#pragma once

#include <algorithm>
#include <array>
#include <cstdint>
#include <type_traits>

namespace rng
{
	template<typename T>
	class range;
	
	template<bool separate, size_t N, typename T>
	class iterable;
	
	template<bool separate, size_t N, typename T>
	class iterator;
	
	template<size_t N, typename T>
	using value = std::array<T, N>;
	
	template<size_t N, typename T>
	bool has_empty_range(value<N, T> const&, range<T> const&);
	
	////////////////////////////////////////////////////////////////
	
	template<bool separate, size_t N, typename T>
	class iterator
	{
	public:
		using value_t = value<N, T>;
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
		template<size_t N, typename U> friend bool has_empty_range(value<N, U> const&, range<U> const&);
	};
	
	template<bool separate, size_t N, typename T>
	class iterable
	{
		static_assert(N > 0, "There must be at least one subrange");
	public:
		using range_t = range<T>;
		using iterator_t = iterator<separate, N, T>;
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
	
	template<bool separate, size_t N, typename T>
	typename iterable<separate, N, T>::iterator_t iterable<separate, N, T>::begin() const
	{
		iterator_t res(_range, _range._begin);	
		if(separate)
		{
			size_t const R = rngdistance(_range._begin, _range._end);
			for(size_t i=0; i <N; ++i)
			{
				if(i < R)
				{
					rngadvance(res._array[i], i);
				}
				else
				{
					res._array[i] = _range._end;
				}
			}
		}
				
		return res;
	}
	
	template<bool separate, size_t N, typename T>
	typename iterable<separate, N, T>::iterator_t iterable<separate, N, T>::end() const
	{
		iterator_t res(_range, _range._begin);
		res._array[0] = _range._end;
		return res;
	}
	
	template<bool separate, size_t N, typename T>
	iterator<separate, N, T> &iterator<separate, N, T>::operator++()
	{
		iterator &res = *this;
		
		size_t i = 1;
		for(; i <= N; ++i)
		{
			if(res._array[N-i] == res._range->_end)
			{
				if(i == N)
				{
					res = iterable<separate, N, T>(*_range).end();
					return res;
				}
				continue;
			}
			break;
		}
			
		rngadvance(res._array[N-i], size_t(1));
		for(size_t j = N-i+1; j<N; ++j)
		{
			res._array[j] = res._array[j-1];
			if(separate && res._array[j] != res._range->_end)
			{
				rngadvance(res._array[j], size_t(1));
			}
		}
		
		return res;
	}
	
	template<size_t N, typename T>
	bool has_empty_range(value<N, T> const &v, range<T> const &r)
	{
		return std::any_of(v.begin(), v.end(), [&r](T const &t) { return t == r._end; }) || std::adjacent_find(v.begin(), v.end()) != v.end();
	}
}
