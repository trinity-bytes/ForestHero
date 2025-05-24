#pragma once
#include "../Base/Agente.h"

class Enemigo : public Agente
{
public:
	Enemigo(int x, int y) : Agente(x, y, TipoEntidad::Enemigo)
	{
		this->forma = u8"Ø";
	}

	~Enemigo() {}
};