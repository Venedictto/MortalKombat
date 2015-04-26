#ifndef MORTALKOMBAT_OBJETOCOLISIONABLE_H
#define MORTALKOMBAT_OBJETOCOLISIONABLE_H

#include "Personaje.h"
#include "../Common.h"

class ObjetoColisionable {
public:

    Posicion pos;
    float altura;
    float ancho;

    virtual void solucionColision() = 0;
    virtual ~ObjetoColisionable() {}

};


#endif //MORTALKOMBAT_OBJETOCOLISIONABLE_H



