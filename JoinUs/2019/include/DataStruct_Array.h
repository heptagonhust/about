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
//! @file      FYArray.h
//! @brief     FYArray defines a multidimensional array class. It is a template class.
//!            FYArray<T,N> refers to a N-dimensional T type array
//!            We can construct a multidimensional array by specify every dimension's length or range.
//!            The way of underlying data's storage follow the example of fortran,
//!            e.g. we can construct an 3d float type array by length, FYArray<float,3> array3d = FY<float,3>(10, 20, 30)
//!            and access the i,j,k index data by operator(), i.e. array3d(i,j,k).
//!            The underlying data's memory storage sequence is from innermost(i) layer to outermost layer(k).
//!            So, if we loop over all the data, we recommend you loop from k to i, i.e for(k,...){for(j,...){for(i,...)}}}
//!            FYArray class also implement some other array's scalar operatation +=, -=, *=, /=, e.g. array1 *= 0.1.
//!            Some other set operator like =, +, -, *, /. We can directly use these operators to FYArray object
//!            e.g. dql(I,J,K,M) = xbmuscl * qr(I,J,K,M)
//! @author    Zhang Jian. Original by He Xin, referred from Blitz.
#pragma once
#include <cstddef>
#include <stdexcept>
#include <stdlib.h>
#include "FYSimpleArray.h"
#include "FYStorage.h"
#include "FYMemblock.h"
#include "FYProduct.h"
#include "FYETBase.h"
#include "FYSlice.h"   // Sub-arrays and slicing

namespace FYSPACE
{

template < typename T, int N >
class FYFastArrayIterator;

template < typename T, int N >
class FYArray : public MemoryBlockReference<T> , public FYETBase< FYArray<T,N> >
{
private:
	typedef MemoryBlockReference<T> T_base;
    using T_base::data_;
    using T_base::changeToNullBlock;
    using T_base::numReferences;
    GeneralArrayStorage<N> storage_;
    SimpleArray<int, N> length_;
    SimpleArray<int, N> stride_;
    int zeroOffset_;
public:
	//! T_numtype is the numeric type stored in the array.
	typedef T                   T_numtype;

	//! T_index is a vector type which can be used to access elements
	//! of many-dimensional arrays.
	typedef SimpleArray<int, N> T_index;
	
	//! T_array is the array type itself -- Array<T_numtype, N_rank>
	typedef FYArray<T, N> T_array;

	//! T_iterator is a a fast iterator for the array, used for expression
	//  templates
	typedef FYFastArrayIterator<T, N> T_iterator;

	//! This array's dimension
	static const int ranks = N;

public:
    //! Create a reference of another array
    FYArray(const FYArray<T, N>& array);

    //! Any missing length arguments will have their value taken from the
    //! last argument.  For example,
    //! Array<int,3> A(32,64);
    //! will create a 32x64x64 array.  This is handled by setupStorage().
	//! Construct an array by each dimension's length
    FYArray(GeneralArrayStorage<N> storage = GeneralArrayStorage<N>());

	//! Construct an array by each dimension's length
    explicit FYArray(int length0, 
			GeneralArrayStorage<N> storage = GeneralArrayStorage<N>());

	//! Construct an array by each dimension's length
    FYArray(int length0, int length1,
            GeneralArrayStorage<N> storage = GeneralArrayStorage<N>());

	//! Construct an array by each dimension's length
    FYArray(int length0, int length1, int length2,
            GeneralArrayStorage<N> storage = GeneralArrayStorage<N>());

	//! Construct an array by each dimension's length
    FYArray(int length0, int length1, int length2, int length3,
            GeneralArrayStorage<N> storage = GeneralArrayStorage<N>());

	//! Construct an array by each dimension's length
    FYArray(int length0, int length1, int length2, int length3, int length4,
            GeneralArrayStorage<N> storage = GeneralArrayStorage<N>());

