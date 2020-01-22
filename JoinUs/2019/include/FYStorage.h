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
//! @file      FYStorage.h
//! @brief     Explain this file briefly.
//! @author    xxx.


#pragma once
#include "FYSimpleArray.h"

#ifdef WIN32
//! Shield compiling waring C4800 and C4805 (by zhangjian).
//! The warning is because result &= ascendingFlag_[i];
//! After verification, this code is come from blitz/aray/storage.h
#pragma warning(disable: 4800)
#pragma warning(disable: 4805)
#endif
namespace FYSPACE
{
template < int N >
class GeneralArrayStorage
{
public:
    class noInitializeFlag { };

    GeneralArrayStorage(noInitializeFlag)
    { }

    GeneralArrayStorage()
    {
        for ( int i = 0; i < N; ++ i )
        {
            ordering_[i] = N - 1 - i;
        }
        ascendingFlag_ = true;
        base_ = 0;
    }

    GeneralArrayStorage( const GeneralArrayStorage<N>& rhs )
                        : ordering_(rhs.ordering_), ascendingFlag_(rhs.ascendingFlag_),base_(rhs.base_)
    {
    }

    GeneralArrayStorage(SimpleArray<int,N> ordering,
                        SimpleArray<bool,N> ascendingFlag)
                        : ordering_(ordering), ascendingFlag_(ascendingFlag)
    {
        base_ = 0;
    }

    ~GeneralArrayStorage()
    { }

    GeneralArrayStorage<N>& operator = (const GeneralArrayStorage<N>& rhs)
    {
        ordering_      = rhs.ordering();
        ascendingFlag_ = rhs.ascendingFlag();
        base_          = rhs.base();
        return *this;
    }

    SimpleArray<int, N>& ordering()
    { return ordering_; }

    const SimpleArray<int, N>& ordering() const
    { return ordering_; }

    int ordering(int i) const
    { return ordering_[i]; }

    void setOrdering(int i, int order)
    { ordering_[i] = order; }

    bool allRanksStoredAscending() const
    {
        bool result = true;
        for ( int i = 0; i < N; ++ i )
        {
            result &= ascendingFlag_[i];
        }
        return result;
    }

    bool isRankStoredAscending(int i) const
    {
        return ascendingFlag_[i];
    }

    SimpleArray<bool, N>& ascendingFlag()
    {
        return ascendingFlag_;
    }

    const SimpleArray<bool, N>& ascendingFlag() const
    {
        return ascendingFlag_;
    }

    void setAscendingFlag(int i, bool ascendingFlag)
    {
        ascendingFlag_[i] = ascendingFlag;
    }

    SimpleArray<int, N>& base()
    {
        return base_;
    }

    const SimpleArray<int, N>& base() const
    {
        return base_;
    }

    int base(int i) const
    {
        return base_[i];
    }

    void setBase(int i, int base)
    {
        base_[i] = base;
    }

    void setBase(const SimpleArray<int, N>& base)
    {
        base_ = base;
    }
protected:
    // ordering_[] specifies the order in which the array is stored in
    // memory.  For a newly allocated array, ordering_(0) will give the
    // rank with unit stride, and ordering_(N_rank-1) will be the rank
    // with largest stride.  An order like [2, 1, 0] corresponds to
    // C-style array storage; an order like [0, 1, 2] corresponds to
    // Fortran array storage.
    //
    // ascendingFlag_[] indicates whether the data in a rank is stored
    // in ascending or descending order.  Most of the time these values
    // will all be true (indicating ascending order).  Some peculiar
    // formats (e.g. MS-Windows BMP image format) store the data in
    // descending order.
    //
    // base_[] gives the first valid index for each rank.  For a C-style
    // array, all the base_ elements will be zero; for a Fortran-style
    // array, they will be one.  base_[] can be set arbitrarily using
    // the Array constructor which takes a Range argument, e.g.
    // Array<float,2> A(Range(30,40),Range(23,33));
    // will create an array with base_[] = { 30, 23 }.

    //ascending ÉÏÉýµÄ
    SimpleArray<int,  N> ordering_;
    SimpleArray<bool, N> ascendingFlag_;
    SimpleArray<int,  N> base_;
};

/*
    * Class FortranArray specializes GeneralArrayStorage to provide Fortran
    * style arrays (column major ordering, base of 1).  The noInitializeFlag()
    * passed to the base constructor indicates that the subclass will take
    * care of initializing the ordering_, ascendingFlag_ and base_ members.
    */

template<int N>
class FortranArray : public GeneralArrayStorage<N> {
private:
    typedef GeneralArrayStorage<N> T_base;
    typedef typename T_base::noInitializeFlag noInitializeFlag;
    using T_base::ordering_;
    using T_base::ascendingFlag_;
    using T_base::base_;
public:
    FortranArray()
        : GeneralArrayStorage<N>(noInitializeFlag())
    {
        for ( int i = 0; i < N; ++ i )
        {
            ordering_[i] = i;
        }
        ascendingFlag_ = true;
        base_ = 1;
    }
};


// This tag class can be used to provide a nicer notation for
// constructing Fortran-style arrays: instead of
//     Array<int,2> A(3, 3, FortranArray<2>());
// one can simply write:
//     Array<int,2> A(3, 3, fortranArray);
// where fortranArray is an object of type _bz_fortranTag.

class fortranTag {
public:
    operator GeneralArrayStorage<1>()
    { return FortranArray<1>(); }

    operator GeneralArrayStorage<2>()
    { return FortranArray<2>(); }

    operator GeneralArrayStorage<3>()
    { return FortranArray<3>(); }

    operator GeneralArrayStorage<4>()
    { return FortranArray<4>(); }

    operator GeneralArrayStorage<5>()
    { return FortranArray<5>(); }

    operator GeneralArrayStorage<6>()
    { return FortranArray<6>(); }

    operator GeneralArrayStorage<7>()
    { return FortranArray<7>(); }

    operator GeneralArrayStorage<8>()
    { return FortranArray<8>(); }

    operator GeneralArrayStorage<9>()
    { return FortranArray<9>(); }

    operator GeneralArrayStorage<10>()
    { return FortranArray<10>(); }

    operator GeneralArrayStorage<11>()
    { return FortranArray<11>(); }
};

// A global instance of this class will be placed in
// the blitz library (libblitz.a on unix machines).

extern fortranTag fortranArray;


/*
    * Class ColumnMajorArray specializes GeneralArrayStorage to provide column
    * major arrays (column major ordering, base of 0).
    */

template<int N>
class ColumnMajorArray : public GeneralArrayStorage<N> {
private:
    typedef GeneralArrayStorage<N> T_base;
    typedef typename T_base::noInitializeFlag noInitializeFlag;
    using T_base::ordering_;
    using T_base::ascendingFlag_;
    using T_base::base_;
public:
    ColumnMajorArray()
        : GeneralArrayStorage<N>(noInitializeFlag())
    {
        ordering_ = Range(0, N - 1);
        ascendingFlag_ = true;
        base_ = 0;
    }
};
}
