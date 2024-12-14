#pragma once
#include "Entidad.h"

class Basura : public Entidad
{
public:
	Basura(int, int);
	~Basura();
};

Basura::Basura(int x, int y) : Entidad(x, y) 
{
	this->forma = u8"≡";
}

Basura::~Basura() {}