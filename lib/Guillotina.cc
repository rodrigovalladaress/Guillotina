#include "Guillotina.h"

Guillotina::Guillotina(int altoLamina, int anchoLamina) {
  setAltoLamina(altoLamina);
  setAnchoLamina(anchoLamina);
  inicializarMatrizResultado();
  setProfundidadMaxima(0);
}

Guillotina::Guillotina(int altoLamina, int anchoLamina, const vector<Pieza>& vectorPiezas) {
  setAltoLamina(altoLamina);
  setAnchoLamina(anchoLamina);
  setVectorPiezas(vectorPiezas);
  inicializarMatrizResultado();
  setProfundidadMaxima(0);
}

Guillotina::Guillotina(int altoLamina, int anchoLamina, int numeroPiezas, int* longPiezas,
	   int* anchoPiezas, int* benefPiezas) {
  setAltoLamina(altoLamina);
  setAnchoLamina(anchoLamina);
  for(int i = 0; i < numeroPiezas; i++) {
    Pieza piezaAux(longPiezas[i], anchoPiezas[i], benefPiezas[i]);
    addPieza(piezaAux);
  }
  inicializarMatrizResultado();
  setProfundidadMaxima(0);
}

void Guillotina::calcularMatriz(void) {
  int altoLamina = getAltoLamina();
  int anchoLamina = getAnchoLamina();
  int auxMax;
  vector <Pieza> piezasSolucion;
  for(int i = 0; i <= anchoLamina; i++) {
    for(int j = 0; j <= altoLamina; j++) {
      auxMax = piezaMaxBeneficio(i, j); // H(x, y)
      //piezasSolucion.push_back(
      for(int x0 = 0; x0 <= i / 2; x0++) { // x0 <= x / 2
	auxMax = max(auxMax, 
		     getMatrizResultado(x0, j) + // G(x0, y) + G(x - x0, y)
	             getMatrizResultado(i - x0, j));
      }
      for(int y0 = 0; y0 <= j / 2; y0++) { // y0 <= y / 2
	auxMax = max(auxMax,
		     getMatrizResultado(i, y0) + // G(x, y0) + G(x, y- y0)
		     getMatrizResultado(i, j - y0));
      }
      setMatrizResultado(i, j, auxMax);
    }
  }
}

void Guillotina::calcularResultado(void) {
  setConjuntoCortes(calcularResultadoSuperficial(getAnchoLamina(), getAltoLamina(), 0));
}

