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
	void RevisarColisiones();
	void BorrarTodo();
	void MoverTodo();
	void DibujarTodo();
	void IniciarJuego();
	void AgregarEnemigo();
	void AgregarAgua();
	void AgregarSemilla();
	void AgregarArbol(int, int);
	void AgregarBasura();
	double PorcentajeReforestacion();
};

GestionJuego::GestionJuego()
{
	aguas = vector<Agua*>();
	semillas = vector<Semilla*>();
	arboles = vector<Arbol*>();
	basuras = vector<Basura*>();
	enemigos = vector<Enemigo*>();

	guardian = new Guardian(10, 8);

	IniciarElementos();
}

GestionJuego::~GestionJuego() {}

void GestionJuego::IniciarJuego()
{
	// configurar nuevo tamano y fuente para la ventana
	setFont(L"Cascadia Mono Semibold", 28, 38);
	Console::SetWindowSize(47, 19);

	//reproducirMusicaNivelNormal();
	MostrarUIJuego();

	while (true)
	{
		BorrarTodo();
		MoverTodo();
		DibujarTodo();

		if (kbhit())
		{
			char tecla = getch();

			guardian->Borrar();

			// Verificamos el movimiento
			if (tecla == 'W' || tecla == 'w')
			{
				guardian->setDireccionActual(Arriba);

				// verificar que el personaje se mueva para quitar la colision con la basura
				if (colisionConBasura) colisionConBasura = false;
			}
			else if (tecla == 'S' || tecla == 's')
			{
				guardian->setDireccionActual(Abajo);

				if (colisionConBasura) colisionConBasura = false;
			}
			else if (tecla == 'A' || tecla == 'a')
			{
				guardian->setDireccionActual(Izquierda);

				if (colisionConBasura) colisionConBasura = false;
			}
			else if (tecla == 'D' || tecla == 'd')
			{
				guardian->setDireccionActual(Derecha);

				if (colisionConBasura) colisionConBasura = false;
			}
			else if (tecla == 'M' || tecla == 'm') /// plantar arbol
			{
				// verificamos que haya suficiente agua y semilla para plantar
				if (guardian->getCantAgua() > 0 &&
					guardian->getCantSemillas() > 0)
				{
					bool puedePlantar = true;


				}
			}
			else if (tecla == 'K' || tecla == 'k') /// disparar semilla
			{

			}
			else if (tecla == 27)
			{
				// finalizar el juego si presiona ESC
				break;
			}

			guardian->Mover();
		}
		guardian->Dibujar();

		Esperar(60);
	}
}

void GestionJuego::RevisarColisiones()
{
	vector<int> indicesSemillasEliminar;
	vector<int> indicesEnemigosEliminar;
	vector<int> indicesAguaEliminar;
	vector<int> indicesBasuraEliminar;


}

void GestionJuego::BorrarTodo()
{
	// Borrar semillas
	if (semillas.size() > 0)
	{
		for (int i = 0; i < semillas.size(); i++)
		{
			if (!semillas[i]->getSeMueve()) continue; /// ignorar las semillas estaticas
			setBkgTxtColor(1, 0);
			semillas[i]->Borrar();
		}
	}

	// Borrar enemigos
	if (enemigos.size() > 0)
	{
		for (int i = 0; i < enemigos.size(); i++)
		{
			setBkgTxtColor(1, 0);
			enemigos[i]->Borrar();
		}
	}
}

void GestionJuego::MoverTodo() 
{
	int r;

	// Mover a los enemigos siempre y cuando haya enemigos
	if (enemigos.size() > 0) 
	{
		for (int i = 0; i < enemigos.size(); i++)
		{
			r = GenerarNumeroAleatorio(1, 60);

			switch (r)
			{
			case 1:
				enemigos[i]->setDireccionActual(Arriba); break;
			case 20:
				enemigos[i]->setDireccionActual(Abajo); break;
			case 40:
				enemigos[i]->setDireccionActual(Izquierda); break;
			case 60:
				enemigos[i]->setDireccionActual(Derecha); break;
			default:
				enemigos[i]->setDireccionActual(Ninguna); break;
				break;
			}

			enemigos[i]->Mover();
		}
	}

	// Mover semillas
	if (semillas.size() > 0)
	{
		for (int i = 0; i < semillas.size(); i++)
		{
			if (!semillas[i]->getSeMueve()) continue; /// ignoramos las semillas que no se mueven uwu

			semillas[i]->Mover();

			/// eliminamos las semillas que traspasan los limites del escenario
			if (semillas[i]->getX() < 2 ||
				semillas[i]->getX() > 20 ||
				semillas[i]->getY() < 3 ||
				semillas[i]->getY() > 17)
			{
				semillas.erase(semillas.begin() + i);
				i--;
			}
		}
	}
	
}

void GestionJuego::DibujarTodo()
{
	// Dibujar arboles
	if (arboles.size() > 0) 
	{
		for (int i = 0; i < arboles.size(); i++) 
		{
			setBkgTxtColor(0, 6);
			arboles[i]->Dibujar();
			setBkgTxtColor(1, 0);
		}
	}

	// Dibujar agua
	if (aguas.size() > 0) 
	{
		for (int i = 0; i < aguas.size(); i++) 
		{
			setBkgTxtColor(0, 11);
			aguas[i]->Dibujar();
			setBkgTxtColor(1, 0);
		}
	}

	// Dibujar semillas
	if (semillas.size() > 0) 
	{
		for (int i = 0; i < semillas.size(); i++) 
		{
			setBkgTxtColor(6, 0);
			semillas[i]->Dibujar();
			setBkgTxtColor(1, 0);
		}
	}

	// Dibujar basura
	if (basuras.size() > 0) 
	{
		for (int i = 0; i < basuras.size(); i++) 
		{
			setBkgTxtColor(0, 5);
			basuras[i]->Dibujar();
			setBkgTxtColor(1, 0);
		}
	}

	// Dibujar enemigos
	if (enemigos.size() > 0)
	{
		for (int i = 0; i < enemigos.size(); i++)
		{
			setBkgTxtColor(0, 4);
			enemigos[i]->Dibujar();
			setBkgTxtColor(1, 0);
		}
	}
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
	cx = GenerarNumeroAleatorio(2, 20);
	cy = GenerarNumeroAleatorio(3, 17);

	Enemigo* e = new Enemigo(cx, cy);
	enemigos.push_back(e);
}

void GestionJuego::AgregarAgua()
{
	cx = GenerarNumeroAleatorio(2, 20);
	cy = GenerarNumeroAleatorio(3, 17);

	Agua* a = new Agua(cx, cy);
	aguas.push_back(a);
}

void GestionJuego::AgregarSemilla()
{
	cx = GenerarNumeroAleatorio(2, 20);
	cy = GenerarNumeroAleatorio(3, 17);

	Semilla* s = new Semilla(cx, cy);
	semillas.push_back(s);
}

void GestionJuego::AgregarArbol(int x, int y)
{
	Arbol* a = new Arbol(x, y);
	arboles.push_back(a);
}

void GestionJuego::AgregarBasura()
{
	int r = GenerarNumeroAleatorio(0, enemigos.size() - 1);

	cx = enemigos[r]->getX();
	cy = enemigos[r]->getY();

	Basura* b = new Basura(cx, cy);
	basuras.push_back(b);
}

double GestionJuego::PorcentajeReforestacion()
{
	double retornarPorcentaje;
	double totalArboles = arboles.size();
	retornarPorcentaje = totalArboles / 96;

	return retornarPorcentaje * 100;
}