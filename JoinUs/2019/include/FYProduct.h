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
//! @file      FYProduct.h
//! @brief     Explain this file briefly.
//! @author    He Xin.

#pragma once
namespace FYSPACE
{
template < typename T, int N >
T product(SimpleArray<T, N> &length)
{
    T result = static_cast<T>(1);
    for ( int i = 0; i < N; ++ i )
    {
        result *= length[i];
    }
    return result;
}

template < typename T, int N >
T product(const SimpleArray<T, N> &length)
{
    T result = static_cast<T>(1);
    for ( int i = 0; i < N; ++ i )
    {
        result *= length[i];
    }
    return result;
}

}
