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
//! @file      FYETBase.h
//! @brief     Explain this file briefly.
//! @author    He Xin.

#pragma once
#include <iostream>
using namespace std;

namespace FYSPACE
{

template<typename T>
class FYETBase
{ 
public:
	FYETBase() {}

	FYETBase(const FYETBase<T>&){}
    
    T& unwrap() { return static_cast<T&>(*this); }
    
    const T& unwrap() const { return static_cast<const T&>(*this); }
};
}

