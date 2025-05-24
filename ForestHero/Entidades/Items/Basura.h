#pragma once
#include "../Base/Entidad.h"

class Basura : public Entidad
{
public:
	Basura(int x, int y) : Entidad(x, y, TipoEntidad::Basura) 
	{
		this->forma = u8"≡";
	}
	~Basura() {}
};