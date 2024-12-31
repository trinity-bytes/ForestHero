#pragma once
#include "GestionPuntajes.h"
#include "UI Ascii.h"
#include "Musica.h"
#include "Guardian.h"
#include "Enemigo.h"
#include "Agua.h"
#include "Semilla.h"
#include "Arbol.h"
#include "Basura.h"
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

	const int tiempoAgua = 3;
	const int tiempoSemilla = 2;
	const int tiempoEnemigos = 30;

	int tiempoBasura = 7; // Su valor cambia en la parte final del nivel
	int opcReiniciarJuego = 0;

	const int puntosRecogerSemilla = 1;
	const int puntosRecogerAgua = 2;
	const int puntosPlantarArbol = 10;
	const int puntosDestruirBasura = 5;
	const int puntosEliminarEnemigo = 3;

	const int cantInicialEnemigos = 5;
	const int cantInicialAgua = 10;
	const int cantInicialSemillas = 20;

	const int limiteAgua = 30;
	const int limiteSemillas = 50;
	const int limiteEnemigos = 30;

	bool colisionConBasura = false;
	bool continuar = true;
	bool victoria = false;
	bool musicaFinal = false;

	string nick;

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
	void DispararSemillas(int, int);
	void AgregarArbol(int, int);
	void AgregarBasura();
	double PorcentajeReforestacion();
	bool AnalizarGameOver();
	bool DeterminarVictoria();
	void GuardarPuntajes();
	void ReiniciarEstado();
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

GestionJuego::~GestionJuego() 
{
	delete guardian;
	for (auto agua : aguas) delete agua;
	for (auto semilla : semillas) delete semilla;
	for (auto arbol : arboles) delete arbol;
	for (auto basura : basuras) delete basura;
	for (auto enemigo : enemigos) delete enemigo;
}

