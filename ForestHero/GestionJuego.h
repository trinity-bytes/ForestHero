#pragma once
#include "Utilidades/GestionPuntajes.h"
#include "Utilidades/UI Ascii.h"
#include "Utilidades/Musica.h"
#include "Entidades/Personajes/Guardian.h"
#include "Entidades/Personajes/Enemigo.h"
#include "Entidades/Items/Potenciador.h"
#include "Entidades/Items/Agua.h"
#include "Entidades/Items/Semilla.h"
#include "Entidades/Items/Arbol.h"
#include "Entidades/Items/Basura.h"
#include "Entidades/Factorias/FabricaEntidad.h"
#include "Entidades/Pools/PoolSemillas.h"
#include "Estados/EstadoJuego.h"
#include "Sistemas/GridColisiones.h"
#include "Sistemas/SistemaEventos.h"
#include "vector"
#include "conio.h"
#include <algorithm> // Para std::sort y std::unique
#include <string>    // Para std::to_string y manipulación de strings
#include <iomanip>   // Para std::fixed y std::setprecision (alternativa para formatear double)

class GestionJuego
{
private:
	Guardian* guardian;
	Potenciador* potenciador;

	vector<Agua*> aguas;
	vector<Semilla*> semillas;
	vector<Arbol*> arboles;
	vector<Basura*> basuras;
	vector<Enemigo*> enemigos;

	// clock_t t, tsAgua, tsSemilla, tsEnemigos, tsBasura, tsPowerUp; // Ya no se usan
	// int segundosAgua = 0, segundosSemilla = 0, segundosEnemigos = 0, segundosBasura = 0, segundosPowerUp = 0; // Ya no se usan

	const int tiempoAgua = 3;       // Segundos
	const int tiempoSemilla = 2;    // Segundos
	const int tiempoEnemigos = 25;  // Segundos
	const int tiempoPowerUp = 30;   // Segundos (Aumentado para que sea más probable que aparezca)

	int tiempoBasura = 7; // Su valor cambia en la parte final del nivel
	int opcReiniciarJuego = 0;

	// Para el power-up de inmunidad del guardián (cuenta de ticks del bucle de juego fijo)
	int pseudoTimer = 0;
	// Para cooldown después de colisión con basura (cuenta de ticks del bucle de juego fijo)
	int cooldownColisionBasura = 0;
	// Para cooldown después de colisión con enemigo (cuenta de ticks del bucle de juego fijo)
	int cooldownColisionEnemigo = 0;
	// Si MS_POR_ACTUALIZACION es 16.666 (60FPS), 800ms son 800/16.666 ~= 48 ticks.
	double MS_POR_ACTUALIZACION = 16.666; // Milisegundos por actualización (aprox. 60 FPS)
	// Si MS_POR_ACTUALIZACION es 16.666 (60FPS), 800ms son 800/16.666 ~= 48 ticks.
	const int DURACION_COOLDOWN_COLISION = 48;


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

	bool colisionConBasura = false; // Podría usarse para una breve interrupción del movimiento si se desea.
	// bool continuar = true; // No parece usarse, considerar eliminar.
	// bool victoria = false; // El estado del juego se maneja con GestorEstados
	bool musicaFinal = false;
	bool guardianInmune = false; // Para el PowerUp y cooldowns

	// Temporizadores basados en tiempo real
	double tiempoAcumuladoAgua = 0.0;
	double tiempoAcumuladoSemilla = 0.0;
	double tiempoAcumuladoEnemigos = 0.0;
	double tiempoAcumuladoBasura = 0.0;
	double tiempoAcumuladoPowerUp = 0.0;

	string nick;

	// para las coordenadas de los objetos que se van a generar
	int cx, cy;
public:
	GestionJuego();
	~GestionJuego();

	void IniciarElementos();
	void actualizarTemporizadores(double deltaSegundos);
	void RevisarColisiones();
	void MoverTodo();
	void DibujarMarcoUI(BufferPantalla* buffer); // NUEVA FUNCIÓN
	void DibujarTodo(BufferPantalla* buffer = nullptr);
	void IniciarJuego();
	void AgregarEnemigo();
	void AgregarAgua();
	void AgregarSemilla();
	void DispararSemillas(int, int);
	void AgregarArbol(int, int);
	void AgregarBasura();
	void InvocarPowerUp();
	double PorcentajeReforestacion();
	bool AnalizarGameOver(); // Determina si el juego ha terminado (victoria o derrota)
	bool DeterminarVictoria(); // Específicamente si es victoria
	void GuardarPuntajes();
	void ReiniciarEstado(); // Prepara para un nuevo juego
};

