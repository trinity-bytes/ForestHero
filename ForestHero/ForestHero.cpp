#include "GestionJuego.h"

using namespace std;
using namespace System;

void main()
{
	Console::Title = "ForestHero v1.5";
	Console::SetWindowSize(104, 24);
	ConfigurarConsola();

	short opc;
	bool continuar;

	GestionJuego* juego;

	do
	{
		juego = new GestionJuego();
		juego->IniciarJuego();
	} while (true);
}