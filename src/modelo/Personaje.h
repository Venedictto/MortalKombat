#ifndef PERSONAJE_H_
#define PERSONAJE_H_

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <list>
#include "math.h"
#include <tr1/unordered_map>
#include "Accion.h"
#include "../Common.h"
#include "ObjetoColisionable.h"


using namespace std;

class Personaje: public ObjetoColisionable {

public:

	bool parado;
	bool direccion;
	bool sentido;
	float yPiso;
	TestadoPersonaje estado;
	Accion* accionesEnCurso[4];

	Posicion verificarPuntoEnX(Posicion posicionActual,float anchoEscenario);
	Posicion verificarPuntoEnY(Posicion posicionActual);

	void ejecutarAcionesActivadas(Accion **accionesEnCurso,float anchoEscenario);


	Personaje(bool direccion,Posicion posInicial,float alto,float ancho);
	void realizarAccion(Tinput orden,float anchoEscenario);

	void solucionColision();
	Posicion getPosicion();
	TestadoPersonaje getEstado();
	float getAlturaPersonaje();
	float getAnchoPersonaje();
	bool getDireccion();
	bool getSentido();

	virtual ~Personaje();

};
#endif /* PERSONAJE_H_ */
