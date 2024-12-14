#pragma once
#include "Entidad.h"

class Agente : public Entidad
{
protected:
	int dx, dy, velocidad;
public:
	Agente(int, int);
	~Agente();

	virtual void Mover();
};

Agente::Agente(int x, int y) : Entidad(x, y)
{
	this->dx = this->dy = 0;
	this->velocidad = 1;
}

Agente::~Agente() {}