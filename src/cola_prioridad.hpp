//
// Created by PC on 26/6/2023.
//

#include <map>
#include <vector>
#include <algorithm>
#include "tipos.h"

using namespace std;

#ifndef TP_LOLLA_COLA_PRIORIDAD_H
#define TP_LOLLA_COLA_PRIORIDAD_H

template<class T>
class ColaPrioridad {

    public:
        ColaPrioridad(Nat tam);
        T proximo();
        bool estaVacia();
        void encolar(const T& e);
        void desencolar();

    private:
        Nat _tam;
        map<T, bool> _elementosEnCola; 
        vector<T> _cola;
        void _siftUp(vector<T>& c, Nat i);
        void _siftDown(vector<T>& c, Nat i, Nat tam);
        void swap(Nat i, Nat j);
    
};


template<class T>
ColaPrioridad<T>::ColaPrioridad(Nat tam) {
    _tam = 0;
    _cola = std::vector<T>(tam);
}

template<class T>
T ColaPrioridad<T>::proximo() {
    return _cola[0];
}

template<class T>
bool ColaPrioridad<T>::estaVacia() {
    return _tam == 0;
}

template<class T>
void ColaPrioridad<T>::encolar(const T& e) {
    if (_elementosEnCola.count(e) == 0) {
        _cola[_tam] = e;
        _siftUp(_cola, _tam);
        _tam++;
        _elementosEnCola[e] = true;
    }
}

template<class T>
void ColaPrioridad<T>::desencolar() {
    T ultimo = _cola[_tam - 1];
    _elementosEnCola.erase(_elementosEnCola.begin());
    _cola[0] = ultimo;
    _siftDown(_cola, 0, _tam-1);
    _tam--;
}

template<class T>
void ColaPrioridad<T>::_siftUp(vector<T>& c, Nat i) {
    if (i != 0 && _cola[i] < _cola[(i - 1) / 2]) {
        T elem = _cola[i];
        _cola[i] = _cola[(i - 1) / 2];
        _cola[(i - 1) / 2] = elem;
        _siftUp(_cola, (i - 1) / 2);
    }
}

template<class T>
void ColaPrioridad<T>::_siftDown(vector<T>& c, Nat i, Nat tam){   // es  min heap, contiene infoPuesto
    Nat hijoIzq = 2*i + 1;
    Nat hijoDer = 2*i + 2;

    if (hijoIzq >= tam && hijoDer >= tam) { // el nodo no tiene hijos
        return;
    }
    if (hijoIzq < tam && hijoDer < tam) {   // el nodo tiene 2 hijos

        Nat minIndex;

        if (_cola[hijoDer] < _cola[hijoIzq]) minIndex = hijoDer;
        else minIndex = hijoIzq;

        if(_cola[minIndex] < _cola[i]){
            swap(i, minIndex);
            _siftDown(_cola, minIndex, tam);
        }
        return;

    } else {

        if (hijoDer >= tam) { // solo tiene hijo izquierdo
            if (_cola[hijoIzq] < _cola[i]) {
                swap(i, hijoIzq);
                _siftDown(_cola, hijoIzq, tam);
            }
            else return;    // en caso que el hijo izq no sea menor al nodo actual
        }
        // no puede pasar q solo tenga hijo derecho
        /*else if (hijoIzq >= tam) { // solo tiene hijo derecho
            if (_cola[hijoDer] < _cola[i]) {
                swap(i, hijoDer);
                _siftDown(_cola, hijoDer, tam);
            }
            else return;
        }*/
    }
}

template<class T>
void ColaPrioridad<T>::swap(Nat i, Nat j) {
    T elem = _cola[i];
    _cola[i] = _cola[j];
    _cola[j] = elem;
}



#endif //TP_LOLLA_COLA_PRIORIDAD_H
