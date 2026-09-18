#include <iostream>
#include "ArbolB.h"

using std::cout;
using std::cin;
using std::endl;

int main() {
  int t = 2;
  ArbolB arbol(t);
  int opcion = 0;
  int clave = 0;

  do {
    cout << "\n========== ARBOL B ==========\n";
    cout << "1. Insertar clave\n";
    cout << "2. Buscar clave\n";
    cout << "3. Eliminar clave\n";
    cout << "4. Mostrar arbol\n";
    cout << "5. Salir\n";
    cout << "Seleccione una opcion: ";
    cin >> opcion;

    switch (opcion) {
      case 1:
        cout << "Ingrese clave a insertar: ";
        cin >> clave;
        arbol.insertar(clave);
        break;
      case 2:
        cout << "Ingrese clave a buscar: ";
        cin >> clave;
        if (arbol.buscar(clave)) {
          cout << "Clave " << clave << " encontrada en el arbol.\n";
        } else {
          cout << "Clave " << clave << " no encontrada.\n";
        }
        break;
      case 3:
        cout << "Ingrese clave a eliminar: ";
        cin >> clave;
        arbol.eliminar(clave);
        cout << "Operacion completada.\n";
        break;
      case 4:
        cout << "\nEstructura actual del Arbol B:\n";
        arbol.mostrar();
        break;
      case 5:
        cout << "Saliendo del programa...\n";
        break;
      default:
        cout << "Opcion invalida. Intente de nuevo.\n";
    }
  } while (opcion != 5);
  return 0;
}
