#pragma once
#include "Entidad.h"

enum class Direccion {
    Ninguna,
    Arriba,
    Abajo,
    Izquierda,
    Derecha
};

class Agente : public Entidad {
protected:
    Direccion direccionActual = Direccion::Ninguna;
    int dx = 0;
    int dy = 0;
    int velocidad = 1;

public:
    Agente(int x, int y, TipoEntidad tipo) : Entidad(x, y, tipo) {}
    virtual ~Agente() = default;

    Direccion getDireccion() const { return direccionActual; }
    void setDireccion(Direccion dir) { direccionActual = dir; }

    void setVelocidad(int nuevaVelocidad) { velocidad = nuevaVelocidad; }
    int getVelocidad() const { return velocidad; }

    virtual void mover()
    {
        int tempDx = 0;
        int tempDy = 0;

        switch (direccionActual) 
        { 
        case Direccion::Arriba:    tempDy = -velocidad; break;
        case Direccion::Abajo:     tempDy = velocidad; break;
        case Direccion::Izquierda: tempDx = -velocidad; break;
        case Direccion::Derecha:   tempDx = velocidad; break;
        case Direccion::Ninguna:
        default: break;
        }

        int newX = x + tempDx;
        int newY = y + tempDy;

        // Game boundaries (ensure these are consistent with your game world design)
        const int min_X = 1;  // Minimum X coordinate (inclusive)
        const int max_X = 20; // Maximum X coordinate (inclusive)
        const int min_Y = 3;  // Minimum Y coordinate (inclusive)
        const int max_Y = 17; // Maximum Y coordinate (inclusive)

        if (newX >= min_X && newX <= max_X) {
            setX(newX);
        }
        if (newY >= min_Y && newY <= max_Y) {
            setY(newY);
        }
    }
};