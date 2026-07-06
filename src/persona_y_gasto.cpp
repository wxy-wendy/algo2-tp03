//
// Created by PC on 26/6/2023.
//

#include <iostream>
#include "persona_y_gasto.h"

PersonaYGasto::PersonaYGasto(Persona p, Nat tg) : p(p), tg(tg) {
}

Persona PersonaYGasto::persona() const {
    return p;
}

int PersonaYGasto::totalGastado() const {
    return tg;
}

bool PersonaYGasto::operator>(const PersonaYGasto &e) const {
    return tg > e.tg;
}
bool PersonaYGasto::operator<(const PersonaYGasto &e) const {

    if (tg != e.tg) {
        return tg < e.tg;
    }
    return persona() < e.persona();

}

bool PersonaYGasto::operator==(const PersonaYGasto &e) const {
    return tg == e.tg;
}
