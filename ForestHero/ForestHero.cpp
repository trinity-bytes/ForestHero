#include "GestionJuego.h"

using namespace std;
using namespace System;

void main()
{
	Console::Title = "ForestHero v1.5";
	Console::SetWindowSize(104, 24);
	ConfigurarConsola();

	short opc;
	bool continuar = true;

	GestionJuego* juego;

	do
	{
		juego = new GestionJuego();

		LimpiarPantalla();

		juego->IniciarJuego();

	} while (continuar);
}