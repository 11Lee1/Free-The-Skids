
typedef __int32 intp;
typedef unsigned __int32 uintp;
#ifdef UTBLOCKLMEMORY_TRACK
#define UTLBLOCKMEMORY_TRACK_ALLOC()		MemAlloc_RegisterAllocation( "Sum of all UtlBlockMemory", 0, NumAllocated() * sizeof(T), NumAllocated() * sizeof(T), 0 )
#define UTLBLOCKMEMORY_TRACK_FREE()		if ( !m_pMemory ) ; else MemAlloc_RegisterDeallocation( "Sum of all UtlBlockMemory", 0, NumAllocated() * sizeof(T), NumAllocated() * sizeof(T), 0 )
#else
#define UTLBLOCKMEMORY_TRACK_ALLOC()		((void)0)
#define UTLBLOCKMEMORY_TRACK_FREE()		((void)0)
#endif


//-----------------------------------------------------------------------------
// The CUtlBlockMemory class:
// A growable memory class that allocates non-sequential blocks, but is indexed sequentially
//-----------------------------------------------------------------------------
template< class T, class I >
class CUtlBlockMemory
{
public:
	// constructor, destructor
	CUtlBlockMemory(int nGrowSize = 0, int nInitSize = 0);
	~CUtlBlockMemory();

	// Set the size by which the memory grows - round up to the next power of 2
	void Init(int nGrowSize = 0, int nInitSize = 0);

	// here to match CUtlMemory, but only used by ResetDbgInfo, so it can just return NULL
	T* Base() { return NULL; }
	const T* Base() const { return NULL; }

	class Iterator_t
	{
	public:
		Iterator_t(I i) : index(i) {}
		I index;

		bool operator==(const Iterator_t it) const { return index == it.index; }
		bool operator!=(const Iterator_t it) const { return index != it.index; }
	};
	Iterator_t First() const { return Iterator_t(IsIdxValid(0) ? 0 : InvalidIndex()); }
	Iterator_t Next(const Iterator_t &it) const { return Iterator_t(IsIdxValid(it.index + 1) ? it.index + 1 : InvalidIndex()); }
	I GetIndex(const Iterator_t &it) const { return it.index; }
	bool IsIdxAfter(I i, const Iterator_t &it) const { return i > it.index; }
	bool IsValidIterator(const Iterator_t &it) const { return IsIdxValid(it.index); }
	Iterator_t InvalidIterator() const { return Iterator_t(InvalidIndex()); }

	// element access
	T& operator[](I i);
	const T& operator[](I i) const;
	T& Element(I i);
	const T& Element(I i) const;

	// Can we use this index?
	bool IsIdxValid(I i) const;
	static I InvalidIndex() { return (I)-1; }

	void Swap(CUtlBlockMemory< T, I > &mem);

	// Size
	int NumAllocated() const;
	int Count() const { return NumAllocated(); }

	// Grows memory by max(num,growsize) rounded up to the next power of 2, and returns the allocation index/ptr
	void Grow(int num = 1);

	// Makes sure we've got at least this much memory
	void EnsureCapacity(int num);

	// Memory deallocation
	void Purge();

	// Purge all but the given number of elements
	void Purge(int numElements);

protected:
	int Index(int major, int minor) const { return (major << m_nIndexShift) | minor; }
	int MajorIndex(int i) const { return i >> m_nIndexShift; }
	int MinorIndex(int i) const { return i & m_nIndexMask; }
	void ChangeSize(int nBlocks);
	int NumElementsInBlock() const { return m_nIndexMask + 1; }

	T** m_pMemory;
	int m_nBlocks;
	int m_nIndexMask : 27;
	int m_nIndexShift : 5;
};

//-----------------------------------------------------------------------------
// constructor, destructor
//-----------------------------------------------------------------------------

template< class T, class I >
CUtlBlockMemory<T, I>::CUtlBlockMemory(int nGrowSize, int nInitAllocationCount)
	: m_pMemory(0), m_nBlocks(0), m_nIndexMask(0), m_nIndexShift(0)
{
	Init(nGrowSize, nInitAllocationCount);
}

template< class T, class I >
CUtlBlockMemory<T, I>::~CUtlBlockMemory()
{
	Purge();
}


//-----------------------------------------------------------------------------
// Fast swap
//-----------------------------------------------------------------------------
template< class T, class I >
void CUtlBlockMemory<T, I>::Swap(CUtlBlockMemory< T, I > &mem)
{
	swap(m_pMemory, mem.m_pMemory);
	swap(m_nBlocks, mem.m_nBlocks);
	swap(m_nIndexMask, mem.m_nIndexMask);
	swap(m_nIndexShift, mem.m_nIndexShift);
}


//-----------------------------------------------------------------------------
// Set the size by which the memory grows - round up to the next power of 2
//-----------------------------------------------------------------------------
template< class T, class I >
void CUtlBlockMemory<T, I>::Init(int nGrowSize /* = 0 */, int nInitSize /* = 0 */)
{
	Purge();

	if (nGrowSize == 0)
	{
		// default grow size is smallest size s.t. c++ allocation overhead is ~6% of block size
		nGrowSize = (127 + sizeof(T)) / sizeof(T);
	}
	nGrowSize = SmallestPowerOfTwoGreaterOrEqual(nGrowSize);
	m_nIndexMask = nGrowSize - 1;

	m_nIndexShift = 0;
	while (nGrowSize > 1)
	{
		nGrowSize >>= 1;
		++m_nIndexShift;
	}

	Grow(nInitSize);
}


//-----------------------------------------------------------------------------
// element access
//-----------------------------------------------------------------------------
template< class T, class I >
inline T& CUtlBlockMemory<T, I>::operator[](I i)
{
	Assert(IsIdxValid(i));
	T *pBlock = m_pMemory[MajorIndex(i)];
	return pBlock[MinorIndex(i)];
}

template< class T, class I >
inline const T& CUtlBlockMemory<T, I>::operator[](I i) const
{
	Assert(IsIdxValid(i));
	const T *pBlock = m_pMemory[MajorIndex(i)];
	return pBlock[MinorIndex(i)];
}

template< class T, class I >
inline T& CUtlBlockMemory<T, I>::Element(I i)
{
	T *pBlock = m_pMemory[MajorIndex(i)];
	return pBlock[MinorIndex(i)];
}

template< class T, class I >
inline const T& CUtlBlockMemory<T, I>::Element(I i) const
{
	const T *pBlock = m_pMemory[MajorIndex(i)];
	return pBlock[MinorIndex(i)];
}


//-----------------------------------------------------------------------------
// Size
//-----------------------------------------------------------------------------
template< class T, class I >
inline int CUtlBlockMemory<T, I>::NumAllocated() const
{
	return m_nBlocks * NumElementsInBlock();
}


//-----------------------------------------------------------------------------
// Is element index valid?
//-----------------------------------------------------------------------------
template< class T, class I >
inline bool CUtlBlockMemory<T, I>::IsIdxValid(I i) const
{
	return (i >= 0) && (MajorIndex(i) < m_nBlocks);
}

