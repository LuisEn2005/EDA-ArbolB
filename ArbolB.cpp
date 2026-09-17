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
  while(y->hijos.back()->hoja == false) y = y->hijos.back();

  for(int i = 0; i < y->hijos->claves.size())


  return false;
}
