#pragma once
#include "Agente.h"

class Enemigo : public Agente
{
public:
	Enemigo(int, int);
	~Enemigo();
};

Enemigo::Enemigo(int x, int y) : Agente(x, y) {}

Enemigo::~Enemigo() {}