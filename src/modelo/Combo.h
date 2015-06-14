

#ifndef MORTALKOMBAT_COMBO_H
#define MORTALKOMBAT_COMBO_H

#include "../utils/Common.h"

class Combo {

private:
    TComboData datosDelCombo;
    int ocurrencias;
    int errores;
    unsigned int tiempoInicial;
    unsigned int tiempoFinal;

    void inicializarCombo();
    bool teclaPresionada(Tinput input);

    void teclasAString();

public:
    Combo(TComboData datosDelCombo);
    void actualizar(Tinput input);
    bool puedoRealizarCombo();

    string cadenaParaBuffer;
};


#endif //MORTALKOMBAT_COMBO_H
