
class Vector4D
{
public:
	// Members
	vec_t x, y, z, w;

	// Construction/destruction
	Vector4D(void);
	Vector4D(vec_t X, vec_t Y, vec_t Z, vec_t W);
	Vector4D(const float *pFloat);

	// Initialization
	void Init(vec_t ix = 0.0f, vec_t iy = 0.0f, vec_t iz = 0.0f, vec_t iw = 0.0f);

	// Got any nasty NAN's?
	bool IsValid() const;

	// array access...
	vec_t operator[](int i) const;
	vec_t& operator[](int i);

	// Base address...
	inline vec_t* Base();
	inline vec_t const* Base() const;

	// Cast to Vector and Vector2D...
	Vector& AsVector3D();
	Vector const& AsVector3D() const;

	Vector2D& AsVector2D();
	Vector2D const& AsVector2D() const;

	// Initialization methods
	void Random(vec_t minVal, vec_t maxVal);

	// equality
	bool operator==(const Vector4D& v) const;
	bool operator!=(const Vector4D& v) const;

	// arithmetic operations
	Vector4D&	operator+=(const Vector4D &v);
	Vector4D&	operator-=(const Vector4D &v);
	Vector4D&	operator*=(const Vector4D &v);
	Vector4D&	operator*=(float s);
	Vector4D&	operator/=(const Vector4D &v);
	Vector4D&	operator/=(float s);

	// negate the Vector4D components
	void	Negate();

	// Get the Vector4D's magnitude.
	vec_t	Length() const;

	// Get the Vector4D's magnitude squared.
	vec_t	LengthSqr(void) const;

	// return true if this vector is (0,0,0,0) within tolerance
	bool IsZero(float tolerance = 0.01f) const
	{
		return (x > -tolerance && x < tolerance &&
			y > -tolerance && y < tolerance &&
			z > -tolerance && z < tolerance &&
			w > -tolerance && w < tolerance);
	}

	// Get the distance from this Vector4D to the other one.
	vec_t	DistTo(const Vector4D &vOther) const;

	// Get the distance from this Vector4D to the other one squared.
	vec_t	DistToSqr(const Vector4D &vOther) const;

	// Copy
	void	CopyToArray(float* rgfl) const;

	// Multiply, add, and assign to this (ie: *this = a + b * scalar). This
	// is about 12% faster than the actual Vector4D equation (because it's done per-component
	// rather than per-Vector4D).
	void	MulAdd(Vector4D const& a, Vector4D const& b, float scalar);

	// Dot product.
	vec_t	Dot(Vector4D const& vOther) const;

	// No copy constructors allowed if we're in optimal mode
	Vector4D(Vector4D const& vOther);

	// No assignment operators either...
	Vector4D& operator=(Vector4D const& src);
};
class Vector4DAligned : public Vector4D
{
public:
	Vector4DAligned(void) {}
	Vector4DAligned(vec_t X, vec_t Y, vec_t Z, vec_t W);

	inline void Set(vec_t X, vec_t Y, vec_t Z, vec_t W);
	inline void InitZero(void);

	inline __m128 &AsM128() { return *(__m128*)&x; }
	inline const __m128 &AsM128() const { return *(const __m128*)&x; }

private:
	// No copy constructors allowed if we're in optimal mode
	Vector4DAligned(Vector4DAligned const& vOther);

	// No assignment operators either...
	Vector4DAligned& operator=(Vector4DAligned const& src);
} ALIGN16_POST;

const Vector4D vec4_origin(0.0f, 0.0f, 0.0f, 0.0f);
const Vector4D vec4_invalid(FLT_MAX, FLT_MAX, FLT_MAX, FLT_MAX);


//-----------------------------------------------------------------------------
// Vector4D related operations
//-----------------------------------------------------------------------------

// Vector4D clear
void Vector4DClear(Vector4D& a);

// Copy
void Vector4DCopy(Vector4D const& src, Vector4D& dst);

// Vector4D arithmetic
void Vector4DAdd(Vector4D const& a, Vector4D const& b, Vector4D& result);
void Vector4DSubtract(Vector4D const& a, Vector4D const& b, Vector4D& result);
void Vector4DMultiply(Vector4D const& a, vec_t b, Vector4D& result);
void Vector4DMultiply(Vector4D const& a, Vector4D const& b, Vector4D& result);
void Vector4DDivide(Vector4D const& a, vec_t b, Vector4D& result);
void Vector4DDivide(Vector4D const& a, Vector4D const& b, Vector4D& result);
void Vector4DMA(Vector4D const& start, float s, Vector4D const& dir, Vector4D& result);

// Vector4DAligned arithmetic


#define Vector4DExpand( v ) (v).x, (v).y, (v).z, (v).w

// Normalization
vec_t Vector4DNormalize(Vector4D& v);

// Length
vec_t Vector4DLength(Vector4D const& v);

// Dot Product
vec_t DotProduct4D(Vector4D const& a, Vector4D const& b);

// Linearly interpolate between two vectors
void Vector4DLerp(Vector4D const& src1, Vector4D const& src2, vec_t t, Vector4D& dest);


