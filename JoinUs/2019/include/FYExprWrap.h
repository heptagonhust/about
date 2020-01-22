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
//! @file      FYExprWrap.h
//! @brief     Explain this file briefly.
//! @author    He Xin.

#pragma once

namespace FYSPACE
{

template <typename T>
struct FYExprWrap
{
    typedef FYArrayExprConstant<T> T_expr;
    static T_expr getExpr(const T& x) { return T_expr(x); }
};

//  Already an expression template term
template <typename T>
struct FYExprWrap< FYArrayExpr<T> >
{
    typedef FYArrayExpr<T> T_expr;
    static const T_expr& getExpr(const T_expr& x) { return x; }
};

//  An array operand
template <typename T,int N>
struct FYExprWrap< FYArray<T,N> >
{
    typedef FYFastArrayIterator<T,N> T_expr;
	static T_expr getExpr(const FYArray<T,N>& x) { return x.beginFast(); }
};

template < template < typename T1> class OP, typename O1>
struct FYUnaryExprResult
{
    typedef FYArrayExpr
	<
		FYArrayExprUnaryOp
		<
			typename FYExprWrap<O1>::T_expr,
			OP<typename FYExprWrap<O1>::T_expr::T_numtype> 
		> 
	> T_result;
};

//  A traits class that provides the return type of a binary operation.
template <template <typename T1, typename T2> class OP, typename O1, typename O2>
struct FYBinaryExprResult
{
    typedef FYArrayExpr
	<  
		FYArrayExprBinaryOp
		<
			typename FYExprWrap<O1>::T_expr,
			typename FYExprWrap<O2>::T_expr,
			OP<typename FYExprWrap<O1>::T_expr::T_numtype,typename FYExprWrap<O2>::T_expr::T_numtype>
	    >
	> T_result;
};

}

