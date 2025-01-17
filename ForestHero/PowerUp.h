#pragma once
#include "Entidad.h"

class PowerUp : public Entidad
{
private:
	bool visible;
public:
	PowerUp(int, int);
	~PowerUp();

	bool getVisible();
	void setVisible(bool);
};

PowerUp::PowerUp(int x, int y) : Entidad(x, y)
{
	this->forma = u8"+";
	this->visible = false;
}

PowerUp::~PowerUp() {}

bool PowerUp::getVisible() { return this->visible; }
void PowerUp::setVisible(bool v) { this->visible = v; }