//-----------------------------------------------------------------------------
//
// Inlined Vector4D methods
//
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// constructors
//-----------------------------------------------------------------------------

inline Vector4D::Vector4D(void)
{
#ifdef _DEBUG
	// Initialize to NAN to catch errors
	x = y = z = w = VEC_T_NAN;
#endif
}

inline Vector4D::Vector4D(vec_t X, vec_t Y, vec_t Z, vec_t W)
{
	x = X; y = Y; z = Z; w = W;
}

inline Vector4D::Vector4D(const float *pFloat)
{
	x = pFloat[0]; y = pFloat[1]; z = pFloat[2]; w = pFloat[3];
}


//-----------------------------------------------------------------------------
// copy constructor
//-----------------------------------------------------------------------------

inline Vector4D::Vector4D(const Vector4D &vOther)
{
	x = vOther.x; y = vOther.y; z = vOther.z; w = vOther.w;
}

//-----------------------------------------------------------------------------
// initialization
//-----------------------------------------------------------------------------

inline void Vector4D::Init(vec_t ix, vec_t iy, vec_t iz, vec_t iw)
{
	x = ix; y = iy; z = iz;	w = iw;
}

inline void Vector4D::Random(vec_t minVal, vec_t maxVal)
{
	x = minVal + ((vec_t)rand() / VALVE_RAND_MAX) * (maxVal - minVal);
	y = minVal + ((vec_t)rand() / VALVE_RAND_MAX) * (maxVal - minVal);
	z = minVal + ((vec_t)rand() / VALVE_RAND_MAX) * (maxVal - minVal);
	w = minVal + ((vec_t)rand() / VALVE_RAND_MAX) * (maxVal - minVal);
}

inline void Vector4DClear(Vector4D& a)
{
	a.x = a.y = a.z = a.w = 0.0f;
}

//-----------------------------------------------------------------------------
// assignment
//-----------------------------------------------------------------------------

inline Vector4D& Vector4D::operator=(const Vector4D &vOther)
{
	x = vOther.x; y = vOther.y; z = vOther.z; w = vOther.w;
	return *this;
}

//-----------------------------------------------------------------------------
// Array access
//-----------------------------------------------------------------------------

inline vec_t& Vector4D::operator[](int i)
{
	return ((vec_t*)this)[i];
}

inline vec_t Vector4D::operator[](int i) const
{
	return ((vec_t*)this)[i];
}

//-----------------------------------------------------------------------------
// Cast to Vector and Vector2D...
//-----------------------------------------------------------------------------

inline Vector& Vector4D::AsVector3D()
{
	return *(Vector*)this;
}

inline Vector const& Vector4D::AsVector3D() const
{
	return *(Vector const*)this;
}

inline Vector2D& Vector4D::AsVector2D()
{
	return *(Vector2D*)this;
}

inline Vector2D const& Vector4D::AsVector2D() const
{
	return *(Vector2D const*)this;
}

//-----------------------------------------------------------------------------
// Base address...
//-----------------------------------------------------------------------------

inline vec_t* Vector4D::Base()
{
	return (vec_t*)this;
}

inline vec_t const* Vector4D::Base() const
{
	return (vec_t const*)this;
}

//-----------------------------------------------------------------------------
// IsValid?
//-----------------------------------------------------------------------------

inline bool Vector4D::IsValid() const
{
	return IsFinite(x) && IsFinite(y) && IsFinite(z) && IsFinite(w);
}

//-----------------------------------------------------------------------------
// comparison
//-----------------------------------------------------------------------------

inline bool Vector4D::operator==(Vector4D const& src) const
{
	return (src.x == x) && (src.y == y) && (src.z == z) && (src.w == w);
}

inline bool Vector4D::operator!=(Vector4D const& src) const
{
	return (src.x != x) || (src.y != y) || (src.z != z) || (src.w != w);
}


//-----------------------------------------------------------------------------
// Copy
//-----------------------------------------------------------------------------

inline void Vector4DCopy(Vector4D const& src, Vector4D& dst)
{
	dst.x = src.x;
	dst.y = src.y;
	dst.z = src.z;
	dst.w = src.w;
}

inline void	Vector4D::CopyToArray(float* rgfl) const
{
	rgfl[0] = x; rgfl[1] = y; rgfl[2] = z; rgfl[3] = w;
}

//-----------------------------------------------------------------------------
// standard math operations
//-----------------------------------------------------------------------------

inline void Vector4D::Negate()
{
	x = -x; y = -y; z = -z; w = -w;
}

inline Vector4D& Vector4D::operator+=(const Vector4D& v)
{
	x += v.x; y += v.y; z += v.z; w += v.w;
	return *this;
}

inline Vector4D& Vector4D::operator-=(const Vector4D& v)
{
	x -= v.x; y -= v.y; z -= v.z; w -= v.w;
	return *this;
}

inline Vector4D& Vector4D::operator*=(float fl)
{
	x *= fl;
	y *= fl;
	z *= fl;
	w *= fl;
	return *this;
}

