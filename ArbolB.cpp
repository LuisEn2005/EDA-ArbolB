#include "ArbolB.h"

ArbolB::ArbolB(int gradoMinimo){
  this->raiz = nullptr;
  this->t = gradoMinimo;
}

bool ArbolB::buscar(int clave) const{
  NodoB* curr = raiz;
  while(curr != nullptr){
    int i = 0;
    int n = curr->claves.size();

    while(i < n && clave > curr->claves[i]) i++;

    if(i < n && curr->claves[i] == clave) return true;

    if(curr->hoja) return true;

    curr = curr->hijos[i];
  }

  return false;
}

void ArbolB::dividirHijo(NodoB* padre, int posicion){
  NodoB* y = padre->hijos[posicion];
  NodoB* z = new NodoB(y->hoja);

  for(int j = 0; j < t - 1; j++)
    z->claves.push_back(y->claves[j + t]);

  if(!y->hoja){
    for(int j = 0; j < t; j++){
      z->hijos.push_back(y->hijos[j + t]);
    }
  }

  y->claves.resize(t - 1);
  if(!y->hoja) y->hijos.resize(t);

  padre->hijos.insert(padre->hijos.begin() + posicion + 1, z);

  padre->claves.insert(padre->claves.begin() + posicion, y->claves[t-1]);
}

void ArbolB::insertarNoLleno(NodoB* nodo, int clave) {
  int i = nodo->claves.size() - 1;

  if (nodo->hoja) {
    nodo->claves.push_back(0);

    while (i >= 0 && clave < nodo->claves[i]) {
      nodo->claves[i + 1] = nodo->claves[i];
      i--;
    }

    nodo->claves[i + 1] = clave;
  } 
  else {
    while (i >= 0 && clave < nodo->claves[i]) {
      i--;
    }
    i++;

    if (nodo->hijos[i]->claves.size() == 2 * t - 1) {
      dividirHijo(nodo, i);

      if (clave > nodo->claves[i]) {
        i++;
      }
    }
    insertarNoLleno(nodo->hijos[i], clave);
  }
}

void ArbolB::insertar(int clave) {
  if (raiz == nullptr) {
    raiz = new NodoB(true);
    raiz->claves.push_back(clave);
    return;
  }

  if (raiz->claves.size() == 2 * t - 1) {
    NodoB* nuevaRaiz = new NodoB(false);

    nuevaRaiz->hijos.push_back(raiz);

    dividirHijo(nuevaRaiz, 0);

    int i = 0;
    if (nuevaRaiz->claves[0] < clave) {
      i++;
    }
    insertarNoLleno(nuevaRaiz->hijos[i], clave);

    raiz = nuevaRaiz;
  } 
  else {
    insertarNoLleno(raiz, clave);
  }
}

void ArbolB::mostrar(NodoB* nodo, int nivel) const {
  if (nodo != nullptr) {
    std::cout << "Nivel " << nivel << " [";
    for (size_t i = 0; i < nodo->claves.size(); i++) {
      std::cout << nodo->claves[i] << (i + 1 < nodo->claves.size() ? " " : "");
    }
    std::cout << "]\n";

    if (!nodo->hoja) {
      for (NodoB* hijo : nodo->hijos) {
        mostrar(hijo, nivel + 1);
      }
    }
  }
}

void ArbolB::mostrar() const {
  if (raiz == nullptr) {
    std::cout << "El árbol está vacío.\n";
  } else {
    mostrar(raiz, 0);
  }
}

void ArbolB::liberarMemoria(NodoB* nodo) {
  if (nodo != nullptr) {
    if (!nodo->hoja) {
      for (NodoB* hijo : nodo->hijos) {
        liberarMemoria(hijo);
      }
    }
    delete nodo;
  }
}

ArbolB::~ArbolB() {
  liberarMemoria(raiz);
  raiz = nullptr;
}

int ArbolB::obtenerPredecesor(NodoB* nodo, int idx){
  if(raiz == nullptr || raiz->hoja == true) return false;
  NodoB* y = nodo->hijos[idx];

  while(y->hoja == false) y = y->hijos.back();

  return y->claves.back();
}

int ArbolB::obtenerSucesor(NodoB* nodo, int idx){
  if(raiz == nullptr || raiz->hoja == true) return false;
  NodoB* y = nodo->hijos[idx + 1];
  
  while(y->hoja == false) y = y->hijos.front();

  return y->claves.front();
}

