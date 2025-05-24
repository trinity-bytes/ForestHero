#pragma once
#include <string>
#include <vector>
#include <windows.h>

class BufferPantalla {
private:
    HANDLE salidaConsola;
    HANDLE bufferDelantero;
    HANDLE bufferTrasero;
    COORD tamañoBuffer;
    SMALL_RECT regionEscritura;

    static BufferPantalla* instancia;

    bool usandoBufferAlternativo = false;

public:
    inline BufferPantalla(int ancho, int alto) {
        salidaConsola = GetStdHandle(STD_OUTPUT_HANDLE);

        // Crear buffers de consola
        tamañoBuffer.X = ancho;
        tamañoBuffer.Y = alto;

        bufferDelantero = CreateConsoleScreenBuffer(
            GENERIC_READ | GENERIC_WRITE,
            FILE_SHARE_READ | FILE_SHARE_WRITE,
            NULL,
            CONSOLE_TEXTMODE_BUFFER,
            NULL
        );

        bufferTrasero = CreateConsoleScreenBuffer(
            GENERIC_READ | GENERIC_WRITE,
            FILE_SHARE_READ | FILE_SHARE_WRITE,
            NULL,
            CONSOLE_TEXTMODE_BUFFER,
            NULL
        );

        // Configurar región de escritura
        regionEscritura.Left = 0;
        regionEscritura.Top = 0;
        regionEscritura.Right = ancho - 1;
        regionEscritura.Bottom = alto - 1;

        // Ocultar cursor en ambos buffers
        CONSOLE_CURSOR_INFO infoCursor = { 1, FALSE };
        SetConsoleCursorInfo(bufferDelantero, &infoCursor);
        SetConsoleCursorInfo(bufferTrasero, &infoCursor);

        // Activar el buffer frontal
        SetConsoleActiveScreenBuffer(bufferDelantero);
    }

    inline ~BufferPantalla() {
        // Restaurar el buffer estándar de la consola
        SetConsoleActiveScreenBuffer(salidaConsola);

        // Cerrar los handles de los buffers
        CloseHandle(bufferDelantero);
        CloseHandle(bufferTrasero);

        if (instancia == this) {
            instancia = nullptr;
        }
    }

    inline void limpiar() {
        // Limpiar el buffer trasero
        DWORD caracteresEscritos;
        COORD origen = { 0, 0 };
        DWORD longitud = tamañoBuffer.X * tamañoBuffer.Y;

        FillConsoleOutputCharacterA(bufferTrasero, ' ', longitud, origen, &caracteresEscritos);
        FillConsoleOutputAttribute(bufferTrasero, 0x07, longitud, origen, &caracteresEscritos);
    }

    inline void intercambiar() {
        // Intercambiar buffers
        HANDLE temp = bufferDelantero;
        bufferDelantero = bufferTrasero;
        bufferTrasero = temp;

        // Activar el nuevo buffer frontal
        SetConsoleActiveScreenBuffer(bufferDelantero);
    }

    inline void dibujarTexto(int x, int y, const std::string& texto, int colorFrente, int colorFondo) {
        if (x < 0 || y < 0 || x >= tamañoBuffer.X || y >= tamañoBuffer.Y) {
            return;
        }

        COORD coordenadas = { (SHORT)x, (SHORT)y };
        DWORD caracteresEscritos;

        // Obtener los atributos actuales
        WORD atributos = (WORD)((colorFondo << 4) | colorFrente);

        // Escribir el texto con los atributos especificados
        WriteConsoleOutputCharacterA(bufferTrasero, texto.c_str(), texto.length(), coordenadas, &caracteresEscritos);

        // Establecer los atributos para el texto escrito
        for (size_t i = 0; i < texto.length(); ++i) {
            COORD coordAtributo = { (SHORT)(x + i), (SHORT)y };
            WriteConsoleOutputAttribute(bufferTrasero, &atributos, 1, coordAtributo, &caracteresEscritos);
        }
    }

    inline static BufferPantalla& obtenerInstancia() {
        if (!instancia) {
            instancia = new BufferPantalla(104, 28); // Tamaño base de la consola
        }
        return *instancia;
    }
};

// Inicialización de la variable estática fuera de la clase (pero en el mismo archivo .hpp)
BufferPantalla* BufferPantalla::instancia = nullptr;