namespace FYSPACE
{

//! Construction functions:
template<typename T, int N>
FYArray<T, N>::FYArray(const FYArray<T, N>& array)
	: MemoryBlockReference<T>(), FYETBase< FYArray<T, N> >(array)
{
#ifdef USE_SMARTARRAY
	ZeroAllPointer();
#endif
	// NEEDS_WORK: this const_cast is a tad ugly.
	Reference(const_cast<T_array&>(array));
}

template<typename T, int N>
FYArray<T, N>::FYArray(GeneralArrayStorage<N> storage)
	: storage_(storage)
{
#ifdef USE_SMARTARRAY
	ZeroAllPointer();
#endif
	length_     = 0;
	stride_     = 0;
	zeroOffset_ = 0;
}

template<typename T, int N>
FYArray<T, N>::FYArray(int length0, 
				 GeneralArrayStorage<N> storage)
				 : storage_(storage)
{
#ifdef USE_SMARTARRAY
	ZeroAllPointer();
#endif
	length_[0] = length0;
	setupStorage(0);
}

template<typename T, int N>
FYArray<T, N>::FYArray(int length0, int length1,
		GeneralArrayStorage<N> storage)
		: storage_(storage)
{
#ifdef USE_SMARTARRAY
	ZeroAllPointer();
#endif
	length_[0] = length0;
	length_[1] = length1;
	setupStorage(1);
}

template<typename T, int N>
FYArray<T, N>::FYArray(int length0, int length1, int length2,
		GeneralArrayStorage<N> storage)
		: storage_(storage)
{
#ifdef USE_SMARTARRAY
	ZeroAllPointer();
#endif
	length_[0] = length0;
	length_[1] = length1;
	length_[2] = length2;
	setupStorage(2);
}

template<typename T, int N>
FYArray<T, N>::FYArray(int length0, int length1, int length2, int length3,
		GeneralArrayStorage<N> storage)
		: storage_(storage)
{
#ifdef USE_SMARTARRAY
	ZeroAllPointer();
#endif
	length_[0] = length0;
	length_[1] = length1;
	length_[2] = length2;
	length_[3] = length3;
	setupStorage(3);
}

template<typename T, int N>
FYArray<T, N>::FYArray(int length0, int length1, int length2, int length3, int length4,
		GeneralArrayStorage<N> storage)
		: storage_(storage)
{
#ifdef USE_SMARTARRAY
	ZeroAllPointer();
#endif
	length_[0] = length0;
	length_[1] = length1;
	length_[2] = length2;
	length_[3] = length3;
	length_[4] = length4;
	setupStorage(4);
}

template<typename T, int N>
FYArray<T, N>::FYArray(const SimpleArray<int, N>& extent, 
		GeneralArrayStorage<N> storage)
		: storage_(storage)
{
#ifdef USE_SMARTARRAY
	ZeroAllPointer();
#endif
	length_ = extent;
	setupStorage(N - 1);
}

template<typename T, int N>
FYArray<T, N>::FYArray(const SimpleArray<int, N>& lbounds,
		const SimpleArray<int, N>& extent,
		const GeneralArrayStorage<N>& storage)
		: storage_(storage)
{
#ifdef USE_SMARTARRAY
	ZeroAllPointer();
#endif
	length_ = extent;
	storage_.setBase(lbounds);
	setupStorage(N - 1);
}

template<typename T, int N>
FYArray<T, N>::FYArray(Range r0, 
		GeneralArrayStorage<N> storage)
		: storage_(storage)
{
#ifdef USE_SMARTARRAY
	ZeroAllPointer();
#endif
	length_[0] = r0.length();
	storage_.setBase(0, r0.first());
	setupStorage(0);
}

template<typename T, int N>
FYArray<T, N>::FYArray(Range r0, Range r1,
		GeneralArrayStorage<N> storage)
		: storage_(storage)
{
#ifdef USE_SMARTARRAY
	ZeroAllPointer();
#endif
	length_[0] = r0.length();
	storage_.setBase(0, r0.first());
	length_[1] = r1.length();
	storage_.setBase(1, r1.first());

	setupStorage(1);
}

template<typename T, int N>
FYArray<T, N>::FYArray(Range r0, Range r1, Range r2,
		GeneralArrayStorage<N> storage)
		: storage_(storage)
{
#ifdef USE_SMARTARRAY
	ZeroAllPointer();
#endif
	length_[0] = r0.length();
	storage_.setBase(0, r0.first());
	length_[1] = r1.length();
	storage_.setBase(1, r1.first());
	length_[2] = r2.length();
	storage_.setBase(2, r2.first());

	setupStorage(2);
}

template<typename T, int N>
FYArray<T, N>::FYArray(Range r0, Range r1, Range r2, Range r3,
		GeneralArrayStorage<N> storage)
		: storage_(storage)
{
#ifdef USE_SMARTARRAY
	ZeroAllPointer();
#endif
	length_[0] = r0.length();
	storage_.setBase(0, r0.first());
	length_[1] = r1.length();
	storage_.setBase(1, r1.first());
	length_[2] = r2.length();
	storage_.setBase(2, r2.first());
	length_[3] = r3.length();
	storage_.setBase(3, r3.first());

	setupStorage(3);
}

template<typename T, int N>
FYArray<T, N>::FYArray(Range r0, Range r1, Range r2, Range r3, Range r4,
		GeneralArrayStorage<N> storage)
		: storage_(storage)
{
#ifdef USE_SMARTARRAY
	ZeroAllPointer();
#endif
	length_[0] = r0.length();
	storage_.setBase(0, r0.first());
	length_[1] = r1.length();
	storage_.setBase(1, r1.first());
	length_[2] = r2.length();
	storage_.setBase(2, r2.first());
	length_[3] = r3.length();
	storage_.setBase(3, r3.first());
	length_[4] = r4.length();
	storage_.setBase(4, r4.first());

	setupStorage(4);
}

template<typename T, int N>
FYArray<T, N>::FYArray(T* dataFirst,
		Range r0,
		preexistingMemoryPolicy deletionPolicy,
		GeneralArrayStorage<N> storage)
		: storage_(storage)
{
#ifdef USE_SMARTARRAY
	ZeroAllPointer();
#endif
	length_[0] = r0.length();
	storage_.setBase(0, r0.first());
	setupStorage(0,dataFirst,deletionPolicy);
}

template<typename T, int N>
FYArray<T, N>::FYArray(T* dataFirst,
		Range r0, Range r1,
		preexistingMemoryPolicy deletionPolicy,
		GeneralArrayStorage<N> storage)
		: storage_(storage)
{
#ifdef USE_SMARTARRAY
	ZeroAllPointer();
#endif
	length_[0] = r0.length();
	storage_.setBase(0, r0.first());
	length_[1] = r1.length();
	storage_.setBase(1, r1.first());

	setupStorage(1,dataFirst,deletionPolicy);
}

template<typename T, int N>
FYArray<T, N>::FYArray(T* dataFirst,
		Range r0, Range r1, Range r2,
		preexistingMemoryPolicy deletionPolicy,
		GeneralArrayStorage<N> storage)
		: storage_(storage)
{
#ifdef USE_SMARTARRAY
	ZeroAllPointer();
#endif
	length_[0] = r0.length();
	storage_.setBase(0, r0.first());
	length_[1] = r1.length();
	storage_.setBase(1, r1.first());
	length_[2] = r2.length();
	storage_.setBase(2, r2.first());

	setupStorage(2,dataFirst,deletionPolicy);
}

template<typename T, int N>
FYArray<T, N>::FYArray(T* dataFirst,
		Range r0, Range r1, Range r2, Range r3, Range r4,
		preexistingMemoryPolicy deletionPolicy,
		GeneralArrayStorage<N> storage)
		: storage_(storage)
{
#ifdef USE_SMARTARRAY
	ZeroAllPointer();
#endif
	length_[0] = r0.length();
	storage_.setBase(0, r0.first());
	length_[1] = r1.length();
	storage_.setBase(1, r1.first());
	length_[2] = r2.length();
	storage_.setBase(2, r2.first());
	length_[3] = r3.length();
	storage_.setBase(3, r3.first());
	length_[4] = r4.length();
	storage_.setBase(4, r4.first());

	setupStorage(4,dataFirst,deletionPolicy);
}

template<typename T, int N>
FYArray<T, N>::FYArray(T* dataFirst,
		Range r0, Range r1, Range r2, Range r3,
		preexistingMemoryPolicy deletionPolicy,
		GeneralArrayStorage<N> storage)
		: storage_(storage)
{
#ifdef USE_SMARTARRAY
	ZeroAllPointer();
#endif
	length_[0] = r0.length();
	storage_.setBase(0, r0.first());
	length_[1] = r1.length();
	storage_.setBase(1, r1.first());
	length_[2] = r2.length();
	storage_.setBase(2, r2.first());
	length_[3] = r3.length();
	storage_.setBase(3, r3.first());

	setupStorage(3,dataFirst,deletionPolicy);
}

template<typename T, int N>
FYArray<T, N>::FYArray(FYArray<T, N>& array_in, Range r0)
{
#ifdef USE_SMARTARRAY
	ZeroAllPointer();
#endif
	constructSubarray(array_in, r0);
}

template<typename T, int N>
FYArray<T, N>::FYArray(FYArray<T, N>& array_in, Range r0, Range r1)
{
#ifdef USE_SMARTARRAY
	ZeroAllPointer();
#endif
	constructSubarray(array_in, r0, r1);
}

template<typename T, int N>
FYArray<T, N>::FYArray(FYArray<T, N>& array_in, Range r0, Range r1, Range r2)
{
#ifdef USE_SMARTARRAY
	ZeroAllPointer();
#endif
	constructSubarray(array_in, r0, r1, r2);
}

template<typename T, int N>
FYArray<T, N>::FYArray(FYArray<T, N>& array_in, Range r0, Range r1, Range r2, Range r3)
{
#ifdef USE_SMARTARRAY
	ZeroAllPointer();
#endif
	constructSubarray(array_in, r0, r1, r2, r3);
}

template<typename T, int N>
FYArray<T, N>::FYArray(FYArray<T, N>& array_in, Range r0, Range r1, Range r2, Range r3, Range r4)
{
#ifdef USE_SMARTARRAY
	ZeroAllPointer();
#endif
	constructSubarray(array_in, r0, r1, r2, r3, r4);
}

template<typename T, int N>
FYArray<T, N>::FYArray(FYArray<T, N>& array_in, Range r0, Range r1, Range r2, Range r3, Range r4, Range r5)
{
#ifdef USE_SMARTARRAY
	ZeroAllPointer();
#endif
	constructSubarray(array_in, r0, r1, r2, r3, r4, r5);
}

template<typename T, int N>
FYArray<T, N>::FYArray(FYArray<T, N>& array_in, Range r0, Range r1, Range r2, Range r3, Range r4, Range r5, Range r6)
{
#ifdef USE_SMARTARRAY
	ZeroAllPointer();
#endif
	constructSubarray(array_in, r0, r1, r2, r3, r4, r5, r6);
}

template < typename T, int N >
template < int N2, typename R0, typename R1, typename R2, typename R3, typename R4,
	typename R5, typename R6, typename R7, typename R8, typename R9, typename R10 >
	FYArray<T, N>::FYArray(FYArray<T, N2>& array_in, R0 r0, R1 r1, R2 r2,
	R3 r3, R4 r4, R5 r5, R6 r6, R7 r7, R8 r8, R9 r9, R10 r10)
{
#ifdef USE_SMARTARRAY
	ZeroAllPointer();
#endif
	constructSlice(array_in, r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10);
}

//! Public member functions:
template<typename T, int N>
int FYArray<T, N>::getindex(int i0, int i1, int i2, int i3) const
{
	return i0 * stride_[0] + i1 * stride_[1]
	+ i2 * stride_[2] + i3 * stride_[3];
}

template<typename T, int N>
int FYArray<T, N>::lbound(int rank) const 
{
	return base(rank); 
}

template<typename T, int N>
SimpleArray<int,N> FYArray<T, N>::lbound() const
{ 
	return base();
}

template<typename T, int N>
int FYArray<T, N>::ubound(int rank) const
{ 
	return base(rank) + length(rank) - 1; 
}

template<typename T, int N>
int FYArray<T, N>::length(int rank) const
{
	return length_[rank]; 
}

template<typename T, int N>
const SimpleArray<int, N>& FYArray<T, N>::length() const
{
	return length_; 
}

template<typename T, int N>
const SimpleArray<int, N> & FYArray<T, N>::base() const
{
	return storage_.base(); 
}

template<typename T, int N>
int FYArray<T, N>::base(int rank) const
{
	return storage_.base(rank); 
}

template<typename T, int N>
int FYArray<T, N>::stride(int rank) const
{ 
	return stride_[rank];
}

template<typename T, int N>
int FYArray<T, N>::numElements() const 
{
	return product(length_);
}

template<typename T, int N>
const T * FYArray<T, N>::data() const
{
	return data_ + dataOffset();
}

template<typename T, int N>
T* FYArray<T, N>::data() 
{ 
	return data_ + dataOffset();
}

template<typename T, int N>
bool FYArray<T, N>::canCollapse(int outerRank, int innerRank) const 
{ 
	return (stride(innerRank) * length(innerRank) == stride(outerRank)); 
}

template<typename T, int N>
typename FYArray<T, N>::T_iterator FYArray<T, N>::beginFast() const
{ 
	return T_iterator(*this);
}

template<typename T, int N>
int FYArray<T, N>::ordering(int storageRankIndex) const
{ 
	return storage_.ordering(storageRankIndex);
}

template<typename T, int N>
const SimpleArray<int, N> & FYArray<T, N>::ordering() const
{ 
	return storage_.ordering();
}

template<typename T, int N>
bool FYArray<T, N>::isMajorRank(int rank) const 
{  
	return storage_.ordering(rank) == 0; 
}

template<typename T, int N>
bool FYArray<T, N>::isMinorRank(int rank) const 
{  
	return storage_.ordering(rank) != 0; 
}

template<typename T, int N>
bool FYArray<T, N>::isRankStoredAscending(int rank) const
{
	return storage_.isRankStoredAscending(rank);
}

//! Private member functions:
template<typename T, int N>
int FYArray<T, N>::dataOffset() const
{
	return dot(storage_.base(), stride_);
}

template<typename T, int N>
void FYArray<T, N>::Reference(const T_array& array)
{
    storage_    = array.storage_;
    length_     = array.length_;
    stride_     = array.stride_;
    zeroOffset_ = array.zeroOffset_;

    MemoryBlockReference<T>::changeBlock(array.noConst());
}
template<typename T, int N>
FYArray<T, N> & FYArray<T, N>::noConst() const
{ 
	return const_cast<FYArray<T, N> &>(*this);
}

template<typename T, int N>
void FYArray<T, N>::setupStorage(int lastRankInitialized)
{
        // If the length of some of the ranks was unspecified, fill these
        // in using the last specified value.
        //
        // e.g. Array<int,3> A(40) results in a 40x40x40 array.
    for ( int i = lastRankInitialized + 1; i < N; ++ i )
    {
        storage_.setBase(i, storage_.base(lastRankInitialized));
        length_[i] = length_[lastRankInitialized];
    }

    // Compute strides
    computeStrides();

    // Allocate a block of memory
    int numElem = numElements();
    if ( numElem == 0 )
    {
        MemoryBlockReference<T>::changeToNullBlock();
    }
    else
    {
        MemoryBlockReference<T>::newBlock(numElem);
    }

    // Adjust the base of the array to account for non-zero base
    // indices and reversals
    data_ += zeroOffset_;

	//! Added by zhangjian 20170714
#ifdef USE_SMARTARRAY
	AllocateRange( lastRankInitialized+1);
#endif
	//! End
}

template<typename T, int N>
void FYArray<T, N>::setupStorage(int lastRankInitialized, T *data, preexistingMemoryPolicy deletionPolicy)
{
        // If the length of some of the ranks was unspecified, fill these
        // in using the last specified value.
        //
        // e.g. Array<int,3> A(40) results in a 40x40x40 array.
    for ( int i = lastRankInitialized + 1; i < N; ++ i )
    {
        storage_.setBase(i, storage_.base(lastRankInitialized));
        length_[i] = length_[lastRankInitialized];
    }

    // Compute strides
    computeStrides();

    // Allocate a block of memory
    int numElem = numElements();

	MemoryBlockReference<T>::newBlock(numElem,data,deletionPolicy);

    // Adjust the base of the array to account for non-zero base
    // indices and reversals
    data_ += zeroOffset_;

	//! Added by zhangjian 20170714
#ifdef USE_SMARTARRAY
	AllocateRange( lastRankInitialized+1);
#endif
	//! End
}

template<typename T, int N>
void FYArray<T, N>::computeStrides()
{
    if ( N > 1 )
    {
        int stride = 1;

        // This flag simplifies the code in the loop, encouraging
        // compile-time computation of strides through constant folding.
        bool allAscending = storage_.allRanksStoredAscending();

        for ( int n = 0; n < N; ++ n )
        {
            int strideSign = + 1;

            // If this rank is stored in descending order, then the stride
            // will be negative.
            if ( !allAscending )
            {
                if  ( !isRankStoredAscending( ordering(n) ) )
                {
                    strideSign = - 1;
                }
            }

            // The stride for this rank is the product of the lengths of
            // the ranks minor to it.
            stride_[ ordering(n) ] = stride * strideSign;

            stride *= length_[ ordering(n) ];
        }
    }
    else
    {
        // Specialization for N_rank == 1
        // This simpler calculation makes it easier for the compiler
        // to propagate stride values.

        if ( isRankStoredAscending(0) )
        {
            stride_[0] =   1;
        }
        else
        {
            stride_[0] = - 1;
        }
    }

    calculateZeroOffset();
}

template<typename T,  int N>
void FYArray<T, N>::calculateZeroOffset()
{
    // Compute the offset of (0,0,...,0)
    zeroOffset_ = 0;

    // zeroOffset_ = - sum(where(ascendingFlag_, stride_ * base_,
    //     (length_ - 1 + base_) * stride_))
    for ( int n = 0; n < N; ++ n )
    {
        if ( !isRankStoredAscending(n) )
        {
            zeroOffset_ -= (length_[n] - 1 + base(n) ) * stride_[n];
        }
        else
        {
            zeroOffset_ -= stride_[n] * base(n);
        }
    }
}

template<typename T, int N>
void FYArray<T, N>::constructSubarray(FYArray<T, N>& array_in, Range r0)
{
    Reference(array_in);
    slice(0, r0);
}

template<typename T, int N>
void FYArray<T, N>::constructSubarray(FYArray<T, N>& array_in, Range r0, Range r1)
{
    Reference(array_in);
    slice(0, r0);
    slice(1, r1);
}

template<typename T, int N>
void FYArray<T, N>::constructSubarray(FYArray<T, N>& array_in, Range r0, Range r1, Range r2)
{
    Reference(array_in);
    slice(0, r0);
    slice(1, r1);
    slice(2, r2);
}

template<typename T, int N>
void FYArray<T, N>::constructSubarray(FYArray<T, N>& array_in, Range r0, Range r1, Range r2, Range r3)
{
    Reference(array_in);
    slice(0, r0);
    slice(1, r1);
    slice(2, r2);
    slice(3, r3);
}

template<typename T, int N>
void FYArray<T, N>::constructSubarray(FYArray<T, N>& array_in, Range r0, Range r1, Range r2, Range r3, Range r4)
{
    Reference(array_in);
    slice(0, r0);
    slice(1, r1);
    slice(2, r2);
    slice(3, r3);
	slice(4, r4);
}

template<typename T, int N>
void FYArray<T, N>::constructSubarray(FYArray<T, N>& array_in, Range r0, Range r1, Range r2, Range r3, Range r4, Range r5)
{
    Reference(array_in);
    slice(0, r0);
    slice(1, r1);
    slice(2, r2);
    slice(3, r3);
	slice(4, r4);
	slice(5, r5);
}

template<typename T, int N>
void FYArray<T, N>::constructSubarray(FYArray<T, N>& array_in, Range r0, Range r1, Range r2, Range r3, Range r4, Range r5, Range r6)
{
    Reference(array_in);
    slice(0, r0);
    slice(1, r1);
    slice(2, r2);
    slice(3, r3);
	slice(4, r4);
	slice(5, r5);
	slice(6, r6);
}

//! Added by zhangjian 20170711
#ifdef USE_SMARTARRAY
template<typename T, int N>
void FYArray<T, N>::ZeroAllPointer()
{
	data1 = NULL;
	data2 = NULL;
	data3 = NULL;
	data4 = NULL;
	data5 = NULL;
	datap1 = NULL;
	datap2 = NULL;
	datap3 = NULL;
	datap4 = NULL;
	datap5 = NULL;
}

template<typename T, int N>
void FYArray<T, N>::AllocateRange(int dimension)
{
	switch ( dimension )
	{
	case 1:
		AllocateRange1();
		break;
	case 2:
		AllocateRange2();
		break;
	case 3:
		AllocateRange3();
		break;
	case 4:
		AllocateRange4();
		break;
	case 5:
		AllocateRange5();
		break;
	default:
#ifdef _DEBUG
		printf("File: %s Line: %d Function: FYArray::AllocateRange Error\n",__FILE__, __LINE__);
		//FYSPACE::FYUnexpectedSituation("FYArray::AllocateRange", dimension);
#endif
		exit(0);
		break;
	}
}

template<typename T, int N>
void FYArray<T, N>::AllocateRange1()
{
	datap1 = data_;
}

template<typename T, int N>
void FYArray<T, N>::AllocateRange2()
{
	int bound0 = length_[0];
	int bound1 = length_[1];

	data2 = new T * [ bound1  ];
	data1 = data_ - zeroOffset_;

	int st1 = storage_.base(0);
	int st2 = storage_.base(1);

	datap2 = data2 - st2;
	for ( int i1 = 0; i1 < bound1; ++ i1 )
	{
		int j0 = bound0 * i1;
		datap2[ i1 + st2 ] = & data1[ j0 ] - st1;
	}
}

template<typename T, int N>
void FYArray<T, N>::AllocateRange3()
{
	int bound0 = length_[0];
	int bound1 = length_[1];
	int bound2 = length_[2];

	int const bound12  = bound1 * bound2;
	data3  = new T ** [ bound2   ];
	data2  = new T *  [ bound12  ];
	data1  = data_ - zeroOffset_;

	int st1 = storage_.base(0);
	int st2 = storage_.base(1);
	int st3 = storage_.base(2);
	
	datap3 = data3 - st3;
	for ( int i2 = 0; i2 < bound2; ++ i2 )
	{
		int j1 = bound1 * ( i2 );
		datap3[ i2 + st3 ] = & data2[ j1 ] - st2;
		for ( int i1 = 0; i1 < bound1; ++ i1 )
		{
			int j0 = bound0 * ( i1 + j1 );
			datap3[ i2 + st3 ][ i1 + st2 ] = & data1[ j0 ] - st1;
		}
	}

}

template<typename T, int N>
void FYArray<T, N>::AllocateRange4()
{
	int bound0 = length_[0];
	int bound1 = length_[1];
	int bound2 = length_[2];
	int bound3 = length_[3];

	int const bound23   = bound2 * bound3;
    int const bound123  = bound1 * bound23;
	data4 = new T *** [ bound3    ];
    data3 = new T **  [ bound23   ];
    data2 = new T *   [ bound123  ];
	data1 = data_ - zeroOffset_;

	int st1 = storage_.base(0);
	int st2 = storage_.base(1);
	int st3 = storage_.base(2);
	int st4 = storage_.base(3);

	datap4= data4 - st4;
	for ( int i3 = 0; i3 < bound3; ++ i3 )
    {
        int j2 = bound2 * i3;  // = bound2*(i3 + j3) where j3 = 0
        datap4[ i3 + st4 ] = & data3[ j2 ] - st3;
        for ( int i2 = 0; i2 < bound2; ++ i2 )
        {
            int j1 = bound1 * ( i2 + j2 );
            datap4[ i3 + st4 ][ i2 + st3 ] = & data2[ j1 ] - st2;
            for ( int i1 = 0; i1 < bound1; ++ i1 )
            {
                int j0 = bound0 * ( i1 + j1 );
                datap4[ i3 + st4 ][ i2 + st3 ][ i1 + st2 ] = & data1[ j0 ] - st1;
            }
        }
    }
}

template<typename T, int N>
void FYArray<T, N>::AllocateRange5()
{
	int bound0 = length_[0];
	int bound1 = length_[1];
	int bound2 = length_[2];
	int bound3 = length_[3];
	int bound4 = length_[4];

	int const bound34   = bound3 * bound4;
	int const bound234   = bound2 * bound34;
	int const bound1234  = bound1 * bound234;

	data5 = new T ****[ bound4     ];
	data4 = new T *** [ bound34    ];
	data3 = new T **  [ bound234   ];
	data2 = new T *   [ bound1234  ];

	data1 = data_ - zeroOffset_;

	int st1 = storage_.base(0);
	int st2 = storage_.base(1);
	int st3 = storage_.base(2);
	int st4 = storage_.base(3);
	int st5 = storage_.base(4);

	datap5= data5 - st5;
	for (int i4 = 0; i4 < bound4; ++ i4 )
	{
		int j3 = bound3 * i4;
		datap5[ i4 + st5] = & data4[ j3 ] - st4;
		for ( int i3 = 0; i3 < bound3; ++ i3 )
		{
			int j2 = bound2 * (i3 + j3);
			datap5[ i4 + st5 ][ i3 + st4] = & data3[ j2 ] - st3;
			for ( int i2 = 0; i2 < bound2; ++ i2 )
			{
				int j1 = bound1 * ( i2 + j2 );
				datap5[ i4 + st5 ][ i3 + st4 ][ i2 + st3] = & data2[ j1 ] - st2;
				for ( int i1 = 0; i1 < bound1; ++ i1 )
				{
					int j0 = bound0 * ( i1 + j1 );
					datap5[ i4 + st5 ][ i3 + st4 ][ i2 + st3][ i1 + st2] = & data1[ j0 ] - st1;
				}
			}
		}
	}	
}
#endif
//! End
}

