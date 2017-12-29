#pragma once

#include <algorithm>
#include <array>
#include <cstdint>
#include <stdexcept>
#include <type_traits>
#include <vector>

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
	class DynamicSize
	{
	public:
		using value_t = T;
		using split_t = std::vector<T>;
		
	public:
		DynamicSize(size_t const size) : _size(size)
		{
			if(size == 0)
			{
				throw std::runtime_error("There must be at least one split");
			}
		}
	
		size_t size() const { return _size; }
		split_t split(T const &v) const { return split_t(_size, v); }
		
	private:
		size_t _size;
	};
	
	template<size_t N, typename T>
	class StaticSize
	{
		static_assert(N > 0, "There must be at least one split");
	public:
		using value_t = T;
		using split_t = std::array<T, N>;
		
	public:		
		static constexpr size_t size() { return N; }
		
		split_t split(T const &v) const { split_t res; res.fill(v); return res; }
	};
	
	template<typename T>
	class range;
	
	template<typename separate_facet, typename size_facet>
	class iterable;
	
	template<typename separate_facet, typename size_facet, typename T>
	class iterator;
	
	template<typename split_t, typename T>
	bool has_empty_range(split_t const&, range<T> const&);
	
	////////////////////////////////////////////////////////////////
	
	template<typename separate_facet, typename size_facet, typename T>
	class iterator
	{
	public:
		using split_t = typename size_facet::split_t;
		using iterable_t = iterable<separate_facet, size_facet>;
		
	public:
		iterator(iterator &&other) = default;
		iterator &operator=(iterator &&other) = default;
	
		iterator &operator++();
		
        split_t const &operator*() const { return _split; }
		bool operator!=(iterator const &other) const { return _split != other._split; }
		
	private:
        iterator(iterable_t const &i, T const &v) : _iterable(&i), _split(i.size_facet::split(v)) {}
		
	private:
		iterable_t const *_iterable{};
		split_t _split;
		
	private:
		template<typename, typename> friend class iterable;
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
		template<typename, typename> friend class iterable;
		template<typename, typename, typename> friend class iterator;
		template<typename s, typename U> friend bool has_empty_range(s const&, range<U> const&);
	};
	
	template<typename separate_facet, typename size_facet>
	class iterable : private separate_facet, private size_facet
	{
	public:
		using value_t = typename size_facet::value_t;
		using range_t = range<value_t>;
		using iterator_t = iterator<separate_facet, size_facet, value_t>;
		
	public:
		constexpr iterable(range_t const &r, separate_facet &&separate, size_facet &&size) : separate_facet(std::move(separate)), size_facet(std::move(size)), _range(r) {}
		constexpr iterable(range_t const &r, separate_facet &&separate) : separate_facet(std::move(separate)), _range(r) {}
		constexpr iterable(range_t const &r, size_facet &&size) : size_facet(std::move(size)), _range(r) {}
		constexpr iterable(range_t const &r) : _range(r) {}
		
		iterator_t begin() const;
		iterator_t end() const;
		
	private:
		range_t _range;
		
	private:
		template<typename, typename, typename> friend class iterator;
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
	
	template<typename separate_facet, typename size_facet>
	typename iterable<separate_facet, size_facet>::iterator_t iterable<separate_facet, size_facet>::begin() const
	{
		iterator_t res(*this, _range._begin);	
		if(separate_facet::separate())
		{
			size_t const R = rngdistance(_range._begin, _range._end);
			for(size_t i=0; i<size_facet::size(); ++i)
			{
				if(i + 1 < R)
				{
					rngadvance(res._split[i], i + 1);
				}
				else
				{
					res._split[i] = _range._end;
				}
			}
		}
				
		return res;
	}
	
	template<typename separate_facet, typename size_facet>
	typename iterable<separate_facet, size_facet>::iterator_t iterable<separate_facet, size_facet>::end() const
	{
		iterator_t res(*this, _range._begin);
		res._split[0] = _range._end;
		return res;
	}
	
	template<typename separate_facet, typename size_facet, typename T>
	iterator<separate_facet, size_facet, T> &iterator<separate_facet, size_facet, T>::operator++()
	{
		iterator &res = *this;
		size_t const N = res._iterable->size_facet::size();
		
		size_t i = 1;
		for(; i <= N; ++i)
		{
			if(res._split[N-i] == res._iterable->_range._end)
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
			
		rngadvance(res._split[N-i], size_t(1));
		for(size_t j = N-i+1; j<N; ++j)
		{
			res._split[j] = res._split[j-1];
			if(res._iterable->separate_facet::separate() && res._split[j] != res._iterable->_range._end)
			{
				rngadvance(res._split[j], size_t(1));
			}
		}
		
		return res;
	}
	
	template<typename split_t, typename T>
	bool has_empty_range(split_t const &v, range<T> const &r)
	{
		return
			v.front() == r._begin
			||
			std::any_of(v.begin(), v.end(), [&r](T const &t) { return t == r._end; })
			||
			std::adjacent_find(v.begin(), v.end()) != v.end();
	}
}
