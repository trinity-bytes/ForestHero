#pragma once
#include "FuncionesExtra.h"
#include "Guardian.h";
#include "Enemigo.h";
#include "Basura.h";
#include "Semilla.h";
#include "Agua.h";
#include "Arbol.h";

string barraVidas[6] = {
	"-----",
	"#----",
	"##---",
	"###--",
	"####-",
	"#####"
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
    Arbol* arbol = new Arbol(30, 1);
    Semilla* semilla2 = new Semilla(26, 6);
    Agua* agua2 = new Agua(26, 7);
    Arbol* arbol2 = new Arbol(26, 8);
    Enemigo* enemigo = new Enemigo(26, 9);
    Basura* basura = new Basura(26, 10);

    string interfaz = u8R"(╔═════════════════════════════════════════════╗
║  Salud:-----  #:---  #:---  #:--%           ║
╠════════════════════╦════════════════════════╣
║                    ║  >>>  ForestHero  <<<  ║
║                    ║  Puntos:               ║
║                    ║                        ║
║                    ║    # > Agua            ║
║                    ║    # > Semilla         ║
║                    ║    # > Arbol           ║
║                    ║    # > Enemigo         ║
║                    ║    # > Basura          ║
║                    ║                        ║
║                    ║  W: Arriba             ║
║                    ║  S: Abajo              ║
║                    ║  A: Izquierda          ║
║                    ║  D: Derecha            ║
║                    ║  V: Plantar arbol      ║
║                    ║  I,J,K,L: Disparar     ║
╚════════════════════╩════════════════════════╝)";

    cout << interfaz;

    semilla->Dibujar();
    agua->Dibujar();
    arbol->Dibujar();
    semilla2->Dibujar();
    agua2->Dibujar();
    arbol2->Dibujar();
    enemigo->Dibujar();
    basura->Dibujar();

    delete semilla;
    delete agua;
    delete arbol;
    delete semilla2;
    delete agua2;
    delete arbol2;
    delete enemigo;
    delete basura;
}