GestionJuego::GestionJuego()
{
	aguas = vector<Agua*>();
	semillas = vector<Semilla*>();
	arboles = vector<Arbol*>();
	basuras = vector<Basura*>();
	enemigos = vector<Enemigo*>();

	guardian = FabricaEntidad::obtenerInstancia()->crearGuardian(10, 8);
	potenciador = FabricaEntidad::obtenerInstancia()->crearPotenciador(0, 0);

	IniciarElementos();

	// Registrar suscriptores para eventos
	SistemaEventos::obtenerInstancia()->suscribir(TipoEvento::AguaRecogida,
		[this](void* datos) {
			// Ejemplo: PlaySound(TEXT("Resources/Sound/agua.wav"), NULL, SND_ASYNC | SND_FILENAME);
		});

	SistemaEventos::obtenerInstancia()->suscribir(TipoEvento::SemillaDisparada,
		[this](void* datos) {
			// Ejemplo: PlaySound(TEXT("Resources/Sound/disparo.wav"), NULL, SND_ASYNC | SND_FILENAME);
		});

	SistemaEventos::obtenerInstancia()->suscribir(TipoEvento::ArbolPlantado,
		[this](void* datos) {
			// Ejemplo: PlaySound(TEXT("Resources/Sound/plantar.wav"), NULL, SND_ASYNC | SND_FILENAME);
		});

	SistemaEventos::obtenerInstancia()->suscribir(TipoEvento::EnemigoEliminado,
		[this](void* datos) {
			// Ejemplo: PlaySound(TEXT("Resources/Sound/enemigo_hit.wav"), NULL, SND_ASYNC | SND_FILENAME);
		});

	SistemaEventos::obtenerInstancia()->suscribir(TipoEvento::BasuraDestruida,
		[this](void* datos) {
			// Ejemplo: PlaySound(TEXT("Resources/Sound/basura_hit.wav"), NULL, SND_ASYNC | SND_FILENAME);
		});

	SistemaEventos::obtenerInstancia()->suscribir(TipoEvento::GuardianDañado,
		[this](void* datos) {
			// Ejemplo: PlaySound(TEXT("Resources/Sound/guardian_hit.wav"), NULL, SND_ASYNC | SND_FILENAME);
		});

	SistemaEventos::obtenerInstancia()->suscribir(TipoEvento::PotenciadorRecogido,
		[this](void* datos) {
			// Ejemplo: PlaySound(TEXT("Resources/Sound/powerup.wav"), NULL, SND_ASYNC | SND_FILENAME);
		});
}

GestionJuego::~GestionJuego()
{
	delete guardian;
	delete potenciador;
	for (auto agua : aguas) delete agua;
	// Las semillas activas se devuelven al pool en RevisarColisiones o ReiniciarEstado.
	// El PoolSemillas se encarga de la memoria de las semillas que contiene en su propio destructor.
	for (auto arbol : arboles) delete arbol;
	for (auto basura : basuras) delete basura;
	for (auto enemigo : enemigos) delete enemigo;
}

