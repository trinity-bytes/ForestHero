#pragma once
#include "iostream"
#include "fstream"
#include "vector"
#include "string"
#include "algorithm"

using namespace std;

struct Puntaje {
    string nombre;
    int puntos;

    // Para facilitar la escritura y lectura del archivo binario
    friend ostream& operator<<(ostream& os, const Puntaje& p) {
        size_t nombreLength = p.nombre.size();
        os.write(reinterpret_cast<const char*>(&nombreLength), sizeof(nombreLength));
        os.write(p.nombre.data(), nombreLength);
        os.write(reinterpret_cast<const char*>(&p.puntos), sizeof(p.puntos));
        return os;
    }

    friend istream& operator>>(istream& is, Puntaje& p) {
        size_t nombreLength;
        if (!is.read(reinterpret_cast<char*>(&nombreLength), sizeof(nombreLength))) return is;

        p.nombre.resize(nombreLength);
        if (!is.read(&p.nombre[0], nombreLength)) return is;

        if (!is.read(reinterpret_cast<char*>(&p.puntos), sizeof(p.puntos))) return is;

        return is;
    }
};

class GestionPuntajes
{
private:
    string archivoPuntajes;
public:
    GestionPuntajes(const string& archivo);
    ~GestionPuntajes();

    void GuardarPuntaje(const Puntaje& puntaje);
    vector<Puntaje> LeerPuntajes();
    vector<Puntaje> ObtenerRanking();
};

GestionPuntajes::GestionPuntajes(const string& archivo) : archivoPuntajes(archivo)
{
    ofstream archivoSalida(archivoPuntajes, ios::binary | ios::app);
    if (!archivoSalida.is_open()) {
        cerr << "No se pudo crear el archivo: " << archivoPuntajes << endl;
    }
    archivoSalida.close();
}

GestionPuntajes::~GestionPuntajes() {}

void GestionPuntajes::GuardarPuntaje(const Puntaje& puntaje)
{
    ofstream archivo(archivoPuntajes, ios::binary | ios::app);
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo para guardar el puntaje." << endl;
        return;
    }
    archivo << puntaje;
    archivo.close();
}

vector<Puntaje> GestionPuntajes::LeerPuntajes()
{
    vector<Puntaje> puntajes;
    ifstream archivo(archivoPuntajes, ios::binary);

    // Si el archivo no existe, retorna el vector vacío
    if (!archivo.is_open()) {
        cerr << "El archivo no existe o no se pudo abrir: " << archivoPuntajes << endl;
        return puntajes;
    }

    Puntaje puntaje;
    while (archivo.peek() != EOF && archivo >> puntaje) { // Validar si EOF no se ha alcanzado
        puntajes.push_back(puntaje);
    }

    if (archivo.fail() && !archivo.eof()) {
        cerr << "Error al leer el archivo. Los datos podrían estar corruptos." << endl;
    }

    archivo.close();
    return puntajes;
}

vector<Puntaje> GestionPuntajes::ObtenerRanking()
{
    vector<Puntaje> puntajes = LeerPuntajes();
    sort(puntajes.begin(), puntajes.end(), [](const Puntaje& a, const Puntaje& b) {
        return a.puntos > b.puntos;
        });
    return puntajes;
}