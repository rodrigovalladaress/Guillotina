#include "lib/Guillotina.cc"
int main() {
  int numPiezas = 5;
  int lPiezas[] = {1, 2, 2, 1, 2, 3};
  int wPiezas[] = {2, 1, 2, 2, 3, 4};
  int pPiezas[] = {1, 2, 4, 1, 2, 5};
  Guillotina guillotina(10, 15, numPiezas, lPiezas, wPiezas, pPiezas);
  guillotina.calcularMatriz();
  guillotina.imprimirPiezas();
  cout << endl;
  guillotina.imprimirMatriz();
  cout << endl;
  guillotina.calcularResultado();
  guillotina.imprimirCortes();
  cout << endl;
  guillotina.imprimirEstadisticas();
  cout << endl;
  //guillotina.imprimirCortesGraf();
}