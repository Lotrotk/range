#pragma once

#include <algorithm>
#include <array>
#include <cstdint>
#include <type_traits>

namespace rng
{
	class DynamicSeparate
	{
	public:
		explicit DynamicSeparate(bool const separate) : _separate(separate) {}
		
		bool separate() const { return _separate; }
		
	private:
		bool _separate;
	};
	
	template<bool S>
	class StaticSeparate
	{
	public:
		static constexpr bool separate() { return S; }
	};
	
	template<typename T>
	class range;
	
	template<typename separate_facet, size_t N, typename T>
	class iterable;
	
	template<typename separate_facet, size_t N, typename T>
	class iterator;
	
	template<size_t N, typename T>
	using split = std::array<T, N>;
	
	template<size_t N, typename T>
	bool has_empty_range(split<N, T> const&, range<T> const&);
	
	////////////////////////////////////////////////////////////////
	
	template<typename separate_facet, size_t N, typename T>
	class iterator
	{
	public:
		using split_t = split<N, T>;
		using iterable_t = iterable<separate_facet, N, T>;
		
	public:
		iterator(iterator &&other) = default;
		iterator &operator=(iterator &&other) = default;
	
		iterator &operator++();
		
        split_t const &operator*() const { return _array; }
		bool operator!=(iterator const &other) const { return _array != other._array; }
		
	private:
        iterator(iterable_t const &i, T const &v) : _iterable(&i) { _array.fill(v); }
		
	private:
		iterable_t const *_iterable{};
		split_t _array;
		
	private:
		template<typename, size_t, typename> friend class iterable;
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
		template<typename, size_t, typename> friend class iterable;
		template<typename, size_t, typename> friend class iterator;
		template<size_t N, typename U> friend bool has_empty_range(split<N, U> const&, range<U> const&);
	};
	
	template<typename separate_facet, size_t N, typename T>
	class iterable : private separate_facet
	{
		static_assert(N > 0, "There must be at least one subrange");
	public:
		using range_t = range<T>;
		using iterator_t = iterator<separate_facet, N, T>;
		using split_t = typename iterator_t::split_t;
		
	public:
		constexpr iterable(range_t const &r, separate_facet &&s) : separate_facet(std::move(s)), _range(r) {}
		constexpr iterable(range_t const &r) : _range(r) {}
		
		iterator_t begin() const;
		iterator_t end() const;
		
	private:
		range_t _range;
		
	private:
		template<typename, size_t, typename> friend class iterator;
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
	
	template<typename separate_facet, size_t N, typename T>
	typename iterable<separate_facet, N, T>::iterator_t iterable<separate_facet, N, T>::begin() const
	{
		iterator_t res(*this, _range._begin);	
		if(separate_facet::separate())
		{
			size_t const R = rngdistance(_range._begin, _range._end);
			for(size_t i=0; i <N; ++i)
			{
				if(i + 1 < R)
				{
					rngadvance(res._array[i], i + 1);
				}
				else
				{
					res._array[i] = _range._end;
				}
			}
		}
				
		return res;
	}
	
	template<typename separate_facet, size_t N, typename T>
	typename iterable<separate_facet, N, T>::iterator_t iterable<separate_facet, N, T>::end() const
	{
		iterator_t res(*this, _range._begin);
		res._array[0] = _range._end;
		return res;
	}
	
	template<typename separate_facet, size_t N, typename T>
	iterator<separate_facet, N, T> &iterator<separate_facet, N, T>::operator++()
	{
		iterator &res = *this;
		
		size_t i = 1;
		for(; i <= N; ++i)
		{
			if(res._array[N-i] == res._iterable->_range._end)
			{
				if(i == N)
				{
					res = _iterable->end();
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
			if(res._iterable->separate_facet::separate() && res._array[j] != res._iterable->_range._end)
			{
				rngadvance(res._array[j], size_t(1));
			}
		}
		
		return res;
	}
	
	template<size_t N, typename T>
	bool has_empty_range(split<N, T> const &v, range<T> const &r)
	{
		return
			v.front() == r._begin
			||
			std::any_of(v.begin(), v.end(), [&r](T const &t) { return t == r._end; })
			||
			std::adjacent_find(v.begin(), v.end()) != v.end();
	}
}