template< class T, class I >
void CUtlBlockMemory<T, I>::Grow(int num)
{
	if (num <= 0)
		return;

	int nBlockSize = NumElementsInBlock();
	int nBlocks = (num + nBlockSize - 1) / nBlockSize;

	ChangeSize(m_nBlocks + nBlocks);
}

template< class T, class I >
void CUtlBlockMemory<T, I>::ChangeSize(int nBlocks)
{
	UTLBLOCKMEMORY_TRACK_FREE(); // this must stay before the recalculation of m_nBlocks, since it implicitly uses the old value

	int nBlocksOld = m_nBlocks;
	m_nBlocks = nBlocks;

	UTLBLOCKMEMORY_TRACK_ALLOC(); // this must stay after the recalculation of m_nBlocks, since it implicitly uses the new value

	if (m_pMemory)
	{
		// free old blocks if shrinking
		// Only possible if m_pMemory is non-NULL (and avoids PVS-Studio warning)
		for (int i = m_nBlocks; i < nBlocksOld; ++i)
		{
			UTLBLOCKMEMORY_TRACK_FREE();
			free((void*)m_pMemory[i]);
		}

		m_pMemory = (T**)realloc(m_pMemory, m_nBlocks * sizeof(T*));
	}
	else
	{
		m_pMemory = (T**)malloc(m_nBlocks * sizeof(T*));
	}

	if (!m_pMemory)
	{
		print("CUtlBlockMemory overflow!\n");
	}

	// allocate new blocks if growing
	int nBlockSize = NumElementsInBlock();
	for (int i = nBlocksOld; i < m_nBlocks; ++i)
	{
		m_pMemory[i] = (T*)malloc(nBlockSize * sizeof(T));
	}
}


//-----------------------------------------------------------------------------
// Makes sure we've got at least this much memory
//-----------------------------------------------------------------------------
template< class T, class I >
inline void CUtlBlockMemory<T, I>::EnsureCapacity(int num)
{
	Grow(num - NumAllocated());
}


//-----------------------------------------------------------------------------
// Memory deallocation
//-----------------------------------------------------------------------------
template< class T, class I >
void CUtlBlockMemory<T, I>::Purge()
{
	if (!m_pMemory)
		return;

	for (int i = 0; i < m_nBlocks; ++i)
	{
		UTLBLOCKMEMORY_TRACK_FREE();
		free((void*)m_pMemory[i]);
	}
	m_nBlocks = 0;

	UTLBLOCKMEMORY_TRACK_FREE();
	free((void*)m_pMemory);
	m_pMemory = 0;
}

template< class T, class I >
void CUtlBlockMemory<T, I>::Purge(int numElements)
{

	int nAllocated = NumAllocated();
	if (numElements > nAllocated)
	{
		// Ensure this isn't a grow request in disguise.
		Assert(numElements <= nAllocated);
		return;
	}

	if (numElements <= 0)
	{
		Purge();
		return;
	}

	int nBlockSize = NumElementsInBlock();
	int nBlocksOld = m_nBlocks;
	int nBlocks = (numElements + nBlockSize - 1) / nBlockSize;

	// If the number of blocks is the same as the allocated number of blocks, we are done.
	if (nBlocks == m_nBlocks)
		return;

	ChangeSize(nBlocks);
}
//-----------------------------------------------------------------------------

#ifdef UTLFIXEDMEMORY_TRACK
#define UTLFIXEDMEMORY_TRACK_ALLOC()		MemAlloc_RegisterAllocation( "Sum of all UtlFixedMemory", 0, NumAllocated() * sizeof(T), NumAllocated() * sizeof(T), 0 )
#define UTLFIXEDMEMORY_TRACK_FREE()		if ( !m_pMemory ) ; else MemAlloc_RegisterDeallocation( "Sum of all UtlFixedMemory", 0, NumAllocated() * sizeof(T), NumAllocated() * sizeof(T), 0 )
#else
#define UTLFIXEDMEMORY_TRACK_ALLOC()		((void)0)
#define UTLFIXEDMEMORY_TRACK_FREE()		((void)0)
#endif


//-----------------------------------------------------------------------------
// The CUtlFixedMemory class:
// A growable memory class that allocates non-sequential blocks, but is indexed sequentially
//-----------------------------------------------------------------------------
template< class T >
class CUtlFixedMemory
{
public:
	// constructor, destructor
	CUtlFixedMemory(int nGrowSize = 0, int nInitSize = 0);
	~CUtlFixedMemory();

	// Set the size by which the memory grows
	void Init(int nGrowSize = 0, int nInitSize = 0);

	// here to match CUtlMemory, but only used by ResetDbgInfo, so it can just return NULL
	T* Base() { return NULL; }
	const T* Base() const { return NULL; }

protected:
	struct BlockHeader_t;

public:
	class Iterator_t
	{
	public:
		Iterator_t(BlockHeader_t *p, int i) : m_pBlockHeader(p), m_nIndex(i) {}
		BlockHeader_t *m_pBlockHeader;
		intp m_nIndex;

		bool operator==(const Iterator_t it) const { return m_pBlockHeader == it.m_pBlockHeader && m_nIndex == it.m_nIndex; }
		bool operator!=(const Iterator_t it) const { return m_pBlockHeader != it.m_pBlockHeader || m_nIndex != it.m_nIndex; }
	};
	Iterator_t First() const { return m_pBlocks ? Iterator_t(m_pBlocks, 0) : InvalidIterator(); }
	Iterator_t Next(const Iterator_t &it) const
	{
		if (!IsValidIterator(it))
			return InvalidIterator();

		BlockHeader_t * pHeader = it.m_pBlockHeader;
		if (it.m_nIndex + 1 < pHeader->m_nBlockSize)
			return Iterator_t(pHeader, it.m_nIndex + 1);

		return pHeader->m_pNext ? Iterator_t(pHeader->m_pNext, 0) : InvalidIterator();
	}
	intp GetIndex(const Iterator_t &it) const
	{
		if (!IsValidIterator(it))
			return InvalidIndex();

		return (intp)(HeaderToBlock(it.m_pBlockHeader) + it.m_nIndex);
	}
	bool IsIdxAfter(intp i, const Iterator_t &it) const
	{
		if (!IsValidIterator(it))
			return false;

		if (IsInBlock(i, it.m_pBlockHeader))
			return i > GetIndex(it);

		for (BlockHeader_t * pbh = it.m_pBlockHeader->m_pNext; pbh; pbh = pbh->m_pNext)
		{
			if (IsInBlock(i, pbh))
				return true;
		}
		return false;
	}
	bool IsValidIterator(const Iterator_t &it) const { return it.m_pBlockHeader && it.m_nIndex >= 0 && it.m_nIndex < it.m_pBlockHeader->m_nBlockSize; }
	Iterator_t InvalidIterator() const { return Iterator_t(NULL, INVALID_INDEX); }

	// element access
	T& operator[](intp i);
	const T& operator[](intp i) const;
	T& Element(intp i);
	const T& Element(intp i) const;

	// Can we use this index?
	bool IsIdxValid(intp i) const;

	// Specify the invalid ('null') index that we'll only return on failure
	static const intp INVALID_INDEX = 0; // For use with COMPILE_TIME_ASSERT
	static intp InvalidIndex() { return INVALID_INDEX; }

	// Size
	int NumAllocated() const;
	int Count() const { return NumAllocated(); }

