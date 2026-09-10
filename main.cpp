#include <iostream>
#include <vector>
#include "ArbolB.h"

using std::cout;
using std::cin;
using std::endl;
using std::vector;

void ejecutarCasosDePrueba(ArbolB& arbol) {
  vector<int> casoA = {10, 20, 5, 6, 12, 30, 7, 17};
  cout << "\n--- Ejecutando Caso A (Prueba del laboratorio) ---\n";
  for (int clave : casoA) {
    cout << "\nInsertando " << clave << ":\n";
    arbol.insertar(clave);
    arbol.mostrar();
  }
}

int main() {
  int t = 2;
  ArbolB arbol(t);
  int opcion = 0;
  int clave = 0;

  do {
    cout << "\n========== ARBOL B ==========\n";
    cout << "1. Insertar clave\n";
    cout << "2. Buscar clave\n";
    cout << "3. Mostrar arbol\n";
    cout << "4. Salir\n";
    cout << "Seleccione una opcion: ";
    cin >> opcion;

    switch (opcion) {
      case 1:
        cout << "Ingrese la clave a insertar: ";
        cin >> clave;
        arbol.insertar(clave);
        cout << "Clave " << clave << " insertada correctamente.\n";
        break;

      case 2:
        cout << "Ingrese la clave a buscar: ";
        cin >> clave;
        if (arbol.buscar(clave)) {
          cout << "Resultado: Encontrada\n";
        } else {
          cout << "Resultado: No encontrada\n";
        }
        break;

      case 3:
        cout << "\n--- Estructura del Arbol B ---\n";
        arbol.mostrar();
        break;

      case 4:
        cout << "Saliendo del programa...\n";
        break;

      default:
        cout << "Opcion no valida. Intente de nuevo.\n";
        break;
    }
  } while (opcion != 4);

  return 0;
}
