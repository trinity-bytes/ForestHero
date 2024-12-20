#pragma once
#pragma once
#include "windows.h" // acceder a la api de windows
#include "iostream"
#include "random"

using namespace std;
using namespace System;

struct Color
{
    BYTE r;
    BYTE g;
    BYTE b;
};

// Basado en la paleta de Catpuccin
constexpr Color NEGRO = { 36, 39, 58 };
constexpr Color BLANCO = { 202, 211, 245 };
constexpr Color ROJO = { 237, 135, 150 };
constexpr Color VERDE = { 166, 218, 149 };
constexpr Color AMARILLO = { 238, 212, 159 };
constexpr Color AZUL = { 138, 173, 244 };
constexpr Color MORADO = { 198, 160, 246 };
constexpr Color NARANJA = { 245, 169, 127 };
constexpr Color CIELO = { 145, 215, 227 };
constexpr Color MARRON = { 238, 153, 160 };
constexpr Color GRIS = { 147, 154, 183 };
constexpr Color CELESTE = { 125, 196, 228 };
constexpr Color AGUAROSA = { 244, 219, 214 };
constexpr Color LAVANDA = { 183, 189, 248 };
constexpr Color FLAMENCO = { 145, 215, 227 };
constexpr Color OSCURIDAD = { 24, 25, 38 };

int GenerarNumeroAleatorio(int m, int n) 
{
    // Verificar que m sea menor que n
    if (m >= n) {
        //std::cerr << "Error: m debe ser menor que n" << std::endl;
        return m;  // Retornar m en caso de error
    }

    // Inicializar el generador de números aleatorios
    static std::mt19937 gen(std::time(0));

    // Crear una distribución uniforme en el rango [m, n]
    std::uniform_int_distribution<> dis(m, n);

    // Generar y retornar el número aleatorio
    return dis(gen);
}

void GoTo(int x, int y) 
{
    COORD coord = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void Esperar(int ms)
{
    Sleep(ms); // milisegundos
}

void LimpiarPantalla() 
{
    system("cls");
}

void EsconderCursor() 
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

void MostrarCursor()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = TRUE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}


void setFont(const wchar_t* fontName, SHORT sizeX, SHORT sizeY) 
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(CONSOLE_FONT_INFOEX);
    cfi.nFont = 0;
    cfi.dwFontSize.X = sizeX; // Ancho de cada caracter
    cfi.dwFontSize.Y = sizeY; // Alto de cada caracter
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    wcscpy_s(cfi.FaceName, fontName);
    SetCurrentConsoleFontEx(hConsole, FALSE, &cfi);
}

void setColorPalette(int index, Color color) 
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFOEX csbiex;
    csbiex.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
    GetConsoleScreenBufferInfoEx(hConsole, &csbiex);

    // Establecer el color en la paleta
    csbiex.ColorTable[index] = RGB(color.r, color.g, color.b);

    SetConsoleScreenBufferInfoEx(hConsole, &csbiex);
}

void setBkgTxtColor(int colorTexto, int colorFondo) 
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorTexto | (colorFondo << 4));
}

void ConfigurarConsola() 
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    EsconderCursor();

    setFont(L"Cascadia Mono", 10, 20);

    setColorPalette(0, NEGRO);
    setColorPalette(1, BLANCO);
    setColorPalette(2, VERDE);
    setColorPalette(3, CIELO);
    setColorPalette(4, ROJO);
    setColorPalette(5, MORADO);
    setColorPalette(6, AMARILLO);
    setColorPalette(7, NARANJA);
    setColorPalette(8, AZUL);
    setColorPalette(9, MARRON);
    setColorPalette(10, GRIS);
    setColorPalette(11, CELESTE);
    setColorPalette(12, AGUAROSA);
    setColorPalette(13, LAVANDA);
    setColorPalette(14, FLAMENCO);
    setColorPalette(15, OSCURIDAD);

    setBkgTxtColor(1, 0);

    Console::Title = "ForestHero v1.5";
    Console::SetWindowSize(104, 28);
}

/*
>>>>>>> FUNCIONES SIN USAR

void configurarColorTexto(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void configurarColorFondoIntensoYTexto(int colorTexto, int colorFondo) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorTexto | (colorFondo << 4) | BACKGROUND_INTENSITY);
}

void configurarColorFondoYTextoIntensos(int colorTexto, int colorFondo) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorTexto | (colorFondo << 4) | FOREGROUND_INTENSITY | BACKGROUND_INTENSITY);
}
*/