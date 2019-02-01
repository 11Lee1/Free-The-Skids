//-----------------------------------------------------------------------------
// Methods to invoke the constructor, copy constructor, and destructor
//-----------------------------------------------------------------------------

template <class T>
inline T* Construct(T* pMemory)
{
	return ::new(pMemory) T;
}

template <class T, typename ARG1>
inline T* Construct(T* pMemory, ARG1 a1)
{
	return ::new(pMemory) T(a1);
}

template <class T, typename ARG1, typename ARG2>
inline T* Construct(T* pMemory, ARG1 a1, ARG2 a2)
{
	return ::new(pMemory) T(a1, a2);
}

template <class T, typename ARG1, typename ARG2, typename ARG3>
inline T* Construct(T* pMemory, ARG1 a1, ARG2 a2, ARG3 a3)
{
	return ::new(pMemory) T(a1, a2, a3);
}

template <class T, typename ARG1, typename ARG2, typename ARG3, typename ARG4>
inline T* Construct(T* pMemory, ARG1 a1, ARG2 a2, ARG3 a3, ARG4 a4)
{
	return ::new(pMemory) T(a1, a2, a3, a4);
}

template <class T, typename ARG1, typename ARG2, typename ARG3, typename ARG4, typename ARG5>
inline T* Construct(T* pMemory, ARG1 a1, ARG2 a2, ARG3 a3, ARG4 a4, ARG5 a5)
{
	return ::new(pMemory) T(a1, a2, a3, a4, a5);
}

template <class T, class P>
inline void ConstructOneArg(T* pMemory, P const& arg)
{
	::new(pMemory) T(arg);
}

template <class T, class P1, class P2 >
inline void ConstructTwoArg(T* pMemory, P1 const& arg1, P2 const& arg2)
{
	::new(pMemory) T(arg1, arg2);
}

template <class T, class P1, class P2, class P3 >
inline void ConstructThreeArg(T* pMemory, P1 const& arg1, P2 const& arg2, P3 const& arg3)
{
	::new(pMemory) T(arg1, arg2, arg3);
}

template <class T>
inline T* CopyConstruct(T* pMemory, T const& src)
{
	return ::new(pMemory) T(src);
}

template <class T>
inline void Destruct(T* pMemory)
{
	pMemory->~T();
}

inline int UtlMemory_CalcNewAllocationCount(int nAllocationCount, int nGrowSize, int nNewSize, int nBytesItem)
{
	if (nGrowSize)
	{
		nAllocationCount = ((1 + ((nNewSize - 1) / nGrowSize)) * nGrowSize);
	}
	else
	{
		if (!nAllocationCount)
		{
			// Compute an allocation which is at least as big as a cache line...
			nAllocationCount = (31 + nBytesItem) / nBytesItem;
		}

		while (nAllocationCount < nNewSize)
		{
			nAllocationCount *= 2;
		}
	}

	return nAllocationCount;
}
inline void StagingUtlVectorBoundsCheck(int i, int size)
{
	if ((unsigned)i >= (unsigned)size)
	{

	}
}

template< class T, class I = int >
class CUtlMemory
{
public:
	T& operator[](I i)
	{
		return m_pMemory[i];
	}
	T* Base();
	const T* Base() const;

	void Purge();

	bool IsExternallyAllocated() const;
	// Size
	int NumAllocated() const;
	int Count() const;
	void Grow(int num = 1);
protected:
	T* m_pMemory;
	int m_nAllocationCount;
	int m_nGrowSize;
};
template< class T, class I >
void CUtlMemory<T, I>::Purge()
{
	if (!IsExternallyAllocated())
	{
		if (m_pMemory)
		{
			free((void*)m_pMemory);
			m_pMemory = 0;
		}
		m_nAllocationCount = 0;
	}
}


template< class T, class I >
inline T* CUtlMemory<T, I>::Base()
{
	return m_pMemory;
}

template< class T, class I >
inline const T *CUtlMemory<T, I>::Base() const
{
	return m_pMemory;
}

template< class T, class I >
bool CUtlMemory<T, I>::IsExternallyAllocated() const
{
	return (m_nGrowSize < 0);
}
template< class T, class I >
inline int CUtlMemory<T, I>::NumAllocated() const
{
	return m_nAllocationCount;
}

