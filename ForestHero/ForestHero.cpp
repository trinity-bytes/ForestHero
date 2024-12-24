#include "GestionJuego.h"
#include "Ascii Art.h"

using namespace std;
using namespace System;

void SecuenciaDeInicio();
void Jugar();
void Ranking();
void Tutorial();
void Salir();

void main()
{
	short opc;
	bool continuar = true;

	SecuenciaDeInicio();

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
			Salir(); continuar = false; break;
		default: break;
		}
	} while (continuar);
}

void SecuenciaDeInicio()
{
	ConfigurarConsola();

	PresentacionSkibidiDevs();
	RepSkibididevs();
	LimpiarPantalla();

	Console::CursorVisible = true;
	PresentacionForestHero();
	RepIntroPressStart();
	system("pause>0");
	Console::CursorVisible = false;
	RepIniciandoMenu();
	LimpiarPantalla();
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
	RepSeleccionMenuSecundario();
	LimpiarPantalla();
	RepMenuSecundario();

	MostrarUITutorial();
}

void Salir()
{
	LimpiarPantalla();
	MostrarDespedida();
	RepSalirJuego();
}