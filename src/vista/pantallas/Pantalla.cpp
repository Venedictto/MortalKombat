#include <SDL2/SDL_image.h>
#include "Pantalla.h"

/**
 * Crea los objectos referentes a SDL:
 * - Window
 * - Renderer
 * - VistaUtils
 *
 * d    Dimensiones en pixeles
 */
Pantalla::Pantalla(Tdimension dimPixels, Tdimension dimUl) {

    mWindow = SDL_CreateWindow("MortalKombat", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, (int) dimPixels.w, (int) dimPixels.h, SDL_WINDOW_SHOWN);
    if (mWindow == NULL){
        loguer->loguear("Error al crear la ventana.", Log::LOG_ERR);
        loguer->loguear(SDL_GetError(), Log::LOG_ERR);
        throw new exception();
    }

    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);
    if (mRenderer == NULL){
        loguer->loguear("Error al crear el renderer.", Log::LOG_ERR);
        loguer->loguear(SDL_GetError(), Log::LOG_ERR);
        throw new exception();
    }

    mDimension = dimUl;
    float scales[2] = {dimPixels.w / mDimension.w, dimPixels.h / mDimension.h};
    mUtils = new VistaUtils(mRenderer, mDimension.w / mDimension.h, scales);
}

vector<float> Pantalla::getEscalas(){
    return mUtils->getEscala();
}

void Pantalla::update(vector<Tcambio> changes,Tinput input) {}
void Pantalla::update(EmodeSelection selection) {}
void Pantalla::initialize(vector<Tcapa> capas, string personajes[2]){}
vector<Trect> Pantalla::getCuadradoModos() {
    return std::vector<Trect>();
}

Pantalla::~Pantalla(){
    loguer->loguear("Destruccion de la pantalla", Log::LOG_DEB);
    mUtils->freeTextures();
    delete (mUtils);
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
}