	// Grows memory by max(num,growsize), and returns the allocation index/ptr
	void Grow(int num = 1);

	// Makes sure we've got at least this much memory
	void EnsureCapacity(int num);

	// Memory deallocation
	void Purge();

protected:
	// Fast swap - WARNING: Swap invalidates all ptr-based indices!!!
	void Swap(CUtlFixedMemory< T > &mem);

	bool IsInBlock(intp i, BlockHeader_t *pBlockHeader) const
	{
		T *p = (T*)i;
		const T *p0 = HeaderToBlock(pBlockHeader);
		return p >= p0 && p < p0 + pBlockHeader->m_nBlockSize;
	}

	struct BlockHeader_t
	{
		BlockHeader_t *m_pNext;
		intp m_nBlockSize;
	};

	const T *HeaderToBlock(const BlockHeader_t *pHeader) const { return (T*)(pHeader + 1); }
	const BlockHeader_t *BlockToHeader(const T *pBlock) const { return (BlockHeader_t*)(pBlock)-1; }

	BlockHeader_t* m_pBlocks;
	int m_nAllocationCount;
	int m_nGrowSize;
};

//-----------------------------------------------------------------------------
// constructor, destructor
//-----------------------------------------------------------------------------

template< class T >
CUtlFixedMemory<T>::CUtlFixedMemory(int nGrowSize, int nInitAllocationCount)
	: m_pBlocks(0), m_nAllocationCount(0), m_nGrowSize(0)
{
	Init(nGrowSize, nInitAllocationCount);
}

template< class T >
CUtlFixedMemory<T>::~CUtlFixedMemory()
{
	Purge();
}


//-----------------------------------------------------------------------------
// Fast swap - WARNING: Swap invalidates all ptr-based indices!!!
//-----------------------------------------------------------------------------
template< class T >
void CUtlFixedMemory<T>::Swap(CUtlFixedMemory< T > &mem)
{
	V_swap(m_pBlocks, mem.m_pBlocks);
	V_swap(m_nAllocationCount, mem.m_nAllocationCount);
	V_swap(m_nGrowSize, mem.m_nGrowSize);
}


//-----------------------------------------------------------------------------
// Set the size by which the memory grows - round up to the next power of 2
//-----------------------------------------------------------------------------
template< class T >
void CUtlFixedMemory<T>::Init(int nGrowSize /* = 0 */, int nInitSize /* = 0 */)
{
	Purge();

	m_nGrowSize = nGrowSize;

	Grow(nInitSize);
}

//-----------------------------------------------------------------------------
// element access
//-----------------------------------------------------------------------------
template< class T >
inline T& CUtlFixedMemory<T>::operator[](intp i)
{
	return *(T*)i;
}

template< class T >
inline const T& CUtlFixedMemory<T>::operator[](intp i) const
{
	return *(T*)i;
}

template< class T >
inline T& CUtlFixedMemory<T>::Element(intp i)
{
	return *(T*)i;
}

template< class T >
inline const T& CUtlFixedMemory<T>::Element(intp i) const
{
	return *(T*)i;
}


//-----------------------------------------------------------------------------
// Size
//-----------------------------------------------------------------------------
template< class T >
inline int CUtlFixedMemory<T>::NumAllocated() const
{
	return m_nAllocationCount;
}


//-----------------------------------------------------------------------------
// Is element index valid?
//-----------------------------------------------------------------------------
template< class T >
inline bool CUtlFixedMemory<T>::IsIdxValid(intp i) const
{
#ifdef _DEBUG
	for (BlockHeader_t *pbh = m_pBlocks; pbh; pbh = pbh->m_pNext)
	{
		if (IsInBlock(i, pbh))
			return true;
	}
	return false;
#else
	return i != InvalidIndex();
#endif
}

template< class T >
void CUtlFixedMemory<T>::Grow(int num)
{
	if (num <= 0)
		return;

	int nBlockSize = m_nGrowSize;
	if (nBlockSize == 0)
	{
		if (m_nAllocationCount)
		{
			nBlockSize = m_nAllocationCount;
		}
		else
		{
			// Compute an allocation which is at least as big as a cache line...
			nBlockSize = (31 + sizeof(T)) / sizeof(T);
		}
	}
	if (nBlockSize < num)
	{
		int n = (num + nBlockSize - 1) / nBlockSize;
		nBlockSize *= n;
	}
	m_nAllocationCount += nBlockSize;

	BlockHeader_t *  pBlockHeader = (BlockHeader_t*)malloc(sizeof(BlockHeader_t) + nBlockSize * sizeof(T));
	if (!pBlockHeader)
	{
		print("CUtlFixedMemory overflow!\n");
	}
	pBlockHeader->m_pNext = NULL;
	pBlockHeader->m_nBlockSize = nBlockSize;

	if (!m_pBlocks)
	{
		m_pBlocks = pBlockHeader;
	}
	else
	{
#if 1	// IsIdxAfter assumes that newly allocated blocks are at the end
		BlockHeader_t *  pbh = m_pBlocks;
		while (pbh->m_pNext)
		{
			pbh = pbh->m_pNext;
		}
		pbh->m_pNext = pBlockHeader;
#else
		pBlockHeader = m_pBlocks;
		pBlockHeader->m_pNext = m_pBlocks;
#endif
	}
}


//-----------------------------------------------------------------------------
// Makes sure we've got at least this much memory
//-----------------------------------------------------------------------------
template< class T >
inline void CUtlFixedMemory<T>::EnsureCapacity(int num)
{
	Grow(num - NumAllocated());
}


//-----------------------------------------------------------------------------
// Memory deallocation
//-----------------------------------------------------------------------------
template< class T >
void CUtlFixedMemory<T>::Purge()
{
	if (!m_pBlocks)
		return;

	for (BlockHeader_t *pbh = m_pBlocks; pbh; )
	{
		BlockHeader_t *pFree = pbh;
		pbh = pbh->m_pNext;
		free(pFree);
	}
	m_pBlocks = NULL;
	m_nAllocationCount = 0;
}


#define FOR_EACH_LL( listName, iteratorName ) \
	for( int iteratorName=(listName).Head(); (listName).IsUtlLinkedList && iteratorName != (listName).InvalidIndex(); iteratorName = (listName).Next( iteratorName ) )

//-----------------------------------------------------------------------------
// class CUtlLinkedList:
// description:
//		A lovely index-based linked list! T is the class type, I is the index
//		type, which usually should be an unsigned short or smaller. However,
//		you must avoid using 16- or 8-bit arithmetic on PowerPC architectures; 
//		therefore you should not use UtlLinkedListElem_t::I as the type of 
//		a local variable... ever. PowerPC integer arithmetic must be 32- or 
//		64-bit only; otherwise performance plummets.
//-----------------------------------------------------------------------------

template <class T, class I>
struct UtlLinkedListElem_t
{
	T  m_Element;
	I  m_Previous;
	I  m_Next;

private:
	// No copy constructor for these...
	UtlLinkedListElem_t(const UtlLinkedListElem_t&);
};


