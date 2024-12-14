#pragma once
#include "Entidad.h"

enum Direccion { Arriba, Abajo, Izquierda, Derecha, Ninguna };

class Agente : public Entidad
{
protected:
	int dx, dy, velocidad;
	Direccion direccionActual;
public:
	Agente(int, int);
	~Agente();

    Direccion getDireccionActual();
    void setDireccionActual(Direccion);

	virtual void Mover();
};

Agente::Agente(int x, int y) : Entidad(x, y)
{
	this->dx = this->dy = 0;
	this->velocidad = 1;
	direccionActual = Ninguna;
}

Agente::~Agente() {}

Direccion Agente::getDireccionActual() { return this->direccionActual; }

void Agente::setDireccionActual(Direccion d) { this->direccionActual = d; }

void Agente::Mover()
{
    dx = dy = 0;

    switch (direccionActual)
    {
    case Arriba:
        if (y - 1 > 2) dy = -velocidad;
        else direccionActual = Ninguna;
        break;
    case Abajo:
        if (y + 1 < 18) dy = velocidad;
        else direccionActual = Ninguna;
        break;
    case Izquierda:
        if (x - 1 > 0) dx = -velocidad;
        else direccionActual = Ninguna;
        break;
    case Derecha:
        if (x + 1 < 21) dx = velocidad;
        else direccionActual = Ninguna;
        break;
    }

    if (direccionActual != Direccion::Ninguna)
    {
        x += dx;
        y += dy;
    }
}