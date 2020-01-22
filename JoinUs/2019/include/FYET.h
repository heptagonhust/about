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
//! @file      FYET.h
//! @brief     Explain this file briefly.
//! @author    He Xin.

#pragma once

namespace FYSPACE
{
class FYUpdaterBase { };

template<typename X, typename Y>
class FYUpdate : public FYUpdaterBase
{
public:
    static inline void update(X& x, Y y)
    {
		x = (X)y; 
	}
};

#define FY_DEFINE_UPDATER(name,op)                          \
template<typename X, typename Y>                            \
class name : public FYUpdaterBase                           \
{                                                           \
public:                                                     \
    static inline void update(X& x, Y y)                    \
    {                                                       \
		x op y;                                             \
	}                                                       \
}

FY_DEFINE_UPDATER(fy_plus_update    , +=);
FY_DEFINE_UPDATER(fy_minus_update   , -=);
FY_DEFINE_UPDATER(fy_multiply_update, *=);
FY_DEFINE_UPDATER(fy_divide_update  , /=);

#define FY_DECLARE_ARRAY_UNARY(name,functor)                              \
                                                                          \
template <typename T1>                                                    \
inline                                                                    \
typename FYUnaryExprResult<functor,T1>::T_result                          \
name(const FYETBase<T1>& d1)                                              \
{                                                                         \
    typedef typename FYUnaryExprResult<functor,T1>::T_result result;      \
    return result(FYExprWrap<T1>::getExpr(d1.unwrap()));                  \
}

#define FY_DECLARE_ARRAY_BINARY(name, applic)                             \
                                                                          \
template <typename T1,typename T2>                                        \
inline                                                                    \
typename FYBinaryExprResult<applic,T1,T2>::T_result                       \
name(const FYETBase<T1>& d1,const FYETBase<T2>& d2)                       \
{                                                                         \
    typedef typename FYBinaryExprResult<applic,T1,T2>::T_result result;   \
    return result(FYExprWrap<T1>::getExpr(d1.unwrap()),                   \
                  FYExprWrap<T2>::getExpr(d2.unwrap()));                  \
}

#define FY_DECLARE_ARRAY_BINARY_SCALAR(name, applic, scalar_type)                 \
template<typename T>                                                              \
inline                                                                            \
typename FYBinaryExprResult<applic,scalar_type,T>::T_result                       \
name(const scalar_type d1, const FYETBase<T>& d2)                                 \
{                                                                                 \
    typedef typename FYBinaryExprResult<applic,scalar_type,T>::T_result result;   \
    return result(FYExprWrap<scalar_type >::getExpr(d1),                          \
                  FYExprWrap<T>::getExpr(d2.unwrap()));                           \
}                                                                                 \
                                                                                  \
template<typename T>                                                              \
inline                                                                            \
typename FYBinaryExprResult<applic,T,scalar_type >::T_result                      \
name(const FYETBase<T>& d1, const scalar_type d2)                                 \
{                                                                                 \
    typedef typename FYBinaryExprResult<applic,T,scalar_type >::T_result result;  \
    return result(FYExprWrap<T>::getExpr(d1.unwrap()),                            \
                  FYExprWrap<scalar_type >::getExpr(d2));                         \
}

#define FY_DECLARE_ARRAY_SCALAR_OPERATIONS(scalar_type)                           \
	                                                                              \
FY_DECLARE_ARRAY_BINARY_SCALAR(operator +,  Add     , scalar_type)                \
FY_DECLARE_ARRAY_BINARY_SCALAR(operator -,  Subtract, scalar_type)                \
FY_DECLARE_ARRAY_BINARY_SCALAR(operator *,  Multiply, scalar_type)                \
FY_DECLARE_ARRAY_BINARY_SCALAR(operator /,  Divide  , scalar_type)                 

FY_DECLARE_ARRAY_SCALAR_OPERATIONS(char)
FY_DECLARE_ARRAY_SCALAR_OPERATIONS(unsigned char)
FY_DECLARE_ARRAY_SCALAR_OPERATIONS(short)
FY_DECLARE_ARRAY_SCALAR_OPERATIONS(unsigned short)
FY_DECLARE_ARRAY_SCALAR_OPERATIONS(int)
FY_DECLARE_ARRAY_SCALAR_OPERATIONS(unsigned int)
FY_DECLARE_ARRAY_SCALAR_OPERATIONS(long)
FY_DECLARE_ARRAY_SCALAR_OPERATIONS(unsigned long)
FY_DECLARE_ARRAY_SCALAR_OPERATIONS(float)
FY_DECLARE_ARRAY_SCALAR_OPERATIONS(double)
FY_DECLARE_ARRAY_SCALAR_OPERATIONS(long double)

FY_DECLARE_ARRAY_BINARY(operator+,  Add     )
FY_DECLARE_ARRAY_BINARY(operator-,  Subtract)
FY_DECLARE_ARRAY_BINARY(operator*,  Multiply)
FY_DECLARE_ARRAY_BINARY(operator/,  Divide  )
// unary operators
FY_DECLARE_ARRAY_UNARY(operator+, UnaryPlus)
FY_DECLARE_ARRAY_UNARY(operator-, UnaryMinus)

}

