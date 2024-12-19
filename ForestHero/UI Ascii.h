#pragma once
#include "FuncionesExtra.h"
#include "Guardian.h"
#include "Enemigo.h"
#include "Basura.h"
#include "Semilla.h"
#include "Agua.h"
#include "Arbol.h"
#include "conio.h"

#define TECLA_ARRIBA    72  // Flecha arriba
#define TECLA_ABAJO     80  // Flecha abajo
#define TECLA_IZQUIERDA 75  // Flecha izquierda
#define TECLA_DERECHA   77  // Flecha derecha
#define ENTER           13  // Enter

const int cantOpcMP = 4;
const int cantOpcGameOver = 2;

int opcMPSeleccionada = 0;
int opcGameOverSeleccionada = 0;

const string opcionesMenuPrincipal[cantOpcMP] = {
	"    JUGAR       ",
	"    RANKING     ",
	"    TUTORIAL    ",
	"    SALIR       "
};

const string opcionesGameOver[cantOpcGameOver] = {
    " VOLVER A JUGAR ",
    " IR AL MENU PRINICPAL "
};

const string barraVidas[6] = {
	u8"-----",
	u8"▓----",
	u8"▓▓---",
	u8"▓▓▓--",
	u8"▓▓▓▓-",
	u8"▓▓▓▓▓"
};

void MostrarMenuPrincipal()
{
    string objeto = u8R"(

    ╔═════════════════════════════════════════════════════════════════════════════════════════════╗
    ║                                                                                             ║
    ║                                                                                             ║
    ║    ▄███████ ▄█████▄ █████▄   ▄██████ ▄██████ ███████    ██   ██ ▄██████ █████▄   ▄█████▄    ║ 
    ║    ████████ ███████ ███  █   ███████ ███████ ▀█████▀    ██   ██ ███████ ███  █   ███████    ║ 
    ║    ████     █     █ ███  █   ███     █         ███      ██▄▄▄██ ███     ███  █   █     █    ║
    ║    ████████ █     █ ███████▄ ███████ ▀██████   ███      ███████ ███████ ███████▄ █     █    ║
    ║    █████    ███████ ███    █ ███           █   ███      ██▀▀▀██ ███     ███    █ ███████    ║
    ║    ▀████    ▀█████▀ ███    █ ▀██████ ▄██████   ███      ██   ██ ▀██████ ███    █ ▀█████▀    ║
    ║                                                                                             ║
    ╠═════════════════════════════════════════════════════════════════════════════════════════════╣
    ║                                                                                             ║
    ║                                                                  ,@@@@@@@,                  ║
    ║                                                          ,,,.   ,@@@@@@/@@,  .oo8888o.      ║
    ║                       JUGAR                           ,&%%&%&&%,@@@@@/@@@@@@,8888\88/8o     ║
    ║                       RANKING                        ,%&\%&&%&&%,@@@\@@@/@@@88\88888/88'    ║
    ║                       TUTORIAL                       %&&%&%&/%&&%@@\@@/ /@@@88888\88888'    ║
    ║                       SALIR                          %&&%/ %&%%&&@@\ V /@@' `88\8 `/88'     ║
    ║                                                      `&%\ ` /%&'    |.|        \ '|8'       ║
    ║                                                          |o|        | |         | |         ║
    ║                                                       \\/ ._\//_/__/  ,\_//__\\/.  \_//__/_ ║
    ╚═════════════════════════════════════════════════════════════════════════════════════════════╝
     Usa las teclas ARRIBA y ABAJO para navegar por las opciones.
     Pulsa ENTER para seleccionar la opcion que deseas.
)";

    cout << objeto;
}