void GestionJuego::IniciarJuego()
{
	BufferPantalla& buffer = BufferPantalla::obtenerInstancia();
	GestorEstados::obtenerInstancia()->cambiarEstado(EstadoJuego::Jugando);

	CambiarFuenteConsola(L"Cascadia Mono", { 0, 16 }); // Use "Cascadia Mono" and a smaller size for game
	Console::SetWindowSize(47, 19);
	// BufferPantalla should ideally re-initialize or adapt if console character dimensions change.
	// For now, assume it adapts or is created after these calls.

	RepNivelNormal();

	// Resetear estado para un nuevo juego o al iniciar por primera vez
	ReiniciarEstado();

	// Re-inicializar temporizadores y flags para el nuevo juego
	tiempoAcumuladoAgua = 0.0;
	tiempoAcumuladoSemilla = 0.0;
	tiempoAcumuladoEnemigos = 0.0;
	tiempoAcumuladoBasura = 0.0;
	tiempoAcumuladoPowerUp = 0.0;
	pseudoTimer = 0;
	cooldownColisionBasura = 0;
	cooldownColisionEnemigo = 0;
	guardianInmune = false;
	musicaFinal = false;
	colisionConBasura = false;

	ULONGLONG tiempoAnterior = GetTickCount64();
	double acumulador = 0.0;

	do
	{
		ULONGLONG tiempoActual = GetTickCount64();
		double tiempoPasado = static_cast<double>(tiempoActual - tiempoAnterior);
		tiempoAnterior = tiempoActual;

		if (tiempoPasado > 250.0) tiempoPasado = 250.0; // Cap frame time
		acumulador += tiempoPasado;

		if (kbhit())
		{
			char tecla = getch();
			bool seMovio = false;

			if (tecla == 'W' || tecla == 'w') { guardian->setDireccion(Direccion::Arriba); seMovio = true; }
			else if (tecla == 'S' || tecla == 's') { guardian->setDireccion(Direccion::Abajo); seMovio = true; }
			else if (tecla == 'A' || tecla == 'a') { guardian->setDireccion(Direccion::Izquierda); seMovio = true; }
			else if (tecla == 'D' || tecla == 'd') { guardian->setDireccion(Direccion::Derecha); seMovio = true; }

			if (seMovio) {
				guardian->mover();
				if (colisionConBasura) colisionConBasura = false;
			}
			else if (tecla == 'M' || tecla == 'm')
			{
				if (guardian->getCantAgua() > 0 && guardian->getCantSemillas() > 0)
				{
					bool puedePlantar = true;
					for (size_t i = 0; i < arboles.size(); i++) {
						if (guardian->getX() == arboles[i]->getX() && guardian->getY() == arboles[i]->getY()) {
							puedePlantar = false; break;
						}
					}
					if (puedePlantar) {
						AgregarArbol(guardian->getX(), guardian->getY());
						guardian->setCantAgua(guardian->getCantAgua() - 1);
						guardian->setCantSemillas(guardian->getCantSemillas() - 1);
						guardian->setPuntos(guardian->getPuntos() + puntosPlantarArbol);
					}
				}
			}
			else if (tecla == 'K' || tecla == 'k')
			{
				if (guardian->getCantSemillas() >= 1) {
					DispararSemillas(guardian->getX(), guardian->getY());
					guardian->setCantSemillas(guardian->getCantSemillas() - 1);
				}
			}
			else if (tecla == 'P' || tecla == 'p')
			{
				EstadoJuego estadoActual = GestorEstados::obtenerInstancia()->getEstadoActual();
				if (estadoActual == EstadoJuego::Jugando) {
					GestorEstados::obtenerInstancia()->cambiarEstado(EstadoJuego::Pausado);
					buffer.dibujarTexto(18, 9, "PAUSA", 1, 4);
					buffer.intercambiar();
					char teclaPausa;
					do {
						teclaPausa = getch();
					} while (teclaPausa != 'p' && teclaPausa != 'P');
					GestorEstados::obtenerInstancia()->cambiarEstado(EstadoJuego::Jugando);
				}
			}
			else if (tecla == 27) // ESC - Return to Menu
			{
				// Restore console settings for the main menu
				CambiarFuenteConsola(L"Cascadia Mono", { 0, 20 }); // Menu font size
				Console::SetWindowSize(104, 28);                   // Menu window size
				// Note: If BufferPantalla uses SetConsoleActiveScreenBuffer, it might need
				// to explicitly restore the original standard output buffer here or before
				// this function returns to ensure std::cout works correctly for the menu.
				GestorEstados::obtenerInstancia()->cambiarEstado(EstadoJuego::MenuPrincipal);
			}
		}

		while (acumulador >= MS_POR_ACTUALIZACION)
		{
			if (GestorEstados::obtenerInstancia()->getEstadoActual() == EstadoJuego::Jugando)
			{
				RevisarColisiones();
				MoverTodo();
				actualizarTemporizadores(MS_POR_ACTUALIZACION / 1000.0);

				// Cooldown/immunity logic
				if (pseudoTimer > 0) {
					pseudoTimer--;
					if (pseudoTimer == 0 && cooldownColisionBasura == 0 && cooldownColisionEnemigo == 0) {
						guardianInmune = false;
					}
				}
				if (cooldownColisionBasura > 0) {
					cooldownColisionBasura--;
					if (cooldownColisionBasura == 0 && pseudoTimer == 0 && cooldownColisionEnemigo == 0) {
						guardianInmune = false;
					}
				}
				if (cooldownColisionEnemigo > 0) {
					cooldownColisionEnemigo--;
					if (cooldownColisionEnemigo == 0 && pseudoTimer == 0 && cooldownColisionBasura == 0) {
						guardianInmune = false;
					}
				}
			}
			acumulador -= MS_POR_ACTUALIZACION;
		}

		if (GestorEstados::obtenerInstancia()->getEstadoActual() != EstadoJuego::Jugando &&
			GestorEstados::obtenerInstancia()->getEstadoActual() != EstadoJuego::Pausado) {
			break; // Exit game loop if state changed to Menu, GameOver, etc.
		}

		buffer.limpiar();
		DibujarTodo(&buffer);

		// Draw dynamic UI elements
		buffer.dibujarTexto(32, 5, std::to_string(guardian->getPuntos()), 1, 0);
		DibujarBarraVidasEnBuffer(&buffer, 9, 1, guardian->getVidas());
		buffer.dibujarTexto(18, 1, std::to_string(guardian->getCantAgua()), 1, 0);
		buffer.dibujarTexto(25, 1, std::to_string(guardian->getCantSemillas()), 1, 0);

		std::string porcentajeStr = std::to_string(PorcentajeReforestacion());
		size_t decimalPos = porcentajeStr.find('.');
		if (decimalPos != std::string::npos) {
			porcentajeStr = porcentajeStr.substr(0, decimalPos + 2);
		}
		buffer.dibujarTexto(39, 7, porcentajeStr + "%", 1, 2);

		buffer.intercambiar();

		if (PorcentajeReforestacion() >= 50 && !musicaFinal) {
			RepNivelParteFinal();
			tiempoBasura = 4;
			musicaFinal = true;
		}

		if (AnalizarGameOver())
		{
			// Restore console for Game Over/Victory screens (typically larger like menu)
			CambiarFuenteConsola(L"Cascadia Mono", { 0, 20 });
			Console::SetWindowSize(104, 28);

			if (DeterminarVictoria()) {
				GestorEstados::obtenerInstancia()->cambiarEstado(EstadoJuego::Victoria);
				RepGOVictoria(); RepWinner();
				GoTo(26, 15); MostrarCursor(); getline(cin, nick); EsconderCursor();
				guardian->setNombre(nick);
				opcReiniciarJuego = ObtenerOpcVictoria();
				GuardarPuntajes();
			}
			else {
				GestorEstados::obtenerInstancia()->cambiarEstado(EstadoJuego::GameOver);
				RepGODerrota(); RepLoser();
				opcReiniciarJuego = ObtenerOpcDerrota();
			}

			if (opcReiniciarJuego == 1) { // Play Again
				GestorEstados::obtenerInstancia()->cambiarEstado(EstadoJuego::Jugando);
				// Reset time and accumulator for the new game session
				tiempoAnterior = GetTickCount64();
				acumulador = 0.0;
				// Re-apply console settings for the game
				CambiarFuenteConsola(L"Cascadia Mono", { 0, 16 }); // Game font
				Console::SetWindowSize(47, 19);                   // Game window size
				RepNivelNormal();
				// ReiniciarEstado() will be called at the beginning of the next loop iteration
				// or at the start of IniciarJuego if it were structured to be re-entrant.
				// Current structure: loop continues, ReiniciarEstado() is at the top.
			}
			else { // Go to Main Menu
				GestorEstados::obtenerInstancia()->cambiarEstado(EstadoJuego::MenuPrincipal);
				// Console settings for menu are already set (104x28, font {0,20})
			}
		}
	} while (GestorEstados::obtenerInstancia()->getEstadoActual() == EstadoJuego::Jugando ||
		GestorEstados::obtenerInstancia()->getEstadoActual() == EstadoJuego::Pausado);

	// If exiting IniciarJuego to go to another state (e.g. MenuPrincipal via ESC),
	// ensure console settings are appropriate for that state.
	// This is handled by the ESC block and the GameOver/Victory block.
}

