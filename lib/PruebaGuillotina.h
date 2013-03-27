#include "Guillotina.cc"
#include "tiempo.cc"
class PruebaGuillotina {
private:
  long long tiempo;
  long long sumaTiempos;
  int numeroPruebas;
  int tamProblema;
  
public:
  void realizarPruebas(void);
  PruebaGuillotina(int, int);
private:
  void setNumeroPruebas(int);
  void setTamProblema(int);
  void recalcularSumaTiempos(long long);
  void clearSumaTiempos(void);
public:
  int getNumeroPruebas(void);
  int getTamProblema(void);
  long long getSumaTiempos(void);
  double getMediaTiempo(void);
};