// Class S is the storage type; the type you can use to save off indices in 
// persistent memory. Class I is the iterator type, which is what should be used
// in local scopes. I defaults to be S, but be aware that on the 360, 16-bit 
// arithmetic is catastrophically slow. Therefore you should try to save shorts
// in memory, but always operate on 32's or 64's in local scope.
// The ideal parameter order would be TSMI (you are more likely to override M than I)
// but since M depends on I we can't have the defaults in that order, alas.
template <class T, class S = unsigned short, bool ML = false, class I = S, class M = CUtlMemory< UtlLinkedListElem_t<T, S>, I > >
class CUtlLinkedList
{
public:
	typedef T ElemType_t;
	typedef S IndexType_t; // should really be called IndexStorageType_t, but that would be a huge change
	typedef I IndexLocalType_t;
	typedef M MemoryAllocator_t;
	static const bool IsUtlLinkedList = true; // Used to match this at compiletime 

	// constructor, destructor
	CUtlLinkedList(int growSize = 0, int initSize = 0);
	~CUtlLinkedList();

	// gets particular elements
	T&         Element(I i);
	T const&   Element(I i) const;
	T&         operator[](I i);
	T const&   operator[](I i) const;

	// Make sure we have a particular amount of memory
	void EnsureCapacity(int num);

	void SetGrowSize(int growSize);

	// Memory deallocation
	void Purge();

	// Delete all the elements then call Purge.
	void PurgeAndDeleteElements();

	// Insertion methods....
	I	InsertBefore(I before);
	I	InsertAfter(I after);
	I	AddToHead();
	I	AddToTail();

	I	InsertBefore(I before, T const& src);
	I	InsertAfter(I after, T const& src);
	I	AddToHead(T const& src);
	I	AddToTail(T const& src);

	// Find an element and return its index or InvalidIndex() if it couldn't be found.
	I		Find(const T &src) const;

	// Look for the element. If it exists, remove it and return true. Otherwise, return false.
	bool	FindAndRemove(const T &src);

	// Removal methods
	void	Remove(I elem);
	void	RemoveAll();

	// Allocation/deallocation methods
	// If multilist == true, then list list may contain many
	// non-connected lists, and IsInList and Head + Tail are meaningless...
	I		Alloc(bool multilist = false);
	void	Free(I elem);

	// list modification
	void	LinkBefore(I before, I elem);
	void	LinkAfter(I after, I elem);
	void	Unlink(I elem);
	void	LinkToHead(I elem);
	void	LinkToTail(I elem);

	// invalid index (M will never allocate an element at this index)
	inline static S  InvalidIndex() { return (S)M::InvalidIndex(); }

	// Is a given index valid to use? (representible by S and not the invalid index)
	static bool IndexInRange(I index);

	inline static size_t ElementSize() { return sizeof(ListElem_t); }

	// list statistics
	int	Count() const;
	I	MaxElementIndex() const;
	I	NumAllocated(void) const { return m_NumAlloced; }

	// Traversing the list
	I  Head() const;
	I  Tail() const;
	I  Previous(I i) const;
	I  Next(I i) const;

	// STL compatible const_iterator class
	template < typename List_t >
	class _CUtlLinkedList_constiterator_t
	{
	public:
		typedef typename List_t::ElemType_t ElemType_t;
		typedef typename List_t::IndexType_t IndexType_t;

		// Default constructor -- gives a currently unusable iterator.
		_CUtlLinkedList_constiterator_t()
			: m_list(0)
			, m_index(List_t::InvalidIndex())
		{
		}
		// Normal constructor.
		_CUtlLinkedList_constiterator_t(const List_t& list, IndexType_t index)
			: m_list(&list)
			, m_index(index)
		{
		}

		// Pre-increment operator++. This is the most efficient increment
		// operator so it should always be used.
		_CUtlLinkedList_constiterator_t& operator++()
		{
			m_index = m_list->Next(m_index);
			return *this;
		}
		// Post-increment operator++. This is less efficient than pre-increment.
		_CUtlLinkedList_constiterator_t operator++(int)
		{
			// Copy ourselves.
			_CUtlLinkedList_constiterator_t temp = *this;
			// Increment ourselves.
			++*this;
			// Return the copy.
			return temp;
		}

		// Pre-decrement operator--. This is the most efficient decrement
		// operator so it should always be used.
		_CUtlLinkedList_constiterator_t& operator--()
		{
			Assert(m_index != m_list->Head());
			if (m_index == m_list->InvalidIndex())
			{
				m_index = m_list->Tail();
			}
			else
			{
				m_index = m_list->Previous(m_index);
			}
			return *this;
		}
		// Post-decrement operator--. This is less efficient than post-decrement.
		_CUtlLinkedList_constiterator_t operator--(int)
		{
			// Copy ourselves.
			_CUtlLinkedList_constiterator_t temp = *this;
			// Decrement ourselves.
			--*this;
			// Return the copy.
			return temp;
		}

		bool operator==(const _CUtlLinkedList_constiterator_t& other) const
		{
			Assert(m_list == other.m_list);
			return m_index == other.m_index;
		}

		bool operator!=(const _CUtlLinkedList_constiterator_t& other) const
		{
			Assert(m_list == other.m_list);
			return m_index != other.m_index;
		}

		const ElemType_t& operator*() const
		{
			return m_list->Element(m_index);
		}

		const ElemType_t* operator->() const
		{
			return (&**this);
		}

	protected:
		// Use a pointer rather than a reference so that we can support
		// assignment of iterators.
		const List_t* m_list;
		IndexType_t m_index;
	};

	// STL compatible iterator class, using derivation so that a non-const
	// list can return a const_iterator.
	template < typename List_t >
	class _CUtlLinkedList_iterator_t : public _CUtlLinkedList_constiterator_t< List_t >
	{
	public:
		typedef typename List_t::ElemType_t ElemType_t;
		typedef typename List_t::IndexType_t IndexType_t;
		typedef _CUtlLinkedList_constiterator_t< List_t > Base;

		// Default constructor -- gives a currently unusable iterator.
		_CUtlLinkedList_iterator_t()
		{
		}
		// Normal constructor.
		_CUtlLinkedList_iterator_t(const List_t& list, IndexType_t index)
			: _CUtlLinkedList_constiterator_t< List_t >(list, index)
		{
		}

		// Pre-increment operator++. This is the most efficient increment
		// operator so it should always be used.
		_CUtlLinkedList_iterator_t& operator++()
		{
			Base::m_index = Base::m_list->Next(Base::m_index);
			return *this;
		}
		// Post-increment operator++. This is less efficient than pre-increment.
		_CUtlLinkedList_iterator_t operator++(int)
		{
			// Copy ourselves.
			_CUtlLinkedList_iterator_t temp = *this;
			// Increment ourselves.
			++*this;
			// Return the copy.
			return temp;
		}

		// Pre-decrement operator--. This is the most efficient decrement
		// operator so it should always be used.
		_CUtlLinkedList_iterator_t& operator--()
		{
			Assert(Base::m_index != Base::m_list->Head());
			if (Base::m_index == Base::m_list->InvalidIndex())
			{
				Base::m_index = Base::m_list->Tail();
			}
			else
			{
				Base::m_index = Base::m_list->Previous(Base::m_index);
			}
			return *this;
		}
		// Post-decrement operator--. This is less efficient than post-decrement.
		_CUtlLinkedList_iterator_t operator--(int)
		{
			// Copy ourselves.
			_CUtlLinkedList_iterator_t temp = *this;
			// Decrement ourselves.
			--*this;
			// Return the copy.
			return temp;
		}

