#pragma once
#include "Agente.h"

class Semilla : public Agente
{
private:
	bool seMueve;
public:
	Semilla(int, int);
	~Semilla();

	bool getSeMueve();
    void setSeMueve(bool);

	void Mover() override;
};

Semilla::Semilla(int x, int y) :Agente(x, y) 
{
    this->forma = u8"*";
	this->seMueve = false;
}

Semilla::~Semilla() {}

bool Semilla::getSeMueve() { return seMueve; }
void Semilla::setSeMueve(bool s) { this->seMueve = s; }

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