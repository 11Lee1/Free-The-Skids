template< class T >
class CUtlFlags
{
public:
	CUtlFlags(int nInitialFlags = 0);

	// Flag setting
	void SetFlag(int nFlagMask);
	void SetFlag(int nFlagMask, bool bEnable);

	// Flag clearing
	void ClearFlag(int nFlagMask);
	void ClearAllFlags();
	bool IsFlagSet(int nFlagMask) const;

	// Is any flag set?
	bool IsAnyFlagSet() const;

private:
	T m_nFlags;
};


//-----------------------------------------------------------------------------
// Constructor
//-----------------------------------------------------------------------------
template< class T >
CUtlFlags<T>::CUtlFlags(int nInitialFlags)
{
	m_nFlags = (T)nInitialFlags;
}


//-----------------------------------------------------------------------------
// Set flags
//-----------------------------------------------------------------------------
template< class T >
void CUtlFlags<T>::SetFlag(int nFlagMask)
{

	m_nFlags |= (T)nFlagMask;
}

template< class T >
void CUtlFlags<T>::SetFlag(int nFlagMask, bool bEnable)
{

	if (bEnable)
	{
		m_nFlags |= (T)nFlagMask;
	}
	else
	{
		m_nFlags &= ~((T)nFlagMask);
	}
}


//-----------------------------------------------------------------------------
// Clear flags
//-----------------------------------------------------------------------------
template< class T >
void CUtlFlags<T>::ClearFlag(int nFlagMask)
{
	m_nFlags &= ~((T)nFlagMask);
}

template< class T >
void CUtlFlags<T>::ClearAllFlags()
{
	m_nFlags = 0;
}


//-----------------------------------------------------------------------------
// Is a flag set?
//-----------------------------------------------------------------------------
template< class T >
bool CUtlFlags<T>::IsFlagSet(int nFlagMask) const
{
	return (m_nFlags & nFlagMask) != 0;
}


//-----------------------------------------------------------------------------
// Is any flag set?
//-----------------------------------------------------------------------------
template< class T >
bool CUtlFlags<T>::IsAnyFlagSet() const
{
	return m_nFlags != 0;
}

