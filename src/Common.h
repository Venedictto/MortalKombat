/**
 * Estructuras que se comparten entre
 *  - Configuracion
 *  - Modelo
 *  - Vista
 *  - Controlador
 */

#ifndef _MORTALKOMBAT_COMMON_H_
#define _MORTALKOMBAT_COMMON_H_

#include <cmath>
#include <string>
#include <iostream>
#include "parser/log/WarningLog.h"
#include "parser/log/DebugLog.h"
#include "parser/log/ErrorLog.h"

/**
 * Constantes
 */
static const std::string SPRITES_FORMAT = ".png";
static const float MIN_DISTANCE_FROM_BOUND = 50;

/**
 * Estas estructuras, pseudo-clases cruzan toda
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
        return (p.x == x) && (p.x == y);
    }

    void setX(float pos_x){
        x = pos_x;
    }

    void setY(float pos_y){
        y = pos_y;
    }

    void mostrarPar(){
        std::cout << "X: " << x << " - " << "Y: " << y << std::endl;
    }

};

struct Tdimension{
    float w;
    float h;

    Tdimension(){}

    Tdimension(float w, float h){
        this->w = w;
        this->h = h;
    }

    Tdimension(int w, int h){
        this->w = w;
        this->h = h;
    }
};

struct Trect {
    Tdimension d;
    Posicion p;
};

/**
 * Estructuras para la manipulacion de
 *  los colores.
 */
struct TcolorHSL{
    float h;
    float s;
    float l;

    static TcolorHSL fromRGB(uint8_t R, uint8_t G, uint8_t B){
        TcolorHSL color;
        float r, g, b, max, min, delta, aux;

        r = (float) R / 255;
        g = (float) G / 255;
        b = (float) B / 255;

        aux = std::fmax(r, g);
        max = fmax(aux, b);

        aux = fmin(r, g);
        min = fmin(aux, g);

        delta = max - min;

        // H
        if (delta == 0){
            color.h = 0;
        } else if (max == r){
            color.h = 60 * fmod( ( ( g - b ) / delta ), 6 );
        } else if (max == g){
            color.h = 60 * (( ( b - r ) / delta ) + 2 );
        } else if (max == b){
            color.h = 60 * (( ( r - g ) / delta ) + 4 );
        }
        color.h = (color.h >= 0) ? color.h : 360 + color.h;

        // L
        color.l = (max + min) / 2;

        // S
        color.s = (delta == 0) ? 0 : delta / ( 1 - fabs(max + min - 1) );

        return color;
    }
};

struct TcolorRGB{
    uint8_t r;
    uint8_t g;
    uint8_t b;

    static TcolorRGB fromHSL(float H, float S, float L){
        TcolorRGB color;
        float c, x, m, R = 0, G = 0, B = 0;

        c = (1 - fabs(2*L - 1)) * S;
        x = c * ( 1 - fabs( fmod( (H/60), 2 ) - 1) );
        m = L - (c / 2);

        if ( (H >= 0) && (H < 60) ){
            R = c;
            G = x;
            B = 0;
        }else if ( (H >= 60) && (H < 120) ){
            R = x;
            G = c;
            B = 0;
        }else if ( (H >= 120) && (H < 180) ){
            R = 0;
            G = c;
            B = x;
        }else if ( (H >= 180) && (H < 240) ){
            R = 0;
            G = x;
            B = c;
        }else if ( (H >= 240) && (H < 300) ) {
            R = x;
            G = 0;
            B = c;
        }else if ( (H >= 300) && (H < 360) ){
            R = c;
            G = 0;
            B = x;
        }
        color.r = (uint8_t) ( 255 * (R + m) );
        color.g = (uint8_t) ( 255 * (G + m) );
        color.b = (uint8_t) ( 255 * (B + m) );

        return color;
    }
};

struct TcolorSettings{
    float hmin;
    float hmax;
    float delta;

    TcolorSettings(){}

    TcolorSettings(float min, float max, float d){
        hmin = (min < 0) ? - fmod(-min, 360) + 360 : fmod(min, 360);
        hmax = (max < 0) ? - fmod(-max, 360) + 360 : fmod(max, 360);
        delta = (d < 0) ? - fmod(-d, 360) + 360 : fmod(d, 360);
    }

};


/**
 * Loguer
 */
static Log* loguer = DebugLog::getInstance();

/**
 * Estructuras que se utilizan para
 *  definir la pantalla (px),  escenario
 *  y capa
 */
struct Tventana {
    Tdimension dimPx;
    float ancho;
    float distTope;
};

struct Tescenario {
    Tdimension d;
    float yPiso;
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
    AGACHADO,
    PINIA_ALTA,
    PINIA_BAJA,
    PATADA_ALTA,
    PATADA_BAJA,
    PODER,
    PROTECCION
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
    Tdimension d;
    int zIndex;
    Tdireccion orientacion;
    std::string sprites;

    // para el personaje alternativo
    TcolorSettings colorSettings;
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
    Tdimension dPJ;
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

    // Golpes Basicos
            KEY_PINIA_ALTA,
    KEY_PINIA_BAJA,
    KEY_PATADA_ALTA,
    KEY_PATADA_BAJA,
    KEY_PROTECCION,
    KEY_PODER,

    // Cierre o reinicio del juego
    KEY_RESTART,
    KEY_EXIT
};

#endif //_MORTALKOMBAT_COMMON_H_

