#pragma once
#include "FuncionesExtra.h"
#include "GestionPuntajes.h"
#include "../Entidades/Personajes/Guardian.h"
#include "../Entidades/Personajes/Enemigo.h"
#include "../Entidades/Items/Basura.h"
#include "../Entidades/Items/Semilla.h"
#include "../Entidades/Items/Agua.h"
#include "../Entidades/Items/Arbol.h"
#include "conio.h"
#include "vector"
// #include "../Renderizado/BufferPantalla.h" // No es necesario aquí si MostrarUIJuego ya no lo usa directamente

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

// DibujarBarraVidasEnBuffer ya está bien y usa el buffer.
inline void DibujarBarraVidasEnBuffer(BufferPantalla* buffer, int x, int y, int vidas) {
    int color;
    if (vidas < 0) vidas = 0; // Asegurar que no sea negativo
    if (vidas > 5) vidas = 5; // Asegurar que no exceda el tamaño del array

    switch (vidas) {
    case 0: case 1: color = 4; break; // Rojo
    case 2: case 3: color = 6; break; // Amarillo
    case 4: case 5: color = 2; break; // Verde
    default: color = 2; break; // Por si acaso, aunque vidas ya está acotado
    }
    buffer->dibujarTexto(x, y, barraVidas[vidas], 15, color); // Texto blanco sobre el color de la barra
}

void MostrarMenuPrincipal()
{
    // Esta función sigue usando cout. Debería ser refactorizada para usar BufferPantalla
    // si se quiere una transición suave entre el menú y el juego, o si el menú
    // también va a ser no bloqueante y parte del bucle principal de la aplicación.
    // Por ahora, se asume que se llama cuando el BufferPantalla del juego no está activo.
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

    cout << objeto; // Sigue usando cout
}

void MostrarUIJuego()
{
    // Esta función ya no es necesaria para dibujar el marco del juego,
    // ya que GestionJuego::DibujarMarcoUI() lo hace.
    // Se puede eliminar o dejar vacía si no tiene otro propósito.
    // Ya no se debe usar cout ni crear entidades aquí para la UI del juego.

    /*
    string interfaz = u8R"(...)" // Eliminado
    cout << interfaz; // Eliminado

    // Eliminada la creación de entidades temporales y setBkgTxtColor
    */
}

// Las funciones MostrarMenuVictoria, MostrarMenuDerrota, MostrarUIRanking, MostrarTutorial1/2
// también usan cout y deberían ser refactorizadas a largo plazo para usar BufferPantalla
// si se desea una experiencia de UI más integrada y sin parpadeos al cambiar de pantalla.
// Por ahora, se asume que se llaman en momentos donde el control directo de la consola es aceptable
// (por ejemplo, después de que el bucle de juego principal ha terminado y antes de que otro comience).

// ... (resto de funciones de UI Ascii.h como MostrarOpcMenuPrincipal, ObtenerOpcionMenuPrincipal, etc.
//      que también usan cout, GoTo, Sleep, y _getch de forma bloqueante)
// ... (Mantener DibujarBarraVidas que usa setBkgTxtColor y cout, o preferir DibujarBarraVidasEnBuffer)

// Es recomendable reemplazar DibujarBarraVidas por DibujarBarraVidasEnBuffer en el código del juego.
// void DibujarBarraVidas(int v) { ... } // Esta versión usa cout y setBkgTxtColor

// ... el resto del archivo UI Ascii.h
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

void MostrarUIRanking()
{
    string objetoS = u8R"(

    ╔═════════════════════════════════════════════════════════════════════════════════════════════╗
    ║                             _____             _    _                                        ║
    ║                            |  __ \           | |  (_)                                       ║
    ║                            | |__) |__ _ _ __ | | ___ _ __   __ _                            ║
    ║                            |  _  // _` | '_ \| |/ / | '_ \ / _` |                           ║
    ║                            | | \ \ (_| | | | |   <| | | | | (_| |                           ║
    ║                            |_|  \_\__,_|_| |_|_|\_\_|_| |_|\__, |                           ║
    ║                                                             __/ |                           ║
    ║                                                            |___/                            ║
    ╠═════════════════════════════════════════════════════════════════════════════════════════════╣
    ║                                                                                             ║
    ║                               1. ----------                                                 ║
    ║                               2. ----------                                                 ║
    ║                               3. ----------                                                 ║
    ║                               4. ----------                                                 ║
    ║                               5. ----------                                                 ║
    ║                               6. ----------                                                 ║
    ║                               7. ----------                                                 ║
    ║                               8. ----------                                                 ║
    ║                               9. ----------                                                 ║
    ║                              10. ----------                                                 ║
    ║                                                                                             ║
    ╚═════════════════════════════════════════════════════════════════════════════════════════════╝
     Pulsa ESC para regresar al menu.
)";

    cout << objetoS;
}

