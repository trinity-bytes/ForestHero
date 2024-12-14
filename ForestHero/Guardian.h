#pragma once
#include "Agente.h"
#include "string"

class Guardian : public Agente {
private:
	int vidas, cantAgua, cantSemillas, puntos;
	string nombre;
public:
	Guardian();
	~Guardian();

	int getCantSemillas();
	int getCantAgua();
	int getPuntos();
	int getVidas();
	string getNombre();


	void setCantSemillas(int);
	void setCantAgua(int);
	void setPuntos(int);
	void setVidas(int);

	void ReiniciarEstado();
};

Guardian::Guardian() : Agente(10, 8)
{
	this->vidas = 5;
	this->cantAgua = 15;
	this->cantSemillas = 20;
	this->puntos = 0;
	this->nombre = " ";
}

Guardian::~Guardian() {}

int Guardian::getCantSemillas() { return this->cantAgua; }
int Guardian::getCantAgua() { return this->cantSemillas; }
int Guardian::getPuntos() { return this->puntos; }
int Guardian::getVidas() { return this->vidas; }
string Guardian::getNombre() { return this->nombre; }

void Guardian::setCantSemillas(int i) { this->cantAgua = i; }
void Guardian::setCantAgua(int i) { this->cantSemillas = i; }
void Guardian::setPuntos(int i) { this->puntos = i; }
void Guardian::setVidas(int i) { this->vidas = i; }

void Guardian::ReiniciarEstado()
{
	this->x = 10;
	this->y = 8;
	this->vidas = 5;
	this->cantAgua = 15;
	this->cantSemillas = 20;
	this->puntos = 0;
	this->nombre = " ";
}