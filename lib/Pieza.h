#ifndef PIEZA_H_
#define PIEZA_H_

class Pieza {
private:
  int alto; // li
  int ancho; // wi
  int beneficio; // pi
  
public:
  Pieza(void);
  Pieza(int, int, int);
  inline int getAlto(void) const;
  inline void setAlto(int);
  inline int getAncho(void) const;
  inline void setAncho(int);
  inline int getBeneficio(void) const;
  inline void setBeneficio(int);
  inline int getSuperficie(void);
};

#endif