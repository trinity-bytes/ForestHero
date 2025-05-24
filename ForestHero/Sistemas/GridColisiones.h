#pragma once
#include <vector>
#include <unordered_map>
#include "../Entidades/Base/Entidad.h"

class GridColisiones {
private:
    static const int TAMAÑO_CELDA = 4; // Ajusta según necesites
    std::unordered_map<int, std::vector<Entidad*>> celdas;

    // Función para calcular el índice de celda
    int calcularIndiceCelda(int x, int y) {
        return (y / TAMAÑO_CELDA) * 100 + (x / TAMAÑO_CELDA);
    }

public:
    void limpiar() {
        celdas.clear();
    }

    void registrarEntidad(Entidad* entidad) {
        if (!entidad || !entidad->getActivo()) return;

        int indice = calcularIndiceCelda(entidad->getX(), entidad->getY());
        celdas[indice].push_back(entidad);
    }

    std::vector<Entidad*> obtenerEntidadesCercanas(int x, int y) {
        std::vector<Entidad*> entidadesCercanas;

        // Obtener entidades en la misma celda y celdas adyacentes
        int indiceCentral = calcularIndiceCelda(x, y);

        for (int dy = -1; dy <= 1; dy++) {
            for (int dx = -1; dx <= 1; dx++) {
                int indice = calcularIndiceCelda(x + dx * TAMAÑO_CELDA, y + dy * TAMAÑO_CELDA);

                if (celdas.find(indice) != celdas.end()) {
                    entidadesCercanas.insert(entidadesCercanas.end(),
                        celdas[indice].begin(),
                        celdas[indice].end());
                }
            }
        }

        return entidadesCercanas;
    }
};