inline Vector4D& Vector4D::operator*=(Vector4D const& v)
{
	x *= v.x;
	y *= v.y;
	z *= v.z;
	w *= v.w;
	return *this;
}

inline Vector4D& Vector4D::operator/=(float fl)
{
	float oofl = 1.0f / fl;
	x *= oofl;
	y *= oofl;
	z *= oofl;
	w *= oofl;
	return *this;
}

inline Vector4D& Vector4D::operator/=(Vector4D const& v)
{
	x /= v.x;
	y /= v.y;
	z /= v.z;
	w /= v.w;
	return *this;
}

inline void Vector4DAdd(Vector4D const& a, Vector4D const& b, Vector4D& c)
{
	c.x = a.x + b.x;
	c.y = a.y + b.y;
	c.z = a.z + b.z;
	c.w = a.w + b.w;
}

inline void Vector4DSubtract(Vector4D const& a, Vector4D const& b, Vector4D& c)
{
	c.x = a.x - b.x;
	c.y = a.y - b.y;
	c.z = a.z - b.z;
	c.w = a.w - b.w;
}

inline void Vector4DMultiply(Vector4D const& a, vec_t b, Vector4D& c)
{
	c.x = a.x * b;
	c.y = a.y * b;
	c.z = a.z * b;
	c.w = a.w * b;
}

inline void Vector4DMultiply(Vector4D const& a, Vector4D const& b, Vector4D& c)
{
	c.x = a.x * b.x;
	c.y = a.y * b.y;
	c.z = a.z * b.z;
	c.w = a.w * b.w;
}

inline void Vector4DDivide(Vector4D const& a, vec_t b, Vector4D& c)
{
	vec_t oob = 1.0f / b;
	c.x = a.x * oob;
	c.y = a.y * oob;
	c.z = a.z * oob;
	c.w = a.w * oob;
}

inline void Vector4DDivide(Vector4D const& a, Vector4D const& b, Vector4D& c)
{
	c.x = a.x / b.x;
	c.y = a.y / b.y;
	c.z = a.z / b.z;
	c.w = a.w / b.w;
}

inline void Vector4DMA(Vector4D const& start, float s, Vector4D const& dir, Vector4D& result)
{
	result.x = start.x + s * dir.x;
	result.y = start.y + s * dir.y;
	result.z = start.z + s * dir.z;
	result.w = start.w + s * dir.w;
}

// FIXME: Remove
// For backwards compatability
inline void	Vector4D::MulAdd(Vector4D const& a, Vector4D const& b, float scalar)
{
	x = a.x + b.x * scalar;
	y = a.y + b.y * scalar;
	z = a.z + b.z * scalar;
	w = a.w + b.w * scalar;
}

inline void Vector4DLerp(const Vector4D& src1, const Vector4D& src2, vec_t t, Vector4D& dest)
{
	dest[0] = src1[0] + (src2[0] - src1[0]) * t;
	dest[1] = src1[1] + (src2[1] - src1[1]) * t;
	dest[2] = src1[2] + (src2[2] - src1[2]) * t;
	dest[3] = src1[3] + (src2[3] - src1[3]) * t;
}

//-----------------------------------------------------------------------------
// dot, cross
//-----------------------------------------------------------------------------

inline vec_t DotProduct4D(const Vector4D& a, const Vector4D& b)
{
	return(a.x*b.x + a.y*b.y + a.z*b.z + a.w*b.w);
}

// for backwards compatability
inline vec_t Vector4D::Dot(Vector4D const& vOther) const
{
	return DotProduct4D(*this, vOther);
}


//-----------------------------------------------------------------------------
// length
//-----------------------------------------------------------------------------

inline vec_t Vector4DLength(Vector4D const& v)
{
	return (vec_t)FastSqrt(v.x*v.x + v.y*v.y + v.z*v.z + v.w*v.w);
}

inline vec_t Vector4D::LengthSqr(void) const
{
	return (x*x + y * y + z * z + w * w);
}

inline vec_t Vector4D::Length(void) const
{
	return Vector4DLength(*this);
}


//-----------------------------------------------------------------------------
// Normalization
//-----------------------------------------------------------------------------

// FIXME: Can't use until we're un-macroed in mathlib.h
inline vec_t Vector4DNormalize(Vector4D& v)
{
	vec_t l = v.Length();
	if (l != 0.0f)
	{
		v /= l;
	}
	else
	{
		v.x = v.y = v.z = v.w = 0.0f;
	}
	return l;
}

//-----------------------------------------------------------------------------
// Get the distance from this Vector4D to the other one 
//-----------------------------------------------------------------------------

inline vec_t Vector4D::DistTo(const Vector4D &vOther) const
{
	Vector4D delta;
	Vector4DSubtract(*this, vOther, delta);
	return delta.Length();
}

inline vec_t Vector4D::DistToSqr(const Vector4D &vOther) const
{
	Vector4D delta;
	Vector4DSubtract(*this, vOther, delta);
	return delta.LengthSqr();
}