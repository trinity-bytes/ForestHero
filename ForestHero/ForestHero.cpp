#include "GestionJuego.h"
#include "Ascii Art.h"

using namespace std;
using namespace System;

void Jugar();
void Ranking();
void Tutorial();
void Salir();

void main()
{
	ConfigurarConsola();
	
	short opc;
	bool continuar = true;

	do
	{
		RepMenuPrincipal();
		LimpiarPantalla();

		MostrarMenuPrincipal();
		opc = ObtenerOpcionMenuPrincipal();

		switch (opc)
		{
		case 1:
			Jugar(); break;
		case 2:
			Ranking(); break;
		case 3:
			Tutorial(); break;
		case 4:
			Salir();
			continuar = false;
			break;
		default: break;
		}
	} while (continuar);
}

void Jugar()
{
	GestionJuego* juego;
	juego = new GestionJuego();

	RepSeleccionIniciarJuego();
	LimpiarPantalla();

	juego->IniciarJuego();
	delete juego;
}

void Ranking()
{
	RepSeleccionMenuSecundario();
	LimpiarPantalla();
	RepMenuSecundario();

	MostrarRanking();
	system("pause>0");
}

void Tutorial()
{
	LimpiarPantalla();
	RepSeleccionMenuSecundario();
	RepMenuSecundario();

	system("pause>0");
}

void Salir()
{
	LimpiarPantalla();
	MostrarDespedida();
	RepSalirJuego();
}