void GestionJuego::IniciarJuego()
{
	// configurar nuevo tamano y fuente para la ventana
	setFont(L"Cascadia Mono Semibold", 28, 38);
	Console::SetWindowSize(47, 19);

	MostrarUIJuego();
	RepNivelNormal();

	do
	{
		RevisarColisiones();
		BorrarTodo();
		MoverTodo();
		DibujarTodo();

		if ((t = clock()) >= tsAgua) // Agregar agua cada X tiempo
		{
			segundosAgua += tiempoAgua;
			tsAgua = t + CLOCKS_PER_SEC * tiempoAgua;

			if (aguas.size() <= limiteAgua)
			{
				AgregarAgua();
			}
		}

		if ((t = clock()) >= tsSemilla) // Agregar una semilla cada X tiempo
		{
			segundosSemilla += tiempoSemilla;
			tsSemilla = t + CLOCKS_PER_SEC * tiempoSemilla;

			if (semillas.size() <= limiteSemillas)
			{
				AgregarSemilla();
			}
		}

		if ((t = clock()) >= tsEnemigos) // Agregar un enemigo cada X tiempo
		{
			segundosEnemigos += tiempoEnemigos;
			tsEnemigos = t + CLOCKS_PER_SEC * tiempoEnemigos;

			if (enemigos.size() < limiteEnemigos)
			{
				AgregarEnemigo();
			}
		}

		if ((t = clock()) >= tsBasura)
		{
			segundosBasura += tiempoBasura;
			tsBasura = t + CLOCKS_PER_SEC * tiempoBasura;

			if (enemigos.size() > 0) AgregarBasura(); //Verificamos que hayan eneigos que puedan generar basura
		}

		if (kbhit())
		{
			char tecla = getch();

			guardian->Borrar();

			// Verificamos el movimiento
			if (tecla == 'W' || tecla == 'w')
			{
				guardian->setDireccionActual(Arriba);
				guardian->Mover();

				// verificar que el personaje se mueva para quitar la colision con la basura
				if (colisionConBasura) colisionConBasura = false;
			}
			else if (tecla == 'S' || tecla == 's')
			{
				guardian->setDireccionActual(Abajo);
				guardian->Mover();

				if (colisionConBasura) colisionConBasura = false;
			}
			else if (tecla == 'A' || tecla == 'a')
			{
				guardian->setDireccionActual(Izquierda);
				guardian->Mover();

				if (colisionConBasura) colisionConBasura = false;
			}
			else if (tecla == 'D' || tecla == 'd')
			{
				guardian->setDireccionActual(Derecha);
				guardian->Mover();

				if (colisionConBasura) colisionConBasura = false;
			}
			else if (tecla == 'M' || tecla == 'm') /// plantar arbol
			{
				// verificamos que haya suficiente agua y semilla para plantar
				if (guardian->getCantAgua() > 0 &&
					guardian->getCantSemillas() > 0)
				{
					bool puedePlantar = true;

					// verificamos que no haya otro arbol plantado en esas coordenadas
					for (int i = 0; i < arboles.size(); i++)
					{
						if (guardian->getX() == arboles[i]->getX() &&
							guardian->getY() == arboles[i]->getY())
						{
							puedePlantar = false;
							break;
						}
					}

					if (puedePlantar)
					{
						AgregarArbol(guardian->getX(), guardian->getY());

						guardian->setCantAgua(guardian->getCantAgua() - 1);
						guardian->setCantSemillas(guardian->getCantSemillas() - 1);
						guardian->setPuntos(guardian->getPuntos() + puntosPlantarArbol);
					}
				}
			}
			else if (tecla == 'K' || tecla == 'k') /// disparar semilla
			{
				if (guardian->getCantSemillas() >= 1)
				{
					DispararSemillas(guardian->getX(), guardian->getY());

					guardian->setCantSemillas(guardian->getCantSemillas() - 1);
				}
			}
			else if (tecla == 'P' || tecla == 'p') /// Pausar juego
			{
				system("pause>0");
			}
			else if (tecla == 27)
			{
				// regresar la ventana a su configuracion inicial para evitar errores
				setFont(L"Cascadia Mono", 10, 20);
				Console::SetWindowSize(104, 28);
				break; // finalizar el juego si presiona ESC
			}
		}
		guardian->Dibujar();

	/// Dibujar ESTADISTICAS - NUMEROS
		// ---- Borrar estadisticas anteriores
		GoTo(9, 1);   cout << "   ";
		GoTo(18, 1);  cout << "   ";
		GoTo(25, 1);  cout << "   ";		
		GoTo(39, 7);  cout << "     ";
		// ---- Escribir estadisticas actualizadas
		GoTo(32, 5);  cout << guardian->getPuntos();
		GoTo(9, 1);   DibujarBarraVidas(guardian->getVidas());
		GoTo(18, 1);  cout << guardian->getCantAgua();
		GoTo(25, 1);  cout << guardian->getCantSemillas();

		setBkgTxtColor(0, 2);
		GoTo(39, 7);  cout << PorcentajeReforestacion() << "%";
		setBkgTxtColor(1, 0);
		
		if (PorcentajeReforestacion() >= 50 && musicaFinal == false)
		{
			RepNivelParteFinal();
			tiempoBasura = 4;
			musicaFinal = true;
		}

		if (AnalizarGameOver())
		//if (true)
		{
			// regresar la ventana a su configuracion inicial para evitar errores
			setFont(L"Cascadia Mono", 10, 20);
			Console::SetWindowSize(104, 28);
			LimpiarPantalla();

			if (DeterminarVictoria())
			//if (true)
			{
				MostrarMenuVictoria();
				RepGOVictoria();
				RepWinner();

				GoTo(26, 15);
				MostrarCursor();
				getline(cin, nick);
				EsconderCursor();

				guardian->setNombre(nick);

				opcReiniciarJuego = ObtenerOpcVictoria();

				/// Guardamos el puntaje en un archivo .dat
				GuardarPuntajes();
			}
			else
			{
				MostrarMenuDerrota();
				RepGODerrota();
				RepLoser();

				opcReiniciarJuego = ObtenerOpcDerrota();
			}

			if (opcReiniciarJuego == 1)
			{
				// configurar nuevo tamano y fuente para la ventana
				setFont(L"Cascadia Mono Semibold", 28, 38);
				Console::SetWindowSize(47, 19);
				ReiniciarEstado();

				LimpiarPantalla();
				MostrarUIJuego();
				RepNivelNormal();
			}
			else break;
		}

		Esperar(50);
	} while (true);
}

