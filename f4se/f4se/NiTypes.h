#pragma once

// 8
template <class T>
class NiPointer
{
public:
	T	* m_pObject;	// 00

	inline NiPointer(T* pObject = (T*) 0)
	{
		m_pObject = pObject;
		if(m_pObject) m_pObject->IncRef();
	}

	inline ~NiPointer()
	{
		if(m_pObject) m_pObject->DecRef();
	}

	inline operator T *() const
	{
		return m_pObject;
	}

	inline T & operator*() const
	{
		return *m_pObject;
	}

	inline T * operator->() const
	{
		return m_pObject;
	}

	inline NiPointer <T> & operator=(const NiPointer & rhs)
	{
		if(m_pObject != rhs.m_pObject)
		{
			if(rhs) rhs.m_pObject->IncRef();
			if(m_pObject) m_pObject->DecRef();

			m_pObject = rhs.m_pObject;
		}

		return *this;
	}

	inline NiPointer <T> & operator=(T * rhs)
	{
		if(m_pObject != rhs)
		{
			if(rhs) rhs->IncRef();
			if(m_pObject) m_pObject->DecRef();

			m_pObject = rhs;
		}

		return *this;
	}

	inline bool operator==(T * pObject) const
	{
		return m_pObject == pObject;
	}

	inline bool operator!=(T * pObject) const
	{
		return m_pObject != pObject;
	}

	inline bool operator==(const NiPointer & ptr) const
	{
		return m_pObject == ptr.m_pObject;
	}

	inline bool operator!=(const NiPointer & ptr) const
	{
		return m_pObject != ptr.m_pObject;
	}
};

#define MAKE_NI_POINTER(x)	class x; typedef NiPointer <x> x##Ptr

template <class T_to, class T_from>
T_to * niptr_cast(const T_from & src)
{
	return static_cast <T_to *>(src.m_pObject);
}

// C
class NiPoint3
{
public:
	float	x;	// 0
	float	y;	// 4
	float	z;	// 8

	NiPoint3();
	NiPoint3(float X, float Y, float Z) : x(X), y(Y), z(Z) { };

	// Negative
	NiPoint3 operator- () const;

	// Basic operations
	NiPoint3 operator+ (const NiPoint3& pt) const;
	NiPoint3 operator- (const NiPoint3& pt) const;

	NiPoint3& operator+= (const NiPoint3& pt);
	NiPoint3& operator-= (const NiPoint3& pt);

	// Scalar operations
	NiPoint3 operator* (float fScalar) const;
	NiPoint3 operator/ (float fScalar) const;

	NiPoint3& operator*= (float fScalar);
	NiPoint3& operator/= (float fScalar);
};

// 10
class NiColor
{
public:
	float	r;	// 00
	float	g;	// 04
	float	b;	// 08
	UInt32	pad0C;	// 0C
};

// 10
class NiColorA
{
public:
	float	r;	// 00
	float	g;	// 04
	float	b;	// 08
	float	a;	// 0C
};

// 10
template <class T>
class NiRect
{
public:
	T	m_left;		// 00
	T	m_right;	// 04
	T	m_top;		// 08
	T	m_bottom;	// 0C
};

// 1C
class NiFrustum
{
public:
	float	m_fLeft;	// 00
	float	m_fRight;	// 04
	float	m_fTop;		// 08
	float	m_fBottom;	// 0C
	float	m_fNear;	// 10
	float	m_fFar;		// 14
	bool	m_bOrtho;	// 18
};

// 10
class NiQuaternion
{
public:
	// w is first

	float	m_fW;	// 0
	float	m_fX;	// 4
	float	m_fY;	// 8
	float	m_fZ;	// C
};

// 8
class NiPoint2
{
public:
	float	x;	// 0
	float	y;	// 4
};

// 30
class NiMatrix43
{
public:
	union
	{
		float	data[4][3];
		float   arr[12];
	};
};

// 40
class NiTransform
{
public:
	NiMatrix43	rot;	// 00
	NiPoint3	pos;	// 30
	float		scale;	// 3C
};
STATIC_ASSERT(sizeof(NiTransform) == 0x40);

// 18
template <typename T>
class NiTArray
{
public:
	NiTArray();
	virtual ~NiTArray();

	// sparse array, can have NULL entries that should be skipped
	// iterate from 0 to m_emptyRunStart - 1

//	void	** _vtbl;			// 00
	T		* m_data;			// 08
	UInt16	m_arrayBufLen;		// 0C - max elements storable in m_data
	UInt16	m_emptyRunStart;	// 0E - index of beginning of empty slot run
	UInt16	m_size;				// 10 - number of filled slots
	UInt16	m_growSize;			// 12 - number of slots to grow m_data by
};