template< class T, class I >
inline int CUtlMemory<T, I>::Count() const
{
	return m_nAllocationCount;
}
template< class T, class I >
void CUtlMemory<T, I>::Grow(int num)
{
	if (IsExternallyAllocated())
		return;


	int nAllocationRequested = m_nAllocationCount + num;


	int nNewAllocationCount = UtlMemory_CalcNewAllocationCount(m_nAllocationCount, m_nGrowSize, nAllocationRequested, sizeof(T));

	if ((int)(I)nNewAllocationCount < nAllocationRequested)
	{
		if ((int)(I)nNewAllocationCount == 0 && (int)(I)(nNewAllocationCount - 1) >= nAllocationRequested)
		{
			--nNewAllocationCount; // deal w/ the common case of m_nAllocationCount == MAX_USHORT + 1
		}
		else
		{
			if ((int)(I)nAllocationRequested != nAllocationRequested)
			{
				// we've been asked to grow memory to a size s.t. the index type can't address the requested amount of memory
				return;
			}
			while ((int)(I)nNewAllocationCount < nAllocationRequested)
			{
				nNewAllocationCount = (nNewAllocationCount + nAllocationRequested) / 2;
			}
		}
	}

	m_nAllocationCount = nNewAllocationCount;

	if (m_pMemory)
	{
		m_pMemory = (T*)realloc(m_pMemory, m_nAllocationCount * sizeof(T));
		Assert(m_pMemory);
	}
	else
	{
		m_pMemory = (T*)malloc(m_nAllocationCount * sizeof(T));
		Assert(m_pMemory);
	}
}






template <class T, class A = CUtlMemory<T>> 
class CUtlVector
{
	typedef A CAllocator;

public:
	// element access
	// element access
	T& operator[](int i);
	//const T& operator[](int i) const;
	T& Element(int i);
	const T& Element(int i) const;

	int Count() const
	{
		return m_Size;
	}
	inline void ResetDbgInfo() {}
	int AddToTail();
	int AddToTail(const T& src);
	void Remove(int elem); // preserves order, shifts elements
	void RemoveAll(); // doesn't deallocate memory
	// Memory deallocation
	void Purge();


	void ShiftElementsRight(int elem, int num = 1);

	void ShiftElementsLeft(int elem, int num = 1);

	int InsertBefore(int elem);

protected:
	void GrowVector(int num = 1)
	{
		if (m_Size + num > m_Memory.NumAllocated())
		{
			m_Memory.Grow(m_Size + num - m_Memory.NumAllocated());
		}

		m_Size += num;
	}

	CAllocator m_Memory;
	int m_Size;
	T* m_pElements;
};
template< typename T, class A >
void CUtlVector<T, A>::ShiftElementsRight(int elem, int num)
{
	int numToMove = m_Size - elem - num;
	if ((numToMove > 0) && (num > 0))
		memmove(&Element(elem + num), &Element(elem), numToMove * sizeof(T));
}

template< typename T, class A >
void CUtlVector<T, A>::ShiftElementsLeft(int elem, int num)
{
	int numToMove = m_Size - elem - num;
	if ((numToMove > 0) && (num > 0))
	{
		memmove(&Element(elem), &Element(elem + num), numToMove * sizeof(T));
	}
}

template< typename T, class A >
int CUtlVector<T, A>::InsertBefore(int elem)
{
	GrowVector();
	ShiftElementsRight(elem);
	Construct(&Element(elem));
	return elem;
}


template< typename T, class A >
inline int CUtlVector<T, A>::AddToTail()
{
	return InsertBefore(m_Size);
}

template< typename T, class A >
void CUtlVector<T, A>::Remove(int elem)
{
	Destruct(&Element(elem));
	ShiftElementsLeft(elem);
	--m_Size;
}
template< typename T, class A >
void CUtlVector<T, A>::RemoveAll()
{
	for (int i = m_Size; --i >= 0; )
	{
		Destruct(&Element(i));
	}

	m_Size = 0;
}
template< typename T, class A >
inline void CUtlVector<T, A>::Purge()
{
	RemoveAll();
	m_Memory.Purge();
	ResetDbgInfo();
}
template< typename T, class A >
inline T& CUtlVector<T, A>::operator[](int i)
{
	// Do an inline unsigned check for maximum debug-build performance.
	return m_Memory[i];
}
/*
template< typename T, class A >
inline const T& CUtlVector<T, A>::operator[](int i) const
{
	// Do an inline unsigned check for maximum debug-build performance.
	return m_Memory[i];
}
*/
template< typename T, class A >
inline T& CUtlVector<T, A>::Element(int i)
{
	// Do an inline unsigned check for maximum debug-build performance.
	return m_Memory[i];
}

template< typename T, class A >
inline const T& CUtlVector<T, A>::Element(int i) const
{
	// Do an inline unsigned check for maximum debug-build performance.
	return m_Memory[i];
}