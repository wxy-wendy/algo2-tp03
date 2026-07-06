//
// Created by PC on 26/6/2023.
//

#include "puesto.h"
#include "tipos.h"
#include <utility>
#include <iostream>
#include <algorithm>

using namespace std;

vector<pair<Nat, Nat>> map2Vector(map<Nat, Nat>& m){

    vector<pair<Nat,Nat>> v(m.size());

    map<Nat, Nat>::iterator it = m.begin();
    while (it != m.end()) {

        v.push_back(*it);
        it++;
    }
    // supongo que los vectores ya estan ordenados xq provenian de
    // un diccLog y lo itere en orden??? Sí.

    return v;
}

Puesto::Puesto(Menu m, Stock s, Promociones ps) : _precios(m), _stock(s), _descuentos(), _gastos(), _comprasHackeables(), _comprasNoHackeables(){

    map<Producto, map<Nat, Nat>>::iterator it = ps.begin();

    while (it != ps.end()) {
        _descuentos[it->first] = map2Vector(it->second);
        it++;
    }

}

bool Puesto::vendeItem(Producto i) const {
    return _stock.count(i) == 1;
}

Nat Puesto::stock(Producto i) const {
    if (!vendeItem(i)) {
        return 0;
    }
    return _stock.at(i);
}

Nat Puesto::descuentoDeItem(Nat cantidad, Producto i) const {
    if (_descuentos.count(i) == 0) {
        return 0;
    }

    const vector<pair<Nat, Nat>>& descuentosDisponibles = _descuentos.at(i);
    
    Nat res = 0;

    int low = 0;
    int high = descuentosDisponibles.size();

    if (descuentosDisponibles.size() != 0) {
        while (low + 1 < high) {

            int mid = (low + high)/2;

            if (descuentosDisponibles[mid].first <= cantidad) low = mid;
            else high = mid;
        }
    }

    res = descuentosDisponibles[low].second;
    return res;
}

Nat Puesto::gastoDePersona(Persona a) const{
    Nat res = 0;

    if (_gastos.count(a) == 1) res = _gastos.at(a);

    return res;
}

Nat Puesto::vender(Persona a, Producto i, Nat cantidad) {

    Nat precioBase = _precios[i];
    Nat descuento = descuentoDeItem(cantidad, i); //  log(I)  ???
    Nat res = (precioBase - precioBase*(descuento/100.0)) * cantidad;

    if (_gastos.count(a) == 1) {
        _gastos[a] = _gastos[a] + res;
    } else {
        _gastos[a] = res;
    }

    if(descuento == 0){

        if (_comprasHackeables.count(a) == 0) {

            _comprasHackeables[a] = map<Producto, list<Nat>>();
        }

        map<Producto, list<Nat>>& comprasHackeablesDePersona = _comprasHackeables[a];
        if (comprasHackeablesDePersona.count(i) == 0) {

            comprasHackeablesDePersona[i] = list<Nat>();
            comprasHackeablesDePersona[i].push_back(cantidad);
        } else {

            list<Nat>& cantidadesCompradasHackeables = comprasHackeablesDePersona[i];
            cantidadesCompradasHackeables.push_back(cantidad);
        }

    } else {

        if (_comprasNoHackeables.count(a)==0) {
            _comprasHackeables[a] = map<Producto, list<Nat>>();
        }

        map<Producto, list<Nat>>& comprasNoHackeablesDePersona = _comprasNoHackeables[a];

        if (comprasNoHackeablesDePersona.count(i) == 0) {
            comprasNoHackeablesDePersona[i] = list<Nat>();
            comprasNoHackeablesDePersona[i].push_back(cantidad);
        } else {
            list<Nat>& cantidadesCompradasNoHackeables = comprasNoHackeablesDePersona[i];
            cantidadesCompradasNoHackeables.push_back(cantidad);
        }
    }

    _stock[i] = _stock[i] - cantidad;


    return res;
}

pair<Nat, bool> Puesto::hackearPuesto(Persona a, Producto i) {

    pair<Nat, bool> res = make_pair(_precios.at(i), true);

    _stock[i] = _stock[i] + 1;
    Nat precioItem = _precios.at(i);
    Nat gastoPersonaActualizado = _gastos.at(a) - precioItem;

    if(gastoPersonaActualizado == 0) {
        _gastos.erase(a);
    }else{
        _gastos.at(a) = gastoPersonaActualizado;
    }

    list<Nat>& listaCantHackeable = (list<Nat> &) ((&_comprasHackeables.at(a))->at(i));

    if (listaCantHackeable.size() == 1 && listaCantHackeable.back() == 1) {
        _comprasHackeables.at(a).erase(i);

        if (_comprasHackeables.at(a).size() == 0) { // si la persona no compro nada hackeable
            _comprasHackeables.erase(a);
        }
        res.second = false;
    } else {
        listaCantHackeable.back()--;
        if (listaCantHackeable.back() == 0) listaCantHackeable.pop_back();
    }

    return res;
}

set<Producto> Puesto::items() const {
    set<Producto> res;
    for (auto itDiccStock = _stock.begin(); itDiccStock != _stock.end(); itDiccStock++) {
        res.insert(itDiccStock->first);
    }
    return res;
}
