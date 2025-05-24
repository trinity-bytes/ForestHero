#pragma once
#include "windows.h" // acceder a la api de windows
#include "iostream"
#include "random"
#include <string>      // Required for std::string, std::wstring
#include <locale>      // Required for std::wstring_convert
#include <codecvt>     // Required for std::codecvt_utf8_utf16

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

// Helper function to convert UTF-8 std::string to std::wstring
inline std::wstring ConvertUtf8ToWide(const std::string& utf8Str) {
    try {
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
        return converter.from_bytes(utf8Str);
    }
    catch (const std::range_error&) {
        // Handle cases of invalid UTF-8 sequences if necessary,
        // though for u8 literals this should not be an issue.
        return L""; // Or some placeholder like L"?"
    }
}

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
    COORD coord = { (SHORT)x, (SHORT)y }; // Explicit cast to SHORT
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


// Configurar la fuente y tamano de la letra
inline void CambiarFuenteConsola(const wstring& nombreFuente, COORD tamanioFuente)
{
    HANDLE hConsola = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_FONT_INFOEX cfi = { 0 };
    cfi.cbSize = sizeof(cfi);
    // Ensure FaceName is null-terminated if nombreFuente is too long.
    // wcscpy_s is safer. Max length for FaceName is LF_FACESIZE (32).
    wcsncpy_s(cfi.FaceName, LF_FACESIZE, nombreFuente.c_str(), _TRUNCATE);
    cfi.dwFontSize = tamanioFuente;
    cfi.FontWeight = FW_NORMAL; // Consider FW_REGULAR or other weights if needed
    cfi.FontFamily = FF_DONTCARE; // Or FF_MODERN for monospace

    SetCurrentConsoleFontEx(hConsola, FALSE, &cfi);
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
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)((colorFondo << 4) | colorTexto)); // Explicit cast to WORD
}

void ConfigurarConsola()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    EsconderCursor();

    CambiarFuenteConsola(L"Cascadia Mono", { 0, 20 }); // Default menu font

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

    setBkgTxtColor(1, 0); // Default: White text on Black background

    Console::Title = "ForestHero v1.5";
    Console::SetWindowSize(104, 28); // Default menu size
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