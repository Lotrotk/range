#pragma once

#include <cstdint>
#include <array>
#include <type_traits>

namespace rng
{
	template<typename T>
	class range;
	
	template<size_t N, typename T, bool unique>
	class iterable;
	
	template<size_t N, typename T, bool unique>
	class iterator;
	
	////////////////////////////////////////////////////////////////
	
	template<size_t N, typename T, bool unique>
	class iterator
	{
	public:
		using range_t = range<T>;
		
	public:
		iterator(iterator&&) = default;
		iterator &operator=(iterator&&) = default;
	
		iterator &operator++();
		
		std::array<T, N> const &operator*() const { return _array; }
		bool operator!=(iterator const &other) const { return _array != other._array; }
		
	private:
		template<typename...args_t>
		iterator(range_t const &r, args_t&&...args) : _range(&r), _array{std::forward<args_t...>(args...)} {}
		
	private:
		range_t const *_range{};
		std::array<T, N> _array;
		
	private:
		template<size_t, typename, bool> friend class iterable;
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
		template<size_t, typename, bool> friend class iterable;
		template<size_t, typename, bool> friend class iterator;
	};
	
	template<size_t N, typename T, bool unique>
	class iterable
	{
	public:
		using range_t = range<T>;
		using iterator_t = iterator<N, T, unique>;
		
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
	template<typename T, typename = std::enable_if<std::is_integral<T>::value>>
	T distance(T const a, T const b) { return b - a; }
	
	template<typename T, typename = std::enable_if<std::is_integral<T>::value>>
	void advance(T &a, size_t const d) { a += d; }
	
	template<size_t N, typename T, bool unique>
	typename iterable<N, T, unique>::iterator_t iterable<N, T, unique>::begin() const
	{	
		if(!unique)
		{
			return iterator_t(_range, _range._begin);
		}
		
		using std::distance;
		using rng::distance;
		if(distance(_range._begin, _range._end) < N)
		{
			return end();
		}
		
		iterator_t res(_range, _range._begin);
		for(size_t i = 0; i < N; ++i)
		{
			using std::advance;
			using rng::advance;
			advance(res._array[i], i);
		}
		
		return res;
	}
	
	template<size_t N, typename T, bool unique>
	typename iterable<N, T, unique>::iterator_t iterable<N, T, unique>::end() const
	{
		iterator_t res(_range, _range._begin);
		res._array[0] = _range._end;
		return res;
	}
	
	template<size_t N, typename T, bool unique>
	iterator<N, T, unique> &iterator<N, T, unique>::operator++()
	{
		using std::advance;
		using rng::advance;
		
		iterator &res = *this;
				
		for(size_t i = 1; i <= N; ++i)
		{
			advance(res._array[N-i], size_t(1));
			if(res._array[N-i] == res._range->_end)
			{
				if(i == N)
				{
					res = iterable<N, T, unique>(*_range).end();
					return res;
				}
				continue;
			}
			
			if(unique && distance(res._array[N-i], res._range->_end) <= i-1)
			{
				res = iterable<N, T, unique>(*_range).end();
				return res;
			}
			for(size_t j = N-i+1; j<N; ++j)
			{
				res._array[j] = res._array[j-1];
				if(unique)
				{
					advance(res._array[j], size_t(1));
				}
			}
			break;
		}
		
		return res;
	}
}