vector < vector <int> > Guillotina::calcularResultadoSuperficial(int x, int y, int prof) {
  vector < vector <int> > solucionParcial;
  actualizarProfundidadMaxima(prof);
  if((x >= 0) && (y >= 0) && (getMatrizResultado(x, y) != 0)) {
    vector < vector <int> > solucionPrimerSumando;
    vector < vector <int> > solucionSegundoSumando;
    vector<int> solucionAdicional;
    int celdaxy = getMatrizResultado(x, y);
    int numeroPiezas = getNumeroPiezas();
    if(celdaxy == piezaMaxBeneficio(x, y)) {
      for(int i = 0; i < numeroPiezas; i++) { // Añadir todas las piezas 
        if((getPieza(i).getAlto() <= x) && (getPieza(i).getAncho() <= y) && 
           (getPieza(i).getBeneficio() == celdaxy)) {
	  solucionAdicional.clear();
          solucionAdicional.push_back(i);
	  solucionParcial.push_back(solucionAdicional);
	  return solucionParcial;
        }
      }
    }
    
    for(int x0 = 1; x0 <= x / 2; x0++) {
      if((celdaxy == getMatrizResultado(x0, y) + getMatrizResultado(x - x0, y))) {
        solucionAdicional.clear();
        solucionPrimerSumando = calcularResultadoSuperficial(x0, y, prof + 1);
	solucionSegundoSumando = calcularResultadoSuperficial(x - x0, y, prof + 1);
        if((solucionPrimerSumando.size() > 0) && (solucionSegundoSumando.size() > 0)) {
          for(unsigned k = 0; k < solucionPrimerSumando.size(); k++) {
	    for(unsigned l = 0; l < solucionSegundoSumando.size(); l++) {
	      solucionAdicional = solucionPrimerSumando[k];
	      for(unsigned m = 0; m < solucionSegundoSumando[l].size(); m++) {
	        solucionAdicional.push_back(solucionSegundoSumando[l][m]);
	      }
	      solucionParcial.push_back(solucionAdicional); // Combinar las soluciones de los dos sumandos
	      return solucionParcial;
	    }
          }
        }
        else if((solucionPrimerSumando.size() > 0) && (solucionSegundoSumando.size() == 0)) {
	  for(unsigned k = 0; k < solucionPrimerSumando.size(); k++) {
	    solucionParcial.push_back(solucionPrimerSumando[k]);
	    return solucionParcial;
	  }
        }
        else if((solucionPrimerSumando.size() == 0) && (solucionSegundoSumando.size() > 0)) {
  	  for(unsigned k = 0; k < solucionSegundoSumando.size(); k++) {
	    solucionParcial.push_back(solucionSegundoSumando[k]);
	    return solucionParcial;
	  }
        }
      }
    }
    for(int y0 = 1; y0 <= y / 2; y0++) {
      if((celdaxy == getMatrizResultado(x, y0) + getMatrizResultado(x, y - y0))) {
        solucionAdicional.clear();
        solucionPrimerSumando = calcularResultadoSuperficial(x, y0, prof + 1);
	solucionSegundoSumando = calcularResultadoSuperficial(x, y - y0, prof + 1);
        if((solucionPrimerSumando.size() > 0) && (solucionSegundoSumando.size() > 0)) {
          for(unsigned k = 0; k < solucionPrimerSumando.size(); k++) {
	    for(unsigned l = 0; l < solucionSegundoSumando.size(); l++) {
	      solucionAdicional = solucionPrimerSumando[k];
	      for(unsigned m = 0; m < solucionSegundoSumando[l].size(); m++) {
	        solucionAdicional.push_back(solucionSegundoSumando[l][m]);
	      }
	      solucionParcial.push_back(solucionAdicional); // Combinar las soluciones de los dos sumandos
	      return solucionParcial;
	    }
          }
        }
        else if((solucionPrimerSumando.size() > 0) && (solucionSegundoSumando.size() == 0)) {
	  for(unsigned k = 0; k < solucionPrimerSumando.size(); k++) {
	    solucionParcial.push_back(solucionPrimerSumando[k]);
	    return solucionParcial;
	  }
        }
        else if((solucionPrimerSumando.size() == 0) && (solucionSegundoSumando.size() > 0)) {
	  for(unsigned k = 0; k < solucionSegundoSumando.size(); k++) {
	    solucionParcial.push_back(solucionSegundoSumando[k]);
	    return solucionParcial;
	  }
        }
      }
    }
  }
  return solucionParcial;
}

