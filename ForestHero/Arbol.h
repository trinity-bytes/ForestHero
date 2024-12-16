#pragma once
#include "Entidad.h"

class Arbol : public Entidad
{
public:
	Arbol(int, int);
	~Arbol();
};

Arbol::Arbol(int x, int y) : Entidad(x, y)
{
	this->forma = u8"#";
}

Arbol::~Arbol() {}