#ifndef _VEC4_
#define _VEC4_

#include "Vec2.hpp"


template<class T>
class Vec4 : public Vec2<T> {

private:
	T z;
	T w;

public:
	Vec4(T x, T y, T w, T z): Vec2<T>(x, y)
	{
		this->z = z;
		this->w = w;
	}

	T getZ() 
	{
		return this->z;
	}

	T getW()
	{
		return this->w;
	}

	void setZ(T z)
	{
		this->z = z;
	}
	void setW(T w)
	{
		this->w = w;
	}
};

#endif // _VEC4_