vector < vector <int> > Guillotina::calcularResultado(int x, int y, int prof) {
  
  cout << x << " " << y << endl;
  
  vector < vector <int> > solucionParcial;
  actualizarProfundidadMaxima(prof);
  if((x >= 0) && (y >= 0) && (getMatrizResultado(x, y) != 0)) {
    vector < vector <int> > solucionPrimerSumando;
    vector < vector <int> > solucionSegundoSumando;
    vector<int> solucionAdicional;
    int celdaxy = getMatrizResultado(x, y);
    int numeroPiezas = getNumeroPiezas();
    if(celdaxy == piezaMaxBeneficio(x, y)) {
      for(int i = 0; i < numeroPiezas; i++) { // Añadir todas las piezas 
        if((getPieza(i).getAlto() <= x) && (getPieza(i).getAncho() <= y) && 
           (getPieza(i).getBeneficio() == celdaxy)) {
	  solucionAdicional.clear();
          solucionAdicional.push_back(i);
	  solucionParcial.push_back(solucionAdicional);
        }
      }
    }
    
    for(int x0 = 0; x0 <= x / 2; x0++) {
      if((celdaxy == getMatrizResultado(x0, y) + getMatrizResultado(x - x0, y))) {
        solucionAdicional.clear();
        solucionPrimerSumando = calcularResultado(x0, y, prof + 1);
	if(x0 != 0)
	  solucionSegundoSumando = calcularResultado(x - x0, y, prof + 1);
	else {
	  solucionSegundoSumando.clear();
	}
        if((solucionPrimerSumando.size() > 0) && (solucionSegundoSumando.size() > 0)) {
          for(unsigned k = 0; k < solucionPrimerSumando.size(); k++) {
	    for(unsigned l = 0; l < solucionSegundoSumando.size(); l++) {
	      solucionAdicional = solucionPrimerSumando[k];
	      for(unsigned m = 0; m < solucionSegundoSumando[l].size(); m++) {
	        solucionAdicional.push_back(solucionSegundoSumando[l][m]);
	      }
	      solucionParcial.push_back(solucionAdicional); // Combinar las soluciones de los dos sumandos
	    }
          }
        }
        else if((solucionPrimerSumando.size() > 0) && (solucionSegundoSumando.size() == 0)) {
	  for(unsigned k = 0; k < solucionPrimerSumando.size(); k++)
	    solucionParcial.push_back(solucionPrimerSumando[k]);
        }
        else if((solucionPrimerSumando.size() == 0) && (solucionSegundoSumando.size() > 0)) {
  	  for(unsigned k = 0; k < solucionSegundoSumando.size(); k++)
	    solucionParcial.push_back(solucionSegundoSumando[k]);
        }
      }
    }
    for(int y0 = 0; y0 <= y / 2; y0++) {
      if((celdaxy == getMatrizResultado(x, y0) + getMatrizResultado(x, y - y0))) {
        solucionAdicional.clear();
        solucionPrimerSumando = calcularResultado(x, y0, prof + 1);
	if(y0 != 0)
          solucionSegundoSumando = calcularResultado(x, y - y0, prof + 1);
	else {
	  solucionSegundoSumando.clear();
	}
        if((solucionPrimerSumando.size() > 0) && (solucionSegundoSumando.size() > 0)) {
          for(unsigned k = 0; k < solucionPrimerSumando.size(); k++) {
	    for(unsigned l = 0; l < solucionSegundoSumando.size(); l++) {
	      solucionAdicional = solucionPrimerSumando[k];
	      for(unsigned m = 0; m < solucionSegundoSumando[l].size(); m++) {
	        solucionAdicional.push_back(solucionSegundoSumando[l][m]);
	      }
	      solucionParcial.push_back(solucionAdicional); // Combinar las soluciones de los dos sumandos
	    }
          }
        }
        else if((solucionPrimerSumando.size() > 0) && (solucionSegundoSumando.size() == 0)) {
	  for(unsigned k = 0; k < solucionPrimerSumando.size(); k++)
	    solucionParcial.push_back(solucionPrimerSumando[k]);
        }
        else if((solucionPrimerSumando.size() == 0) && (solucionSegundoSumando.size() > 0)) {
	  for(unsigned k = 0; k < solucionSegundoSumando.size(); k++)
	    solucionParcial.push_back(solucionSegundoSumando[k]);
        }
      }
    }
  }
  return solucionParcial;
}

void Guillotina::imprimirMatriz(void) {
  int altoLamina = getAltoLamina();
  int anchoLamina = getAnchoLamina();
  for(int i = 0; i <= anchoLamina; i++) {
    for(int j = 0; j <= altoLamina; j++) {
      cout << getMatrizResultado(i, j) << " ";
    }
    cout << endl;
  }
}

void Guillotina::imprimirPiezas(void) {
  cout << "  \tl\tw\tp" << endl;
  for(int i = 0; i < getNumeroPiezas(); i++) {
    cout << "z" << i << "\t" << getPieza(i).getAlto() << "\t";
    cout << getPieza(i).getAncho() << "\t";
    cout << getPieza(i).getBeneficio() << endl;
  }
}

