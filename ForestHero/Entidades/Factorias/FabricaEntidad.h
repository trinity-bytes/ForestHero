#pragma once
#include <memory>
#include <unordered_map>
#include <functional>
#include <string>
#include "../Base/Entidad.h"
#include "../Personajes/Guardian.h"
#include "../Personajes/Enemigo.h"
#include "../Items/Agua.h"
#include "../Items/Semilla.h"
#include "../Items/Arbol.h"
#include "../Items/Basura.h"
#include "../Items/Potenciador.h"

class FabricaEntidad {
private:
    static FabricaEntidad* instancia;
    std::unordered_map<TipoEntidad, std::function<Entidad* (int, int)>> fabricas;

    // Constructor privado para singleton
    FabricaEntidad() {
        // Registrar todos los tipos de entidades
        registrarTipoEntidad(TipoEntidad::Guardian, [](int x, int y) { return new Guardian(x, y); });
        registrarTipoEntidad(TipoEntidad::Enemigo, [](int x, int y) { return new Enemigo(x, y); });
        registrarTipoEntidad(TipoEntidad::Agua, [](int x, int y) { return new Agua(x, y); });
        registrarTipoEntidad(TipoEntidad::Semilla, [](int x, int y) { return new Semilla(x, y); });
        registrarTipoEntidad(TipoEntidad::Arbol, [](int x, int y) { return new Arbol(x, y); });
        registrarTipoEntidad(TipoEntidad::Basura, [](int x, int y) { return new Basura(x, y); });
        registrarTipoEntidad(TipoEntidad::PowerUp, [](int x, int y) { return new Potenciador(x, y); });
    }

public:
    // Patrón singleton
    static FabricaEntidad* obtenerInstancia() {
        if (!instancia) {
            instancia = new FabricaEntidad();
        }
        return instancia;
    }

    void registrarTipoEntidad(TipoEntidad tipo, std::function<Entidad* (int, int)> fabrica) {
        fabricas[tipo] = fabrica;
    }

    Entidad* crearEntidad(TipoEntidad tipo, int x, int y) {
        auto it = fabricas.find(tipo);
        if (it != fabricas.end()) {
            return it->second(x, y);
        }
        return nullptr;
    }

    // Métodos de conveniencia heredados
    Guardian* crearGuardian(int x, int y) {
        return static_cast<Guardian*>(crearEntidad(TipoEntidad::Guardian, x, y));
    }

    Enemigo* crearEnemigo(int x, int y) {
        return static_cast<Enemigo*>(crearEntidad(TipoEntidad::Enemigo, x, y));
    }

    Agua* crearAgua(int x, int y) {
        return static_cast<Agua*>(crearEntidad(TipoEntidad::Agua, x, y));
    }

    Semilla* crearSemilla(int x, int y) {
        return static_cast<Semilla*>(crearEntidad(TipoEntidad::Semilla, x, y));
    }

    Arbol* crearArbol(int x, int y) {
        return static_cast<Arbol*>(crearEntidad(TipoEntidad::Arbol, x, y));
    }

    Basura* crearBasura(int x, int y) {
        return static_cast<Basura*>(crearEntidad(TipoEntidad::Basura, x, y));
    }

    Potenciador* crearPotenciador(int x, int y) {
        return static_cast<Potenciador*>(crearEntidad(TipoEntidad::PowerUp, x, y));
    }

    ~FabricaEntidad() {
        delete instancia;
        instancia = nullptr;
    }
};

// Inicializar miembro estático
FabricaEntidad* FabricaEntidad::instancia = nullptr;