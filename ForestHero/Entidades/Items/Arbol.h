#pragma once
#include "../Base/Entidad.h"

class Arbol : public Entidad
{
public:
	Arbol(int x, int y) : Entidad(x, y, TipoEntidad::Arbol) 
	{
		this->forma = u8"#";
	}
	~Arbol() {}
};