    //! This constructor takes an extent (length) vector and storage format.
    FYArray(const SimpleArray<int, N>& extent, 
            GeneralArrayStorage<N> storage = GeneralArrayStorage<N>());

    //! This constructor takes a vector of bases (lbounds) and a vector of extents.
    FYArray(const SimpleArray<int, N>& lbounds,
            const SimpleArray<int, N>& extent,
            const GeneralArrayStorage<N>& storage = GeneralArrayStorage<N>());

    //! These constructors allow arbitrary bases (starting indices) to be set.
    //! e.g. Array<int,2> A(Range(10,20), Range(20,30))
    //! will create an 11x11 array whose indices are 10..20 and 20..30
	//! Construct an array by each dimension's range
    FYArray(Range r0, 
            GeneralArrayStorage<N> storage = GeneralArrayStorage<N>());

	//! Construct an array by each dimension's range
    FYArray(Range r0, Range r1,
            GeneralArrayStorage<N> storage = GeneralArrayStorage<N>());

	//! Construct an array by each dimension's range
    FYArray(Range r0, Range r1, Range r2,
            GeneralArrayStorage<N> storage = GeneralArrayStorage<N>());

	//! Construct an array by each dimension's range
    FYArray(Range r0, Range r1, Range r2, Range r3,
            GeneralArrayStorage<N> storage = GeneralArrayStorage<N>());

	//! Construct an array by each dimension's range
    FYArray(Range r0, Range r1, Range r2, Range r3, Range r4,
            GeneralArrayStorage<N> storage = GeneralArrayStorage<N>());

	//! Construct an array from an existing block of memory.
    FYArray(T* dataFirst,
			Range r0,
			preexistingMemoryPolicy deletionPolicy,
            GeneralArrayStorage<N> storage = GeneralArrayStorage<N>());

	//! Construct an array from an existing block of memory.
    FYArray(T* dataFirst,
			Range r0, Range r1,
			preexistingMemoryPolicy deletionPolicy,
            GeneralArrayStorage<N> storage = GeneralArrayStorage<N>());

	//! Construct an array from an existing block of memory.
    FYArray(T* dataFirst,
			Range r0, Range r1, Range r2,
			preexistingMemoryPolicy deletionPolicy,
            GeneralArrayStorage<N> storage = GeneralArrayStorage<N>());

	//! Construct an array from an existing block of memory.
    FYArray(T* dataFirst,
			Range r0, Range r1, Range r2, Range r3,
			preexistingMemoryPolicy deletionPolicy,
            GeneralArrayStorage<N> storage = GeneralArrayStorage<N>());

	//! Construct an array from an existing block of memory.
    FYArray(T* dataFirst,
			Range r0, Range r1, Range r2, Range r3, Range r4,
			preexistingMemoryPolicy deletionPolicy,
            GeneralArrayStorage<N> storage = GeneralArrayStorage<N>());

	//! These constructors construct an subarray from another array
	//! Construct an subarray from another array
	FYArray(FYArray<T, N>& array_in, Range r0);

	//! Construct an subarray from another array
	FYArray(FYArray<T, N>& array_in, Range r0, Range r1);

	//! Construct an subarray from another array
	FYArray(FYArray<T, N>& array_in, Range r0, Range r1, Range r2);

	//! Construct an subarray from another array
	FYArray(FYArray<T, N>& array_in, Range r0, Range r1, Range r2, Range r3);

	//! Construct an subarray from another array
	FYArray(FYArray<T, N>& array_in, Range r0, Range r1, Range r2, Range r3, Range r4);

	//! Construct an subarray from another array
	FYArray(FYArray<T, N>& array_in, Range r0, Range r1, Range r2, Range r3, Range r4, Range r5);

	//! Construct an subarray from another array
	FYArray(FYArray<T, N>& array_in, Range r0, Range r1, Range r2, Range r3, Range r4, Range r5, Range r6);

