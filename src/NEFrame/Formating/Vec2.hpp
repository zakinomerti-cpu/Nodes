#ifndef _VEC2_
#define _VEC2_

template<class T>
class Vec2 {

private:
	T x;
	T y;
	
public:
	Vec2(T x, T y) 
	{
		this->x = x;
		this->y = y;
	}

	T getX() 
	{
		return this->x;
	}

	T getY() 
	{
		return this->y;
	}

	void setX(T x) 
	{
		this->x = x;
	}

	void setY(T y) 
	{
		this->y = y;
	}
};

#endif // _VEC2_