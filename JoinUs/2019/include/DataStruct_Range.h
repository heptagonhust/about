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
//! @file      DataStruct_Range.h
//! @brief     Arbitrary range of array which is encapsulated using C++.
//!			   Fortran custom is considered also. The start and end indices can be arbitrary.
//!			   This is referred from Blitz.
//! @author    Bell, original by He Xin.

#pragma once
#include <iostream>
#include <climits>
using namespace std;
namespace FYSPACE
{
	//! @brief Range: arbitrary range of array which is encapsulated using C++.
	//!			   Fortran custom is considered also. The start and end indices can be arbitrary.
	class Range
	{
	private:
		//! The start index of the range.
		int first_;

		//! The end index of the range.
		int last_;

		//! Stride.
		int stride_;

	public:
		// This declaration not yet supported by all compilers
		// const int fromStart = INT_MIN;
		// const int toEnd = INT_MIN;

		typedef int T_numtype;

		enum { fromStart = INT_MIN, toEnd = INT_MIN };

		Range()
		{
			first_  = fromStart;
			last_   = toEnd;
			stride_ = 1;
		}

		// Range(Range r): allow default copy constructor to be used

		Range(const Range& rightRange)
		{
			first_  = rightRange.first_;
			last_   = rightRange.last_;
			stride_ = rightRange.stride_;
		}

		explicit Range(int slicePosition)
		{
			first_  = slicePosition;
			last_   = slicePosition;
			stride_ = 1;
		}

		Range(int first, int last, int stride = 1)
			: first_(first), last_(last), stride_(stride)
		{ 
		}

		//! Return the start index.
		int first(int lowRange = 0) const;

		//! Return the end index.
		int last(int highRange = 0) const;

		//! Return the range length.
		unsigned length( int = 0 ) const;

		//! Return the stride.
		int stride() const;

		//! Return if the range is ascending ordered.
		bool isAscendingContiguous() const;

		//! Reset the range, start with first, end with last, and stride.
		void setRange(int first, int last, int stride=1);

		//! If the stride is one or not.
		bool isUnitStride() const;

		bool hasFastAccess() const;

		T_numtype fastAccess(unsigned i) const;

		unsigned suggestLength() const;

		static Range all() 
		{ 
			return Range(fromStart,toEnd,1);
		}

		// Operators
		Range operator - (int shift) const
		{ 
			return Range(first_ - shift, last_ - shift, stride_); 
		}

		Range operator + (int shift) const
		{ 
			return Range(first_ + shift, last_ + shift, stride_); 
		}

		int operator [] (unsigned i) const
		{
			return first_ + i * stride_;
		}

		int operator () (unsigned i) const
		{
			return first_ + i * stride_;
		}

		friend inline ostream& operator << (ostream& os, const Range& range)
		{
			os << "Range(" << range.first() << "," << range.last() << ","
				<< range.stride() << ")";

			return os;
		}
	};

#include "DataStruct_Range.hxx"

}