	//! This constructor is invoked by the operator()'s which take
	//! a combination of integer and Range arguments.  
	//! It's not intended for end-user use.
	template < int N2, typename R0, typename R1, typename R2, typename R3, typename R4,
		typename R5, typename R6, typename R7, typename R8, typename R9, typename R10 >
		FYArray(FYArray<T, N2>& array_in, R0 r0, R1 r1, R2 r2,
		R3 r3, R4 r4, R5 r5, R6 r6, R7 r7, R8 r8, R9 r9, R10 r10);

public:
	//! operator() functions:
	//! Returns constant reference to array[i0]
    const T& operator()(int i0) const;

	//! Returns reference to array[i0]
    T&  operator()(int i0);

	//! Returns constant reference to array[i0][i1]
    const T&  operator()(int i0, int i1) const;

	//! Returns reference to array[i0][i1]
    T&  operator()(int i0, int i1);

	//! Returns constant reference to array[i0][i1][i2]
    const T&  operator()(int i0, int i1, int i2) const;

	//! Returns reference to array[i0][i1][i2]
    T&  operator()(int i0, int i1, int i2);

	//! Returns constant reference to array[i0][i1][i2][i3]
    const T&  operator()(int i0, int i1, int i2, int i3) const;

	//! Returns reference to array[i0][i1][i2][i3]
    T&  operator()(int i0, int i1, int i2, int i3);

	//! Returns constant reference to array[i0][i1][i2][i3][i4]
    const T&  operator()(int i0, int i1, int i2, int i3, int i4) const;

	//! Returns reference to array[i0][i1][i2][i3][i4]
    T&  operator()(int i0, int i1, int i2, int i3, int i4);

	//! Returns constant reference to underlying data storage at index i, 
	//! ie. data_[i]
	const T& operator[](int i) const;

	//! Returns reference to underlying data storage at index i, 
	//! ie. data_[i]
	T& operator[](int i);

	//! Returns const reference to underlying data stored by an index array.
	//! e.g index = (10, 20), calculate offset = stride_[0]*10+stride_[1]*20
	//! then returns data_[offset]
    template<int N_rank2>
    const T& operator()(const SimpleArray<int,N_rank2>& index) const;

	//! Returns reference to underlying data stored by an index array.
	//! e.g index = (10, 20), calculate offset = stride_[0]*10+stride_[1]*20
	//! then returns data_[offset]
    template<int N_rank2>
    T& operator()(const SimpleArray<int,N_rank2>& index);

	//! These constructors construct an subarray from this array self
	//! Construct an subarray from this array self by offering a range
    T_array operator()(Range r0) const;

	//! Construct an subarray from this array self by offering a range
    T_array operator()(Range r0, Range r1) const;

	//! Construct an subarray from this array self by offering a range
    T_array operator()(Range r0, Range r1, Range r2) const;

	//! Construct an subarray from this array self by offering a range
    T_array operator()(Range r0, Range r1, Range r2, Range r3) const;

	//! Construct an subarray from this array self by offering a range
    T_array operator()(Range r0, Range r1, Range r2, Range r3, Range r4) const;

	//! Construct an subarray from this array self by offering a range
    T_array operator()(Range r0, Range r1, Range r2, Range r3, Range r4, Range r5) const;

	//! Construct an subarray from this array self by offering a range
    T_array operator()(Range r0, Range r1, Range r2, Range r3, Range r4, Range r5, Range r6) const;

	//! After calling slice(int rank, Range r), the array refers only to the
	//! Range r of the original array.
	//!	 e.g. Array<int,1> x(100);
	//!      x.slice(firstRank, Range(25,50));
	//!      x = 0;       // Sets elements 25..50 of the original array to 0
    template < typename T1, typename T2 >
    typename FYSliceInfo<T,T1,T2>::T_slice operator()(T1 r1, T2 r2) const;

    template < typename T1, typename T2, typename T3 >
    typename FYSliceInfo<T,T1,T2,T3>::T_slice operator()(T1 r1, T2 r2, T3 r3) const;

