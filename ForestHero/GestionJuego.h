#pragma once
#include "UI Ascii.h"
#include "Guardian.h"
#include "Enemigo.h"
#include "Agua.h";
#include "Semilla.h";
#include "Arbol.h";
#include "Basura.h";
#include "vector"
#include "conio.h"

class GestionJuego
{
private:
	Guardian* guardian;

	vector<Agua*> aguas;
	vector<Semilla*> semillas;
	vector<Arbol*> arboles;
	vector<Basura*> basuras;
	vector<Enemigo*> enemigos;

	clock_t t, tsAgua, tsSemilla, tsEnemigos, tsBasura;
	int segundosAgua = 0, segundosSemilla = 0, segundosEnemigos = 0, segundosBasura = 0;

	const int puntosRecogerSemilla = 2;
	const int puntosRecogerAgua = 3;
	const int puntosPlantarArbol = 10;
	const int puntosDestruirBasura = 8;

	const int cantInicialEnemigos = 5;
	const int cantInicialAgua = 10;
	const int cantInicialSemillas = 15;

	int tiempoBasura = 7;
	bool colisionConBasura = false;
	bool continuar = true;
	bool victoria = false;
	bool musicaFinal = false;

	// para las coordenadas de los objetos que se van a generar
	int cx, cy;
public:
	GestionJuego();
	~GestionJuego();

	void IniciarElementos();
	void IniciarJuego();
	void AgregarEnemigo();
	void AgregarAgua();
	void AgregarSemilla();
};

GestionJuego::GestionJuego()
{
	aguas = vector<Agua*>();
	semillas = vector<Semilla*>();
	arboles = vector<Arbol*>();
	basuras = vector<Basura*>();
	enemigos = vector<Enemigo*>();

	IniciarElementos();
}

GestionJuego::~GestionJuego() {}

void GestionJuego::IniciarJuego()
{
	// configurar nuevo tamano y fuente para la ventana
	setFont(L"Cascadia Mono Semibold", 28, 38);
	Console::SetWindowSize(47, 19);

	//reproducirMusicaNivelNormal();
	mostrarInterfazJuego();
}

void GestionJuego::IniciarElementos()
{
	// inicializar enemigos
	for (int i = 0; i < cantInicialEnemigos; i++)
	{
		AgregarEnemigo();
	}

	// inicializar agua
	for (int i = 0; i < cantInicialAgua; i++)
	{
		AgregarAgua();
	}

	// inicializar semillas
	for (int i = 0; i < cantInicialSemillas; i++)
	{
		AgregarSemilla();
	}
}

void GestionJuego::AgregarEnemigo()
{

}

void GestionJuego::AgregarAgua()
{

}

void GestionJuego::AgregarSemilla()
{

}