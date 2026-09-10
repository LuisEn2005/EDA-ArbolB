#include "ArbolB.h"

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

void ArbolB::dividirHijo(NodoB* padre, int posicion, NodoB* hijo){
  
}