void Guillotina::imprimirCortes(void) {
  vector<int> vectorAux;
  for(int i = 0; i < getNumeroSoluciones(); i++) {
    vectorAux = getConjuntoCortes(i);
    cout << "Sol" << i + 1 << " = (";
    for(unsigned j = 0; j < vectorAux.size(); j++) {
      cout << "z" << vectorAux[j];
      if(j != vectorAux.size() - 1)
	cout << ", ";
    }
    cout << ")" << endl;
  }
}

void Guillotina::imprimirCortesGraf(void) {
  int anchoLam = getAnchoLamina();
  //int altoLam = getAltoLamina();
  //int superficieSobrante = getAnchoLamina() * getAltoLamina();
  unsigned j;
  int anchoOcupado;
  vector<int> vectorAux;
  vector<int> piezasAImprimir;
  for(int i = 0; i < getNumeroSoluciones(); i++) {
    j = 0;
    anchoOcupado = 0;
    vectorAux = getConjuntoCortes(i);
    cout << "Sol" << i + 1 << " {" << endl;
    imprimirParteSuperiorLamina();
    while(j < vectorAux.size()) {
      piezasAImprimir.clear();
      anchoOcupado = 0;
      while((j < vectorAux.size()) && (anchoOcupado < anchoLam)) { // Se intentan colocar a lo ancho
        piezasAImprimir.push_back(vectorAux[j]);
        anchoOcupado += getPieza(vectorAux[j]).getAncho();
        j++;
      }
      if(anchoOcupado > anchoLam) { // Si se ha sobrepasado el ancho
        piezasAImprimir.pop_back();
        anchoOcupado -= getPieza(vectorAux[j]).getAncho();
        j--;
      }
      imprimirPiezaGraf(piezasAImprimir);
      if(j != vectorAux.size())
        cout << endl;
    }
    imprimirParteInferiorLamina();
    cout << "}" << endl;
    cout << endl;
  }
}

void Guillotina::imprimirParteSuperiorLamina(void) {
  if(getAnchoLamina() > 1) {
    cout << "┌";
    for(int i = 0; i < ZOOM - 1; i++)
      cout << "─";
    for(int i = 0; i < getAnchoLamina() - ZOOM; i++)
      for(int j = 0; j < ZOOM; j++) 
	cout << "─";
    for(int i = 0; i < ZOOM - 1; i++)
      cout << "─";
    cout << "┐" << endl;
  }
  else
    cout << "┌┐" << endl;
}

void Guillotina::imprimirParteInferiorLamina(void) {
  if(getAnchoLamina() > 1) {
    cout << "└";
    for(int i = 0; i < ZOOM - 1; i++)
      cout << "─";
    for(int i = 0; i < getAnchoLamina() - ZOOM; i++)
      for(int j = 0; j < ZOOM; j++) 
	cout << "─";
    for(int i = 0; i < ZOOM - 1; i++)
      cout << "─";
    cout << "┘" << endl;
  }
  else
    cout << "└┘" << endl;
}

void Guillotina::imprimirPiezaGraf(const vector<int>& piezasAImprimir) {
  int maxLongitud = 0;
  int anchoTotal = 0;
  int anchoImpreso;
  //vector <int> altoImpresoPiezas; // Altura de cada pieza que se ha imprimido
  for(unsigned i = 0; i < piezasAImprimir.size(); i++) {
    maxLongitud = max(maxLongitud, getPieza(piezasAImprimir[i]).getAlto());
    anchoTotal += getPieza(piezasAImprimir[i]).getAncho();
    //altoImpresoPiezas.push_back(0);
  }
  //for(int i = 0; i < anchoTotal; i++) { // i = ancho impreso
    for(int j = 1; j < maxLongitud; j++) { // j =  altura impresa
      cout << "│";
      for(unsigned k = 0; k < piezasAImprimir.size(); k++) { // k = pieza actual
	anchoImpreso = 0;
        for(int l = 0; l <= getPieza(piezasAImprimir[k]).getAncho() - 2; l++) {
	  // Si la altura actual es la misma que la de la pieza
	  if((j < getPieza(piezasAImprimir[k]).getAlto() - 1)) {
	    imprimirEspacioHorizontal();
	    anchoImpreso += 1;
	  }
	  else {
	    imprimirUnidadHorizontal();
	  }
	  
	}
	cout << "│";
      }
      if(anchoImpreso < anchoTotal - 2) { // Si sobra ancho de lámina al cortar
        for(int l = 0; l < anchoTotal - anchoImpreso - 2; l++) {
	  imprimirEspacioHorizontal();
	 
        }
        cout << "│";
      }
      cout << endl;
    }
  //}
  /*while((j < vectorAux.size()) && 
          (vectorAux[j].getSuperficie() != superficieSobrante)) {
      cout << "│";
      if(vectorAux[j].getAncho() <= anchoLam - j) {
        for(int k = 0; k < vectorAux[j].getAncho() - 1; k++) {
	cout << " ";
      }
    }
  }*/
}