		ElemType_t& operator*() const
		{
			// Const_cast to allow sharing the implementation with the
			// base class.
			List_t* pMutableList = const_cast<List_t*>(Base::m_list);
			return pMutableList->Element(Base::m_index);
		}

		ElemType_t* operator->() const
		{
			return (&**this);
		}
	};

	typedef _CUtlLinkedList_constiterator_t<CUtlLinkedList<T, S, ML, I, M> > const_iterator;
	typedef _CUtlLinkedList_iterator_t<CUtlLinkedList<T, S, ML, I, M> > iterator;
	const_iterator begin() const
	{
		return const_iterator(*this, Head());
	}
	iterator begin()
	{
		return iterator(*this, Head());
	}

	const_iterator end() const
	{
		return const_iterator(*this, InvalidIndex());
	}
	iterator end()
	{
		return iterator(*this, InvalidIndex());
	}

	// Are nodes in the list or valid?
	bool  IsValidIndex(I i) const;
	bool  IsInList(I i) const;

protected:

	// What the linked list element looks like
	typedef UtlLinkedListElem_t<T, S>  ListElem_t;

	// constructs the class
	I		AllocInternal(bool multilist = false);
	void ConstructList();

	// Gets at the list element....
	ListElem_t& InternalElement(I i) { return m_Memory[i]; }
	ListElem_t const& InternalElement(I i) const { return m_Memory[i]; }

	// copy constructors not allowed
	CUtlLinkedList(CUtlLinkedList<T, S, ML, I, M> const& list) { }

	M	m_Memory;
	I	m_Head;
	I	m_Tail;
	I	m_FirstFree;
	I	m_ElementCount;		// The number actually in the list
	I	m_NumAlloced;		// The number of allocated elements
	typename M::Iterator_t	m_LastAlloc; // the last index allocated

	// For debugging purposes; 
	// it's in release builds so this can be used in libraries correctly
	ListElem_t  *m_pElements;

	FORCEINLINE M const &Memory(void) const
	{
		return m_Memory;
	}

	void ResetDbgInfo()
	{
		m_pElements = m_Memory.Base();
	}

private:
	// Faster version of Next that can only be used from tested code internal
	// to this class, such as Find(). It avoids the cost of checking the index
	// validity, which is a big win on debug builds.
	I  PrivateNext(I i) const;
};


// this is kind of ugly, but until C++ gets templatized typedefs in C++0x, it's our only choice
template < class T >
class CUtlFixedLinkedList : public CUtlLinkedList< T, int, true, int, CUtlFixedMemory< UtlLinkedListElem_t< T, int > > >
{
public:
	CUtlFixedLinkedList(int growSize = 0, int initSize = 0)
		: CUtlLinkedList< T, int, true, int, CUtlFixedMemory< UtlLinkedListElem_t< T, int > > >(growSize, initSize) {}

	typedef CUtlLinkedList< T, int, true, int, CUtlFixedMemory< UtlLinkedListElem_t< T, int > > > BaseClass;
	bool IsValidIndex(int i) const
	{
		if (!BaseClass::Memory().IsIdxValid(i))
			return false;

#ifdef _DEBUG // it's safe to skip this here, since the only way to get indices after m_LastAlloc is to use MaxElementIndex
		if (BaseClass::Memory().IsIdxAfter(i, this->m_LastAlloc))
		{
			Assert(0);
			return false; // don't read values that have been allocated, but not constructed
		}
#endif

		return (BaseClass::Memory()[i].m_Previous != i) || (BaseClass::Memory()[i].m_Next == i);
	}

private:
	int	MaxElementIndex() const { return BaseClass::InvalidIndex(); } // fixedmemory containers don't support iteration from 0..maxelements-1
	void ResetDbgInfo() {}
};

// this is kind of ugly, but until C++ gets templatized typedefs in C++0x, it's our only choice
template < class T, class I = unsigned short >
class CUtlBlockLinkedList : public CUtlLinkedList< T, I, true, I, CUtlBlockMemory< UtlLinkedListElem_t< T, I >, I > >
{
public:
	CUtlBlockLinkedList(int growSize = 0, int initSize = 0)
		: CUtlLinkedList< T, I, true, I, CUtlBlockMemory< UtlLinkedListElem_t< T, I >, I > >(growSize, initSize) {}
protected:
	void ResetDbgInfo() {}
};


//-----------------------------------------------------------------------------
// constructor, destructor
//-----------------------------------------------------------------------------

template <class T, class S, bool ML, class I, class M>
CUtlLinkedList<T, S, ML, I, M>::CUtlLinkedList(int growSize, int initSize) :
	m_Memory(growSize, initSize), m_LastAlloc(m_Memory.InvalidIterator())
{
	// Prevent signed non-int datatypes
	ConstructList();
	ResetDbgInfo();
}

template <class T, class S, bool ML, class I, class M>
CUtlLinkedList<T, S, ML, I, M>::~CUtlLinkedList()
{
	RemoveAll();
}

template <class T, class S, bool ML, class I, class M>
void CUtlLinkedList<T, S, ML, I, M>::ConstructList()
{
	m_Head = InvalidIndex();
	m_Tail = InvalidIndex();
	m_FirstFree = InvalidIndex();
	m_ElementCount = 0;
	m_NumAlloced = 0;
}


//-----------------------------------------------------------------------------
// gets particular elements
//-----------------------------------------------------------------------------

template <class T, class S, bool ML, class I, class M>
inline T& CUtlLinkedList<T, S, ML, I, M>::Element(I i)
{
	return m_Memory[i].m_Element;
}

template <class T, class S, bool ML, class I, class M>
inline T const& CUtlLinkedList<T, S, ML, I, M>::Element(I i) const
{
	return m_Memory[i].m_Element;
}

template <class T, class S, bool ML, class I, class M>
inline T& CUtlLinkedList<T, S, ML, I, M>::operator[](I i)
{
	return m_Memory[i].m_Element;
}

template <class T, class S, bool ML, class I, class M>
inline T const& CUtlLinkedList<T, S, ML, I, M>::operator[](I i) const
{
	return m_Memory[i].m_Element;
}

//-----------------------------------------------------------------------------
// list statistics
//-----------------------------------------------------------------------------

template <class T, class S, bool ML, class I, class M>
inline int CUtlLinkedList<T, S, ML, I, M>::Count() const
{
#ifdef MULTILIST_PEDANTIC_ASSERTS
	AssertMsg(!ML, "CUtlLinkedList::Count() is meaningless for linked lists.");
#endif
	return m_ElementCount;
}

template <class T, class S, bool ML, class I, class M>
inline I CUtlLinkedList<T, S, ML, I, M>::MaxElementIndex() const
{
	return m_Memory.NumAllocated();
}


//-----------------------------------------------------------------------------
// Traversing the list
//-----------------------------------------------------------------------------

template <class T, class S, bool ML, class I, class M>
inline I  CUtlLinkedList<T, S, ML, I, M>::Head() const
{
	return m_Head;
}

