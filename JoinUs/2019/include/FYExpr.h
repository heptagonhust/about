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
//! @file      FYExpr.h
//! @brief     Explain this file briefly.
//! @author    He Xin.

#pragma once

#include "FYOps.h"

namespace FYSPACE
{

template<typename P_numtype>
class FYArrayExprConstant
{
public:
    typedef P_numtype T_numtype;
    typedef T_numtype T_ctorArg1;
    typedef int       T_ctorArg2;    // dummy

    static const int 
        numArrayOperands = 0, 
        numIndexPlaceholders = 0, 
        rank = 0;

    FYArrayExprConstant(const FYArrayExprConstant<T_numtype>& a)
        : value_(a.value_)
    { }

    FYArrayExprConstant(T_numtype value)
        : value_( value )
    { 
    }
public:
    template<int N_rank>
    T_numtype operator()(const SimpleArray<int,N_rank>&)
    { 
		return value_; 
	}

    T_numtype operator * ()
    { 
		return value_; 
	}

    void loadStride(int rank) {}

    bool isUnitStride(int) const
    { 
		return true;
	}

    bool canCollapse(int outerLoopRank, int innerLoopRank) const 
    {
		return true; 
	}

    T_numtype fastRead(int i)
    {
		return value_; 
	}

    void push(int position) {}
    void pop(int position) {}
    void advance() {};
	void advance(int n) {};
protected:
    FYArrayExprConstant() { }

    T_numtype value_;
};

template<typename P_expr, typename P_op>
class FYArrayExprUnaryOp
{
public:
    typedef P_expr T_expr;
    typedef P_op T_op;
    typedef typename T_expr::T_numtype T_numtype1;
    typedef typename T_op::T_numtype T_numtype;
    typedef T_expr T_ctorArg1;
    typedef int    T_ctorArg2;    // dummy

    FYArrayExprUnaryOp(const FYArrayExprUnaryOp<T_expr, T_op>& a)
        : iter_(a.iter_)
    { }

    FYArrayExprUnaryOp(const T_expr& a)
        : iter_(a)
    { }

    int lbound(int rank)
    { 
		return iter_.lbound(rank);
	}

    int ubound(int rank)
    { 
		return iter_.ubound(rank);
	}

    T_numtype operator*()
    {
		return T_op::apply(*iter_); 
	}

    template<int N_rank>
    T_numtype operator()(const SimpleArray<int,N_rank>& i)
    { 
		return T_op::apply(iter1_(i));
	}

    void push(int position)
    {
        iter_.push(position);
    }

    void pop(int position)
    {
        iter_.pop(position);
    }

    void advance()
    {
        iter_.advance();
    }

    void advance(int n)
    {
        iter_.advance(n);
    }

    void loadStride(int rank)
    {
        iter_.loadStride(rank);
    }

    bool isUnitStride(int rank) const
    { 
		return iter_.isUnitStride(rank);
	}

    void advanceUnitStride()
    {
        iter_.advanceUnitStride();
    }

    bool canCollapse(int outerLoopRank, int innerLoopRank) const
    { 
        return iter_.canCollapse(outerLoopRank, innerLoopRank); 
    }

    T_numtype operator[](int i)
    {
		return T_op::apply(iter_[i]); 
	}

    T_numtype fastRead(int i)
    { 
		return T_op::apply(iter_.fastRead(i)); 
	}

    int suggestStride(int rank) const
    {
		return iter_.suggestStride(rank); 
	}

    bool isStride(int rank, int stride) const
    { 
		return iter_.isStride(rank,stride); 
	}

protected:
    FYArrayExprUnaryOp() { }

    T_expr iter_;
};

template<typename P_expr1, typename P_expr2, typename P_op>
class FYArrayExprBinaryOp
{
public:
    typedef P_expr1 T_expr1;
    typedef P_expr2 T_expr2;
	typedef P_op T_op;

	typedef typename T_op::T_numtype T_numtype;

    FYArrayExprBinaryOp(const FYArrayExprBinaryOp<T_expr1, T_expr2, T_op>& a)
        : iter1_(a.iter1_), iter2_(a.iter2_)
    { }

    template<typename T1, typename T2>
    FYArrayExprBinaryOp(T1 &a, T2 &b)
        : iter1_(a), iter2_(b)
    { }
public:
    template<int N_rank>
    T_numtype operator()(const SimpleArray<int,N_rank>& i)
    { 
		return T_op::apply(iter1_(i), iter2_(i));
	}

    T_numtype operator * ()
    { 
		return T_op::apply(*iter1_, *iter2_);
	}

    void loadStride(int rank)
    { 
        iter1_.loadStride(rank); 
        iter2_.loadStride(rank);
    }

    bool isUnitStride(int rank) const
    { 
		return iter1_.isUnitStride(rank) && iter2_.isUnitStride(rank); 
	}

    void push(int position)
    { 
        iter1_.push(position); 
        iter2_.push(position);
    }

    void pop(int position)
    { 
        iter1_.pop(position); 
        iter2_.pop(position);
    }

    void advance()
    { 
        iter1_.advance(); 
        iter2_.advance();
    }

    void advance(int n)
    {
        iter1_.advance(n);
        iter2_.advance(n);
    }

    bool canCollapse(int outerLoopRank, int innerLoopRank) const
    { 
        return iter1_.canCollapse(outerLoopRank, innerLoopRank)
            && iter2_.canCollapse(outerLoopRank, innerLoopRank);
    }

    T_numtype fastRead(int i)
    { 
		return T_op::apply(iter1_.fastRead(i), iter2_.fastRead(i));
	}

protected:
    FYArrayExprBinaryOp() { }

    T_expr1 iter1_;
    T_expr2 iter2_;
};

template<typename P_expr>
class FYArrayExpr : public FYETBase< FYArrayExpr<P_expr > >
{
public:
    typedef P_expr T_expr;
    typedef typename T_expr::T_numtype T_numtype;
    typedef T_expr T_ctorArg1;
    typedef int    T_ctorArg2;    // dummy
public:
    FYArrayExpr(const FYArrayExpr<T_expr>& a)
        : FYETBase< FYArrayExpr<T_expr> >(a), iter_(a.iter_)
    { }

    template<typename T1, typename T2>
    FYArrayExpr(const T1 &a, const T2 &b)
        : iter_(a, b)
    { }

    template<typename T>
    FYArrayExpr(const T& a)
        : iter_(a)
    { }
public:

    T_numtype operator * ()
    {
		return *iter_; 
	}

    template<int N_rank>
    T_numtype operator()(const SimpleArray<int, N_rank>& i)
    {
		return iter_(i);
	}

    void loadStride(int rank)
    { 
		iter_.loadStride(rank);
	}

    bool isUnitStride(int rank) const
    { 
		return iter_.isUnitStride(rank);
	}

    bool canCollapse(int outerLoopRank, int innerLoopRank) const
    { 
        return iter_.canCollapse(outerLoopRank, innerLoopRank); 
    }

    T_numtype fastRead(int i)
    { 
		return iter_.fastRead(i);
	}

    void advance()
    {
		iter_.advance();
	}

    void advance(int n)
    { 
		iter_.advance(n);
	}

    void push(int position)
    { 
		iter_.push(position);
	}

    void pop(int position)
    {
		iter_.pop(position); 
	}

protected:
    FYArrayExpr() { }
    T_expr iter_;
};

}

