#pragma once
#include "Agente.h"

class Semilla : public Agente
{
private:
	bool seMueve;
public:
	Semilla(int, int);
	Semilla(int, int, Direccion);
	~Semilla();

	bool getSeMueve();

	void Mover() override;
};

Semilla::Semilla(int x, int y) :Agente(x, y) 
{
	this->seMueve = false;
	this->velocidad = 0;
	this->direccionActual = Ninguna;
}

Semilla::Semilla(int x, int y, Direccion d) :Agente(x, y)
{
	this->seMueve = false;
	this->velocidad = 1;
	this->direccionActual = d;
}

Semilla::~Semilla() {}

bool Semilla::getSeMueve() { return seMueve; }

void Semilla::Mover()
{
    switch (direccionActual)
    {
    case Arriba:
        if (y - 1 > 2) {
            dx = 0;
            dy = -velocidad;
            y += dy;
        }
        break;
    case Abajo:
    case Ninguna:
        if (y + 1 < 18) {
            dx = 0;
            dy = velocidad;
            y += dy;
        }
        break;
    case Izquierda:
        if (x - 1 > 0) {
            dx = -velocidad;
            dy = 0;
            x += dx;
        }
        break;
    case Derecha:
        if (x + 1 < 21) {
            dx = velocidad;
            dy = 0;
            x += dx;
        }
        break;
    }
}