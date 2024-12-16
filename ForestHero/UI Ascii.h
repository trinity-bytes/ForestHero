#pragma once
#include "FuncionesExtra.h"
#include "Guardian.h";
#include "Enemigo.h";
#include "Basura.h";
#include "Semilla.h";
#include "Agua.h";
#include "Arbol.h";

string barraVidas[6] = {
	u8"-----",
	u8"▓----",
	u8"▓▓---",
	u8"▓▓▓--",
	u8"▓▓▓▓-",
	u8"▓▓▓▓▓"
};

void DibujarBarraVidas(int v) {
	switch (v)
	{
	case 0:
		setBkgTxtColor(1, 4);
		cout << barraVidas[0];
		setBkgTxtColor(1, 0);
		break;
	case 1:
		setBkgTxtColor(1, 4);
		cout << barraVidas[1];
		setBkgTxtColor(1, 0);
		break;
	case 2:
		setBkgTxtColor(1, 7);
		cout << barraVidas[2];
		setBkgTxtColor(1, 0);
		break;
	case 3:
		setBkgTxtColor(1, 7);
		cout << barraVidas[3];
		setBkgTxtColor(1, 0);
		break;
	case 4:
		setBkgTxtColor(1, 8);
		cout << barraVidas[4];
		setBkgTxtColor(1, 0);
		break;
	case 5:
		setBkgTxtColor(1, 8);
		cout << barraVidas[5];
		setBkgTxtColor(1, 0);
		break;
	default:
		break;
	}
}

void MostrarUIJuego()
{
    Semilla* semilla = new Semilla(23, 1);
    Agua* agua = new Agua(16, 1);
    Semilla* semilla2 = new Semilla(34, 10);
    Agua* agua2 = new Agua(24, 10);
    Arbol* arbol2 = new Arbol(24, 11);
    Enemigo* enemigo = new Enemigo(34, 11);
    Basura* basura = new Basura(24, 12);

    string interfaz = u8R"(╔═════════════════════════════════════════════╗
║  Vidas:-----  #:---  #:---      ESC: Salir  ║
╠════════════════════╦════════════════════════╣
║                    ║  >>>  ForestHero  <<<  ║
║                    ║                        ║
║                    ║  Puntos:               ║
║                    ║                        ║
║                    ║  Reforestacion: --.-%  ║
║                    ║                        ║
║                    ╠════════════════════════╣
║                    ║  #: Agua   #: Semilla  ║
║                    ║  #: Arbol  #: Enemigo  ║
║                    ║  #: Basura             ║
║                    ╠════════════════════════╣
║                    ║  W,A,S,D: Movimiento   ║
║                    ║  M: Plantar arbol      ║
║                    ║  K: Disparar semillas  ║
║                    ║  P: Pausar el juego    ║
╚════════════════════╩════════════════════════╝)";

    cout << interfaz;

	setBkgTxtColor(6, 0);
    semilla->Dibujar();
	semilla2->Dibujar();

	setBkgTxtColor(11, 0);
    agua->Dibujar();
	agua2->Dibujar();

	setBkgTxtColor(0, 2);
	arbol2->Dibujar();
    
	setBkgTxtColor(0, 4);
    enemigo->Dibujar();

	setBkgTxtColor(0, 5);
    basura->Dibujar();

    delete semilla;
    delete agua;
    delete semilla2;
    delete agua2;
    delete arbol2;
    delete enemigo;
    delete basura;
}