#include <iostream>
#include <SDL2/SDL.h>
#include "vista/Pantalla.h"
#include "parser/config.h"
#include "modelo/Mundo.h"
#include "controlador/Controlador.h"
#include <time.h>

const float delay = 45.0;

int main(int argc, char **argv) {

    bool endGame = false;
    cout << "------------------------------------------------------------" << endl;
    cout << "------------------INICIO DEL JUEGO--------------------------" << endl;
    cout << "------------------------------------------------------------" << endl;

    clock_t t1, t2;
    float timeloop = 00.0;

    while (!endGame) {

        cout << "-------------- Cargando la configuracion -------------------" << endl;

        config configuracion = config(argv[1]);

        cout << "Inicia la creacion de la pantalla..." << endl;
        Tventana tventana = configuracion.getVentana();
        std::vector<Tcapa> vectorTcapa = configuracion.getCapas();
        Tescenario tescenario = configuracion.getEscenario();
        Tpersonaje tpersonaje = configuracion.getPersonaje();
        tventana.distTope = MIN_DISTANCE_FROM_BOUND;
        Pantalla pantalla = Pantalla(vectorTcapa, tventana, tescenario, tpersonaje);
        cout << "Finaliza la creacion de la pantalla" << endl;

        cout << "Inicia la creacion del mundo..." << endl;
        Mundo mundo = Mundo(configuracion);
        cout << "Finaliza la creacion del mundo" << endl;

        cout << "Inicia la creacion del controlador" << endl;
        Controlador controlador = Controlador();
        cout << "Finaliza la creacion del controlador" << endl;

        bool restart = false;
        cout << "-------------- GameLoop ----------------------------" << endl;

        while ( !restart && !endGame ) {
            //Declaracion de variables necesarias para el gameloop

            //0 PARADO
            //1 SALTAR
            //2 AGACHAR
            //3 Caminar a la derecha
            //4 Caminar a la izquierda
            //5 Salto oblicuo a la derecha
            //6 Salto oblicuo a la izquierda
            //7 Restart
            //8 Exit

            Tcambio c;
            Tinput input;

            t1 = clock();

            // INPUT
            input = controlador.getInputs();

            //SI SE DESEA SALIR DEL JUEGO
            if (input == KEY_EXIT)
                endGame = true;

            //PARA RESTABLECER EL JUEGO
            if (input == KEY_RESTART) {


                restart = true;
            }

                //DEMAS ACCIONES
            else {
                c = mundo.actualizarMundo(c, input);
                pantalla.update(c);
                pantalla.dibujar();
            }
            t2 = clock();
            timeloop = (((float)t2 - (float)t1) / 1000000.0F ) * 1000;
            SDL_Delay(delay - timeloop);
        }
    }

    cout << "------------------------------------------------------------" << endl;
    cout << "---------------------FIN DEL JUEGO--------------------------" << endl;
    cout << "------------------------------------------------------------" << endl;

    return 0;
}