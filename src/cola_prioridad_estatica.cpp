//
// Created by pablo on 26-Jun-23.
//
#include "cola_prioridad_estatica.h"

using namespace std;

ColaPrioridadEstatica::ColaPrioridadEstatica(set<Persona> s) { // el construcor de cola de prior estatica
    set<Persona>::iterator it = s.begin();

    while (it != s.end()) {
        _colaGastadores[PersonaYGasto(*it, 0)] = true;  // inicializa todas las personas de la cola de gastadores con gasto 0, tdos los sign bool basura.
        _gastoDePersonas[*it] = 0;      //  inicializa los gastos de todas las personas en 0
        it++;
    }
}

void ColaPrioridadEstatica::cambiarPrioridad(Persona p, Nat t) {
    PersonaYGasto pygACambiarPrio = PersonaYGasto(p, _gastoDePersonas[p]);
    PersonaYGasto pygConPrioNueva = PersonaYGasto(p, t);
    _colaGastadores.erase(pygACambiarPrio);
    _colaGastadores.insert(pair<PersonaYGasto, bool>(pygConPrioNueva, true));
    _gastoDePersonas[p] = t;
}

const Persona ColaPrioridadEstatica::proximo() const {
    auto itFinal = _colaGastadores.end();    // suponemos que el iterador avanza de pricipio a fin de forma ascendente...
    itFinal--;                  // el elemento antes del final seria el que tiene el gasto mas grande de las tuplas de claves
    return (itFinal->first).persona();
}

const Nat ColaPrioridadEstatica::obtenerGasto(Persona p) const {
    // Acceso a diccionario logaritmico
    return _gastoDePersonas.at(p);
}
