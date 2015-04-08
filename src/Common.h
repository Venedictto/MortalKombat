/**
 * Estructuras que se comparten entre
 *  - Configuracion
 *  - Modelo
 *  - Vista
 *  - Controlador
 */

#ifndef _MORTALKOMBAT_COMMON_H_
#define _MORTALKOMBAT_COMMON_H_

#include <string>
#include <iostream>

/**
 * Esta estructura, pseudo-clase cruza toda
 *  la aplicacion.
 */
struct Posicion{
    float x;
    float y;

    Posicion(float pos_x,float pos_y) {
        x = pos_x;
        y = pos_y;
    }

    float getX(){
        return x;
    }

    float getY(){
        return y;
    }

    Posicion(){
        x = 0;
        y = 0;
    }

    Posicion operator=(Posicion p){
        x = p.x;
        y = p.y;
        return p;
    }
    Posicion operator+(Posicion p){
        return Posicion(x + p.x, y + p.y);
    }
    Posicion operator-(Posicion p){
        return Posicion(x - p.x, y - p.y);
    }
    bool operator==(Posicion p){
        if ( (p.x == x) && (p.x == y) )
            return true;
        return false;
    }

    void setX(float pos_x){
        x = pos_x;
    }

    void setY(float pos_y){
        y = pos_y;
    }

    void mostrarPar(){
        std::cout << "ESTA ES LA POSICION" << std::endl;
        std::cout << "X: " << x << " - " << "Y: " << y << std::endl;
    }

};

/**
 * Estructuras que se utilizan para
 *  definir la pantalla (px) y el
 *  escenario
 */
struct Tventana {
    int altopx;
    int anchopx;
    float ancho;
};

struct Tescenario {
    float ancho;
    float alto;
    int yPiso;
};

struct Tcapa {
    std::string dirCapa;
    float ancho;
};


/**
 * Estructuras y enums propios de los
 *  Personajes
 */
enum TestadoPersonaje {
    PARADO,
    CAMINANDO,
    SALTANDO_VERTICAL,
    SALTANDO_OBLICUO,
    AGACHADO
};

static std::string TestadoPersonajeToString(TestadoPersonaje e) {
    switch (e) {
        case TestadoPersonaje::PARADO: return "parado";
        case TestadoPersonaje::CAMINANDO: return "caminando";
        case TestadoPersonaje::SALTANDO_VERTICAL: return "salto_vertical";
        case TestadoPersonaje::SALTANDO_OBLICUO: return "salto_oblicuo";
        case TestadoPersonaje::AGACHADO: return "agachado";
    }
    return NULL;
}

static const int TestadoPersonajeCount = 5;

enum Tdireccion{
    DERECHA,
    IZQUIERDA
};

enum Tsentido{
    ADELANTE,
    ATRAS
};

struct Tpersonaje {
    float ancho;
    float alto;
    int zIndex;
    Tdireccion orientacion;
};


/**
 * Estructura que media entre el modelo y
 *  la vista y tiene como finalidad contener
 *  todos los cambios que se produjeron a lo
 *  largo de un gameloop.
 */
struct Tcambio{
    Posicion posicion;
    TestadoPersonaje estado;
    Tdireccion direccion;
    Tsentido sentido;
};

/**
 * Enum con todos los posibles inputs que el
 *  juego debe ser capaz de manejar.
 */
enum Tinput{
    // Teclas no utilizadas
    KEY_NADA,

    // Movimientos Basicos
    KEY_ARRIBA,
    KEY_ABAJO,
    KEY_DERECHA,
    KEY_IZQUIERDA,
    KEY_ARRIBA_DERECHA,
    KEY_ARRIBA_IZQUIERDA,

    // Cierre o reinicio del juego
    KEY_RESTART,
    KEY_EXIT
};

/**
 * Se define esta constante por si se llega a
 *  necesitar cambiar la extension de las imagenes
 *  que se utilizan para los sprites.
 * TODO - Revisar si vale la pena mantener esta constante
 */
static const std::string SPRITES_FORMAT = ".png";

#endif //_MORTALKOMBAT_COMMON_H_
