//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                                                             +
//       Hybrid Platform for Engineering and Research of Flows (HyperFlow)     +
//                        面向流体工程与研究的混合CFD平台                      +
//                        （C）Zhang Laiping and He Xin                        +
//                    State Key Laboratory of Aerodynamics                     +
//                    Computational Aerodynamics Institute                     +
//            China Aerodynamics Research and Development Center               +
//                                 Since 2007                                  +
//                                                                             +
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 文件头部说明：                                                              +
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// FILE:       XXX.cpp (XXX.h)                                                 +
// AUTHOR(S):  He Xin                                                          +
// PURPOSE:    simulation object                                               +
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 函数头部说明：                                                              +
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Function:   例如：Simulation::Simulation()                                  +
// AUTHOR(S):  He Xin                                                          +
// PURPOSE:    具体说明本模块的功能                                            +
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once

namespace FYSPACE
{

// This member template is also used in the implementation of
// operator() with any combination of int and Rank parameters.
// It's called by constructSlice(), above.  This version handles
// Range parameters.

template < typename T, int N > template < int N2 >
void FYArray<T, N>::slice(int& setRank, Range r, FYArray<T,N2>& array_in, SimpleArray<int,N2>& rankMap, int sourceRank)
{
    // NEEDS WORK: ordering will change completely when some ranks
    // are deleted.

    rankMap[sourceRank] = setRank;
    length_[setRank]    = array_in.length(sourceRank);
    stride_[setRank]    = array_in.stride(sourceRank);
    storage_.setAscendingFlag(setRank, array_in.isRankStoredAscending(sourceRank));
    storage_.setBase(setRank, array_in.base(sourceRank));
    slice(setRank, r);
    ++ setRank;
}

// This member template is also used in the implementation of
// operator() with any combination of int and Rank parameters.
// It's called by constructSlice(), above.  This version handles
// int parameters, which reduce the dimensionality by one.

template < typename T, int N > template  <int N2 >
void FYArray<T, N>::slice(int& setRank, int i, FYArray<T,N2>& array_in, SimpleArray<int,N2>& rankMap, int sourceRank)
{
    rankMap[sourceRank] = -1;
    data_ += i * array_in.stride(sourceRank);
}

template < typename T, int N > template<int N2>
void FYArray<T, N>::slice(int& setRank, FYnilArraySection nil, FYArray<T,N2>& array_in, SimpleArray<int,N2>& rankMap, int sourceRank)
{ }

// This member template is used to implement operator() with any
// combination of int and Range parameters.  There's room for up
// to 11 parameters, but any unused parameters have no effect.

template < typename T, int N > template < int N2, typename R0,
    typename R1, typename R2, typename R3, typename R4, typename R5, typename R6, typename R7,
    typename R8, typename R9, typename R10 >
void FYArray<T, N>::constructSlice(FYArray<T, N2>& array_in,
    R0 r0, R1 r1, R2 r2, R3 r3, R4 r4, R5 r5, R6 r6, R7 r7, R8 r8, R9 r9, R10 r10)
{
    MemoryBlockReference<T>::changeBlock(array_in);

    int setRank = 0;

	SimpleArray<int,N2> rankMap;

    slice(setRank, r0 , array_in, rankMap, 0 );
    slice(setRank, r1 , array_in, rankMap, 1 );
    slice(setRank, r2 , array_in, rankMap, 2 );
    slice(setRank, r3 , array_in, rankMap, 3 );
    slice(setRank, r4 , array_in, rankMap, 4 );
    slice(setRank, r5 , array_in, rankMap, 5 );
    slice(setRank, r6 , array_in, rankMap, 6 );
    slice(setRank, r7 , array_in, rankMap, 7 );
    slice(setRank, r8 , array_in, rankMap, 8 );
    slice(setRank, r9 , array_in, rankMap, 9 );
    slice(setRank, r10, array_in, rankMap, 10);

    // Redo the ordering_ array to account for dimensions which
    // have been sliced away.
    int j = 0;
    for ( int i = 0; i < N2; ++ i )
    {
        if ( rankMap[array_in.ordering(i)] != -1 )
		{
            storage_.setOrdering(j ++, rankMap[array_in.ordering(i)]);
		}
    }

    calculateZeroOffset();
}

/*
 * After calling slice(int rank, Range r), the array refers only to the
 * Range r of the original array.
 * e.g. Array<int,1> x(100);
 *      x.slice(firstRank, Range(25,50));
 *      x = 0;       // Sets elements 25..50 of the original array to 0
 */
template<typename T, int N>
void FYArray<T, N>::slice(int rank, Range r)
{
	int first  = r.first(lbound(rank));
    int last   = r.last (ubound(rank));
    int stride = r.stride();

    // Will the storage be non-contiguous?
    // (1) Slice in the minor dimension and the range does not span
    //     the entire index interval (NB: non-unit strides are possible)
    // (2) Slice in a middle dimension and the range is not Range::all()

    length_[rank] = (last - first) / stride + 1;

    // TV 20000312: added second term here, for testsuite/Josef-Wagenhuber
    int offset = (first - base(rank) * stride) * stride_[rank];

    data_       += offset;
    zeroOffset_ += offset;
    stride_[rank] *= stride;

    // JCC: adjust ascending flag if slicing with backwards Range
    if ( stride < 0 )
	{
        storage_.setAscendingFlag(rank, !isRankStoredAscending(rank));
	}
}

}


