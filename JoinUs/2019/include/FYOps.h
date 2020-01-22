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
//! @file      FYOps.h
//! @brief     Explain this file briefly.
//! @author    He Xin.

namespace FYSPACE
{

template<typename T>
struct autopromote_trait
{
	typedef T T_numtype;
};

template<typename T1, typename T2, bool promote2T1>
struct promote2
{
    typedef T1 T_promote;
};

template<typename T1, typename T2>
struct promote2<T1,T2,false>
{
    typedef T2 T_promote;
};

/*
 * This compiler supports partial specialization, so type promotion
 * can be done the elegant way.  This implementation is after ideas
 * by Jean-Louis Leroy.
 */

template<typename T>
struct precision_trait 
{
    static const int  precisionRank = 0;
    static const bool knowPrecisionRank = false;
};

template<typename T1_orig, typename T2_orig>
struct promote_trait 
{
    // Handle promotion of small integers to int/unsigned int
    typedef typename autopromote_trait<T1_orig>::T_numtype T1;
    typedef typename autopromote_trait<T2_orig>::T_numtype T2;

    // True if T1 is higher ranked
    static const bool T1IsBetter = precision_trait<T1>::precisionRank > precision_trait<T2>::precisionRank;

    // True if we know ranks for both T1 and T2
    static const bool knowBothRanks = precision_trait<T1>::knowPrecisionRank && precision_trait<T2>::knowPrecisionRank;

    // True if we know T1 but not T2
    static const bool knowT1butNotT2 = precision_trait<T1>::knowPrecisionRank && !precision_trait<T2>::knowPrecisionRank;

    // True if we know T2 but not T1
    static const bool knowT2butNotT1 = precision_trait<T2>::knowPrecisionRank && !precision_trait<T1>::knowPrecisionRank;

    // True if T1 is bigger than T2
    static const bool T1IsLarger = sizeof(T1) >= sizeof(T2);

    // We know T1 but not T2: false
    // We know T2 but not T1: true
    // Otherwise, if T1 is bigger than T2: true
	// static const bool
	// defaultPromotion = knowT1butNotT2 ? false : (knowT2butNotT1 ? true : T1IsLarger);
	
    // If we have both ranks, then use them.
    // If we have only one rank, then use the unknown type.
    // If we have neither rank, then promote to the larger type.
    static const bool promoteToT1 = knowBothRanks ? T1IsBetter : (knowT1butNotT2 ? false : (knowT2butNotT1 ? true : T1IsLarger));

    typedef typename promote2<T1,T2,promoteToT1>::T_promote T_promote;
};


//#define FY_PROMOTE(A,B) A
#define FY_PROMOTE(A,B) typename promote_trait<A,B>::T_promote


#define FY_DEFINE_UNARY_OP(name,op)                            \
template<typename T_numtype1>                                  \
struct name                                                    \
{                                                              \
    typedef T_numtype1 T_numtype;                              \
                                                               \
    static inline T_numtype                                    \
    apply(T_numtype1 a)                                        \
    {                                                          \
		return op a;                                           \
	}                                                          \
							                                   \
};

#define FY_DEFINE_BINARY_OPERATION(name,op)                       \
template<typename T_numtype1, typename T_numtype2>                \
struct name                                                       \
{                                                                 \
    typedef FY_PROMOTE(T_numtype1, T_numtype2) T_numtype;         \
                                                                  \
    static inline T_numtype                                       \
    apply(T_numtype1 a, T_numtype2 b)                             \
    {                                                             \
		return a op b;                                            \
	}                                                             \
							                                      \
};

#define FY_DEFINE_BINARY_FUNCTION(name,functor)                   \
template<typename T_numtype1, typename T_numtype2>                \
struct name                                                       \
{                                                                 \
    typedef FY_PROMOTE(T_numtype1, T_numtype2) T_numtype;         \
                                                                  \
    static inline T_numtype                                       \
    apply(T_numtype1 a, T_numtype2 b)                             \
    {                                                             \
		return functor(a, b);                                     \
	}                                                             \
							                                      \
};

FY_DEFINE_UNARY_OP(UnaryPlus ,+)
FY_DEFINE_UNARY_OP(UnaryMinus,-)

FY_DEFINE_BINARY_OPERATION(Add     , +)
FY_DEFINE_BINARY_OPERATION(Subtract, -)
FY_DEFINE_BINARY_OPERATION(Multiply, *)
FY_DEFINE_BINARY_OPERATION(Divide  , /)

}