void MostrarTutorial1()
{
    string objetoI = u8R"(

 ╔════════════════════════════════════════════════════════════════════════════════════════════════════╗ 
 ║                                  _______    _             _       _                                ║
 ║                                 |__   __|  | |           (_)     | |                               ║
 ║                                    | |_   _| |_ ___  _ __ _  __ _| |                               ║
 ║                                    | | | | | __/ _ \| '__| |/ _` | |                               ║
 ║                                    | | |_| | || (_) | |  | | (_| | |                               ║
 ║                                    |_|\__,_|\__\___/|_|  |_|\__,_|_|                               ║
 ║                                                                                                    ║
 ╠═══════════════════════════╦═════════════════════════════════════════╦══════════════════════════════╣
 ║                           ║                                         ║                              ║
 ║   GUARDIAN (Jugador): @   ║   SEMILLA: @     AGUA: @     ARBOL: @   ║   ENEMIGO: @     BASURA: @   ║
 ║                           ║                                         ║                              ║
 ╠═══════════════════════════╩══════════════╦══════════════════════════╩══════════════════════════════╣
 ║                                          ║                                                         ║
 ║   CONTROLES:                             ║   INSTRUCCIONES:                                        ║
 ║                                          ║                                                         ║
 ║   - Utiliza las teclas W,A,S,D para      ║   - Eres el GUARDIAN de bosque.                         ║
 ║   - Presiona K para DISPARAR semillas.   ║   - Tu deber es restaurar el equilibrio en el bosque    ║
 ║   - Presiona M para PLANTAR un arbol.    ║     a travez de la reforestacion.                       ║
 ║   - Presiona P para PAUSAR el juego.     ║   - Para ganar, debes REFORESTAR al menos el 70%        ║
 ║   - Presiona ESC para salir del nivel.   ║     del escenario.                                      ║
 ║                                          ║                                                         ║
 ╚══════════════════════════════════════════╩═════════════════════════════════════════════════════════╝
  Utiliza las techas IZQUIERDA y DERECHA para navegar por las instrucciones.
  Presion ESC para regresar al menu principal. 
)";

    // La creación de entidades aquí es solo para mostrar iconos en el tutorial,
    // si el tutorial se rediseña para usar el buffer, esto cambiaría.
    // Por ahora, se mantiene ya que es una pantalla estática fuera del bucle de juego principal.
    Semilla* semilla = new Semilla(42, 12); // Estas coordenadas son relativas a la salida de cout
    Agua* agua = new Agua(54, 12);
    Arbol* arbol = new Arbol(67, 12);
    Enemigo* enemigo = new Enemigo(84, 12);
    Basura* basura = new Basura(98, 12);

    cout << objetoI;

    // Estas llamadas a Dibujar() de las entidades no funcionarán como antes si Entidad::Dibujar
    // fue modificada para usar BufferPantalla y no se le pasa un buffer.
    // Si se quiere mostrar los iconos, se debería usar GoTo y cout con el caracter de la forma.
    // O, idealmente, el tutorial también usaría BufferPantalla.
    // Por simplicidad, comentamos estas llamadas por ahora.
    // GoTo(42,12); setBkgTxtColor(6,0); cout << semilla->getForma();
    // ...etc.

    delete semilla;
    delete agua;
    delete arbol;
    delete enemigo;
    delete basura;
}

void MostrarTutorial2()
{
    string objetoI = u8R"(

 ╔════════════════════════════════════════════════════════════════════════════════════════════════════╗ 
 ║                                  _______    _             _       _                                ║
 ║                                 |__   __|  | |           (_)     | |                               ║
 ║                                    | |_   _| |_ ___  _ __ _  __ _| |                               ║
 ║                                    | | | | | __/ _ \| '__| |/ _` | |                               ║
 ║                                    | | |_| | || (_) | |  | | (_| | |                               ║
 ║                                    |_|\__,_|\__\___/|_|  |_|\__,_|_|                               ║
 ║                                                                                                    ║
 ╠═════════════════════════════════════════════════════╦══════════════════════════════════════════════╣
 ║                                                     ║                                              ║
 ║   RECURSOS:                                         ║   ENEMIGOS:                                  ║
 ║                                                     ║                                              ║
 ║   - Cada vez que plantas un arbol se consume        ║   - La cantidad de enemigos INCREMENTA con   ║
 ║     una unidad de semilla y de agua.                ║     el transcurso del tiempo.                ║
 ║   - Cada vez que disparas se consume 1 semilla.     ║   - Si tocas a un ENEMIGO o a la BASURA,     ║
 ║   - Las semillas disparadas pueden destruir         ║     perderas una vida.                       ║
 ║     la basura y eliminar enemigos.                  ║   - Si te quedas sin vidas, PIERDES la       ║
 ║                                                     ║     partida.                                 ║
 ║                                                     ║                                              ║
 ╚═════════════════════════════════════════════════════╩══════════════════════════════════════════════╝
  Utiliza las techas IZQUIERDA y DERECHA para navegar por las instrucciones.
  Presion ESC para regresar al menu principal. 
)";

    cout << objetoI;
}

