#ifndef GUILLOTINA_H_
#define GUILLOTINA_H_

#include "Pieza.cc"
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>

using std::vector;
using std::cout;
using std::endl;
using std::max;
using std::cin;
using std::string;

class Guillotina {
private:
  int altoLamina; // L
  int anchoLamina; // W
  const static int ZOOM = 1;
  /* Profundidad en el árbol al buscar recursivamente los cortes solución del
   * problema */
  int profundidadMaxima; 
  vector < vector <int> > matrizResultado;
  vector < vector <int> > conjuntoCortes;
  vector <Pieza> vectorPiezas;
public:
  // Alto lámina, ancho lámina (no usar)
  Guillotina(int, int);
  // Alto lámina, ancho lámina, vector de objetos Pieza
  Guillotina(int, int, const vector<Pieza>&);
  // Alto lámina, ancho lámina, número piezas, array altura de piezas
  // array ancho de piezas, array beneficio de piezas
  Guillotina(int, int, int, int*, int*, int*);
  void calcularMatriz(void);
  void calcularResultado(void);
private:
  vector < vector <int> > calcularResultadoSuperficial(int, int, int);
  vector < vector <int> > calcularResultado(int, int, int);
public:
  void imprimirMatriz(void);
  void imprimirPiezas(void);
  void imprimirCortes(void);
  void imprimirCortesGraf(void);
private:
  void imprimirParteSuperiorLamina(void);
  void imprimirParteInferiorLamina(void);
  void imprimirPiezaGraf(const vector<int>&);
  void imprimirUnidadHorizontal(void);
  void imprimirEspacioHorizontal(void);
public:
  void imprimirEstadisticas(void);
private:
  int piezaMaxBeneficio(int, int); // H(x)
  inline int getNumeroPiezas(void);
  void inicializarMatrizResultado(void);
  void inicializarMatrizCortes(void);
  inline const int& getAltoLamina(void);
  inline void setAltoLamina(const int&);
  inline const int& getAnchoLamina(void);
  inline void setAnchoLamina(const int&);
  inline int getProfundidadMaxima(void);
  inline void actualizarProfundidadMaxima(int);
  inline void setProfundidadMaxima(int);
  inline int getMatrizResultado(int, int);
  inline void setMatrizResultado(int, int, int);
  inline const vector<int>& getConjuntoCortes(int);
  inline int getNumeroSoluciones(void);
  inline void setConjuntoCortes(const vector < vector <int> >&);
  inline void setVectorPiezas(const vector <Pieza>&);
  inline void addPieza(const Pieza&);
  inline const Pieza& getPieza(int);
};

#endif