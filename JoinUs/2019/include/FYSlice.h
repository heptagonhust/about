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
// Forward declaration
template<typename T, int N>
class FYArray;


class FYnilArraySection { };

template<typename T>
class FYArraySectionInfo
{
public:
    static const int isValidType = 0, rank = 0, isPick = 0;
};

template<>
class FYArraySectionInfo<Range> 
{
public:
    static const int isValidType = 1, rank = 1, isPick = 0;
};

template<>
class FYArraySectionInfo<int>
{
public:
    static const int isValidType = 1, rank = 0, isPick = 0;
};

template<>
class FYArraySectionInfo<FYnilArraySection>
{
public:
    static const int isValidType = 1, rank = 0, isPick = 0;
};

template<typename T,  typename T1,   typename T2 = FYnilArraySection, 
    typename T3 = FYnilArraySection, typename T4 = FYnilArraySection, 
    typename T5 = FYnilArraySection, typename T6 = FYnilArraySection, 
    typename T7 = FYnilArraySection, typename T8 = FYnilArraySection, 
    typename T9 = FYnilArraySection, typename T10 = FYnilArraySection, 
    typename T11 = FYnilArraySection>
class FYSliceInfo
{
public:
    static const int 
        numValidTypes = FYArraySectionInfo<T1>::isValidType
                      + FYArraySectionInfo<T2>::isValidType
                      + FYArraySectionInfo<T3>::isValidType
                      + FYArraySectionInfo<T4>::isValidType
                      + FYArraySectionInfo<T5>::isValidType
                      + FYArraySectionInfo<T6>::isValidType
                      + FYArraySectionInfo<T7>::isValidType
                      + FYArraySectionInfo<T8>::isValidType
                      + FYArraySectionInfo<T9>::isValidType
                      + FYArraySectionInfo<T10>::isValidType
                      + FYArraySectionInfo<T11>::isValidType,

        rank          = FYArraySectionInfo<T1>::rank
                      + FYArraySectionInfo<T2>::rank
                      + FYArraySectionInfo<T3>::rank
                      + FYArraySectionInfo<T4>::rank
                      + FYArraySectionInfo<T5>::rank
                      + FYArraySectionInfo<T6>::rank
                      + FYArraySectionInfo<T7>::rank
                      + FYArraySectionInfo<T8>::rank
                      + FYArraySectionInfo<T9>::rank
                      + FYArraySectionInfo<T10>::rank
                      + FYArraySectionInfo<T11>::rank,

        isPick        = FYArraySectionInfo<T1>::isPick
                      + FYArraySectionInfo<T2>::isPick
                      + FYArraySectionInfo<T3>::isPick
                      + FYArraySectionInfo<T4>::isPick
                      + FYArraySectionInfo<T5>::isPick
                      + FYArraySectionInfo<T6>::isPick
                      + FYArraySectionInfo<T7>::isPick
                      + FYArraySectionInfo<T8>::isPick
                      + FYArraySectionInfo<T9>::isPick
                      + FYArraySectionInfo<T10>::isPick
                      + FYArraySectionInfo<T11>::isPick;

    typedef FYArray<T,numValidTypes> T_array;
    typedef FYArray<T,rank> T_slice;
};

}