void GestionJuego::actualizarTemporizadores(double deltaSegundos)
{
	tiempoAcumuladoAgua += deltaSegundos;
	if (tiempoAcumuladoAgua >= tiempoAgua) {
		tiempoAcumuladoAgua -= tiempoAgua;
		if (aguas.size() < limiteAgua) AgregarAgua();
	}

	tiempoAcumuladoSemilla += deltaSegundos;
	if (tiempoAcumuladoSemilla >= tiempoSemilla) {
		tiempoAcumuladoSemilla -= tiempoSemilla;
		if (semillas.size() < limiteSemillas) AgregarSemilla();
	}

	tiempoAcumuladoEnemigos += deltaSegundos;
	if (tiempoAcumuladoEnemigos >= tiempoEnemigos) {
		tiempoAcumuladoEnemigos -= tiempoEnemigos;
		if (enemigos.size() < limiteEnemigos) AgregarEnemigo();
	}

	tiempoAcumuladoBasura += deltaSegundos;
	if (tiempoAcumuladoBasura >= tiempoBasura) {
		tiempoAcumuladoBasura -= tiempoBasura;
		if (!enemigos.empty()) AgregarBasura();
	}

	tiempoAcumuladoPowerUp += deltaSegundos;
	if (tiempoAcumuladoPowerUp >= tiempoPowerUp) {
		tiempoAcumuladoPowerUp -= tiempoPowerUp;
		if (pseudoTimer == 0 && !potenciador->getVisible()) {
			InvocarPowerUp();
		}
	}
}

