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

namespace FYSPACE
{
//! Operator() functions:
template<typename T, int N>
const T&  FYArray<T, N>::operator()(int i0) const
{ 
	//assertInRange(i0);
#ifdef USE_SMARTARRAY
	return datap1[i0];
#else
	return data_[i0 * stride_[0]];
#endif
}

template<typename T, int N>
T&  FYArray<T, N>::operator()(int i0) 
{
	//assertInRange(i0);
#ifdef USE_SMARTARRAY
	return datap1[i0];
#else
	return data_[i0 * stride_[0]];
#endif
}

template<typename T, int N>
const T&  FYArray<T, N>::operator()(int i0, int i1) const
{ 
	//assertInRange(i0, i1);
#ifdef USE_SMARTARRAY
	return datap2[i1][i0];
#else
	return data_[i0 * stride_[0] + i1 * stride_[1]];
#endif
}

template<typename T, int N>
T&  FYArray<T, N>::operator()(int i0, int i1)
{
	//assertInRange(i0, i1);
#ifdef USE_SMARTARRAY
	return datap2[i1][i0];
#else
	return data_[i0 * stride_[0] + i1 * stride_[1]];
#endif
}

template<typename T, int N>
const T&  FYArray<T, N>::operator()(int i0, int i1, int i2) const
{
	//assertInRange(i0, i1, i2);
#ifdef USE_SMARTARRAY
	return datap3[i2][i1][i0];
#else
	return data_[i0 * stride_[0] + i1 * stride_[1]
	+ i2 * stride_[2]];
#endif
}

template<typename T, int N>
T&  FYArray<T, N>::operator()(int i0, int i1, int i2) 
{
	//assertInRange(i0, i1, i2);
#ifdef USE_SMARTARRAY
	return datap3[i2][i1][i0];
#else
	return data_[i0 * stride_[0] + i1 * stride_[1]
	+ i2 * stride_[2]];
#endif
}

template<typename T, int N>
const T&  FYArray<T, N>::operator()(int i0, int i1, int i2, int i3) const
{
	//assertInRange(i0, i1, i2);
#ifdef USE_SMARTARRAY
	return datap4[i3][i2][i1][i0];
#else
	return data_[i0 * stride_[0] + i1 * stride_[1]
	+ i2 * stride_[2] + i3 * stride_[3]];
#endif
}

template<typename T, int N>
T&  FYArray<T, N>::operator()(int i0, int i1, int i2, int i3) 
{
	//assertInRange(i0, i1, i2);
#ifdef USE_SMARTARRAY
	return datap4[i3][i2][i1][i0];
#else
	return data_[i0 * stride_[0] + i1 * stride_[1]
	+ i2 * stride_[2] + i3 * stride_[3]];
#endif
}

template<typename T, int N>
const T&  FYArray<T, N>::operator()(int i0, int i1, int i2, int i3, int i4) const
{
#ifdef USE_SMARTARRAY
	return datap5[i4][i3][i2][i1][i0];
#else
	return data_[i0 * stride_[0] + i1 * stride_[1]
	+ i2 * stride_[2] + i3 * stride_[3] + i4 * stride_[4]];
#endif
}

template<typename T, int N>
T&  FYArray<T, N>::operator()(int i0, int i1, int i2, int i3, int i4) 
{
#ifdef USE_SMARTARRAY
	return datap5[i4][i3][i2][i1][i0];
#else
	return data_[i0 * stride_[0] + i1 * stride_[1]
	+ i2 * stride_[2] + i3 * stride_[3] + i4 * stride_[4]];
#endif
}

template<typename T, int N>
const T& FYArray<T, N>::operator[](int i) const
{
	return data_[i];
}

template<typename T, int N>
T& FYArray<T, N>::operator[](int i)
{
	return data_[i];
}

template<typename T, int N>
template<int N_rank2>
const T& FYArray<T, N>::operator()(const SimpleArray<int,N_rank2>& index) const
{
	return data_[dot(index, stride_)];
}

template<typename T, int N>
template<int N_rank2>
T& FYArray<T, N>::operator()(const SimpleArray<int,N_rank2>& index) 
{
	return data_[dot(index, stride_)];
}

template<typename T, int N>
FYArray<T, N> FYArray<T, N>::operator()(Range r0) const
{
	return FYArray<T, N>(noConst(), r0);
}

template<typename T, int N>
FYArray<T, N> FYArray<T, N>::operator()(Range r0, Range r1) const
{
	return FYArray<T, N>(noConst(), r0, r1);
}

template<typename T, int N>
FYArray<T, N> FYArray<T, N>::operator()(Range r0, Range r1, Range r2) const
{
	return T_array(noConst(), r0, r1, r2);
}

template<typename T, int N>
FYArray<T, N> FYArray<T, N>::operator()(Range r0, Range r1, Range r2, Range r3) const
{
	return FYArray<T, N>(noConst(), r0, r1, r2, r3);
}

template<typename T, int N>
FYArray<T, N> FYArray<T, N>::operator()(Range r0, Range r1, Range r2, Range r3, Range r4) const
{
	return FYArray<T, N>(noConst(), r0, r1, r2, r3, r4);
}

template<typename T, int N>
FYArray<T, N> FYArray<T, N>::operator()(Range r0, Range r1, Range r2, Range r3, Range r4, Range r5) const        
{
	return FYArray<T, N>(noConst(), r0, r1, r2, r3, r4, r5);
}

template<typename T, int N>
FYArray<T, N> FYArray<T, N>::operator()(Range r0, Range r1, Range r2, Range r3, Range r4, Range r5, Range r6) const
{
	return FYArray<T, N>(noConst(), r0, r1, r2, r3, r4, r5, r6);
}

template<typename T, int N>
template < typename T1, typename T2 >
typename FYSliceInfo<T,T1,T2>::T_slice
	FYArray<T, N>::operator()(T1 r1, T2 r2) const
{
	typedef typename FYSliceInfo<T,T1,T2>::T_slice slice;
	return slice(noConst(), r1, r2, FYnilArraySection(), FYnilArraySection(), FYnilArraySection(),
		FYnilArraySection(), FYnilArraySection(), FYnilArraySection(),
		FYnilArraySection(), FYnilArraySection(), FYnilArraySection());
}

template<typename T, int N>
template < typename T1, typename T2, typename T3 >
typename FYSliceInfo<T,T1,T2,T3>::T_slice 
	FYArray<T, N>::operator()(T1 r1, T2 r2, T3 r3) const
{
	typedef typename FYSliceInfo<T,T1,T2,T3>::T_slice slice;
	return slice(noConst(), r1, r2, r3, FYnilArraySection(), FYnilArraySection(), FYnilArraySection(),
		FYnilArraySection(), FYnilArraySection(), FYnilArraySection(),
		FYnilArraySection(), FYnilArraySection());
}

template<typename T, int N>
template < typename T1, typename T2, typename T3, typename T4 >
typename FYSliceInfo<T,T1,T2,T3,T4>::T_slice
	FYArray<T, N>::operator()(T1 r1, T2 r2, T3 r3, T4 r4) const
{
	typedef typename FYSliceInfo<T,T1,T2,T3,T4>::T_slice slice;
	return slice(noConst(), r1, r2, r3, r4, FYnilArraySection(), FYnilArraySection(),
		FYnilArraySection(), FYnilArraySection(), FYnilArraySection(),
		FYnilArraySection(), FYnilArraySection());
}

template<typename T, int N>
template < typename T1, typename T2, typename T3, typename T4, typename T5 >
typename FYSliceInfo<T,T1,T2,T3,T4,T5>::T_slice
	FYArray<T, N>::operator()(T1 r1, T2 r2, T3 r3, T4 r4, T5 r5) const
{
	typedef typename FYSliceInfo<T,T1,T2,T3,T4,T5>::T_slice slice;
	return slice(noConst(), r1, r2, r3, r4, r5, FYnilArraySection(),
		FYnilArraySection(), FYnilArraySection(), FYnilArraySection(),
		FYnilArraySection(), FYnilArraySection());
}

template<typename T, int N>
template < typename T1, typename T2, typename T3, typename T4, typename T5, typename T6 >
typename FYSliceInfo<T,T1,T2,T3,T4,T5,T6>::T_slice
	FYArray<T, N>::operator()(T1 r1, T2 r2, T3 r3, T4 r4, T5 r5, T6 r6) const
{
	typedef typename FYSliceInfo<T,T1,T2,T3,T4,T5,T6>::T_slice slice;
	return slice(noConst(), r1, r2, r3, r4, r5, r6, FYnilArraySection(), FYnilArraySection(), FYnilArraySection(),
		FYnilArraySection(), FYnilArraySection());
}
#define FY_ARRAY_UPDATE(op,name)                                     \
template < typename P_numtype, int N_rank >                          \
template < typename T >                                              \
inline FYArray<P_numtype,N_rank>&                                    \
FYArray<P_numtype,N_rank>::operator op(const T& expr)                \
{                                                                    \
    evaluate(typename FYExprWrap<T>::T_expr(expr),                   \
      name<T_numtype, typename FYExprWrap<T>::T_expr::T_numtype>()); \
    return *this;                                                    \
}

FY_ARRAY_UPDATE(+=, fy_plus_update    )
FY_ARRAY_UPDATE(-=, fy_minus_update   )
FY_ARRAY_UPDATE(*=, fy_multiply_update)
FY_ARRAY_UPDATE(/=, fy_divide_update  )

template < typename T_numtype, int N_rank > template < typename T_expr, typename T_update >
FYArray<T_numtype, N_rank>&
FYArray<T_numtype, N_rank>::evaluateWithIndexTraversal1(T_expr expr, T_update)
{
    SimpleArray<int,N_rank> index;

    if ( stride(firstRank) == 1 )
    {
		int first = lbound(firstRank);
        int last  = ubound(firstRank);

        T_numtype * iter = data_ + first;

        for ( index[0] = first; index[0] <= last; ++ index[0] )
        {
            T_update::update(*iter++, expr(index));
			int kk=1;
			int i = *iter;
			//T_update::update(*iter++,3);
			//FYUpdate<int,int>::update(kk,2);
			int kkk = 1;
        }
    }
    else
	{
        FYFastArrayIterator<T_numtype, N_rank> iter(*this);
        iter.loadStride(0);
		int first = lbound(firstRank);
        int last  = ubound(firstRank);

        for ( index[0] = first; index[0] <= last; ++ index[0] )
        {
            T_update::update(*const_cast<T_numtype*>(iter.data()), expr(index));
            iter.advance();
        }
    }

    return *this;
}

template < typename T_numtype, int N_rank > template < typename T_expr, typename T_update >
FYArray<T_numtype, N_rank>&
FYArray<T_numtype, N_rank>::evaluateWithIndexTraversalN(T_expr expr, T_update)
    
{
    // Do a stack-type traversal for the destination array and use
    // index traversal for the source expression
   
    const int maxRank = ordering(0);

    FYFastArrayIterator<T_numtype, N_rank> iter(*this);
    for ( int i = 1; i < N_rank; ++ i )
	{
        iter.push(ordering(i));
	}

    iter.loadStride(maxRank);

    SimpleArray<int,N_rank> index, last;

    index = storage_.base();

    for ( int i = 0; i < N_rank; ++ i )
	{
		last[i] = storage_.base(i) + length_[i];
	}

    // int lastLength = length(maxRank);

    while ( true )
	{
		int a = base(maxRank);
		int b = last[maxRank];
        for ( index[maxRank] = base(maxRank); index[maxRank] < last[maxRank]; ++ index[maxRank] )
        {
            T_update::update(*const_cast<T_numtype*>(iter.data()), expr(index));
            iter.advance();
        }

        int j = 1;
        for ( ; j < N_rank; ++ j )
        {
            iter.pop(ordering(j));
            iter.loadStride(ordering(j));
            iter.advance();

            index[ordering(j-1)] = base(ordering(j-1));
            ++index[ordering(j)];
            if (index[ordering(j)] != last[ordering(j)])
			{
                break;
			}
        }

        if ( j == N_rank )
		{
            break;
		}

        for ( ; j > 0; -- j )
        {
            iter.push(ordering(j));
        }

        iter.loadStride(maxRank);
    }

    return *this; 
}

template < typename T_numtype, int N_rank > template < typename T_expr, typename T_update >
FYArray<T_numtype, N_rank>&
FYArray<T_numtype, N_rank>::evaluateWithStackTraversal1(T_expr expr, T_update)
{
    FYFastArrayIterator<T_numtype, N_rank> iter(*this);
    iter.loadStride(firstRank);
    expr.loadStride(firstRank);

    bool useUnitStride = iter.isUnitStride(firstRank) && expr.isUnitStride(firstRank);

    int  commonStride = 1;
    bool useCommonStride = false;

    const T_numtype * last = iter.data() + length(firstRank) * stride(firstRank);

    while ( iter.data() != last )
    {
        T_update::update(*const_cast<T_numtype*>(iter.data()), *expr);
        iter.advance();
        expr.advance();
    }

    return *this;
}

template < typename T_numtype, int N_rank > template < typename T_expr, typename T_update >
FYArray <T_numtype, N_rank>&
FYArray<T_numtype, N_rank>::evaluateWithStackTraversalN(T_expr expr, T_update)
{
    /*
     * A stack traversal replaces the usual nested loops:
     *
     * for (int i=A.lbound(firstDim); i <= A.ubound(firstDim); ++i)
     *   for (int j=A.lbound(secondDim); j <= A.ubound(secondDim); ++j)
     *     for (int k=A.lbound(thirdDim); k <= A.ubound(thirdDim); ++k)
     *       A(i,j,k) = 0;
     *
     * with a stack data structure.  The stack allows this single
     * routine to replace any number of nested loops.
     *
     * For each dimension (loop), these quantities are needed:
     * - a pointer to the first element encountered in the loop
     * - the stride associated with the dimension/loop
     * - a pointer to the last element encountered in the loop
     *
     * The basic idea is that entering each loop is a "push" onto the
     * stack, and exiting each loop is a "pop".  In practice, this
     * routine treats accesses the stack in a random-access way,
     * which confuses the picture a bit.  But conceptually, that's
     * what is going on.
     */

    /*
     * ordering(0) gives the dimension associated with the smallest
     * stride (usually; the exceptions have to do with subarrays and
     * are uninteresting).  We call this dimension maxRank; it will
     * become the innermost "loop".
     *
     * Ordering the loops from ordering(N_rank-1) down to
     * ordering(0) ensures that the largest stride is associated
     * with the outermost loop, and the smallest stride with the
     * innermost.  This is critical for good performance on
     * cached machines.
     */

    const int maxRank = ordering(0);
    // const int secondLastRank = ordering(1);

    // Create an iterator for the array receiving the result
    FYFastArrayIterator<T_numtype, N_rank> iter(*this);

    // Set the initial stack configuration by pushing the pointer
    // to the first element of the array onto the stack N times.

    int i;
    for ( i = 1; i < N_rank; ++ i )
    {
        iter.push(i);
        expr.push(i);
    }

    // Load the strides associated with the innermost loop.
    iter.loadStride(maxRank);
    expr.loadStride(maxRank);

    /* 
     * Is the stride in the innermost loop equal to 1?  If so,
     * we might take advantage of this and generate more
     * efficient code.
     */
    bool useUnitStride = iter.isUnitStride(maxRank) && expr.isUnitStride(maxRank);

    /*
     * Do all array operands share a common stride in the innermost
     * loop?  If so, we can generate more efficient code (but only
     * if this optimization has been enabled).
     */
#ifdef BZ_ARRAY_EXPR_USE_COMMON_STRIDE
    int commonStride = expr.suggestStride(maxRank);
    if ( iter.suggestStride(maxRank) > commonStride )
	{
        commonStride = iter.suggestStride(maxRank);
	}
    bool useCommonStride = iter.isStride(maxRank,commonStride) && expr.isStride(maxRank,commonStride);
#else
    int commonStride = 1;
    bool useCommonStride = false;
#endif

    /*
     * The "last" array contains a pointer to the last element
     * encountered in each "loop".
     */
    const T_numtype* last[N_rank];

    // Set up the initial state of the "last" array
    for ( i = 1; i < N_rank; ++ i )
	{
        last[i] = iter.data() + length(ordering(i)) * stride(ordering(i));
	}

    int lastLength = length(maxRank);
    int firstNoncollapsedLoop = 1;

    /*
     * This bit of code handles collapsing loops.  When possible,
     * the N nested loops are converted into a single loop (basically,
     * the N-dimensional array is treated as a long vector).
     * This is important for cases where the length of the innermost
     * loop is very small, for example a 100x100x3 array.
     * If this code can't collapse all the loops into a single loop,
     * it will collapse as many loops as possible starting from the
     * innermost and working out.
     */

    // Collapse loops when possible
    for ( i = 1; i < N_rank; ++ i )
    {
        // Figure out which pair of loops we are considering combining.
        int outerLoopRank = ordering(i);
        int innerLoopRank = ordering(i-1);

        /*
         * The canCollapse() routines look at the strides and extents
         * of the loops, and determine if they can be combined into
         * one loop.
         */

        if ( canCollapse(outerLoopRank,innerLoopRank) && expr.canCollapse(outerLoopRank,innerLoopRank))
        {
            lastLength *= length(outerLoopRank);
            firstNoncollapsedLoop = i+1;
        }
        else
		{
            break;
		}
    }

    /*
     * Now we actually perform the loops.  This while loop contains
     * two parts: first, the innermost loop is performed.  Then we
     * exit the loop, and pop our way down the stack until we find
     * a loop that isn't completed.  We then restart the inner loops
     * and push them onto the stack.
     */

    while ( true )
	{

        /*
         * This bit of code handles the innermost loop.  It would look
         * a lot simpler if it weren't for unit stride and common stride
         * optimizations; these clutter up the code with multiple versions.
         */

        if ( (useUnitStride) || (useCommonStride) )
        {
            /*
             * The check for BZ_USE_FAST_READ_ARRAY_EXPR can probably
             * be taken out.  This was put in place while the unit stride/
             * common stride optimizations were being implemented and
             * tested.
             */

            // Compute the end of the innermost loop
            int ubound = lastLength * commonStride;

            /*
             * This is a real kludge.  I didn't want to have to write
             * a const and non-const version of FastArrayIterator, so I use a
             * const iterator and cast away const.  This could
             * probably be avoided with some trick, but the whole routine
             * is ugly, so why bother.
             */

            T_numtype* data = const_cast<T_numtype*>(iter.data());

            /*
             * BZ_NEEDS_WORK-- need to implement optional unrolling.
             */
            if ( commonStride == 1 )
            {
                for ( int i = 0; i < ubound; ++ i )
				{
                    T_update::update(*data++, expr.fastRead(i));
				}
            }
            else 
			{
                for ( int i = 0; i != ubound; i += commonStride )
				{
                    T_update::update(data[i], expr.fastRead(i));
				}
            }
            /*
             * Tidy up for the fact that we haven't actually been
             * incrementing the iterators in the innermost loop, by
             * faking it afterward.
             */
            iter.advance(lastLength * commonStride);
            expr.advance(lastLength * commonStride);

        }
        else
		{
            /*
             * We don't have a unit stride or common stride in the innermost
             * loop.  This is going to hurt performance.  Luckily 95% of
             * the time, we hit the cases above.
             */
            T_numtype * end = const_cast<T_numtype*>(iter.data()) + lastLength * stride(maxRank);
                

            while ( iter.data() != end )
            {
                T_update::update(*const_cast<T_numtype*>(iter.data()), *expr);
                iter.advance();
                expr.advance();
            }
        }


        /*
         * We just finished the innermost loop.  Now we pop our way down
         * the stack, until we hit a loop that hasn't completed yet.
         */ 
        int j = firstNoncollapsedLoop;
        for ( ; j < N_rank; ++ j )
        {
            // Get the next loop
            int r = ordering(j);

            // Pop-- this restores the data pointers to the first element
            // encountered in the loop.
            iter.pop(j);
            expr.pop(j);

            // Load the stride associated with this loop, and increment
            // once.
            iter.loadStride(r);
            expr.loadStride(r);
            iter.advance();
            expr.advance();

            // If we aren't at the end of this loop, then stop popping.
            if ( iter.data() != last[j] )
			{
                break;
			}
        }

        // Are we completely done?
        if ( j == N_rank )
		{
            break;
		}

        // No, so push all the inner loops back onto the stack.
        for ( ; j >= firstNoncollapsedLoop; --j )
        {
            int r2 = ordering(j-1);
            iter.push(j);
            expr.push(j);
            last[j-1] = iter.data() + length(r2) * stride(r2);
        }

        // Load the stride for the innermost loop again.
        iter.loadStride(maxRank);
        expr.loadStride(maxRank);
    }

    return *this;
}


template < typename T_numtype, int N_rank > template < typename T_expr, typename T_update >
FYArray<T_numtype, N_rank>& 
FYArray<T_numtype, N_rank>::evaluate(T_expr expr, T_update)
{
    // Check that all arrays have the same shape
    /*
     * Check that the arrays are not empty (e.g. length 0 arrays)
     * This fixes a bug found by Peter Bienstman, 6/16/99, where
     * Array<double,2> A(0,0),B(0,0); B=A(tensor::j,tensor::i);
     * went into an infinite loop.
     */

    if ( numElements() == 0 )
	{
        return *this;
	}

    if ( N_rank == 1 )
	{
        return evaluateWithStackTraversal1(expr, T_update());
	}
    else
	{
		return evaluateWithStackTraversalN(expr, T_update());
	}
}

template < typename T, int N >
FYArray<T, N>& FYArray<T, N>::operator=(T x)
{
	return initialize(x);
}

template < typename T, int N > template < typename T_expr >
FYArray<T, N>& 
FYArray<T, N>::operator = (const FYETBase<T_expr> &expr)
{
	evaluate(expr.unwrap(), FYUpdate<T_numtype, typename T_expr::T_numtype>());

    return *this;
}

template < typename T, int N >
FYArray<T, N>&
FYArray<T, N>::operator = (const FYArray<T, N>& x)
{
    (*this) = FYArrayExpr< FYFastArrayIterator<T, N> >( x.beginFast() );
    return *this;
}

template < typename T, int N >
FYArray<T, N>& 
FYArray<T,N>::initialize(T x)
{
	(*this) = FYArrayExpr< FYArrayExprConstant<T > >(x);
	return *this;
}

}

