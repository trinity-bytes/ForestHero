#pragma once
#include "Agente.h"

class Enemigo : public Agente
{
public:
	Enemigo(int, int);
	~Enemigo();
};

Enemigo::Enemigo(int x, int y) : Agente(x, y)
{
	this->forma = u8"Ø";
}

Enemigo::~Enemigo() {}