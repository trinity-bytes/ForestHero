#pragma once
#include <vector>
#include "../Items/Semilla.h"

class PoolSemillas {
private:
    static PoolSemillas* instancia;
    std::vector<Semilla*> semillasDisponibles;

    PoolSemillas(int cantidadInicial = 50) {
        // Preinicializar el pool con semillas
        for (int i = 0; i < cantidadInicial; i++) {
            semillasDisponibles.push_back(new Semilla(0, 0));
        }
    }

public:
    static PoolSemillas* obtenerInstancia() {
        if (!instancia) {
            instancia = new PoolSemillas();
        }
        return instancia;
    }

    Semilla* obtenerSemilla(int x, int y, bool seMueve = false, Direccion dir = Direccion::Ninguna) {
        Semilla* semilla;

        if (semillasDisponibles.empty()) {
            // Si no hay semillas disponibles, crear una nueva
            semilla = new Semilla(x, y);
        }
        else {
            // Obtener una semilla del pool
            semilla = semillasDisponibles.back();
            semillasDisponibles.pop_back();

            // Reinicializar sus propiedades
            semilla->setX(x);
            semilla->setY(y);
            semilla->setActivo(true);
        }

        semilla->setSeMueve(seMueve);
        semilla->setDireccion(dir);

        return semilla;
    }

    void devolverSemilla(Semilla* semilla) {
        if (semilla) {
            // Reiniciar estado y devolver al pool
            semilla->setActivo(false);
            semilla->setSeMueve(false);
            semilla->setDireccion(Direccion::Ninguna);
            semillasDisponibles.push_back(semilla);
        }
    }

    ~PoolSemillas() {
        for (auto semilla : semillasDisponibles) {
            delete semilla;
        }
        semillasDisponibles.clear();
    }
};

// Inicialización de la variable estática
PoolSemillas* PoolSemillas::instancia = nullptr;