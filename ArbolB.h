#ifndef ARBOLB_H
#define ARBOLB_H

#include <iostream>
#include <vector>
using std::vector;

struct NodoB{
  vector<int> claves;
  vector<NodoB*> hijos;
  bool hoja;

  NodoB(bool esHoja = true) : hoja(esHoja) {}
};

class ArbolB{
  private:
    NodoB* raiz;
    int t;
    void insertarNoLleno(NodoB* nodo, int clave);
    void dividirHijo(NodoB* padre, int posicion, NodoB* hijo);
    void mostrar(NodoB* nodo) const;
    void liberarMemoria(NodoB* nodo);

  public:
    ArbolB(int gradoMinimo);
    ~ArbolB();
    
    bool buscar(int clave) const;
    void insertar(int clave);
    void mostrar() const;
};

#endif //ARBOLB_H
