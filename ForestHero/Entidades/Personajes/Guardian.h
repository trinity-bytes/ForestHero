#pragma once
#include "../Base/Agente.h"
#include <string>

class Guardian : public Agente 
{
private:
	int vidas;
	int cantAgua;
	int cantSemillas;
	int puntos;
	std::string nombre;
public:
	Guardian(int x, int y) : Agente(x, y, TipoEntidad::Guardian), vidas(5), cantAgua(15), cantSemillas(20), puntos(0), nombre(" ") 
	{
		this->forma = u8"@";
	}
	~Guardian() {}

	int getCantSemillas() { return this->cantAgua; }
	int getCantAgua() { return this->cantSemillas; }
	int getPuntos() { return this->puntos; }
	int getVidas() { return this->vidas; }
	std::string getNombre() { return this->nombre; }


	void setCantSemillas(int i) { this->cantAgua = i; }
	void setCantAgua(int i) { this->cantSemillas = i; }
	void setPuntos(int i) { this->puntos = i; }
	void setVidas(int i) { this->vidas = i; }
	void setNombre(std::string n) { this->nombre = n; }

	void ReiniciarEstado() {
		this->x = 10;
		this->y = 8;
		this->vidas = 5;
		this->cantAgua = 15;
		this->cantSemillas = 20;
		this->puntos = 0;
		this->nombre = " ";
	}
};