    template < typename T1, typename T2, typename T3, typename T4 >
    typename FYSliceInfo<T,T1,T2,T3,T4>::T_slice operator()(T1 r1, T2 r2, T3 r3, T4 r4) const;

    template < typename T1, typename T2, typename T3, typename T4, typename T5 >
    typename FYSliceInfo<T,T1,T2,T3,T4,T5>::T_slice operator()(T1 r1, T2 r2, T3 r3, T4 r4, T5 r5) const;

    template < typename T1, typename T2, typename T3, typename T4, typename T5, typename T6 >
    typename FYSliceInfo<T,T1,T2,T3,T4,T5,T6>::T_slice operator()(T1 r1, T2 r2, T3 r3, T4 r4, T5 r5, T6 r6) const;

    //! Array expression operands

    //! Scalar operand
    //! NEEDS_WORK : need a precondition check on
    //! isStorageContiguous when operator, is used.
    T_array& operator=(T x);

	//! operator = expr
	template<typename T_expr>
	T_array& operator = (const FYETBase<T_expr> & expr);

	//! operator = FYArray<T,N>
    T_array& operator = (const FYArray<T,N> & rhs);

	//! operator +=
    template<typename T_expr> T_array& operator += (const T_expr& expr);

	//! operator -=
    template<typename T_expr> T_array& operator -= (const T_expr& expr);

	//! operator *=
    template<typename T_expr> T_array& operator *= (const T_expr& expr);

	//! operator /=
    template<typename T_expr> T_array& operator /= (const T_expr& expr);

    //! Member functions

	//! Returns index relative to data_, ie. data_[index].
	//! index =  i0 * stride_[0] + i1 * stride_[1] + i2 * stride_[2] + i3 * stride_[3].
	int getindex(int i0, int i1, int i2, int i3) const;

	//! Returns the rank dimension's lower bound, ie. range's first index, equals base_[rank]
    int lbound(int rank) const;

	//! Returns the rank dimension's upper bound, ie. range's last index, equals base_[rank]+length_[rank]-1
	int ubound(int rank) const;

	//! Returns the array storing lbound, ie. base_
    SimpleArray<int,N> lbound() const;

	//! Returns the rank dimension's length, ig length_[rank]
    int length(int rank) const;

	//! Returns the array storing length_
    const SimpleArray<int, N>& length() const;

	//! Returns the array storing base_
	//! base_ is each dimension's lower bound
    const SimpleArray<int, N> & base() const;

	//! Return the rank dimension's base, ie. base_[rank]
    int base(int rank) const;

	//! Returns the rank dimension's stride, ie. stride_[rank]
    int stride(int rank) const;

	//! Total number of elements in this array
    int numElements() const;

	
    //! data_ always refers to the point (0,0,...,0) which may
    //! not be in the array if the base is not zero in each rank.
    //! These data() routines return a pointer to the first
    //! element in the array (but note that it may not be
    //! stored first in memory if some ranks are stored descending).
    const T * data() const;

	//! data()是第一个数据成员所在位置，即base点所在位置
	//! base数组时每一维的起始下标,ri.first()
	//! 这对于slice情形尤其重要
	//! slice后第一个数据点实际上为（ifirst，jfirst，...）
	//! 实际位置为data_ + dataOffset();
    T* data();

	//! Judge whether the array's outer dimension's stride equals sum of inner dimension's stride.
	//! eg. if outerRank =3 and innerRank =2 , returns true if stride[3] == stride[2]*length[2], otherwise, returns false
    bool canCollapse(int outerRank, int innerRank) const;

	//! Returns the FYFastArrayIterator of this array
	//! It's not intended for end-user use.
    T_iterator beginFast() const;

	//! Return storage_.ordering(storageRankIndex);
	//! It's not intended for end-user use.
	int ordering(int storageRankIndex) const;

	//! Returns storage_.ordering();
	//! It's not intended for end-user use.
    const SimpleArray<int, N> & ordering() const;

