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

//#include "FYMemblock.h"

namespace FYSPACE
{
// Null memory block for each (template) instantiation of MemoryBlockReference
template<typename P_type>
NullMemoryBlock<P_type> MemoryBlockReference<P_type>::nullBlock_;

template<typename P_type>
void MemoryBlock<P_type>::deallocate()
{
    if ( !NumericTypeTraits<T_type>::hasTrivialCtor ) {
        for ( std::size_t i = 0; i < length_; ++ i )
        {
            data_[i].~T_type();
        }
        delete [] reinterpret_cast<char*>(dataBlockAddress_);
    }
    else
    {
        delete [] dataBlockAddress_;
    }
}

template<typename P_type>
inline void MemoryBlock<P_type>::allocate(size_t length)
{
    size_t numBytes = length * sizeof(T_type);

    if ( numBytes < 1024 )
    {
        dataBlockAddress_ = new T_type[length];
        data_ = dataBlockAddress_;
    }
    else
    {
        // We're allocating a large array.  For performance reasons,
        // it's advantageous to force the array to start on a
        // cache line boundary.  We do this by allocating a little
        // more memory than necessary, then shifting the pointer
        // to the next cache line boundary.

        // Patches by Petter Urkedal to support types with nontrivial
        // constructors.

        const int cacheBlockSize = 128;    // Will work for 32, 16 also

        dataBlockAddress_ = reinterpret_cast<T_type*>( new char[numBytes + cacheBlockSize - 1] );
        // Shift to the next cache line boundary

        //ptrdiff_t offset = ptrdiff_t(dataBlockAddress_) % cacheBlockSize;
        ptrdiff_t offset = reinterpret_cast<ptrdiff_t>(dataBlockAddress_) % cacheBlockSize;
        ptrdiff_t shift = ( offset == 0 ) ? 0 : ( cacheBlockSize - offset );
        data_ = reinterpret_cast<T_type*>(reinterpret_cast<char*>(dataBlockAddress_) + shift);

        // Use placement new to construct types with nontrival ctors
        if ( !NumericTypeTraits<T_type>::hasTrivialCtor )
        {
            for ( std::size_t i = 0; i < length; ++ i )
            {
                new(&data_[i]) T_type;
            }
        }
    }
}

}

