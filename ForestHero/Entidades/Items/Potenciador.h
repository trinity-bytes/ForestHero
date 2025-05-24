#pragma once
#include "../Base/Entidad.h"

class Potenciador : public Entidad
{
private:
	bool visible;
public:
	Potenciador(int x, int y) : Entidad(x, y, TipoEntidad::PowerUp), visible(false) 
	{
		this->forma = u8"+";
	}
	~Potenciador() {}

	bool getVisible() { return this->visible; }
	void setVisible(bool v) { this->visible = v; }
};