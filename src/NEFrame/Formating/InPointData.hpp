#ifndef  _IN_POINT_DATA_
#define _IN_POINT_DATA_

#include "Types.hpp"
#include <functional>

typedef std::function<void()> voidfunc;


class InPointData{
private:
	voidfunc calledFunc; // Функция для текущего вызова

	voidfunc wlf; // Функция орисовки присоеденённой точки
	voidfunc wnlf; // Функция отрисовки неприсоединенной точки

	unsigned int pointID;

	Type type;

	bool free;

public:
	InPointData(
		unsigned int pointID, 
		Type type, 
		voidfunc wnlf, 
		voidfunc wlf
	);

	unsigned int getPointID();
	Type getType();
	bool isFree();

	void drawPointBody();

	void changeToWNLF();
	void changeToWLF();
};

#endif // _IN_POINT_DATA_