template <class T, class S, bool ML, class I, class M>
inline I  CUtlLinkedList<T, S, ML, I, M>::Tail() const
{
	return m_Tail;
}

template <class T, class S, bool ML, class I, class M>
inline I  CUtlLinkedList<T, S, ML, I, M>::Previous(I i) const
{
	return InternalElement(i).m_Previous;
}

template <class T, class S, bool ML, class I, class M>
inline I  CUtlLinkedList<T, S, ML, I, M>::Next(I i) const
{
	return InternalElement(i).m_Next;
}

template <class T, class S, bool ML, class I, class M>
inline I  CUtlLinkedList<T, S, ML, I, M>::PrivateNext(I i) const
{
	return InternalElement(i).m_Next;
}


//-----------------------------------------------------------------------------
// Are nodes in the list or valid?
//-----------------------------------------------------------------------------

#pragma warning(push)
#pragma warning( disable: 4310 ) // Allows "(I)(S)M::INVALID_INDEX" below
template <class T, class S, bool ML, class I, class M>
inline bool CUtlLinkedList<T, S, ML, I, M>::IndexInRange(I index) // Static method
{
	// Since S is not necessarily the type returned by M, we need to check that M returns indices
	// which are representable by S. A common case is 'S === unsigned short', 'I == int', in which
	// case CUtlMemory will have 'InvalidIndex == (int)-1' (which casts to 65535 in S), and will
	// happily return elements at index 65535 and above.

	// Do some static checks here:
	//  'I' needs to be able to store 'S'
	COMPILE_TIME_ASSERT(sizeof(I) >= sizeof(S));
	//  'S' should be unsigned (to avoid signed arithmetic errors for plausibly exhaustible ranges)
	COMPILE_TIME_ASSERT((sizeof(S) > 2) || (((S)-1) > 0));
	//  M::INVALID_INDEX should be storable in S to avoid ambiguities (e.g. with 65536)
	COMPILE_TIME_ASSERT((M::INVALID_INDEX == -1) || (M::INVALID_INDEX == (S)M::INVALID_INDEX));

	return (((S)index == index) && ((S)index != InvalidIndex()));
}
#pragma warning(pop)

template <class T, class S, bool ML, class I, class M>
inline bool CUtlLinkedList<T, S, ML, I, M>::IsValidIndex(I i) const
{
	if (!m_Memory.IsIdxValid(i))
		return false;

	if (m_Memory.IsIdxAfter(i, m_LastAlloc))
		return false; // don't read values that have been allocated, but not constructed

	return (m_Memory[i].m_Previous != i) || (m_Memory[i].m_Next == i);
}

template <class T, class S, bool ML, class I, class M>
inline bool CUtlLinkedList<T, S, ML, I, M>::IsInList(I i) const
{
	if (!m_Memory.IsIdxValid(i) || m_Memory.IsIdxAfter(i, m_LastAlloc))
		return false; // don't read values that have been allocated, but not constructed

	return Previous(i) != i;
}

/*
template <class T>
inline bool CUtlFixedLinkedList<T>::IsInList( int i ) const
{
	return m_Memory.IsIdxValid( i ) && (Previous( i ) != i);
}
*/

//-----------------------------------------------------------------------------
// Makes sure we have enough memory allocated to store a requested # of elements
//-----------------------------------------------------------------------------

template< class T, class S, bool ML, class I, class M >
void CUtlLinkedList<T, S, ML, I, M>::EnsureCapacity(int num)
{
	m_Memory.EnsureCapacity(num);
	ResetDbgInfo();
}

template< class T, class S, bool ML, class I, class M >
void CUtlLinkedList<T, S, ML, I, M>::SetGrowSize(int growSize)
{
	RemoveAll();
	m_Memory.Init(growSize);
	ResetDbgInfo();
}


//-----------------------------------------------------------------------------
// Deallocate memory
//-----------------------------------------------------------------------------

template <class T, class S, bool ML, class I, class M>
void  CUtlLinkedList<T, S, ML, I, M>::Purge()
{
	RemoveAll();

	m_Memory.Purge();
	m_FirstFree = InvalidIndex();
	m_NumAlloced = 0;

	//Routing "m_LastAlloc = m_Memory.InvalidIterator();" through a local const to sidestep an internal compiler error on 360 builds
	const typename M::Iterator_t scInvalidIterator = m_Memory.InvalidIterator();
	m_LastAlloc = scInvalidIterator;
	ResetDbgInfo();
}


template<class T, class S, bool ML, class I, class M>
void CUtlLinkedList<T, S, ML, I, M>::PurgeAndDeleteElements()
{
	I iNext;
	for (I i = Head(); i != InvalidIndex(); i = iNext)
	{
		iNext = Next(i);
		delete Element(i);
	}

	Purge();
}


//-----------------------------------------------------------------------------
// Node allocation/deallocation
//-----------------------------------------------------------------------------
template <class T, class S, bool ML, class I, class M>
I CUtlLinkedList<T, S, ML, I, M>::AllocInternal(bool multilist)
{
	Assert(!multilist || ML);
#ifdef MULTILIST_PEDANTIC_ASSERTS
	Assert(multilist == ML);
#endif
	I elem;
	if (m_FirstFree == InvalidIndex())
	{
		Assert(m_Memory.IsValidIterator(m_LastAlloc) || m_ElementCount == 0);

		typename M::Iterator_t it = m_Memory.IsValidIterator(m_LastAlloc) ? m_Memory.Next(m_LastAlloc) : m_Memory.First();

		if (!m_Memory.IsValidIterator(it))
		{
			m_Memory.Grow();
			ResetDbgInfo();

			it = m_Memory.IsValidIterator(m_LastAlloc) ? m_Memory.Next(m_LastAlloc) : m_Memory.First();

			Assert(m_Memory.IsValidIterator(it));
			if (!m_Memory.IsValidIterator(it))
			{
				// We rarely if ever handle alloc failure. Continuing leads to corruption.
				print("CUtlLinkedList overflow! (exhausted memory allocator)\n");
				return InvalidIndex();
			}
		}

		// We can overflow before the utlmemory overflows, since S != I
		if (!IndexInRange(m_Memory.GetIndex(it)))
		{
			// We rarely if ever handle alloc failure. Continuing leads to corruption.
			print("CUtlLinkedList overflow! (exhausted index range)\n");
			return InvalidIndex();
		}

		m_LastAlloc = it;
		elem = m_Memory.GetIndex(m_LastAlloc);
		m_NumAlloced++;
	}
	else
	{
		elem = m_FirstFree;
		m_FirstFree = InternalElement(m_FirstFree).m_Next;
	}

	if (!multilist)
	{
		InternalElement(elem).m_Next = elem;
		InternalElement(elem).m_Previous = elem;
	}
	else
	{
		InternalElement(elem).m_Next = InvalidIndex();
		InternalElement(elem).m_Previous = InvalidIndex();
	}

	return elem;
}

template <class T, class S, bool ML, class I, class M>
I CUtlLinkedList<T, S, ML, I, M>::Alloc(bool multilist)
{
	I elem = AllocInternal(multilist);
	if (elem == InvalidIndex())
		return elem;

	Construct(&Element(elem));

	return elem;
}

