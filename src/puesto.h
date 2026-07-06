#include <vector>
#include <utility>
#include <set>

#include "tipos.h"

#ifndef TP_LOLLA_PUESTO_H
#define TP_LOLLA_PUESTO_H

#include "list"

class Puesto {

    public:
        Puesto(Menu m, Stock s, Promociones ps);
        bool vendeItem(Producto i) const;
        Nat stock(Producto i) const;
        Nat descuentoDeItem(Nat, Producto) const;
        Nat gastoDePersona(Persona a) const;
        Nat vender(Persona a, Producto i, Nat cantidad);
        pair<Nat, bool> hackearPuesto(Persona a, Producto i);
        std::set<Producto> items() const;
    private:
        Stock _stock;
        Menu _precios;
        map<Producto, vector<pair<Nat, Nat>>> _descuentos;
        map<Persona, Nat> _gastos;
        map<Persona, map<Producto, std::list<Nat>>> _comprasHackeables;
        map<Persona, map<Producto, std::list<Nat>>> _comprasNoHackeables;

        void _ordenar(vector<pair<Nat, Nat>> p);

};


#endif //TP_LOLLA_PUESTO_H
