#include "lib/PruebaGuillotina.cc"
#include "lib/tratamientocadenas.cpp"
int main(int argc, const char* argv[]) {
  int numeroPruebas;
  int tamProblema;
  if((argc == 3)&&(cadenaEsNumero(argv[1]))&&(cadenaEsNumero(argv[2]))) {
    numeroPruebas = StringToNumber(argv[1]);
    tamProblema = StringToNumber(argv[2]);
    PruebaGuillotina prueba(numeroPruebas, tamProblema);
    cout << "Número de pruebas: " << numeroPruebas << endl;
    cout << "Tamaño n del problema: " << tamProblema << endl;
    cout << endl;

    cout << "Media de tiempos:" << endl;
    cout << "Multiplicación clásica = " << prueba.getMediaTiempo() << " ms" << endl;
  }
  else {
    cout << "El programa debe ser llamado así: " << endl;
    cout << "<Número_de_pruebas> <Tamaño_del_problema>" << endl;
  }
}