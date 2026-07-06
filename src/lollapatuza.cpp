//
// Created by PC on 26/6/2023.
//

#include "lollapatuza.h"
#include "puesto.h"
#include <iostream>

using namespace std;

Lollapatuza::Lollapatuza(map<IdPuesto, Puesto> diccPuestos, const set<Persona>& as) :
    _consumidores(ColaPrioridadEstatica(as)),
    _puestos(diccPuestos),
    _personas(as) {
        
    auto itPersonas = as.begin();
    while (itPersonas != as.end()) {
        map<Producto, ColaPrioridad<infoPuesto>> diccItems;

        set<Producto> itemsVendidosEnLolla = _itemsDeLolla(diccPuestos);

        auto itItems = itemsVendidosEnLolla.begin();

        while (itItems != itemsVendidosEnLolla.end()) {
            Nat cantPuestos = diccPuestos.size();
            diccItems.insert(pair<Producto, ColaPrioridad<infoPuesto>>(*itItems,ColaPrioridad<infoPuesto>(cantPuestos)));
            itItems++;
        }

        _puestosHackeables[*itPersonas] = diccItems;

        itPersonas++;
    }
}

void Lollapatuza::vender(IdPuesto idPuestoVendedor, Persona comprador, Producto prod, Nat cant) {
    Puesto* puestoVendedor = &(_puestos.at(idPuestoVendedor));

    Nat precioFinal = puestoVendedor->vender(comprador, prod, cant);
    Nat descuentoAplicado = puestoVendedor->descuentoDeItem(cant, prod);

    Nat gastoTotalViejo = _consumidores.obtenerGasto(comprador);
    Nat gastoTotalNuevo = gastoTotalViejo + precioFinal;

    _consumidores.cambiarPrioridad(comprador, gastoTotalNuevo);

    if (descuentoAplicado == 0) {
        map<Producto, ColaPrioridad<infoPuesto>>* puestosHackeablesDePersona = &(_puestosHackeables.at(comprador));
        ColaPrioridad<infoPuesto>* puestosHackeablesPorItem = &(puestosHackeablesDePersona->at(prod));
        puestosHackeablesPorItem->encolar(infoPuesto(idPuestoVendedor, puestoVendedor));
    }
}

void Lollapatuza::hackear(Persona comprador, Producto prod) {
    map<Producto, ColaPrioridad<infoPuesto>> itemsHackeables = _puestosHackeables[comprador];

    infoPuesto puestoAHackear = itemsHackeables.at(prod).proximo();

    pair<Nat, bool> resHackeoPuesto = puestoAHackear.puesto->hackearPuesto(comprador, prod) ;

    _consumidores.cambiarPrioridad(
        comprador,
        _consumidores.obtenerGasto(comprador) - resHackeoPuesto.first
    );

    // si ya no sigue siendo hackeable
    if (!resHackeoPuesto.second) {
        _puestosHackeables[comprador].at(prod).desencolar();
    }

}


Nat Lollapatuza::gastoTotal(Persona p) const {
    return _consumidores.obtenerGasto(p);
}

Persona Lollapatuza::masGasto() const {
    return _consumidores.proximo();     // _consumidores es una cola de prior est, atributo de lolla, a su vez la cola tiene 2 diccionarios
    // cola de gastadores y gastos por persona, ambos dicc log, solo que el primero seria como un conj log <persona, gasto>
    // por alguna razon, la colaDeGastadores de la cola estatica, solamente tiene un elemento... revisar el constructore de cola estatica...
}

std::set<Producto> Lollapatuza::_itemsDeLolla(map<IdPuesto, Puesto> diccPuestos) {
    set<Producto> res;
    auto itDiccPuestos = diccPuestos.begin();
    while (itDiccPuestos != diccPuestos.end()) {
    set<Producto> itemsDePuesto = itDiccPuestos->second.items();
        auto itItems = itemsDePuesto.begin();
        while (itItems != itemsDePuesto.end()) {
            res.insert(*itItems);
            itItems++;
        }
        itDiccPuestos++;
    }
    return res;
}

IdPuesto Lollapatuza::puestoDeMenorStock(Producto i) const {
    map<IdPuesto, Puesto>::const_iterator itPuestos = _puestos.begin();
    auto minimo = itPuestos;

    while (itPuestos != _puestos.end() && !((itPuestos->second).vendeItem(i))) {
        itPuestos++;
    }

    if (itPuestos == _puestos.end()) {
        minimo = _puestos.begin();
    } else {
        itPuestos++;
        
        while (itPuestos != _puestos.end()) {
            const Puesto& sigPuesto = itPuestos->second;
            if (sigPuesto.vendeItem(i)) {
                Nat stockMinActual = minimo->second.stock(i);
                Nat stockPuestoIterando = sigPuesto.stock(i);
                if (stockPuestoIterando < stockMinActual || (stockPuestoIterando == stockMinActual && itPuestos->first < minimo->first)){
                    minimo = itPuestos;
                }
            }
            itPuestos++;
        }
    }
    return minimo->first;
}

const set<Persona>& Lollapatuza::obtenerPersonas() const {
    return _personas;
}

const map<IdPuesto, Puesto>& Lollapatuza::obtenerPuestos() const {
    return _puestos;
}