void ArbolB::prestarAnterior(NodoB* nodo, int idx){
  if(raiz == nullptr || raiz->hoja == true) return;
  
  NodoB* y = nodo->hijos[idx];
  NodoB* bro = nodo->hijos[idx-1];

  y->claves.insert(y->claves.begin(), nodo->claves[idx-1]);
  
  if(y->hoja == false){
    y->hijos.insert(y->hijos.begin(), bro->hijos.back());
    bro->hijos.pop_back();
  }

  nodo->claves[idx-1] = bro->claves.back();
  bro->claves.pop_back();  
}

void ArbolB::prestarSiguiente(NodoB* nodo, int idx){
  if(raiz == nullptr || raiz->hoja == true) return;
  
  NodoB* y = nodo->hijos[idx];
  NodoB* bro = nodo->hijos[idx+1];

  y->claves.push_back(nodo->claves[idx]);

  if(y->hoja == false){
    y->hijos.push_back(bro->hijos.front());
    bro->hijos.erase(bro->hijos.begin());
  }

  nodo->claves[idx] = bro->claves.front();

  bro->claves.erase(bro->claves.begin());
}

void ArbolB::fusionar(NodoB* nodo, int idx){
  NodoB* y = nodo->hijos[idx];
  NodoB* bro = nodo->hijos[idx + 1];

  y->claves.push_back(nodo->claves[idx]);

  for(int i = 0; i < bro->claves.size(); i++){
    y->claves.push_back(bro->claves[i]);
  }
  
  if(!y->hoja){
    for(int i = 0; i < bro->hijos.size(); i++){
      y->hijos.push_back(bro->hijos[i]);
    }
  }

  nodo->claves.erase(nodo->claves.begin() + idx);
  nodo->hijos.erase(nodo->hijos.begin() + idx + 1);

  delete bro;
}

void ArbolB::llenar(NodoB* nodo, int idx){
  if(idx != 0 && nodo->hijos[idx - 1]->claves.size() >= t){
    prestarAnterior(nodo, idx);
  }

  else if(idx != nodo->claves.size() && nodo->hijos[idx + 1]->claves.size() >= t){
    prestarSiguiente(nodo, idx);
  }

  else{
    if(idx != nodo->claves.size()){
      fusionar(nodo, idx);
    }
    else{
      fusionar(nodo, idx - 1);
    }
  }
}

void ArbolB::eliminarNodo(NodoB* nodo, int clave){
  int idx = 0;
  while (idx < nodo->claves.size() && nodo->claves[idx] < clave){
    idx++;
  }

  if (idx < nodo->claves.size() && nodo->claves[idx] == clave){

    if (nodo->hoja){
      nodo->claves.erase(nodo->claves.begin() + idx);
    } 
    else{
      if (nodo->hijos[idx]->claves.size() >= t){
        int pred = obtenerPredecesor(nodo, idx);
        nodo->claves[idx] = pred;
        eliminarNodo(nodo->hijos[idx], pred);
      } 
      else if (nodo->hijos[idx + 1]->claves.size() >= t){
        int suc = obtenerSucesor(nodo, idx);
        nodo->claves[idx] = suc;
        eliminarNodo(nodo->hijos[idx + 1], suc);
      } 
      else{
        fusionar(nodo, idx);
        eliminarNodo(nodo->hijos[idx], clave);
      }
    }
  } 
  else{
    if (nodo->hoja){
      std::cout << "La clave " << clave << " no existe en el arbol.\n";
      return;
    }

    bool esUltimoHijo = (idx == nodo->claves.size());

    if (nodo->hijos[idx]->claves.size() < t){
      llenar(nodo, idx);
    }

    if (esUltimoHijo && idx > nodo->claves.size()){
      eliminarNodo(nodo->hijos[idx - 1], clave);
    } else {
      eliminarNodo(nodo->hijos[idx], clave);
    }
  }
}

void ArbolB::eliminar(int clave){
  if (raiz == nullptr){
    std::cout << "El arbol esta vacio.\n";
    return;
  }

  eliminarNodo(raiz, clave);

  if (raiz->claves.empty()){
    NodoB* temp = raiz;
    if (raiz->hoja) {
      raiz = nullptr;
    } else {
      raiz = raiz->hijos[0];
    }
    delete temp;
  }
}