void GestionJuego::RevisarColisiones()
{
	vector<int> indicesSemillasEliminar;
	vector<int> indicesEnemigosEliminar;
	vector<int> indicesAguaEliminar;
	vector<int> indicesBasuraEliminar;

	vector<Agua*> aguasColisionadasGuardian;
	vector<Semilla*> semillasColisionadasGuardian;
	vector<Enemigo*> enemigosColisionadosGuardian;

	vector<Semilla*> semillasMovilesParaEliminar;
	vector<Enemigo*> enemigosGolpeadosPorSemilla;
	vector<Basura*> basuraGolpeadaPorSemilla;

	GridColisiones grid;
	grid.limpiar();

	for (auto& agua : aguas) if (agua->getActivo()) grid.registrarEntidad(agua);
	for (auto& semilla : semillas) if (semilla->getActivo()) grid.registrarEntidad(semilla);
	for (auto& basura : basuras) if (basura->getActivo()) grid.registrarEntidad(basura);
	for (auto& enemigo : enemigos) if (enemigo->getActivo()) grid.registrarEntidad(enemigo);
	if (potenciador->getVisible()) grid.registrarEntidad(potenciador);

	// --- Colisiones del Guardián ---
	bool guardianSufrioDañoEsteFrame = false;

	auto entidadesCercanasGuardian = grid.obtenerEntidadesCercanas(guardian->getX(), guardian->getY());
	for (const auto& entidad : entidadesCercanasGuardian)
	{
		if (!entidad->getActivo()) continue;

		if (guardian->getRectangle().IntersectsWith(entidad->getRectangle()))
		{
			switch (entidad->getTipo())
			{
			case TipoEntidad::Agua:
			{
				guardian->setCantAgua(guardian->getCantAgua() + 1);
				guardian->setPuntos(guardian->getPuntos() + puntosRecogerAgua);
				aguasColisionadasGuardian.push_back(static_cast<Agua*>(entidad));
				SistemaEventos::obtenerInstancia()->publicar(TipoEvento::AguaRecogida, entidad);
				break;
			}
			case TipoEntidad::Basura:
			{
				if (!guardianInmune && cooldownColisionBasura == 0) {
					if (guardian->getVidas() > 0) guardian->setVidas(guardian->getVidas() - 1);
					SistemaEventos::obtenerInstancia()->publicar(TipoEvento::GuardianDañado, guardian);
					colisionConBasura = true;
					cooldownColisionBasura = DURACION_COOLDOWN_COLISION;
					guardianInmune = true;
					guardianSufrioDañoEsteFrame = true;
				}
				break;
			}
			case TipoEntidad::Enemigo:
			{
				if (!guardianInmune && cooldownColisionEnemigo == 0) {
					if (guardian->getVidas() > 0) guardian->setVidas(guardian->getVidas() - 1);
					SistemaEventos::obtenerInstancia()->publicar(TipoEvento::GuardianDañado, guardian);
					enemigosColisionadosGuardian.push_back(static_cast<Enemigo*>(entidad));
					cooldownColisionEnemigo = DURACION_COOLDOWN_COLISION;
					guardianInmune = true;
					guardianSufrioDañoEsteFrame = true;
				}
				break;
			}
			case TipoEntidad::Semilla:
			{
				Semilla* semillaPtr = static_cast<Semilla*>(entidad);
				if (!semillaPtr->getSeMueve()) {
					guardian->setCantSemillas(guardian->getCantSemillas() + 1);
					guardian->setPuntos(guardian->getPuntos() + puntosRecogerSemilla);
					semillasColisionadasGuardian.push_back(semillaPtr);
					SistemaEventos::obtenerInstancia()->publicar(TipoEvento::SemillaRecogida, entidad);
				}
				break;
			}
			case TipoEntidad::PowerUp:
			{
				if (entidad == potenciador && potenciador->getVisible()) {
					pseudoTimer = 5 * (int)(1000.0 / MS_POR_ACTUALIZACION);
					guardianInmune = true;
					potenciador->setVisible(false);
					SistemaEventos::obtenerInstancia()->publicar(TipoEvento::PotenciadorRecogido, guardian);
					cooldownColisionBasura = 0;
					cooldownColisionEnemigo = 0;
				}
				break;
			}
			default:
				break;
			}
		}
	}

	if (!guardianSufrioDañoEsteFrame && pseudoTimer == 0 && cooldownColisionBasura == 0 && cooldownColisionEnemigo == 0) {
		guardianInmune = false;
	}


	// --- Colisiones de Semillas Móviles ---
	for (Semilla* semillaActual : semillas)
	{
		if (!semillaActual->getActivo() || !semillaActual->getSeMueve()) continue;

		bool semillaImpacto = false;
		auto entidadesCercanasSemilla = grid.obtenerEntidadesCercanas(semillaActual->getX(), semillaActual->getY());

		for (const auto& entidadGolpeada : entidadesCercanasSemilla)
		{
			if (!entidadGolpeada->getActivo() || entidadGolpeada == semillaActual) continue;

			if (semillaActual->getRectangle().IntersectsWith(entidadGolpeada->getRectangle()))
			{
				if (entidadGolpeada->getTipo() == TipoEntidad::Enemigo)
				{
					enemigosGolpeadosPorSemilla.push_back(static_cast<Enemigo*>(entidadGolpeada));
					guardian->setPuntos(guardian->getPuntos() + puntosEliminarEnemigo);
					semillaImpacto = true;
					break;
				}
				else if (entidadGolpeada->getTipo() == TipoEntidad::Basura)
				{
					basuraGolpeadaPorSemilla.push_back(static_cast<Basura*>(entidadGolpeada));
					guardian->setPuntos(guardian->getPuntos() + puntosDestruirBasura);
					semillaImpacto = true;
					break;
				}
			}
		}

		if (semillaImpacto) {
			semillasMovilesParaEliminar.push_back(semillaActual);
		}
		else {
			if ((semillaActual->getDireccion() == Direccion::Arriba && semillaActual->getY() - 1 <= 2) ||
				(semillaActual->getDireccion() == Direccion::Abajo && semillaActual->getY() + 1 >= 18) ||
				(semillaActual->getDireccion() == Direccion::Izquierda && semillaActual->getX() - 1 <= 0) ||
				(semillaActual->getDireccion() == Direccion::Derecha && semillaActual->getX() + 1 >= 21))
			{
				semillasMovilesParaEliminar.push_back(semillaActual);
			}
		}
	}

	// --- Procesar Eliminaciones ---
	auto add_unique_index = [](vector<int>& indices, int index_to_add) {
		if (std::find(indices.begin(), indices.end(), index_to_add) == indices.end()) {
			indices.push_back(index_to_add);
		}
		};

	for (Agua* aguaPtr : aguasColisionadasGuardian) {
		auto it = std::find(aguas.begin(), aguas.end(), aguaPtr);
		if (it != aguas.end()) add_unique_index(indicesAguaEliminar, std::distance(aguas.begin(), it));
	}
	for (Semilla* semillaPtr : semillasColisionadasGuardian) {
		auto it = std::find(semillas.begin(), semillas.end(), semillaPtr);
		if (it != semillas.end()) add_unique_index(indicesSemillasEliminar, std::distance(semillas.begin(), it));
	}
	for (Semilla* semillaPtr : semillasMovilesParaEliminar) {
		auto it = std::find(semillas.begin(), semillas.end(), semillaPtr);
		if (it != semillas.end()) add_unique_index(indicesSemillasEliminar, std::distance(semillas.begin(), it));
	}
	for (Enemigo* enemigoPtr : enemigosColisionadosGuardian) {
		auto it = std::find(enemigos.begin(), enemigos.end(), enemigoPtr);
		if (it != enemigos.end()) {
			add_unique_index(indicesEnemigosEliminar, std::distance(enemigos.begin(), it));
			SistemaEventos::obtenerInstancia()->publicar(TipoEvento::EnemigoEliminado, enemigoPtr);
		}
	}
	for (Enemigo* enemigoPtr : enemigosGolpeadosPorSemilla) {
		auto it = std::find(enemigos.begin(), enemigos.end(), enemigoPtr);
		if (it != enemigos.end()) {
			add_unique_index(indicesEnemigosEliminar, std::distance(enemigos.begin(), it));
			SistemaEventos::obtenerInstancia()->publicar(TipoEvento::EnemigoEliminado, enemigoPtr);
		}
	}
	for (Basura* basuraPtr : basuraGolpeadaPorSemilla) {
		auto it = std::find(basuras.begin(), basuras.end(), basuraPtr);
		if (it != basuras.end()) {
			add_unique_index(indicesBasuraEliminar, std::distance(basuras.begin(), it));
			SistemaEventos::obtenerInstancia()->publicar(TipoEvento::BasuraDestruida, basuraPtr);
		}
	}

	std::sort(indicesSemillasEliminar.rbegin(), indicesSemillasEliminar.rend());
	std::sort(indicesEnemigosEliminar.rbegin(), indicesEnemigosEliminar.rend());
	std::sort(indicesAguaEliminar.rbegin(), indicesAguaEliminar.rend());
	std::sort(indicesBasuraEliminar.rbegin(), indicesBasuraEliminar.rend());

	indicesSemillasEliminar.erase(std::unique(indicesSemillasEliminar.begin(), indicesSemillasEliminar.end()), indicesSemillasEliminar.end());
	indicesEnemigosEliminar.erase(std::unique(indicesEnemigosEliminar.begin(), indicesEnemigosEliminar.end()), indicesEnemigosEliminar.end());
	indicesAguaEliminar.erase(std::unique(indicesAguaEliminar.begin(), indicesAguaEliminar.end()), indicesAguaEliminar.end());
	indicesBasuraEliminar.erase(std::unique(indicesBasuraEliminar.begin(), indicesBasuraEliminar.end()), indicesBasuraEliminar.end());


	for (int index : indicesSemillasEliminar) {
		if (index >= 0 && static_cast<size_t>(index) < semillas.size()) {
			PoolSemillas::obtenerInstancia()->devolverSemilla(semillas[index]);
			semillas.erase(semillas.begin() + index);
		}
	}
	for (int index : indicesEnemigosEliminar) {
		if (index >= 0 && static_cast<size_t>(index) < enemigos.size()) {
			delete enemigos[index];
			enemigos.erase(enemigos.begin() + index);
		}
	}
	for (int index : indicesBasuraEliminar) {
		if (index >= 0 && static_cast<size_t>(index) < basuras.size()) {
			delete basuras[index];
			basuras.erase(basuras.begin() + index);
		}
	}
	for (int index : indicesAguaEliminar) {
		if (index >= 0 && static_cast<size_t>(index) < aguas.size()) {
			delete aguas[index];
			aguas.erase(aguas.begin() + index);
		}
	}
}

