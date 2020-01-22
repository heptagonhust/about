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
//! @file      FYFastArrayIterator.h
//! @brief     Explain this file briefly.
//! @author    He Xin.

#pragma once

namespace FYSPACE
{

// helper class ConstPointerStack
template<typename T, int N>
class FYConstPointerStack
{
public:
    typedef T  T_numtype;

    void operator = (const FYConstPointerStack<T,N>& rhs) 
    {
        for ( int i = 0; i < N; ++ i )
		{
			stack_[i] = rhs.stack_[i];
		}
    }

    const T_numtype*& operator[](int position)
    {
        return stack_[position];
    }
      
private:
    const T_numtype * stack_[N];
};

template<typename T, int N>
class FYFastArrayIterator
{
public:
	typedef T             T_numtype;
    typedef FYArray<T, N> T_array;
    typedef FYFastArrayIterator<T, N> iterator;
    typedef const T_array& T_ctorArg1;
    typedef int            T_ctorArg2;    // dummy

    static const int 
        numArrayOperands = 1, 
        numIndexPlaceholders = 0,
        rank = N;

    FYFastArrayIterator(const FYFastArrayIterator<T, N>& x)
        : data_(x.data_), array_(x.array_)
    { }

    void operator = (const FYFastArrayIterator<T, N>& x)
    {
		array_  = x.array_;
		data_   = x.data_;
		stack_  = x.stack_;
		stride_ = x.stride_;
    }

    FYFastArrayIterator(const T_array& array)
        : array_(array)
    {
        data_ = array.data();
    }

    ~FYFastArrayIterator()
    { }

    T_numtype operator()(const SimpleArray<int, N>& i)
    { 
		return array_(i);
	}

    int ascending(int rank)
    {
        if ( rank < N )
		{
            return array_.isRankStoredAscending(rank);
		}
        else
		{
            return INT_MIN;   // tiny(int());
		}
    }

    int ordering(int rank)
    {
        if ( rank < N )
		{
            return array_.ordering(rank);
		}
        else
		{
            return INT_MIN;   // tiny(int());
		}
    }

    int lbound(int rank)
    { 
        if ( rank < N )
		{
            return array_.lbound(rank); 
		}
        else
		{
            return INT_MIN;   // tiny(int());
		}
    }

    int ubound(int rank)
    { 
        if ( rank < N )
		{
            return array_.ubound(rank); 
		}
        else
		{
            return INT_MAX;   // huge(int());
		}
    }

    T operator * ()
    { 
		return *data_; 
	}

    T operator[](int i)
    { 
		return data_[i * stride_];
	}

    T fastRead(int i)
    { 
		return data_[i]; 
	}

    int suggestStride(int rank) const
    { 
		return array_.stride(rank); 
	}

    bool isStride(int rank, int stride) const
    {
		return array_.stride(rank) == stride; 
	}

    void push(int position)
    {
        stack_[position] = data_;
    }
  
    void pop(int position)
    { 
        data_ = stack_[position];
    }

    void advance()
    {
        data_ += stride_;
    }

    void advance(int n)
    {
        data_ += n * stride_;
    }

    void loadStride(int rank)
    {
        stride_ = array_.stride(rank);
    }

    const T * data() const
    { 
		return data_;
	}

    void SetData(const T* ptr)
    {
		data_ = ptr;
	}

    int stride() const
    {
		return stride_;
	}

    bool isUnitStride(int rank) const
    {
		return array_.stride(rank) == 1;
	}

    void advanceUnitStride()
    {
		++ data_; 
	}

    bool canCollapse(int outerLoopRank, int innerLoopRank) const
    { 
		return array_.canCollapse(outerLoopRank, innerLoopRank);
	}

 //   template<typename T_shape>
 //   bool shapeCheck(const T_shape& shape)
 //   { 
	//	return areShapesConformable(shape, array_.length());
	//}
private:
    const T *                data_;
    const T_array&           array_;
    FYConstPointerStack<T,N> stack_;
    int                      stride_;
};

}


