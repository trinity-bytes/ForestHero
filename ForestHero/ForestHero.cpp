#include "GestionJuego.h"
#include "Ascii Art.h"

using namespace std;
using namespace System;

void main()
{
	ConfigurarConsola();
	Console::Title = "ForestHero v1.5";
	Console::SetWindowSize(104, 28);

	short opc;
	bool continuar = true;

	GestionJuego* juego;

	do
	{
		RepMenuPrincipal();
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
			delete juego;
			break;
		case 2:
			RepSeleccionMenuSecundario();
			LimpiarPantalla();
			RepMenuSecundario();

			system("pause>0");
			break;
		case 3:
			LimpiarPantalla();
			RepSeleccionMenuSecundario();
			RepMenuSecundario();

			system("pause>0");
			break;
		case 4:
			LimpiarPantalla();
			MostrarDespedida();
			RepSalirJuego();
			continuar = false;
			break;
		default:
			break;
		}
	} while (continuar);
}