template <class T, class S, bool ML, class I, class M>
void  CUtlLinkedList<T, S, ML, I, M>::Free(I elem)
{
	Assert(IsValidIndex(elem) && IndexInRange(elem));
	Unlink(elem);

	ListElem_t &internalElem = InternalElement(elem);
	Destruct(&internalElem.m_Element);
	internalElem.m_Next = m_FirstFree;
	m_FirstFree = elem;
}

//-----------------------------------------------------------------------------
// Insertion methods; allocates and links (uses default constructor)
//-----------------------------------------------------------------------------

template <class T, class S, bool ML, class I, class M>
I CUtlLinkedList<T, S, ML, I, M>::InsertBefore(I before)
{
	// Make a new node
	I   newNode = AllocInternal();
	if (newNode == InvalidIndex())
		return newNode;

	// Link it in
	LinkBefore(before, newNode);

	// Construct the data
	Construct(&Element(newNode));

	return newNode;
}

template <class T, class S, bool ML, class I, class M>
I CUtlLinkedList<T, S, ML, I, M>::InsertAfter(I after)
{
	// Make a new node
	I   newNode = AllocInternal();
	if (newNode == InvalidIndex())
		return newNode;

	// Link it in
	LinkAfter(after, newNode);

	// Construct the data
	Construct(&Element(newNode));

	return newNode;
}

template <class T, class S, bool ML, class I, class M>
inline I CUtlLinkedList<T, S, ML, I, M>::AddToHead()
{
	return InsertAfter(InvalidIndex());
}

template <class T, class S, bool ML, class I, class M>
inline I CUtlLinkedList<T, S, ML, I, M>::AddToTail()
{
	return InsertBefore(InvalidIndex());
}


//-----------------------------------------------------------------------------
// Insertion methods; allocates and links (uses copy constructor)
//-----------------------------------------------------------------------------

template <class T, class S, bool ML, class I, class M>
I CUtlLinkedList<T, S, ML, I, M>::InsertBefore(I before, T const& src)
{
	// Make a new node
	I   newNode = AllocInternal();
	if (newNode == InvalidIndex())
		return newNode;

	// Link it in
	LinkBefore(before, newNode);

	// Construct the data
	CopyConstruct(&Element(newNode), src);

	return newNode;
}

template <class T, class S, bool ML, class I, class M>
I CUtlLinkedList<T, S, ML, I, M>::InsertAfter(I after, T const& src)
{
	// Make a new node
	I   newNode = AllocInternal();
	if (newNode == InvalidIndex())
		return newNode;

	// Link it in
	LinkAfter(after, newNode);

	// Construct the data
	CopyConstruct(&Element(newNode), src);

	return newNode;
}

template <class T, class S, bool ML, class I, class M>
inline I CUtlLinkedList<T, S, ML, I, M>::AddToHead(T const& src)
{
	return InsertAfter(InvalidIndex(), src);
}

template <class T, class S, bool ML, class I, class M>
inline I CUtlLinkedList<T, S, ML, I, M>::AddToTail(T const& src)
{
	return InsertBefore(InvalidIndex(), src);
}


//-----------------------------------------------------------------------------
// Removal methods
//-----------------------------------------------------------------------------

template<class T, class S, bool ML, class I, class M>
I CUtlLinkedList<T, S, ML, I, M>::Find(const T &src) const
{
	// Cache the invalidIndex to avoid two levels of function calls on each iteration.
	I invalidIndex = InvalidIndex();
	for (I i = Head(); i != invalidIndex; i = PrivateNext(i))
	{
		if (Element(i) == src)
			return i;
	}
	return InvalidIndex();
}


template<class T, class S, bool ML, class I, class M>
bool CUtlLinkedList<T, S, ML, I, M>::FindAndRemove(const T &src)
{
	I i = Find(src);
	if (i == InvalidIndex())
	{
		return false;
	}
	else
	{
		Remove(i);
		return true;
	}
}


template <class T, class S, bool ML, class I, class M>
void  CUtlLinkedList<T, S, ML, I, M>::Remove(I elem)
{
	Free(elem);
}

template <class T, class S, bool ML, class I, class M>
void  CUtlLinkedList<T, S, ML, I, M>::RemoveAll()
{
	// Have to do some convoluted stuff to invoke the destructor on all
	// valid elements for the multilist case (since we don't have all elements
	// connected to each other in a list).

	if (m_LastAlloc == m_Memory.InvalidIterator())
	{
		return;
	}

	if (ML)
	{
		for (typename M::Iterator_t it = m_Memory.First(); it != m_Memory.InvalidIterator(); it = m_Memory.Next(it))
		{
			I i = m_Memory.GetIndex(it);
			if (IsValidIndex(i)) // skip elements already in the free list
			{
				ListElem_t &internalElem = InternalElement(i);
				internalElem.m_Previous = i;
				internalElem.m_Next = m_FirstFree;
				m_FirstFree = i;
			}

			if (it == m_LastAlloc)
				break; // don't destruct elements that haven't ever been constructed
		}
	}
	else
	{
		I i = Head();
		I next;
		while (i != InvalidIndex())
		{
			next = Next(i);
			ListElem_t &internalElem = InternalElement(i);
			internalElem.m_Previous = i;
			internalElem.m_Next = next == InvalidIndex() ? m_FirstFree : next;
			i = next;
		}
		if (Head() != InvalidIndex())
		{
			m_FirstFree = Head();
		}
	}

	// Clear everything else out
	m_Head = InvalidIndex();
	m_Tail = InvalidIndex();
	m_ElementCount = 0;
}


//-----------------------------------------------------------------------------
// list modification
//-----------------------------------------------------------------------------

template <class T, class S, bool ML, class I, class M>
void  CUtlLinkedList<T, S, ML, I, M>::LinkBefore(I before, I elem)
{
	Assert(IsValidIndex(elem));

	// Unlink it if it's in the list at the moment
	Unlink(elem);

	ListElem_t * pNewElem = &InternalElement(elem);

	// The element *after* our newly linked one is the one we linked before.
	pNewElem->m_Next = before;

	S newElem_mPrevious; // we need to hang on to this for the compairson against InvalidIndex()
					// below; otherwise we get a a load-hit-store on pNewElem->m_Previous, even
					// with RESTRICT
	if (before == InvalidIndex())
	{
		// In this case, we're linking to the end of the list, so reset the tail
		newElem_mPrevious = m_Tail;
		pNewElem->m_Previous = m_Tail;
		m_Tail = elem;
	}
	else
	{
		// Here, we're not linking to the end. Set the prev pointer to point to
		// the element we're linking.
		Assert(IsInList(before));
		ListElem_t * beforeElem = &InternalElement(before);
		pNewElem->m_Previous = newElem_mPrevious = beforeElem->m_Previous;
		beforeElem->m_Previous = elem;
	}

	// Reset the head if we linked to the head of the list
	if (newElem_mPrevious == InvalidIndex())
		m_Head = elem;
	else
		InternalElement(newElem_mPrevious).m_Next = elem;

	// one more element baby
	++m_ElementCount;
}

