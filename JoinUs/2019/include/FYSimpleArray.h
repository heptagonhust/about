//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//          PPPPP  H   H  EEEEE  N    N  GGGGG  L      EEEEE  III         +  
//          P   P  H   H  E      NN   N  G      L      E       I          +
//          PPPPP  HHHHH  EEEEE  N N  N  G  GG  L      EEEEE   I          +
//          P      H   H  E      N  N N  G   G  L      E       I          +
//          P      H   H  EEEEE  N    N  GGGGG  LLLLL  EEEEE  III         +
//------------------------------------------------------------------------+
//          Platform for Hybrid Engineering Simulation of Flows           +
//          China Aerodynamics Research and Development Center            +
//                     (C) Copyright, Since 2010                          +
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//! @file      FYSimpleArray.h
//! @brief     Explain this file briefly.
//! @author    xxx.


#pragma once
#include <cstddef>
#include <stdexcept>
#include "DataStruct_Range.h"
namespace FYSPACE
{
template < typename T, int N >
class SimpleArray
{
public:
    T elems[N];    // fixed-size array of elements of type T
public:
    // type definitions
    typedef T              value_type;
    typedef T*             iterator;
    typedef const T*       const_iterator;
    typedef T&             reference;
    typedef const T&       const_reference;
    typedef std::size_t    size_type;
    typedef std::ptrdiff_t difference_type;

    // iterator support
    iterator begin() { return elems; }
    const_iterator begin() const { return elems; }
    iterator end() { return elems+N; }
    const_iterator end() const { return elems+N; }

    // reverse iterator support
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

    reverse_iterator rbegin() { return reverse_iterator(end()); }
    const_reverse_iterator rbegin() const
    {
        return const_reverse_iterator(end());
    }
    reverse_iterator rend() { return reverse_iterator(begin()); }
    const_reverse_iterator rend() const
    {
        return const_reverse_iterator(begin());
    }

    // operator[]
    reference operator[](size_type i)
    {
        return elems[i];
    }

    const_reference operator[](size_type i) const
    {
        return elems[i];
    }

    // at() with range check
    reference at(size_type i) { rangecheck(i); return elems[i]; }
    const_reference at(size_type i) const { rangecheck(i); return elems[i]; }

    // front() and back()
    reference front()
    {
        return elems[0];
    }

    const_reference front() const
    {
        return elems[0];
    }

    reference back()
    {
        return elems[N-1];
    }

    const_reference back() const
    {
        return elems[N-1];
    }

    // size is constant
    static size_type size() { return N; }
    static bool empty() { return false; }
    static size_type max_size() { return N; }
    enum { static_size = N };

    // swap (note: linear complexity)
    void swap (SimpleArray<T,N>& y)
    {
        std::swap_ranges(begin(),end(),y.begin());
    }

    // direct access to data (read-only)
    const T* data() const { return elems; }

    // use array as C array (direct read/write access to data)
    T* c_array() { return elems; }

    // assignment with type conversion
    template <typename T2>
    SimpleArray<T,N>& operator = (const SimpleArray<T2,N>& rhs) {
        std::copy(rhs.begin(),rhs.end(), begin());
        return *this;
    }

    SimpleArray<T,N>& operator = (const T & value) {
        std::fill_n(begin(),size(),value);
        return *this;
    }
    SimpleArray<T,N>& operator += (const T & value)
    {
        for ( int i = 0; i < N; ++ i )
        {
            elems[i] += value;
        }
        return *this;
    }

    SimpleArray<T,N>& operator += (const SimpleArray<T, N>& x)
    {
        const T * tmp = x.data();
        for ( int i = 0; i < N; ++ i )
        {
            elems[i] += tmp[i];
        }
        return *this;
    }

    SimpleArray<T,N>& operator -= (const T & value)
    {
        for ( int i = 0; i < N; ++ i )
        {
            elems[i] -= value;
        }
        return *this;
    }

    SimpleArray<T,N>& operator -= (const SimpleArray<T, N>& x)
    {
        const T * tmp = x.data();
        for ( int i = 0; i < N; ++ i )
        {
            elems[i] -= tmp[i];
        }
        return *this;
    }
    // assign one value to all elements
    void assign (const T& value)
    {
        std::fill_n(begin(),size(),value);
    }

    // check range (may be private because it is static)
    static void rangecheck (size_type i)
    {
        if ( i >= size() )
        {
            throw std::range_error("SimpleArray<>: index out of range");
        }
    }
};

// comparisons
template < typename T, int N >
bool operator == (const SimpleArray<T,N>& x, const SimpleArray<T,N>& y)
{
    return std::equal(x.begin(), x.end(), y.begin());
}
template < typename T, int N >
bool operator < (const SimpleArray<T,N>& x, const SimpleArray<T,N>& y)
{
    return std::lexicographical_compare(x.begin(),x.end(),y.begin(),y.end());
}

template < typename T, int N >
bool operator != (const SimpleArray<T,N>& x, const SimpleArray<T,N>& y)
{
    return ! ( x == y );
}

template < typename T, int N >
bool operator > (const SimpleArray<T,N>& x, const SimpleArray<T,N>& y)
{
    return y < x;
}

template < typename T, int N >
bool operator <= (const SimpleArray<T,N>& x, const SimpleArray<T,N>& y)
{
    return ! ( y < x );
}

template < typename T, int N >
bool operator >= (const SimpleArray<T,N>& x, const SimpleArray<T,N>& y)
{
    return ! ( x < y );
}

// global swap()
template <typename T, int N >
inline void swap (SimpleArray<T,N>& x, SimpleArray<T,N>& y)
{
    x.swap(y);
}

template < typename T, int N >
inline T dot (const SimpleArray<T,N>& x, const SimpleArray<T,N>& y)
{
	T sum = 0;
    for ( int i = 0; i < N; ++ i )
	{
		sum += x[i] * y[i];
	}
	return sum;
}

}
