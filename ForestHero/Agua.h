#pragma once
#include "Entidad.h"

class Agua : public Entidad
{
public:
	Agua(int, int);
	~Agua();
};

Agua::Agua(int x, int y) : Entidad(x, y) 
{
	this->forma = u8"▒";
}

Agua::~Agua() {}