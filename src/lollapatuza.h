//
// Created by PC on 26/6/2023.
//

#ifndef TP_LOLLA_LOLLAPATUZA_H
#define TP_LOLLA_LOLLAPATUZA_H

#include "utility"
#include "puesto.h"
#include "set"
#include "cola_prioridad_estatica.h"
#include "cola_prioridad.hpp"

using namespace std;

struct infoPuesto {

    IdPuesto idp;
    Puesto* puesto;

    infoPuesto(IdPuesto i, Puesto* puesto) : puesto(puesto), idp(i) {}

    // Para los espacios inutilizados del vector
    // (el vector de c++ no acepta posiciones sin inicializar)
    infoPuesto() {}

    bool operator<(const infoPuesto a) const {
        return idp < a.idp;
    }
};

class Lollapatuza {
private:

    map<IdPuesto, Puesto> _puestos;
    set<Persona> _personas;
    ColaPrioridadEstatica _consumidores;
    map<Persona, map<Producto, ColaPrioridad<infoPuesto>>> _puestosHackeables;

    std::set<Producto> _itemsDeLolla(map<IdPuesto, Puesto>);

public:
    // el constructor corresponde a la función nuevo sistema
    Lollapatuza(map<IdPuesto, Puesto> puestos, const set<Persona>& personas);
    void vender(IdPuesto id, Persona a, Producto i, Nat cant);
    void hackear(Persona a, Producto i);
    Nat gastoTotal(Persona a) const;
    Persona masGasto() const;
    IdPuesto puestoDeMenorStock(Producto i) const;
    const std::set<Persona>& obtenerPersonas() const;
    const std::map<IdPuesto, Puesto>& obtenerPuestos() const;

};

#endif //TP_LOLLA_LOLLAPATUZA_H