void GestionJuego::MoverTodo()
{
	int r;
	if (!enemigos.empty()) {
		for (size_t i = 0; i < enemigos.size(); i++) {
			if (!enemigos[i]->getActivo()) continue;
			r = GenerarNumeroAleatorio(1, 60);
			switch (r) {
			case 1:  enemigos[i]->setDireccion(Direccion::Arriba); break;
			case 20: enemigos[i]->setDireccion(Direccion::Abajo); break;
			case 40: enemigos[i]->setDireccion(Direccion::Izquierda); break;
			case 60: enemigos[i]->setDireccion(Direccion::Derecha); break;
			default: enemigos[i]->setDireccion(Direccion::Ninguna); break;
			}
			enemigos[i]->mover();
		}
	}
	if (!semillas.empty()) {
		for (size_t i = 0; i < semillas.size(); i++) {
			if (!semillas[i]->getActivo()) continue;
			if (semillas[i]->getSeMueve()) semillas[i]->mover();
		}
	}
}

void GestionJuego::DibujarMarcoUI(BufferPantalla* buffer) {
	if (!buffer) buffer = &BufferPantalla::obtenerInstancia();
	int colorTextoMarco = 1;
	int colorFondoMarco = 0;

	buffer->dibujarTexto(0, 0, u8"╔════════════════════╦════════════════════════╗", colorTextoMarco, colorFondoMarco);
	buffer->dibujarTexto(0, 1, u8"║  Vidas:            #:     #:                 ║", colorTextoMarco, colorFondoMarco);
	buffer->dibujarTexto(21, 1, u8"║", colorTextoMarco, colorFondoMarco);
	buffer->dibujarTexto(46, 1, u8"║", colorTextoMarco, colorFondoMarco);
	buffer->dibujarTexto(28, 1, u8"ESC: Salir", colorTextoMarco, colorFondoMarco);


	buffer->dibujarTexto(0, 2, u8"╠════════════════════╩════════════════════════╣", colorTextoMarco, colorFondoMarco);

	for (int y = 3; y <= 17; ++y) {
		buffer->dibujarTexto(0, y, u8"║", colorTextoMarco, colorFondoMarco);
		buffer->dibujarTexto(21, y, u8"║", colorTextoMarco, colorFondoMarco);
		buffer->dibujarTexto(46, y, u8"║", colorTextoMarco, colorFondoMarco);
	}

	buffer->dibujarTexto(23, 3, u8">>> ForestHero <<<", 11, colorFondoMarco);
	buffer->dibujarTexto(23, 5, u8"Puntos:", colorTextoMarco, colorFondoMarco);
	buffer->dibujarTexto(23, 7, u8"Reforestacion:", colorTextoMarco, colorFondoMarco);

	buffer->dibujarTexto(21, 9, u8"╠════════════════════════╣", colorTextoMarco, colorFondoMarco);
	buffer->dibujarTexto(23, 10, u8" : Agua     : Semilla", colorTextoMarco, colorFondoMarco);
	buffer->dibujarTexto(23, 11, u8" : Arbol    : Enemigo", colorTextoMarco, colorFondoMarco);
	buffer->dibujarTexto(23, 12, u8" : Basura", colorTextoMarco, colorFondoMarco);

	Agua tempAgua(0, 0); Semilla tempSemilla(0, 0); Arbol tempArbol(0, 0); Enemigo tempEnemigo(0, 0); Basura tempBasura(0, 0);
	buffer->dibujarTexto(24, 10, tempAgua.getForma(), 11, 0);
	buffer->dibujarTexto(35, 10, tempSemilla.getForma(), 6, 0);
	buffer->dibujarTexto(24, 11, tempArbol.getForma(), 2, 0);
	buffer->dibujarTexto(35, 11, tempEnemigo.getForma(), 4, 0);
	buffer->dibujarTexto(24, 12, tempBasura.getForma(), 5, 0);


	buffer->dibujarTexto(21, 13, u8"╠════════════════════════╣", colorTextoMarco, colorFondoMarco);
	buffer->dibujarTexto(23, 14, u8"W,A,S,D: Movimiento", colorTextoMarco, colorFondoMarco);
	buffer->dibujarTexto(23, 15, u8"M: Plantar arbol", colorTextoMarco, colorFondoMarco);
	buffer->dibujarTexto(23, 16, u8"K: Disparar semillas", colorTextoMarco, colorFondoMarco);
	buffer->dibujarTexto(23, 17, u8"P: Pausar el juego", colorTextoMarco, colorFondoMarco);

	buffer->dibujarTexto(0, 18, u8"╚════════════════════╩════════════════════════╝", colorTextoMarco, colorFondoMarco);
}


