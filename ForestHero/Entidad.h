#pragma once
#include "FuncionesExtra.h"

class Entidad
{
protected:
	int x, y;
	string forma;
public:
	Entidad(int, int);
	~Entidad();

	int getX();
	int getY();
	void setForma(string f);

	virtual void Dibujar();
	void Borrar();
	System::Drawing::Rectangle getRectangle();
};

Entidad::Entidad(int x, int y)
{
	this->x = x;
	this->y = y;
	this->forma = " ";
}

Entidad::~Entidad() {}

int Entidad::getX() { return this->x; }
int Entidad::getY() { return this->y; }

void Entidad::setForma(string f) { this->forma = f; }

void Entidad::Dibujar() 
{
	GoTo(x, y); cout << forma;
}

void Entidad::Borrar()
{
	GoTo(x, y); cout << " ";
}

System::Drawing::Rectangle Entidad::getRectangle()
{
	return System::Drawing::Rectangle(x, y, 1, 1);
}