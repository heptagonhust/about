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
//! @file      FYMemblock.h
//! @brief     Explain this file briefly.
//! @author    He Xin.

#pragma once

#include <stddef.h>     // ptrdiff_t

namespace FYSPACE
{
template<typename P_numtype>
class NumericTypeTraits
{
public:
    typedef P_numtype T_sumtype;    // Type to be used for summing
    typedef P_numtype T_difftype;   // Type to be used for difference
    typedef P_numtype T_floattype;  // Type to be used for floating-point
                                    // calculations
    typedef P_numtype T_signedtype; // Type to be used for signed calculations
    enum { hasTrivialCtor = 0 };    // Assume the worst
};
enum preexistingMemoryPolicy
{ 
    duplicateData, 
    deleteDataWhenDone, 
    neverDeleteData 
};

// Forward declaration of MemoryBlockReference
template < typename T_type > class MemoryBlockReference;

// Class MemoryBlock provides a reference-counted block of memory.  This block
// may be referred to by multiple vector, matrix and array objects.  The memory
// is automatically deallocated when the last referring object is destructed.
// MemoryBlock may be subclassed to provide special allocators.
template<typename P_type>
class MemoryBlock
{
    friend class MemoryBlockReference<P_type>;
public:
    typedef P_type T_type;
protected:
    MemoryBlock()
    {
        length_ = 0;
        data_ = 0;
        dataBlockAddress_ = 0;
        references_ = 0;
    }

    explicit MemoryBlock(size_t items)
    {
        length_ = items;
        allocate(length_);

        references_ = 0;
    }

    MemoryBlock(size_t length, T_type* data)
    {
        length_ = length;
        data_   = data;
        dataBlockAddress_ = data;
        references_ = 0;
    }

    virtual ~MemoryBlock()
    {
        if (dataBlockAddress_) 
        {
            deallocate();
        }
    }

    void addReference()
    { 
        ++ references_;
    }

    T_type * data() 
    { 
        return data_; 
    }

    const T_type * data()      const
    { 
        return data_; 
    }

    T_type*&      dataBlockAddress() 
    { 
        return dataBlockAddress_; 
    }

    size_t        length()    const
    { 
        return length_; 
    }

    int           removeReference()
    {
        int refcount = -- references_;
        return refcount;
    }

    int references() const
    {
        int refcount = references_;
        return refcount;
    }

protected:
    inline void allocate(size_t length);
    void deallocate();

private:   // Disabled member functions
    MemoryBlock(const MemoryBlock<T_type>&)
    { }

    void operator=(const MemoryBlock<T_type>&)
    { }

private:   // Data members
    T_type *              data_;
    T_type *              dataBlockAddress_;

    volatile int references_;
    size_t  length_;
};

template<typename P_type>
class UnownedMemoryBlock : public MemoryBlock<P_type>
{
public:
    UnownedMemoryBlock(size_t length, P_type* data)
        : MemoryBlock<P_type>(length,data)
    {
        // This ensures that MemoryBlock destructor will not 
        // attempt to delete data
        MemoryBlock<P_type>::dataBlockAddress() = 0;
    }

    virtual ~UnownedMemoryBlock()
    {
    }
};

template<typename P_type>
class NullMemoryBlock : public MemoryBlock<P_type>
{
public:
    NullMemoryBlock()
    { 
        // This ensures that the delete operator will not be invoked
        // on an instance of NullMemoryBlock in removeReference().
        MemoryBlock<P_type>::addReference();        
    }

    virtual ~NullMemoryBlock()  
    { }
};

template<typename P_type>
class MemoryBlockReference
{
public:
    typedef P_type T_type;
protected:
    T_type *  data_;

private:
    MemoryBlock<T_type>* block_;
    static NullMemoryBlock<T_type> nullBlock_;
public:
    MemoryBlockReference()
    {
        block_ = &nullBlock_;
        block_->addReference();
        data_ = 0;
    }

    MemoryBlockReference(MemoryBlockReference<T_type>& ref, size_t offset=0)
    {
        block_ = ref.block_;
        block_->addReference();
        data_ = ref.data_ + offset;
    }

    MemoryBlockReference(size_t length, T_type* data, 
        preexistingMemoryPolicy deletionPolicy)
    {
        // Create a memory block using already allocated memory. 

        // Note: if the deletionPolicy is duplicateData, this must
        // be handled by the leaf class.  In MemoryBlockReference,
        // this is treated as neverDeleteData; the leaf class (e.g. Array)
        // must duplicate the data.

        if (    (deletionPolicy == neverDeleteData ) 
                || (deletionPolicy == duplicateData   )  )
        {
            block_ = new UnownedMemoryBlock<T_type>(length, data);
        }
        else if ( deletionPolicy == deleteDataWhenDone )
        {
            block_ = new MemoryBlock<T_type>(length, data);
        }
        block_->addReference();

        data_ = data;
    }

    explicit MemoryBlockReference(size_t items)
    {
        block_ = new MemoryBlock<T_type>(items);
        block_->addReference();
        data_ = block_->data();
    }

    void blockRemoveReference()
    {
        int refcount = block_->removeReference();
        if ( ( refcount == 0 ) && ( block_ != &nullBlock_ ) )
        {
            delete block_;
        }
    }

    ~MemoryBlockReference()
    {
        blockRemoveReference();
    }

    int numReferences() const
    {
        return block_->references();
    }

protected:
    void changeToNullBlock()
    {
        blockRemoveReference();
        block_ = &nullBlock_;
        block_->addReference();
        data_ = 0;
    }

    void changeBlock(MemoryBlockReference<T_type>& ref, size_t offset=0)
    {
        blockRemoveReference();
        block_ = ref.block_;
        block_->addReference();
        data_ = ref.data_ + offset;
    }

    void newBlock(size_t items)
    {
        blockRemoveReference();
        block_ = new MemoryBlock<T_type>(items);
        block_->addReference();
        data_ = block_->data();
    }

    void newBlock(size_t length, T_type* data, 
        preexistingMemoryPolicy deletionPolicy)
    {
        // Create a memory block using already allocated memory. 

        // Note: if the deletionPolicy is duplicateData, this must
        // be handled by the leaf class.  In MemoryBlockReference,
        // this is treated as neverDeleteData; the leaf class (e.g. Array)
        // must duplicate the data.
        blockRemoveReference();

        if (    (deletionPolicy == neverDeleteData ) 
                || (deletionPolicy == duplicateData   )  )
        {
            block_ = new UnownedMemoryBlock<T_type>(length, data);
        }
        else if ( deletionPolicy == deleteDataWhenDone )
        {
            block_ = new MemoryBlock<T_type>(length, data);
        }
        block_->addReference();

        data_ = data;
    }


private:
    void operator=(const MemoryBlockReference<T_type>&)
    { }
};

}

#include "FYMemblock.hxx"
