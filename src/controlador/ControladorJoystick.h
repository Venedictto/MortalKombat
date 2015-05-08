
#ifndef MORTALKOMBAT_CONTROLADORJOYSTICK_H
#define MORTALKOMBAT_CONTROLADORJOYSTICK_H

#include <SDL2/SDL_events.h>
#include <SDL2/SDL.h>
#include <vector>
#include "../Common.h"
#include <fstream>

class ControladorJoystick {

    enum Tflecha{
        FLECHA_ARRIBA=4,
        FLECHA_DERECHA,
        FLECHA_ABAJO,
        FLECHA_IZQUIERDA
    };
private:
    Tinput esAnterior(SDL_Joystick*);
    void guardarAnteriorX(SDL_Joystick* ,Tinput );
    void setInputAnteriorX(SDL_Joystick*,Tinput&  );
    Tinput inputAnteriorX(SDL_Joystick* );
    void vibrar();
    SDL_Joystick* player1 = NULL;
    SDL_Joystick* player2 = NULL;
    SDL_Haptic *haptic=NULL;
    SDL_HapticEffect effect;
    int effect_id=0;
public:
    Tinput inputAnterior1;
    Tinput inputAnterior2;
    ControladorJoystick();
    vector<Tinput> getInputs();

};


#endif //MORTALKOMBAT_CONTROLADORJOYSTICK_H