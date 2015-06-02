#ifndef MORTALKOMBAT_CAPAINFO_H
#define MORTALKOMBAT_CAPAINFO_H

#include <string>
#include <SDL2/SDL_render.h>
#include "../VistaUtils.h"
#include <queue>

using namespace std;

class CapaInfo {
private:
    struct TeclaBuffer {
        Ttexture textura;
        Uint32 tiempoInicial;
    };

    VistaUtils* mUtils;
    Ttexture barraVidaCompletaText;
    Ttexture barraVidaParcialText;
    Ttexture mNombre1;
    Ttexture mNombre2;
    float anchoBorde, anchoRelleno,anchoPantalla, distBorde;
    Trect barraVidaCompleta1, barraVidaCompleta2, barraVidaParcialPedazo1,
            barraVidaParcialPedazo2, barraVidaParcialPantalla1, barraVidaParcialPantalla2,
            mNombre1Rect, mNombre2Rect;
    vector<Trect> rectBotones;
    queue<TeclaBuffer> buffer;


public:
    CapaInfo();
    /*
    *  Crea una capa.
    *  renderer : renderer utilizado
    *  dirPath : direccion de la imagen de la capa
    *  rectPantalla : contiene el tamaño de la pantalla y la posicion inicial de la
    *  capa en relacion a su tamaño total de la imagen
    */
    CapaInfo(VistaUtils* utils, Tdimension dimPantalla, string nombres[2]);


    /*
    *  Guarda el pedazo de la capa a mostrar en le pedazo de textura pasado por parametro.
    *  texture : puntero a una textura del tamaño de la pantalla
    */
    void getTexture(Ttexture texture);


    /*
     * Cambia la posicion de la capa ajustandola a la posicion del escenario
     */
    void update(float porcVida1,float porcVida2,Tinput input);

    void freeTextures();

    virtual ~CapaInfo();
};


#endif //MORTALKOMBAT_CAPAINFO_H
