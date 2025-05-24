#pragma once

enum class EstadoJuego {
    MenuPrincipal,
	Tutorial,
    Jugando,
    Pausado,
    GameOver,
    Victoria
};

class GestorEstados {
private:
    static GestorEstados* instancia;
    EstadoJuego estadoActual;

    GestorEstados() : estadoActual(EstadoJuego::MenuPrincipal) {}

public:
    static GestorEstados* obtenerInstancia() {
        if (!instancia) {
            instancia = new GestorEstados();
        }
        return instancia;
    }

    EstadoJuego getEstadoActual() const {
        return estadoActual;
    }

    void cambiarEstado(EstadoJuego nuevoEstado) {
        estadoActual = nuevoEstado;
    }

    bool esEstado(EstadoJuego estado) const {
        return estadoActual == estado;
    }
};

// Inicializaci�n de la variable est�tica
GestorEstados* GestorEstados::instancia = nullptr;