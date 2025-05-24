#pragma once
#include "../Base/Agente.h"

class Semilla : public Agente
{
private:
	bool seMueve;
public:
	Semilla(int x, int y) :Agente(x, y, TipoEntidad::Semilla), seMueve(false) 
	{
		this->forma = u8"*";
	}
	~Semilla() {}

	bool getSeMueve() { return seMueve; }
	void setSeMueve(bool s) { this->seMueve = s; }

	void mover() override 
	{
		switch (direccionActual)
		{
		case Direccion::Arriba:
			if (y - 1 > 2) {
				dx = 0;
				dy = -velocidad;
				y += dy;
			}
			break;
		case Direccion::Abajo:
			if (y + 1 < 18) {
				dx = 0;
				dy = velocidad;
				y += dy;
			}
			break;
		case Direccion::Izquierda:
			if (x - 1 > 0) {
				dx = -velocidad;
				dy = 0;
				x += dx;
			}
			break;
		case Direccion::Derecha:
			if (x + 1 < 21) {
				dx = velocidad;
				dy = 0;
				x += dx;
			}
			break;
		}
	}
};