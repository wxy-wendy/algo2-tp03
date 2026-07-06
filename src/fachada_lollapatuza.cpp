#include "fachada_lollapatuza.h"

using namespace std;

map<IdPuesto, Puesto> FachadaLollapatuza::_convertirPuestos(const map<IdPuesto, aed2_Puesto> puestos) const {
    
    map<IdPuesto, Puesto> res;
    
    for (pair<IdPuesto, aed2_Puesto> pid : puestos) {
        Puesto p = Puesto(pid.second.menu, pid.second.stock, pid.second.promociones);
        res.insert(pair<IdPuesto, Puesto>(pid.first, p));
        // res[pid.first] = p;
    }
    return res; 
}

FachadaLollapatuza::FachadaLollapatuza(const set<Persona> &personas, const map<IdPuesto, aed2_Puesto> &infoPuestos) : _lolla(Lollapatuza(_convertirPuestos(infoPuestos), personas)) {}

void FachadaLollapatuza::registrarCompra(Persona persona, Producto producto, Nat cant, IdPuesto idPuesto) {
    _lolla.vender(idPuesto, persona, producto, cant);
}

void FachadaLollapatuza::hackear(Persona persona, Producto producto) {
    _lolla.hackear(persona, producto);
}

Nat FachadaLollapatuza::gastoTotal(Persona persona) const {
    return _lolla.gastoTotal(persona);
}

Persona FachadaLollapatuza::mayorGastador() const {
    return _lolla.masGasto();
}

IdPuesto FachadaLollapatuza::menorStock(Producto producto) const {
    return _lolla.puestoDeMenorStock(producto);
}

const set<Persona>& FachadaLollapatuza::personas() const {
    return _lolla.obtenerPersonas();
}

Nat FachadaLollapatuza::stockEnPuesto(IdPuesto idPuesto, const Producto &producto) const {
    map<IdPuesto, Puesto> diccPuestosId = _lolla.obtenerPuestos();
    Puesto puesto = diccPuestosId.at(idPuesto);
    return puesto.stock(producto);
}

Nat FachadaLollapatuza::descuentoEnPuesto(IdPuesto idPuesto, const Producto &producto, Nat cantidad) const {
    map<IdPuesto, Puesto> diccPuestosId = _lolla.obtenerPuestos();
    Puesto puesto = diccPuestosId.at(idPuesto);
    return puesto.descuentoDeItem(cantidad, producto);
}

Nat FachadaLollapatuza::gastoEnPuesto(IdPuesto idPuesto, Persona persona) const {
    map<IdPuesto, Puesto> diccPuestosId = _lolla.obtenerPuestos();
    Puesto puesto = diccPuestosId.at(idPuesto);
    return puesto.gastoDePersona(persona);
}

set<IdPuesto> FachadaLollapatuza::idsDePuestos() const {
    const map<IdPuesto, Puesto> puestos = _lolla.obtenerPuestos();
    set<IdPuesto> res;
    for (pair<IdPuesto, Puesto> puestoConId : puestos) {
        res.insert(puestoConId.first);
    }
    return res;
}