void GestionJuego::DibujarTodo(BufferPantalla* buffer)
{
	if (!buffer) buffer = &BufferPantalla::obtenerInstancia();

	DibujarMarcoUI(buffer);

	for (Arbol* arbol_obj : arboles) if (arbol_obj->getActivo()) arbol_obj->dibujarConColor(buffer, 0, 2);
	for (Agua* agua_obj : aguas) if (agua_obj->getActivo()) agua_obj->dibujarConColor(buffer, 11, 0);
	for (Semilla* semilla_obj : semillas) if (semilla_obj->getActivo()) semilla_obj->dibujarConColor(buffer, 6, 0);
	for (Basura* basura_obj : basuras) if (basura_obj->getActivo()) basura_obj->dibujarConColor(buffer, 0, 5);
	for (Enemigo* enemigo_obj : enemigos) if (enemigo_obj->getActivo()) enemigo_obj->dibujarConColor(buffer, 1, 4);

	if (potenciador->getVisible()) {
		potenciador->dibujarConColor(buffer, 1, 13);
	}
	if (guardian->getActivo()) guardian->dibujarConColor(buffer, 1, 0);
}

void GestionJuego::IniciarElementos()
{
	for (int i = 0; i < cantInicialEnemigos; i++) AgregarEnemigo();
	for (int i = 0; i < cantInicialAgua; i++) AgregarAgua();
	for (int i = 0; i < cantInicialSemillas; i++) AgregarSemilla();
}

