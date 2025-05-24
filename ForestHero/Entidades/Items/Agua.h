#pragma once
#include "../Base/Entidad.h"

class Agua : public Entidad
{
public:
	Agua(int, int) : Entidad(x, y, TipoEntidad::Agua)
	{
		this->forma = u8"▒";
	}
	~Agua() {}
};