void MostrarUIJuego()
{
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

    Semilla* semilla = new Semilla(23, 1);
    Agua* agua = new Agua(16, 1);
    Semilla* semilla2 = new Semilla(34, 10);
    Agua* agua2 = new Agua(24, 10);
    Arbol* arbol2 = new Arbol(24, 11);
    Enemigo* enemigo = new Enemigo(34, 11);
    Basura* basura = new Basura(24, 12);

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

void MostrarMenuVictoria()
{
    string objeto = u8R"(

    ╔═════════════════════════════════════════════════════════════════════════════════════════════╗
    ║                                                                                             ║
    ║                                                                                             ║
    ║                           ,,                                  ,,                            ║
    ║             `7MMF'   `7MF'db           mm                     db           OO               ║
    ║               `MA     ,V               MM                                  88               ║
    ║                VM:   ,V `7MM  ,p6"bo mmMMmm ,pW"Wq.`7Mb,od8 `7MM   ,6"Yb.  ||               ║
    ║                 MM.  M'   MM 6M'  OO   MM  6W'   `Wb MM' "'   MM  8)   MM  ||               ║
    ║                 `MM A'    MM 8M        MM  8M     M8 MM       MM   ,pm9MM  `'               ║
    ║                  :MM;     MM YM.    ,  MM  YA.   ,A9 MM       MM  8M   MM  ,,               ║
    ║                   VF    .JMML.YMbmd'   `Mbmo`Ybmd9'.JMML.   .JMML.`Moo9^Yo.db               ║
    ║                                                                                             ║
    ║                                                                                             ║
    ║    Escribe tu nick:                                                                         ║
    ║                                                                                             ║
    ║                                                                                             ║
    ║                                                                                             ║
    ║                        VOLVER A JUGAR            IR AL MENU PRINCIPAL                       ║   
    ║                                                                                             ║
    ║                                                                                             ║
    ╚═════════════════════════════════════════════════════════════════════════════════════════════╝
     Usa las teclas IZQUIERDA y DERECHA para navegar por las opciones.
     Pulsa ENTER para guardar tu nick o seleccionar la opcion que deseas.
)";

    cout << objeto;
}

void MostrarMenuDerrota()
{
    string objeto = u8R"(

    ╔═════════════════════════════════════════════════════════════════════════════════════════════╗
    ║                                                                                             ║
    ║                                                                                             ║
    ║              `7MM"""Yb.                                      mm            OO               ║
    ║                MM    `Yb.                                    MM            88               ║
    ║                MM     `Mb  .gP"Ya `7Mb,od8 `7Mb,od8 ,pW"Wq.mmMMmm  ,6"Yb.  ||               ║
    ║                MM      MM ,M'   Yb  MM' "'   MM' "'6W'   `Wb MM   8)   MM  ||               ║
    ║                MM     ,MP 8M""""""  MM       MM    8M     M8 MM    ,pm9MM  `'               ║
    ║                MM    ,dP' YM.    ,  MM       MM    YA.   ,A9 MM   8M   MM  ,,               ║
    ║              .JMMmmmdP'    `Mbmmd'.JMML.   .JMML.   `Ybmd9'  `Mbmo`Moo9^Yo.db               ║
    ║                                                                                             ║
    ║                                                                                             ║
    ║                                                                                             ║
    ║                                                                                             ║
    ║                        VOLVER A JUGAR            IR AL MENU PRINCIPAL                       ║   
    ║                                                                                             ║
    ║                                                                                             ║
    ╚═════════════════════════════════════════════════════════════════════════════════════════════╝
     Usa las teclas IZQUIERDA y DERECHA para navegar por las opciones.
     Pulsa ENTER para seleccionar la opcion que deseas.
)";

    cout << objeto;
}

void MostrarOpcMenuPrincipal()
{
    for (int i = 0; i < cantOpcMP; i++) 
    {
        GoTo(24, 16 + i);
        if (i == opcMPSeleccionada) 
        {
            setBkgTxtColor(0, 1);
        }
        else 
        {
            setBkgTxtColor(1, 0);
        }

        cout << opcionesMenuPrincipal[i] << endl;
    }
}

short ObtenerOpcionMenuPrincipal() 
{
    char tecla;
    do {
        MostrarOpcMenuPrincipal();
        tecla = _getch(); // Obtener la tecla presionada sin necesidad de Enter
        switch (tecla) 
        {
        case TECLA_ARRIBA: // Flecha arriba
            opcMPSeleccionada = (opcMPSeleccionada - 1 + cantOpcMP) % cantOpcMP; break;
        case TECLA_ABAJO: // Flecha abajo
            opcMPSeleccionada = (opcMPSeleccionada + 1) % cantOpcMP; break;
        case ENTER: // Enter
            return opcMPSeleccionada + 1;
        }
        Sleep(40);
    } while (true);
}

void MostrarOpcVictoria()
{
	int posicionesX[cantOpcGameOver] = { 28, 54 }; // Coordenadas X para cada opc
    int posicionY = 19; // Coordenada Y fija para ambas opc

    for (int i = 0; i < cantOpcGameOver; i++) 
    {
        GoTo(posicionesX[i], posicionY); // Mueve el cursor a la posición correspondiente

        if (i == opcGameOverSeleccionada) setBkgTxtColor(0, 1);
        else setBkgTxtColor(1, 0);
       
        cout << opcionesGameOver[i];
    }
    setBkgTxtColor(1, 0);
}

short ObtenerOpcVictoria() 
{
    char tecla;
    do {
        MostrarOpcVictoria();
        tecla = getch(); // Obtener la tecla presionada sin necesidad de Enter
        switch (tecla)
        {
        case TECLA_IZQUIERDA: // Flecha izquierda
            opcGameOverSeleccionada = (opcGameOverSeleccionada - 1 + cantOpcGameOver) % cantOpcGameOver;
            break;
        case TECLA_DERECHA: // Flecha derecha
            opcGameOverSeleccionada = (opcGameOverSeleccionada + 1) % cantOpcGameOver; 
            break;
        case ENTER: // Enter
            return opcGameOverSeleccionada + 1;
        }
        Sleep(40);
    } while (true);
}

void MostrarOpcDerrota() 
{
    int posicionesX[cantOpcGameOver] = { 28, 54 }; // Coordenadas X para cada opc
    int posicionY = 16; // Coordenada Y fija para ambas opc

    for (int i = 0; i < cantOpcGameOver; i++) 
    {
        GoTo(posicionesX[i], posicionY); // Mueve el cursor a la posición correspondiente

        if (i == opcGameOverSeleccionada) setBkgTxtColor(0, 1);
        else setBkgTxtColor(1, 0);
       
        cout << opcionesGameOver[i];
    }
    setBkgTxtColor(1, 0);
}

short ObtenerOpcDerrota() 
{
    char tecla;
    do {
        MostrarOpcDerrota();
        tecla = getch(); // Obtener la tecla presionada sin necesidad de Enter
        switch (tecla)
        {
        case TECLA_IZQUIERDA: // Flecha izquierda
            opcGameOverSeleccionada = (opcGameOverSeleccionada - 1 + cantOpcGameOver) % cantOpcGameOver;
            break;
        case TECLA_DERECHA: // Flecha derecha
            opcGameOverSeleccionada = (opcGameOverSeleccionada + 1) % cantOpcGameOver;
            break;
        case ENTER: // Enter
            return opcGameOverSeleccionada + 1;
        }
        Sleep(40);
    } while (true);
}

void DibujarBarraVidas(int v) 
{
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