	//! True if storage_.ordering(rank) == 0
	//! It's not intended for end-user use.
    bool isMajorRank(int rank) const;
	
	//! True if storage_.ordering(rank) != 0
	//! It's not intended for end-user use.
    bool isMinorRank(int rank) const;

	//! Call storage_.isRankStoredAscending(rank)
	//! It's not intended for end-user use.
    bool isRankStoredAscending(int rank) const;

protected:
    //! Implementation routines
    void computeStrides();

    void setupStorage(int rank);

    void setupStorage(int rank, T *data, preexistingMemoryPolicy deletionPolicy);

    void calculateZeroOffset();

	void Reference(const T_array&);

	T_array & noConst() const;

	void constructSubarray(FYArray<T, N>& array_in, Range r0);

	void constructSubarray(FYArray<T, N>& array_in, Range r0, Range r1);

	void constructSubarray(FYArray<T, N>& array_in, Range r0, Range r1, Range r2);

	void constructSubarray(FYArray<T, N>& array_in, Range r0, Range r1, Range r2, Range r3);

	void constructSubarray(FYArray<T, N>& array_in, Range r0, Range r1, Range r2, Range r3, Range r4);

	void constructSubarray(FYArray<T, N>& array_in, Range r0, Range r1, Range r2, Range r3, Range r4, Range r5);

	void constructSubarray(FYArray<T, N>& array_in, Range r0, Range r1, Range r2, Range r3, Range r4, Range r5, Range r6);

	template < int N2, typename R0,
		typename R1, typename R2, typename R3, typename R4, typename R5, typename R6, typename R7,
		typename R8, typename R9, typename R10 >
		void constructSlice(FYArray<T, N2>& array_in,
		R0 r0, R1 r1, R2 r2, R3 r3, R4 r4, R5 r5, R6 r6, R7 r7, R8 r8, R9 r9, R10 r10);
	void slice(int rank, Range r);

	template<int N2>
	void slice(int& setRank, Range r, FYArray<T,N2>& array_in, SimpleArray<int,N2>& rankMap, int sourceRank);

	template<int N2>
	void slice(int& setRank, int i, FYArray<T,N2>& array_in, SimpleArray<int,N2>& rankMap, int sourceRank);

	template<int N2>
	void slice(int& setRank, FYnilArraySection nil, FYArray<T,N2>& array_in, SimpleArray<int,N2>& rankMap, int sourceRank);

	T_array& initialize(T x);

	int dataOffset() const;

	template<typename T_expr, typename T_update>
	T_array& evaluate(T_expr expr, T_update);

	template<typename T_expr, typename T_update>
	T_array& evaluateWithIndexTraversal1(T_expr expr, T_update);

	template<typename T_expr, typename T_update>
	T_array& evaluateWithIndexTraversalN(T_expr expr, T_update);

	template<typename T_expr, typename T_update>
	T_array& evaluateWithStackTraversal1(T_expr expr, T_update);

	template<typename T_expr, typename T_update>
	T_array& evaluateWithStackTraversalN(T_expr expr, T_update);

