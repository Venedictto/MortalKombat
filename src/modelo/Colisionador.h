#ifndef MORTALKOMBAT_COLISIONADOR_H
#define MORTALKOMBAT_COLISIONADOR_H

#include "Personaje.h"
#include "Golpe.h"
#include "Poder.h"
#include "../Common.h"
#include "ObjetoColisionable.h"
#include <vector>

using namespace std;

class Colisionador {

public:
    float anchoEsc;

    Colisionador();
    void setEscenario(float ancho);
    vector<ObjetoColisionable*> detectorDeProximidad(vector<ObjetoColisionable*> objetos, float delta );
    bool sonProximos(ObjetoColisionable* primerObjeto,ObjetoColisionable* segundoObjeto,float delta);
    bool seVan(Personaje* PJ1, Personaje* PJ2, float delta );
    void solucionarColision(Personaje* PJ1, Personaje* PJ2);
    void solucionarColision(Personaje* PJ,Golpe* golpeOponente);
    void solucionarColision(Personaje* PJ, Poder* poderOponente);

    float distanciaColisionadaenX(ObjetoColisionable *objeto1, ObjetoColisionable *objeto2);

    bool seProdujoColision(ObjetoColisionable* rectangulo1, ObjetoColisionable* rectangulo2);
    virtual ~Colisionador();

    bool detectarLejania(Personaje *PJ1, Personaje *PJ2, float delta);
};


#endif //MORTALKOMBAT_COLISIONADOR_H