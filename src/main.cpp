#include <iostream>
#include "parser/config.h"
#include "controlador/ControladorTeclado.h"
#include "Game.h"


const int frameRate = 45;

int main(int argc, char **argv) {

    loguer->borrar();

    string jsonPath = (argv[1] == nullptr) ? string("") : argv[1];

    loguer->loguear("------------------INICIANDO MORTAL KOMBAT--------------------------", Log::LOG_DEB);

    bool endGame = false;
    while (!endGame) {

        loguer->loguear("-------------- Cargando la configuracion -------------------", Log::LOG_DEB);
        loguer->loguear("Inicia la creacion del controlador", Log::LOG_DEB);

        config* configuracion = new config(jsonPath);

        //TODO: Modificar los dos controladores para que devuelvan los nuevos inputs del struct Tinput
        ControladorTeclado controlador = ControladorTeclado();
        //ControladorJoystick controlador = ControladorJoystick(configuracion.getBotones());

        loguer->loguear("Finaliza la creacion del controlador", Log::LOG_DEB);
        loguer->loguear("-------------- Iniciando el Juego -------------------", Log::LOG_DEB);

        Game game = Game(configuracion, frameRate);
        bool restart = false;
        do {
            vector<Tinput> inputs = controlador.getInputs();
            if(inputs[0].game == TinputGame::KEY_NADA) {
                inputs[0].tiempo = SDL_GetTicks();
                inputs[1].tiempo = SDL_GetTicks();
            }
            switch (inputs.at(0).game) {
                case TinputGame::KEY_EXIT:
                    endGame = true;
                    break;
                case TinputGame::KEY_RESTART:
                    restart = true;
                    break;
                default:
                    game.play(inputs);
            }
        } while (!restart && !endGame);

    }

    loguer->loguear("---------------------FIN DEL JUEGO--------------------------", Log::LOG_DEB);

    return 0;
}