void MostrarOpcMenuPrincipal()
{
    for (int i = 0; i < cantOpcMP; i++)
    {
        GoTo(24, 16 + i);
        if (i == opcMPSeleccionada)
        {
            setBkgTxtColor(0, 1); // Negro sobre Blanco
        }
        else
        {
            setBkgTxtColor(1, 0); // Blanco sobre Negro
        }

        cout << opcionesMenuPrincipal[i] << endl;
    }
    setBkgTxtColor(1, 0); // Reset a Blanco sobre Negro
}

short ObtenerOpcionMenuPrincipal()
{
    char tecla;
    do {
        MostrarOpcMenuPrincipal();
        tecla = _getch();
        switch (tecla)
        {
        case TECLA_ARRIBA:
            opcMPSeleccionada = (opcMPSeleccionada - 1 + cantOpcMP) % cantOpcMP; break;
        case TECLA_ABAJO:
            opcMPSeleccionada = (opcMPSeleccionada + 1) % cantOpcMP; break;
        case ENTER:
            return opcMPSeleccionada + 1;
        }
        Sleep(40); // Pequeña pausa para evitar selección múltiple rápida
    } while (true);
}

void MostrarOpcVictoria()
{
    int posicionesX[cantOpcGameOver] = { 28, 54 };
    int posicionY = 19;

    for (int i = 0; i < cantOpcGameOver; i++)
    {
        GoTo(posicionesX[i], posicionY);

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
        tecla = getch();
        switch (tecla)
        {
        case TECLA_IZQUIERDA:
            opcGameOverSeleccionada = (opcGameOverSeleccionada - 1 + cantOpcGameOver) % cantOpcGameOver;
            break;
        case TECLA_DERECHA:
            opcGameOverSeleccionada = (opcGameOverSeleccionada + 1) % cantOpcGameOver;
            break;
        case ENTER:
            return opcGameOverSeleccionada + 1;
        }
        Sleep(40);
    } while (true);
}

void MostrarOpcDerrota()
{
    int posicionesX[cantOpcGameOver] = { 28, 54 };
    int posicionY = 16;

    for (int i = 0; i < cantOpcGameOver; i++)
    {
        GoTo(posicionesX[i], posicionY);

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
        tecla = getch();
        switch (tecla)
        {
        case TECLA_IZQUIERDA:
            opcGameOverSeleccionada = (opcGameOverSeleccionada - 1 + cantOpcGameOver) % cantOpcGameOver;
            break;
        case TECLA_DERECHA:
            opcGameOverSeleccionada = (opcGameOverSeleccionada + 1) % cantOpcGameOver;
            break;
        case ENTER:
            return opcGameOverSeleccionada + 1;
        }
        Sleep(40);
    } while (true);
}

void MostrarRanking()
{
    GestionPuntajes rank("Resources/Data/Puntaje.dat");

    MostrarUIRanking(); // Esto usa cout

    vector<Puntaje> ranking = rank.ObtenerRanking();
    size_t limite = min(ranking.size(), size_t(10));

    for (size_t i = 0; i < limite; i++)
    {
        GoTo(39, 13 + i); // Usa GoTo
        cout << ranking[i].nombre << "  -  " << ranking[i].puntos << " puntos" << endl; // Usa cout
    }
}

void MostrarUITutorial()
{
    char tecla = TECLA_DERECHA; // Iniciar mostrando la primera página (o TECLA_IZQUIERDA si prefieres)

    do
    {
        LimpiarPantalla(); // Usa system("cls")
        if (tecla == TECLA_DERECHA) {
            MostrarTutorial1(); // Usa cout
        }
        else if (tecla == TECLA_IZQUIERDA) {
            MostrarTutorial2(); // Usa cout
        }
        else {
            // Si es la primera vez o una tecla inválida, mostrar la primera página por defecto
            MostrarTutorial1();
        }

        char inputTecla = getch();
        if (inputTecla == 0 || inputTecla == 224) { // Teclas especiales (flechas)
            tecla = getch(); // Leer el segundo byte
        }
        else {
            tecla = inputTecla;
        }

        if (tecla == 27) break; // ESC para salir
    } while (true);
}

// Esta función usa cout y setBkgTxtColor, preferir DibujarBarraVidasEnBuffer
void DibujarBarraVidas(int v)
{
    if (v < 0) v = 0;
    if (v >= 6) v = 5; // Asegurar que el índice esté dentro del rango de barraVidas

    switch (v)
    {
    case 0: case 1: setBkgTxtColor(15, 4); break; // Blanco sobre Rojo
    case 2: case 3:	setBkgTxtColor(0, 6); break; // Negro sobre Amarillo
    case 4: case 5:	setBkgTxtColor(15, 2); break; // Blanco sobre Verde
    default: setBkgTxtColor(1, 0); break; // Default Blanco sobre Negro
    }

    cout << barraVidas[v];
    setBkgTxtColor(1, 0); // Reset a Blanco sobre Negro
}