void GestionJuego::RevisarColisiones()
{
	vector<int> indicesSemillasEliminar;
	vector<int> indicesEnemigosEliminar;
	vector<int> indicesAguaEliminar;
	vector<int> indicesBasuraEliminar;

	//Colisiones guardian
	if (true) // Comprobando que el guardian no sea inmune
	{
		/// Guardian - Semilla
		for (int i = 0; i < semillas.size(); i++)
		{
			if (semillas[i]->getSeMueve()) continue; // Igoramos a las semillas que se mueven

			if (guardian->getRectangle().IntersectsWith(semillas[i]->getRectangle()))
			{
				indicesSemillasEliminar.push_back(i);

				guardian->setCantSemillas(guardian->getCantSemillas() + 1); // Incrementa la cntidad de semillas del guardian
				guardian->setPuntos(guardian->getPuntos() + puntosRecogerSemilla); // Incrementa los puntos
			}
		}

		/// Guardian - Agua
		for (int i = 0; i < aguas.size(); i++)
		{
			if (guardian->getRectangle().IntersectsWith(aguas[i]->getRectangle()))
			{
				indicesAguaEliminar.push_back(i);

				guardian->setCantAgua(guardian->getCantAgua() + 1); // Incrementa l cantidad de agua del guardian
				guardian->setPuntos(guardian->getPuntos() + puntosRecogerAgua); // Incrementa los puntos
			}
		}

		/// Guardian - Basura
		for (int i = 0; i < basuras.size(); i++)
		{
			if (guardian->getRectangle().IntersectsWith(basuras[i]->getRectangle()) && !colisionConBasura)
			{
				// El guardian pierde una vida
				if (guardian->getVidas() > 0) guardian->setVidas(guardian->getVidas() - 1);

				colisionConBasura = true;
				Esperar(800);
			}
		}

		/// Guardian - Enemigo
		for (int i = 0; i < enemigos.size(); i++)
		{
			if (guardian->getRectangle().IntersectsWith(enemigos[i]->getRectangle()))
			{
				indicesEnemigosEliminar.push_back(i);

				// El guardian pierde una vida
				if (guardian->getVidas() > 0) guardian->setVidas(guardian->getVidas() - 1);

				guardian->Borrar();
				Esperar(800);
			}
		}
	}

	//Colisiones semilas
	if (semillas.size() > 0)
	{
		for (int i = 0; i < semillas.size(); i++)
		{
			if (!semillas[i]->getSeMueve()) continue;

			/// Semilla - Enemigos
			for (int j = 0; j < enemigos.size(); j++)
			{
				if (semillas[i]->getRectangle().IntersectsWith(enemigos[j]->getRectangle()))
				{
					// Guardamos el indice de las semillas que seran eliminadas
					if (std::find(indicesSemillasEliminar.begin(), indicesSemillasEliminar.end(), i) == indicesSemillasEliminar.end())
						indicesSemillasEliminar.push_back(i);

					// Guardamos el indice de los enemigos que seran eliminados
					if (std::find(indicesEnemigosEliminar.begin(), indicesEnemigosEliminar.end(), j) == indicesEnemigosEliminar.end())
						indicesEnemigosEliminar.push_back(j);

					guardian->setPuntos(guardian->getPuntos() + puntosEliminarEnemigo);
					break;
				}
			}

			/// Semilla - Basura
			for (int j = 0; j < basuras.size(); j++)
			{
				if (semillas[i]->getRectangle().IntersectsWith(basuras[j]->getRectangle()))
				{
					// Guardamos el indice de las semillas que seran eliminadas
					if (std::find(indicesSemillasEliminar.begin(), indicesSemillasEliminar.end(), i) == indicesSemillasEliminar.end())
						indicesSemillasEliminar.push_back(i);

					// Guardamos el indice de las basuras que seran eliminadas
					if (std::find(indicesBasuraEliminar.begin(), indicesBasuraEliminar.end(), j) == indicesBasuraEliminar.end())
						indicesBasuraEliminar.push_back(j);

					guardian->setPuntos(guardian->getPuntos() + puntosDestruirBasura);
					break;
				}
			}

			/// eliminamos las semillas que traspasan los limites del escenario
			if (semillas[i]->getDireccionActual() == Arriba &&
				semillas[i]->getY() - 1 == 2)
			{
				// Guardamos el indice de las semillas que seran eliminadas
				if (std::find(indicesSemillasEliminar.begin(), 
					indicesSemillasEliminar.end(), i) == indicesSemillasEliminar.end())
					indicesSemillasEliminar.push_back(i);

				semillas[i]->Borrar();
			}
			else if (semillas[i]->getDireccionActual() == Abajo &&
				semillas[i]->getY() + 1 == 18)
			{
				// Guardamos el indice de las semillas que seran eliminadas
				if (std::find(indicesSemillasEliminar.begin(), 
					indicesSemillasEliminar.end(), i) == indicesSemillasEliminar.end())
					indicesSemillasEliminar.push_back(i);

				semillas[i]->Borrar();
			}
			else if (semillas[i]->getDireccionActual() == Izquierda &&
				semillas[i]->getX() - 1 == 0)
			{
				// Guardamos el indice de las semillas que seran eliminadas
				if (std::find(indicesSemillasEliminar.begin(), 
					indicesSemillasEliminar.end(), i) == indicesSemillasEliminar.end())
					indicesSemillasEliminar.push_back(i);

				semillas[i]->Borrar();
			}
			else if (semillas[i]->getDireccionActual() == Derecha &&
				semillas[i]->getX() + 1 == 21)
			{
				// Guardamos el indice de las semillas que seran eliminadas
				if (std::find(indicesSemillasEliminar.begin(), 
					indicesSemillasEliminar.end(), i) == indicesSemillasEliminar.end())
					indicesSemillasEliminar.push_back(i);

				semillas[i]->Borrar();
			}
		}
	}

	/// Eliminamos los elementos con los índices almacenados (procesar en orden inverso)
	for (auto it = indicesSemillasEliminar.rbegin(); it != indicesSemillasEliminar.rend(); ++it) {
		if (*it >= 0 && *it < semillas.size()) {  // Validar el índice
			delete semillas[*it];  // Liberar memoria si es un puntero
			semillas.erase(semillas.begin() + *it);
		}
	}

	for (auto it = indicesEnemigosEliminar.rbegin(); it != indicesEnemigosEliminar.rend(); ++it) {
		if (*it >= 0 && *it < enemigos.size()) {  // Validar el índice
			enemigos[*it]->Borrar();  // Borrar visualmente antes de eliminar
			delete enemigos[*it];  // Liberar memoria si es un puntero
			enemigos.erase(enemigos.begin() + *it);
		}
	}

	for (auto it = indicesBasuraEliminar.rbegin(); it != indicesBasuraEliminar.rend(); ++it) {
		if (*it >= 0 && *it < basuras.size()) {  // Validar el índice
			basuras[*it]->Borrar();
			delete basuras[*it];  // Liberar memoria si es un puntero
			basuras.erase(basuras.begin() + *it);
		}
	}

	for (auto it = indicesAguaEliminar.rbegin(); it != indicesAguaEliminar.rend(); ++it) {
		if (*it >= 0 && *it < aguas.size()) {  // Validar el índice
			delete aguas[*it];  // Liberar memoria si es un puntero
			aguas.erase(aguas.begin() + *it);
		}
	}
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
			setBkgTxtColor(0, 2);
			arboles[i]->Dibujar();
			setBkgTxtColor(1, 0);
		}
	}

	// Dibujar agua
	if (aguas.size() > 0) 
	{
		for (int i = 0; i < aguas.size(); i++) 
		{
			setBkgTxtColor(11, 0);
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

void GestionJuego::DispararSemillas(int x, int y)
{
	Semilla* s1 = new Semilla(x, y);
	Semilla* s2 = new Semilla(x, y);
	Semilla* s3 = new Semilla(x, y);
	Semilla* s4 = new Semilla(x, y);

	s1->setSeMueve(true);
	s2->setSeMueve(true);
	s3->setSeMueve(true);
	s4->setSeMueve(true);

	s1->setDireccionActual(Arriba);
	s2->setDireccionActual(Abajo);
	s3->setDireccionActual(Izquierda);
	s4->setDireccionActual(Derecha);

	semillas.push_back(s1);
	semillas.push_back(s2);
	semillas.push_back(s3);
	semillas.push_back(s4);
}

void GestionJuego::AgregarArbol(int x, int y)
{
	Arbol* a = new Arbol(x, y);
	arboles.push_back(a);
}

void GestionJuego::AgregarBasura()
{
	int r = GenerarNumeroAleatorio(0, enemigos.size() - 1);

	bool puedePoner = true;

	for (int i = 0; i < basuras.size(); i++)
	{
		if (enemigos[r]->getX() == basuras[i]->getX() &&
			enemigos[r]->getY() == basuras[i]->getY())
		{
			puedePoner = false;
		}
	}

	if (puedePoner)
	{
		cx = enemigos[r]->getX();
		cy = enemigos[r]->getY();

		Basura* b = new Basura(cx, cy);
		basuras.push_back(b);
	}
}

double GestionJuego::PorcentajeReforestacion()
{
	double porcentaje = (arboles.size() / 300.0) * 100;
	porcentaje = round(porcentaje * 10.0) / 10.0;

	return porcentaje;
}

bool GestionJuego::AnalizarGameOver()
{
	if (guardian->getVidas() <= 0 || PorcentajeReforestacion() >= 70)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool GestionJuego::DeterminarVictoria()
{
	if (PorcentajeReforestacion() >= 70 && guardian->getVidas() > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void GestionJuego::GuardarPuntajes()
{
	GestionPuntajes rank("Resources/Data/Puntaje.dat");

	Puntaje pts;
	pts.nombre = guardian->getNombre();
	pts.puntos = guardian->getPuntos();

	rank.GuardarPuntaje(pts);
}

void GestionJuego::ReiniciarEstado()
{
	/// limpiamos todos los vectores de elementos
	aguas.clear();
	semillas.clear();
	arboles.clear();
	basuras.clear();
	enemigos.clear();

	guardian->ReiniciarEstado();

	IniciarElementos();
}