	//! PARATERA START
#ifdef USE_ARRAY_OPT	  
	public:
	//! the underlying data storage(data_) always refers to the point index at (0,0,...,0) which may
	//! not be in the array if the base is not zero in each rank.
	//! returns the pointer to data_
	T* getData() const {
		return data_;
	}
	int get_stride(int rank) const {
		return stride_[rank];//!mei yi wei du de jisuan kuadu   
	}
	int offset(int rank, int indx) const {
		return stride_[rank] * indx;//!the length of (indx) branch
	}
	friend void QsubQ1(FYArray<float, 4> dst1, const FYArray<float, 4> &src1, const FYArray<float, 4> &src2);
	friend void TheReciprocalOfVolAddVol(FYArray<float, 3> dst1, const FYArray<float,3> &src1,const FYArray<float,3> &src2);
	friend void DqdxMultiWorkqm(FYArray<float, 3> dst1, FYArray<float,3> dst2,FYArray<float,3> dst3,const FYArray<float, 3> &src1);
	friend void QlrEqualDq(FYArray<float, 4> dst1, FYArray<float, 4> dst2, const FYArray<float, 4> &src1, const FYArray<float, 4> &src2);
	friend void ParaVanleer(FYArray<float, 4> dst, FYArray<float, 4> dst1, const FYArray<float, 4> &src1, const FYArray<float, 4> &src2,float xbmuscl);
	friend void QaddDqladdDqr(float c1, float c2, FYArray<float, 4> dst1, FYArray<float, 4> dst2, const FYArray<float, 4> &src1, const FYArray<float, 4> &src2, const FYArray<float, 4> &src3);
	friend void FourthMultiQ(const float fourth,FYArray<float,3> dst1,const FYArray<float, 3> &src1, const FYArray<float, 3> &src2,const FYArray<float, 3> &src3, const FYArray<float, 3> &src4);
	friend void XfnMultiAreaAddXfnMultiArea(FYArray<float, 3> &dstx, FYArray<float, 3> &dsty, FYArray<float, 3>& dstz, const FYArray<float, 3> &srcx1, const FYArray<float, 3> &srcy1, const FYArray<float, 3>& srcz1, 
		const FYArray<float, 3> &share1, const FYArray<float, 3> &srcx2, const FYArray<float, 3> &srcy2, const FYArray<float, 3>& srcz2, const FYArray<float, 3> &share2);
	friend void WorksxyzMultiQ(FYArray<float, 3> dstx, FYArray<float, 3> dstx1, FYArray<float, 3> dsty, FYArray<float, 3> dsty1,FYArray<float, 3> dstz, FYArray<float, 3> dstz1,const FYArray<float, 3> &srcx1,
		const FYArray<float, 3> &srcy1,const FYArray<float, 3> &srcz1, const FYArray<float, 3> &src2);

