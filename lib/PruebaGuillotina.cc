#include "PruebaGuillotina.h"

void PruebaGuillotina::realizarPruebas(void) {
  clearSumaTiempos();
  for(int i = 0; i < getNumeroPruebas(); i++) {
    cronomilisec(1);
    recalcularSumaTiempos(cronomilisec(0));
  }
}

PruebaGuillotina::PruebaGuillotina(int numPruebas, int tamProblema) {
  srand(time(NULL));
  clearSumaTiempos();
  setNumeroPruebas(numPruebas);
  setTamProblema(tamProblema);
}

void PruebaGuillotina::setNumeroPruebas(int nPruebas) {
  numeroPruebas = nPruebas;
}

void PruebaGuillotina::setTamProblema(int tProblema) {
  tamProblema = tProblema;
}

void PruebaGuillotina::recalcularSumaTiempos(long long tiempo) {
  sumaTiempos += tiempo; 
}

void PruebaGuillotina::clearSumaTiempos(void) {
  sumaTiempos = 0;
}

int PruebaGuillotina::getNumeroPruebas(void) {
  return numeroPruebas;
}

int PruebaGuillotina::getTamProblema(void) {
  return tamProblema;
}

long long PruebaGuillotina::getSumaTiempos(void) {
  return sumaTiempos;
}

double PruebaGuillotina::getMediaTiempo(void) {
  return (double)getSumaTiempos() / (double)getNumeroPruebas();
}