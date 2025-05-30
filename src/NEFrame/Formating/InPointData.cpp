#include "InPointData.hpp"

InPointData::InPointData(
	unsigned int pointID, 
	Type type, 
	voidfunc wnlf, 
	voidfunc wlf
){
	this->pointID = pointID;

	this->type = type;

	this->free = true;

	this->wlf = wlf;
	this->wnlf = wnlf;

	this->calledFunc = wnlf;
}

unsigned int InPointData::getPointID()
{
	return this->pointID;
}

Type InPointData::getType()
{
	return this->type;
}

bool InPointData::isFree()
{
	return this->free;
}

void InPointData::drawPointBody()
{
	this->calledFunc();
}

void InPointData::changeToWNLF()
{
	this->calledFunc = this->wnlf;

	this->free = true;
}

void InPointData::changeToWLF()
{
	this->calledFunc = this->wlf;

	this->free = false;
}