void GestionJuego::AgregarEnemigo()
{
	cx = GenerarNumeroAleatorio(2, 20); cy = GenerarNumeroAleatorio(3, 17);
	Enemigo* e = FabricaEntidad::obtenerInstancia()->crearEnemigo(cx, cy);
	enemigos.push_back(e);
}

void GestionJuego::AgregarAgua()
{
	cx = GenerarNumeroAleatorio(2, 20); cy = GenerarNumeroAleatorio(3, 17);
	Agua* a = FabricaEntidad::obtenerInstancia()->crearAgua(cx, cy);
	aguas.push_back(a);
}

void GestionJuego::AgregarSemilla()
{
	cx = GenerarNumeroAleatorio(2, 20); cy = GenerarNumeroAleatorio(3, 17);
	Semilla* s = PoolSemillas::obtenerInstancia()->obtenerSemilla(cx, cy);
	semillas.push_back(s);
}

void GestionJuego::DispararSemillas(int x, int y)
{
	PoolSemillas* pool = PoolSemillas::obtenerInstancia();
	semillas.push_back(pool->obtenerSemilla(x, y, true, Direccion::Arriba));
	semillas.push_back(pool->obtenerSemilla(x, y, true, Direccion::Abajo));
	semillas.push_back(pool->obtenerSemilla(x, y, true, Direccion::Izquierda));
	semillas.push_back(pool->obtenerSemilla(x, y, true, Direccion::Derecha));
	SistemaEventos::obtenerInstancia()->publicar(TipoEvento::SemillaDisparada, guardian);
}

void GestionJuego::AgregarArbol(int x, int y)
{
	Arbol* a = FabricaEntidad::obtenerInstancia()->crearArbol(x, y);
	arboles.push_back(a);
	SistemaEventos::obtenerInstancia()->publicar(TipoEvento::ArbolPlantado, a);
}

void GestionJuego::AgregarBasura()
{
	if (enemigos.empty()) return;
	int r = GenerarNumeroAleatorio(0, enemigos.size() - 1);
	bool puedePoner = true;
	for (size_t i = 0; i < basuras.size(); i++) {
		if (enemigos[r]->getX() == basuras[i]->getX() && enemigos[r]->getY() == basuras[i]->getY()) {
			puedePoner = false; break;
		}
	}
	for (size_t i = 0; i < arboles.size(); i++) {
		if (enemigos[r]->getX() == arboles[i]->getX() && enemigos[r]->getY() == arboles[i]->getY()) {
			puedePoner = false; break;
		}
	}
	if (enemigos[r]->getX() == guardian->getX() && enemigos[r]->getY() == guardian->getY()) {
		puedePoner = false;
	}

	if (puedePoner) {
		cx = enemigos[r]->getX(); cy = enemigos[r]->getY();
		Basura* b = FabricaEntidad::obtenerInstancia()->crearBasura(cx, cy);
		basuras.push_back(b);
	}
}

void GestionJuego::InvocarPowerUp()
{
	cx = GenerarNumeroAleatorio(2, 20); cy = GenerarNumeroAleatorio(3, 17);
	potenciador->setX(cx); potenciador->setY(cy);
	potenciador->setVisible(true);
}

double GestionJuego::PorcentajeReforestacion()
{
	if (arboles.empty()) return 0.0;
	double maxArbolesPosibles = 18.0 * 15.0;
	double objetivoArboles = 50.0;
	double porcentaje = (static_cast<double>(arboles.size()) / objetivoArboles) * 100.0;
	if (porcentaje > 100.0) porcentaje = 100.0;
	return round(porcentaje * 10.0) / 10.0;
}

bool GestionJuego::AnalizarGameOver()
{
	return guardian->getVidas() <= 0 || PorcentajeReforestacion() >= 70.0;
}

bool GestionJuego::DeterminarVictoria()
{
	return PorcentajeReforestacion() >= 70.0 && guardian->getVidas() > 0;
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
	for (Semilla* s : semillas) {
		PoolSemillas::obtenerInstancia()->devolverSemilla(s);
	}
	semillas.clear();

	for (auto agua : aguas) delete agua; aguas.clear();
	for (auto arbol : arboles) delete arbol; arboles.clear();
	for (auto basura : basuras) delete basura; basuras.clear();
	for (auto enemigo : enemigos) delete enemigo; enemigos.clear();

	guardian->ReiniciarEstado();
	IniciarElementos();
	potenciador->setVisible(false);
}