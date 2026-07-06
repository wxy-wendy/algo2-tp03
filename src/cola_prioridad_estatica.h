#ifndef TP_LOLLA_COLA_PRIORIDAD_ESTATICA_H
#define TP_LOLLA_COLA_PRIORIDAD_ESTATICA_H

#include <set>
#include "persona_y_gasto.h"

using namespace std;

class ColaPrioridadEstatica {

    private:
        map<PersonaYGasto, bool> _colaGastadores;   // ordena por gasto de la persona en la tupla.
        map<Persona, Nat> _gastoDePersonas;        // para poder obtener el gasto de la persona en tiempo log, dada la persona
        
    public:
        ColaPrioridadEstatica(set<Persona> s);
        void cambiarPrioridad(Persona, Nat);
        const Persona proximo() const;
        const Nat obtenerGasto(Persona) const;

};


#endif //TP_LOLLA_COLA_PRIORIDAD_ESTATICA_H
