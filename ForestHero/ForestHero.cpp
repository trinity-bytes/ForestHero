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
		LimpiarPantalla();

		MostrarMenuPrincipal();
		opc = ObtenerOpcionMenuPrincipal();

		switch (opc)
		{
		case 1:
			juego = new GestionJuego();

			RepSeleccionIniciarJuego();
			LimpiarPantalla();

			juego->IniciarJuego();
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		default:
			break;
		}
	} while (continuar);

	delete juego;
}