void Guillotina::imprimirUnidadHorizontal(void) {
  for(int i = 0; i < ZOOM; i++)
      cout << "─";
}

void Guillotina::imprimirEspacioHorizontal(void) {
  for(int i = 0; i < ZOOM; i++)
      cout << " ";
}

void Guillotina::imprimirEstadisticas(void) {
  cout << "Profundidad = " << getProfundidadMaxima() << endl;
}

int Guillotina::piezaMaxBeneficio(int x, int y) {
  int maximo = 0;
  int numeroPiezas = getNumeroPiezas();
  for(int i = 0; i < numeroPiezas; i++) {
    if((getPieza(i).getAlto() <= x) && (getPieza(i).getAncho() <= y)) {
      maximo = max(maximo, getPieza(i).getBeneficio());
    }
  }
  return maximo;
}


int Guillotina::getNumeroPiezas(void) {
  return vectorPiezas.size();
}

void Guillotina::inicializarMatrizResultado(void) {
  int altoLamina = getAltoLamina() + 1;
  int anchoLamina = getAnchoLamina() + 1;
  vector<int> vectorAux;
  for(int i = 0; i < altoLamina; i++)
    vectorAux.push_back(0);
  for(int i = 0; i < anchoLamina; i++)
    matrizResultado.push_back(vectorAux);
}

const int& Guillotina::getAltoLamina(void) {
  return altoLamina;
}

void Guillotina::setAltoLamina(const int& altoLamina_) {
  altoLamina = altoLamina_;
}

const int& Guillotina::getAnchoLamina(void) {
  return anchoLamina;
}

void Guillotina::setAnchoLamina(const int& anchoLamina_) {
  anchoLamina = anchoLamina_;
}

int Guillotina::getProfundidadMaxima(void) {
  return profundidadMaxima;
}

void Guillotina::actualizarProfundidadMaxima(int profundidad) {
  setProfundidadMaxima(max(getProfundidadMaxima(), profundidad));
}

void Guillotina::setProfundidadMaxima(int profundidad) {
  profundidadMaxima = profundidad;
}

int Guillotina::getMatrizResultado(int i, int j) {
  if((i >= 0) && (j >= 0))
    return matrizResultado[i][j];
  else
    return 0;
}

void Guillotina::setMatrizResultado(int i, int j, int valor) {
  matrizResultado[i][j] = valor;
}

const vector<int>& Guillotina::getConjuntoCortes(int i) {
  return conjuntoCortes[i];
}

int Guillotina::getNumeroSoluciones(void) {
  return conjuntoCortes.size();
}

void Guillotina::setConjuntoCortes(const vector < vector <int> >& conjuntoCortes_) {
  conjuntoCortes = conjuntoCortes_;
}

void Guillotina::setVectorPiezas(const vector <Pieza>& vectorPiezas_) {
  vectorPiezas = vectorPiezas_;
}

void Guillotina::addPieza(const Pieza& pieza) {
  vectorPiezas.push_back(pieza);
}

const Pieza& Guillotina::getPieza(int i) {
  return vectorPiezas[i];
}