template <class T, class S, bool ML, class I, class M>
void  CUtlLinkedList<T, S, ML, I, M>::LinkAfter(I after, I elem)
{
	Assert(IsValidIndex(elem));

	// Unlink it if it's in the list at the moment
	if (IsInList(elem))
		Unlink(elem);

	ListElem_t& newElem = InternalElement(elem);

	// The element *before* our newly linked one is the one we linked after
	newElem.m_Previous = after;
	if (after == InvalidIndex())
	{
		// In this case, we're linking to the head of the list, reset the head
		newElem.m_Next = m_Head;
		m_Head = elem;
	}
	else
	{
		// Here, we're not linking to the end. Set the next pointer to point to
		// the element we're linking.
		Assert(IsInList(after));
		ListElem_t& afterElem = InternalElement(after);
		newElem.m_Next = afterElem.m_Next;
		afterElem.m_Next = elem;
	}

	// Reset the tail if we linked to the tail of the list
	if (newElem.m_Next == InvalidIndex())
		m_Tail = elem;
	else
		InternalElement(newElem.m_Next).m_Previous = elem;

	// one more element baby
	++m_ElementCount;
}

template <class T, class S, bool ML, class I, class M>
void  CUtlLinkedList<T, S, ML, I, M>::Unlink(I elem)
{
	Assert(IsValidIndex(elem));
	if (IsInList(elem))
	{
		ListElem_t * pOldElem = &m_Memory[elem];

		// If we're the first guy, reset the head
		// otherwise, make our previous node's next pointer = our next
		if (pOldElem->m_Previous != InvalidIndex())
		{
			m_Memory[pOldElem->m_Previous].m_Next = pOldElem->m_Next;
		}
		else
		{
			m_Head = pOldElem->m_Next;
		}

		// If we're the last guy, reset the tail
		// otherwise, make our next node's prev pointer = our prev
		if (pOldElem->m_Next != InvalidIndex())
		{
			m_Memory[pOldElem->m_Next].m_Previous = pOldElem->m_Previous;
		}
		else
		{
			m_Tail = pOldElem->m_Previous;
		}

		// This marks this node as not in the list, 
		// but not in the free list either
		pOldElem->m_Previous = pOldElem->m_Next = elem;

		// One less puppy
		--m_ElementCount;
	}
}

template <class T, class S, bool ML, class I, class M>
inline void CUtlLinkedList<T, S, ML, I, M>::LinkToHead(I elem)
{
	LinkAfter(InvalidIndex(), elem);
}

template <class T, class S, bool ML, class I, class M>
inline void CUtlLinkedList<T, S, ML, I, M>::LinkToTail(I elem)
{
	LinkBefore(InvalidIndex(), elem);
}


//-----------------------------------------------------------------------------
// Class to drop in to replace a CUtlLinkedList that needs to be more memory agressive
//-----------------------------------------------------------------------------

DECLARE_POINTER_HANDLE(UtlPtrLinkedListIndex_t); // to enforce correct usage

template < typename T >
class CUtlPtrLinkedList
{
public:
	CUtlPtrLinkedList()
		: m_pFirst(NULL),
		m_nElems(0)
	{
		COMPILE_TIME_ASSERT(sizeof(IndexType_t) == sizeof(Node_t *));
	}

	~CUtlPtrLinkedList()
	{
		RemoveAll();
	}

	typedef UtlPtrLinkedListIndex_t IndexType_t;

	T &operator[](IndexType_t i)
	{
		return ((Node_t *)i)->elem;
	}

	const T &operator[](IndexType_t i) const
	{
		return ((Node_t *)i)->elem;
	}

	IndexType_t	AddToTail()
	{
		return DoInsertBefore((IndexType_t)m_pFirst, NULL);
	}

	IndexType_t	AddToTail(T const& src)
	{
		return DoInsertBefore((IndexType_t)m_pFirst, &src);
	}

	IndexType_t	AddToHead()
	{
		IndexType_t result = DoInsertBefore((IndexType_t)m_pFirst, NULL);
		m_pFirst = ((Node_t *)result);
		return result;
	}

	IndexType_t	AddToHead(T const& src)
	{
		IndexType_t result = DoInsertBefore((IndexType_t)m_pFirst, &src);
		m_pFirst = ((Node_t *)result);
		return result;
	}

	IndexType_t InsertBefore(IndexType_t before)
	{
		return DoInsertBefore(before, NULL);
	}

	IndexType_t InsertAfter(IndexType_t after)
	{
		Node_t *pBefore = ((Node_t *)after)->next;
		return DoInsertBefore(pBefore, NULL);
	}

	IndexType_t InsertBefore(IndexType_t before, T const& src)
	{
		return DoInsertBefore(before, &src);
	}

	IndexType_t InsertAfter(IndexType_t after, T const& src)
	{
		Node_t *pBefore = ((Node_t *)after)->next;
		return DoInsertBefore(pBefore, &src);
	}

	void Remove(IndexType_t elem)
	{
		Node_t *p = (Node_t *)elem;

		if (p->pNext == p)
		{
			m_pFirst = NULL;
		}
		else
		{
			if (m_pFirst == p)
			{
				m_pFirst = p->pNext;
			}
			p->pNext->pPrev = p->pPrev;
			p->pPrev->pNext = p->pNext;
		}

		delete p;
		m_nElems--;
	}

	void RemoveAll()
	{
		Node_t *p = m_pFirst;
		if (p)
		{
			do
			{
				Node_t *pNext = p->pNext;
				delete p;
				p = pNext;
			} while (p != m_pFirst);
		}

		m_pFirst = NULL;
		m_nElems = 0;
	}

	int	Count() const
	{
		return m_nElems;
	}

	IndexType_t Head() const
	{
		return (IndexType_t)m_pFirst;
	}

	IndexType_t Next(IndexType_t i) const
	{
		Node_t *p = ((Node_t *)i)->pNext;
		if (p != m_pFirst)
		{
			return (IndexType_t)p;
		}
		return NULL;
	}

	bool IsValidIndex(IndexType_t i) const
	{
		Node_t *p = ((Node_t *)i);
		return (p && p->pNext && p->pPrev);
	}

	inline static IndexType_t  InvalidIndex()
	{
		return NULL;
	}
private:

	struct Node_t
	{
		Node_t() {}
		Node_t(const T &_elem) : elem(_elem) {}

		T elem;
		Node_t *pPrev, *pNext;
	};

	Node_t *AllocNode(const T *pCopyFrom)
	{
		Node_t *p;

		if (!pCopyFrom)
		{
			p = new Node_t;
		}
		else
		{
			p = new Node_t(*pCopyFrom);
		}

		return p;
	}

	IndexType_t DoInsertBefore(IndexType_t before, const T *pCopyFrom)
	{
		Node_t *p = AllocNode(pCopyFrom);
		Node_t *pBefore = (Node_t *)before;
		if (pBefore)
		{
			p->pNext = pBefore;
			p->pPrev = pBefore->pPrev;
			pBefore->pPrev = p;
			p->pPrev->pNext = p;
		}
		else
		{
			Assert(!m_pFirst);
			m_pFirst = p->pNext = p->pPrev = p;
		}

		m_nElems++;
		return (IndexType_t)p;
	}

	Node_t *m_pFirst;
	unsigned m_nElems;
};

//-----------------------------------------------------------------------------
