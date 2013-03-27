#include "Pieza.h"

Pieza::Pieza(void) {
  setAlto(0);
  setAncho(0);
}

Pieza::Pieza(int alto, int ancho, int beneficio) {
  setAlto(alto);
  setAncho(ancho);
  setBeneficio(beneficio);
}

int Pieza::getAlto(void) const {
  return alto;
}

void Pieza::setAlto(int alto_) {
  alto = alto_;
}

int Pieza::getAncho(void) const {
  return ancho;
}

void Pieza::setAncho(int ancho_) {
  ancho = ancho_;
}

int Pieza::getBeneficio(void) const {
  return beneficio;
}

void Pieza::setBeneficio(int beneficio_) {
  beneficio = beneficio_;
}

int Pieza::getSuperficie(void) {
  return getAlto() * getAncho();
}