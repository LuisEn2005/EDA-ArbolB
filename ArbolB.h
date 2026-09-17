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
    void dividirHijo(NodoB* padre, int posicion);
    void mostrar(NodoB* nodo, int nivel) const;
    void liberarMemoria(NodoB* nodo);
    void eliminarNodo(NodoB* nodo, int idx);
    int obtenerPredecesor(NodoB* nodo, int idx);
    int obtenerSucesor(NodoB* nodo, int idx);
    void llenar(NodoB* nodo, int idx);
    void prestarAnterior(NodoB* nodo, int idx);
    void prestarSiguiente(NodoB* nodo, int idx);
    void fusionar(NodoB* nodo, int idx);

  public:
    ArbolB(int gradoMinimo);
    ~ArbolB();
    
    bool buscar(int clave) const;
    void insertar(int clave);
    void mostrar() const;
    void eliminar(int clave);

};

#endif //ARBOLB_H
