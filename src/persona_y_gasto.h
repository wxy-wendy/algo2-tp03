
#ifndef TP_LOLLA_PERSONA_Y_GASTO_H
#define TP_LOLLA_PERSONA_Y_GASTO_H


#include <utility>
#include "tipos.h"

class PersonaYGasto {

    private:
        Persona p;
        int tg;
        
    public:
        // el constructor es equivalente a la operación generar del modulo
        PersonaYGasto(Persona p, Nat tg);
        Persona persona() const;
        int totalGastado() const;
        bool operator> (const PersonaYGasto& e) const;
        bool operator< (const PersonaYGasto& e) const;
        bool operator== (const PersonaYGasto& e) const;

};



#endif //TP_LOLLA_PERSONA_Y_GASTO_H
