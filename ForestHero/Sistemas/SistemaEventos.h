#pragma once
#include <functional>
#include <unordered_map>
#include <vector>
#include <string>

enum class TipoEvento {
    ColisionJugador,
    EnemigoEliminado,
    SemillaPlantada,
    PotenciadorRecogido,
    CambioEstadoJuego,
    AguaRecogida,
	SemillaRecogida,
    SemillaDisparada,
    BasuraDestruida,
    ArbolPlantado,
    GuardianDa�ado
};

class SistemaEventos {
private:
    static SistemaEventos* instancia;
    std::unordered_map<TipoEvento, std::vector<std::function<void(void*)>>> suscriptores;

    SistemaEventos() {}

public:
    static SistemaEventos* obtenerInstancia() {
        if (!instancia) {
            instancia = new SistemaEventos();
        }
        return instancia;
    }

    void suscribir(TipoEvento evento, std::function<void(void*)> callback) {
        suscriptores[evento].push_back(callback);
    }

    void publicar(TipoEvento evento, void* datos = nullptr) {
        if (suscriptores.find(evento) != suscriptores.end()) {
            for (auto& callback : suscriptores[evento]) {
                callback(datos);
            }
        }
    }
};

// Inicializaci�n de la variable est�tica
SistemaEventos* SistemaEventos::instancia = nullptr;