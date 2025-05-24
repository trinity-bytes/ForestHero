#pragma once
#include <string>
//#include <System.Drawing.h> // agregado en el proyecto como referencia
#include "../../Renderizado/BufferPantalla.h"

enum class TipoEntidad 
{
    Guardian, 
    Enemigo, 
    Arbol, 
    Agua, 
    Semilla, 
    Basura, 
    PowerUp
};

class Entidad {
protected:
    int x, y;
    std::string forma;
    TipoEntidad tipo;
    bool activo = true;

public:
    Entidad(int x, int y, TipoEntidad tipo) : x(x), y(y), tipo(tipo) {}
    virtual ~Entidad() {}

    int getX() const { return x; }
    int getY() const { return y; }
    void setX(int nuevoX) { x = nuevoX; }
    void setY(int nuevoY) { y = nuevoY; }
    void setForma(const std::string& f) { forma = f; }
    const std::string& getForma() const { return forma; }
    TipoEntidad getTipo() const { return tipo; }
    bool getActivo() const { return activo; }
    void setActivo(bool estado) { activo = estado; }

    // Métodos para dibujar con buffer
    virtual void dibujar(BufferPantalla* buffer) {
        if (!buffer || !activo) return;
        buffer->dibujarTexto(x, y, forma, 15, 0); // Por defecto blanco sobre negro
    }

    virtual void dibujarConColor(BufferPantalla* buffer, int colorFrente, int colorFondo) {
        if (!buffer || !activo) return;
        buffer->dibujarTexto(x, y, forma, colorFrente, colorFondo);
    }

    System::Drawing::Rectangle getRectangle() const {
        return System::Drawing::Rectangle(x, y, forma.length(), 1);
    }

    bool IntersectsWith(const Entidad* otro) const {
        return getRectangle().IntersectsWith(otro->getRectangle());
    }
};