	friend void DqdxAddWorksxyzMultiQ(FYArray<float, 4> &dqdx, FYArray<float, 4> &dqdy, FYArray<float, 4> &dqdz, 
		FYArray<float, 3> &worksx, FYArray<float, 3> &worksy, FYArray<float, 3> &worksz, 
		FYArray<float, 4> &q, Range &I, Range &J, Range &K, int mst, int med, int il1, int jl1, int kl1);
	friend void ZeroAssig(FYArray<float, 4> &src);
    friend void MinModOpt(float value,int ifirst,int iend,float *dst1,float *dst2,float *__restrict src1,float *__restrict srcsl1,float * __restrict srcpl1);
	friend void Q1_P_S_MinMod_Q2 (FYArray<float, 4> dst1, FYArray<float, 4> dst2, const FYArray<float, 4> &src1, int il1,int jl1,int kl1,float value);
	friend void ResComputing(FYArray<float, 4> dst,const FYArray<float, 4> &src,int il1,int jl1,int kl1);
	friend void limiterComputing_If(int str_limiter,FYArray<float, 4> dst1,FYArray<float, 4> dst2,const FYArray<float , 4> &src1,int il1,int jl1,int kl1,float value);
	friend void CalculatebyCellCenterReviseComputingInFYOps(FYArray<float, 4> dqdx_4d,FYArray<float, 4> dqdy_4d,FYArray<float, 4> dqdz_4d,const FYArray<float , 3> &vol,const FYArray<float,4> &dqdxcc_4d,const FYArray<float, 4>dqdycc_4d,const FYArray<float, 4>dqdzcc_4d,const FYArray<float, 3> xvn,const FYArray<float, 3> yvn ,const FYArray<float, 3> zvn,const FYArray<float, 4> q_4d,int il1,int jl1,int kl1,int med,int mst);
	friend void AssignInFYOpt(FYArray<float, 3> dst1,FYArray<float, 3> dst2,FYArray<float, 3> dst3,FYArray<float, 3> dst4,FYArray<float, 3> dst5,FYArray<float, 3> dst6,FYArray<float, 3> dst7,FYArray<float, 3> dst8,FYArray<float, 3> dst9,const FYArray<float, 3> &src1,const FYArray<float, 3> &src2,const FYArray<float, 3> &src3,const FYArray<float, 3> &src4,const FYArray<float, 3> &src5,const FYArray<float, 3> &src6,const FYArray<float, 3> &src7,const FYArray<float, 3> &src8,const FYArray<float, 3> &src9);
#endif
	//! PARATERA END
	//! Added by zhangjian 20170711
	//! #ifdef USE_SMARTARRY will construct an multi-array pointer to the underlying data_
	//! e.g. for a three dimensional T type array with range(r0, r1, r2)
	//! we can get and T*** type pointer called datap3 by GetSmartArrayP3() function
	//! and access the data at index i, j, k directly by datap3[k][j][i].
	//! Remember the way of array storage of range r0, r1, ... corresponding with innermost layer to outermost layer.
	//! Moreover, if use operator(i, j, k), will return datap3[k][j][i] instead of data_[i0 * stride_[0] + i1 * stride_[1]+ i2 * stride_[2]];
#ifdef USE_SMARTARRAY
public:
	typedef T      * TypeP1; //TypeP1 T *
	typedef TypeP1 * TypeP2; //TypeP2 T **
	typedef TypeP2 * TypeP3; //TypeP3 T ***
	typedef TypeP3 * TypeP4; //TypeP4 T ****
	typedef TypeP4 * TypeP5; //TypeP5 T *****
private:
	TypeP1 data1, datap1; //TypeP1 T *
	TypeP2 data2, datap2; //TypeP2 T **
	TypeP3 data3, datap3; //TypeP3 T ***
	TypeP4 data4, datap4; //TypeP4 T ****
	TypeP5 data5, datap5; //TypeP5 T *****
private:
	void ZeroAllPointer();
	void AllocateRange(int dimension);
	void AllocateRange1();
	void AllocateRange2();
	void AllocateRange3();
	void AllocateRange4();
	void AllocateRange5();
public:
	~FYArray()
	{
		if (data1 != NULL){                  data1 = NULL;}
		if (data2 != NULL){ delete [] data2; data2 = NULL;}
		if (data3 != NULL){ delete [] data3; data3 = NULL;}
		if (data4 != NULL){ delete [] data4; data4 = NULL;}
		if (data5 != NULL){ delete [] data5; data5 = NULL;}
	}
	TypeP1 GetSmartArrayP1() const
	{
		return datap1;
	}
	TypeP2 GetSmartArrayP2() const
	{
		return datap2;
	}
	TypeP3 GetSmartArrayP3() const
	{
		return datap3;
	}
	TypeP4 GetSmartArrayP4() const
	{
		return datap4;
	}
	TypeP5 GetSmartArrayP5() const
	{
		return datap5;
	}
#endif
	//! End
};

}

const int firstRank    = 0;
const int secondRank   = 1;
const int thirdRank    = 2;
const int fourthRank   = 3;
const int fifthRank    = 4;
const int sixthRank    = 5;
const int seventhRank  = 6;
const int eighthRank   = 7;
const int ninthRank    = 8;
const int tenthRank    = 9;
const int eleventhRank = 10;

const int firstDim    = 0;
const int secondDim   = 1;
const int thirdDim    = 2;
const int fourthDim   = 3;
const int fifthDim    = 4;
const int sixthDim    = 5;
const int seventhDim  = 6;
const int eighthDim   = 7;
const int ninthDim    = 8;
const int tenthDim    = 9;
const int eleventhDim = 10;

#include "FYFastArrayIterator.h"   // Fast Array iterators (for et)
#include "FYExpr.h"                // Array expression objects
#include "FYExprWrap.h"
#include "FYET.h"                  // Expression templates
#include "FYOps.hxx"               // Assignment operators
#include "FYArray.hxx"
#include "FYSlice.hxx"             // Slicing and sub-arrays
