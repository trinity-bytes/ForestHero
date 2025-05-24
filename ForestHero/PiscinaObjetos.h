#pragma once
#include <vector>
#include <algorithm>
#include <functional>
#include "Entidades/Base/Entidad.h"

template <typename T>
class PiscinaObjetos {
private:
    std::vector<T*> objetosActivos;
    std::vector<T*> objetosDisponibles;
    std::function<T* (int, int)> fabrica;
    size_t capacidadInicial;

public:
    PiscinaObjetos(std::function<T* (int, int)> funcionFabrica, size_t tamanoInicial = 0)
        : fabrica(funcionFabrica), capacidadInicial(tamanoInicial) {
        // Pre-alocar objetos si se proporciona un tamaño inicial
        for (size_t i = 0; i < tamanoInicial; i++) {
            T* objeto = fabrica(0, 0);
            objeto->establecerActivo(false);
            objetosDisponibles.push_back(objeto);
        }
    }

    T* adquirir(int x, int y) {
        T* objeto = nullptr;

        if (!objetosDisponibles.empty()) {
            // Reutilizar un objeto existente
            objeto = objetosDisponibles.back();
            objetosDisponibles.pop_back();

            // Reiniciar y reposicionar el objeto
            objeto->establecerX(x);
            objeto->establecerY(y);
            objeto->establecerActivo(true);
        }
        else {
            // Crear un nuevo objeto
            objeto = fabrica(x, y);
        }

        objetosActivos.push_back(objeto);
        return objeto;
    }

    void liberar(T* objeto) {
        auto it = std::find(objetosActivos.begin(), objetosActivos.end(), objeto);
        if (it != objetosActivos.end()) {
            objeto->establecerActivo(false);
            objetosActivos.erase(it);
            objetosDisponibles.push_back(objeto);
        }
    }

    const std::vector<T*>& obtenerObjetosActivos() const {
        return objetosActivos;
    }

    ~PiscinaObjetos() {
        // Eliminar todos los objetos
        for (auto* obj : objetosActivos) {
            delete obj;
        }

        for (auto* obj : objetosDisponibles) {
            delete obj;
        }

        objetosActivos.clear();
        objetosDisponibles.clear();
    }
};