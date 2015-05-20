#include <functional>
#include "../parser/config.h"
#include "Mundo.h"

const float delta = 5.00;
const float deltaLejania = 80;
const float deltaCero = 0;
const float deltaParaPelea = 25.00;
const float deltaParaPoder = 5.00;

/* Constructor de Mundo.
 * Recibe la configuracion que se devuelve del parser.
 * Crea un personaje e inicializa su posicion, altura y ancho.
 * Tambien se inicializa el alto, ancho y yPiso del escenario.

 */
Mundo::Mundo(config configuracion) {
	Tescenario escenario = configuracion.getEscenario();
	vector<Tpersonaje> personajes = configuracion.getPersonajes();
	float anchoVentana = configuracion.getVentana().ancho;

	Tpersonaje PJ1 = personajes[0];
	Tpersonaje PJ2 = personajes[1];

	anchoEscenario = escenario.d.w;
	altoEscenario = escenario.d.h;
	altoPiso = escenario.yPiso;


	float pos_x1 = anchoEscenario/2 - anchoVentana/2 + MIN_DISTANCE_FROM_BOUND;
	float pos_x2 = anchoEscenario/2 + anchoVentana/2 - PJ2.d.w - MIN_DISTANCE_FROM_BOUND;
	float pos_y1 = altoEscenario - altoPiso - PJ1.d.h;
	float pos_y2 = altoEscenario - altoPiso - PJ2.d.h;

	Tdireccion direccion1 = PJ1.orientacion;
	Tdireccion direccion2 = PJ2.orientacion;

	Trect rectanguloPj1,rectanguloPj2;
	rectanguloPj1.d = PJ1.d;
	rectanguloPj2.d = PJ2.d;
	rectanguloPj1.p = {pos_x1, pos_y1};
	rectanguloPj2.p = {pos_x2,pos_y2};

	//TODO: EL PJ1 Y PJ2 EMPIEZAN EN LADOS OPUESTOS - lo dejamos asi por los controles del teclado

	personaje1 = new Personaje(PJ1.nombre,direccion1,rectanguloPj1,anchoVentana);
	//cout<<"Costado izquierdo personaje 1: "<<personaje1->rectanguloPj.p.getX() - personaje1->rectanguloPj.d.w<<endl;
	personaje2 = new Personaje(PJ2.nombre,direccion2,rectanguloPj2,anchoVentana);
	//cout<<"Costado derecho personaje 2: "<<personaje2->rectanguloPj.p.getX() + personaje2->rectanguloPj.d.w<<endl;


	colisionador = DetectorDeColisiones(anchoVentana,anchoEscenario);

	anchoPantalla = configuracion.getVentana().ancho;
}


vector<Personaje*> Mundo::getPersonajes(){
	return vector<Personaje*> {personaje1,personaje2};
};

void Mundo::verificarDireccionDeLosPersonajes() {
	//direccion derecha igual true
	if(personaje1->rectanguloPj.p.getX() < personaje2->rectanguloPj.p.getX()){
		personaje1->direccionPj = DERECHA;
		personaje2->direccionPj = IZQUIERDA;

	}
	else if(personaje1->rectanguloPj.p.getX() > personaje2->rectanguloPj.p.getX()){
		personaje1->direccionPj = IZQUIERDA;
		personaje2->direccionPj = DERECHA;
	}
}

Tcambio Mundo::actualizarPJ(Personaje *PJ) {
	Tcambio cambio;
	cambio.dPJ = PJ->rectanguloPj.d;
	cambio.posicion = PJ->rectanguloPj.p;
	cambio.direccion = PJ->direccionPj;
	cambio.sentido = PJ->sentidoPj;
	cambio.estado = PJ->estadoActual;

	cambio.vida = PJ->vida;

	cambio.poder.d = PJ->poder->rectanguloPoder.d;
	cambio.poder.p = PJ->poder->rectanguloPoder.p;
	cambio.poder.e = PJ->poder->estado;

	return cambio;
}

/* Devuelve la actualizacion del struct Tcambio recibido junto con el numero de accion que debe realizar
 * Personaje realiza su respectiva accion.
 * Se asigna todos los datos pertinentes de personaje a Tcambio.
 */
vector<Tcambio> Mundo::actualizarMundo(vector<Tinput> inputs) {
	vector<Tcambio> c;
	Tcambio cambio1, cambio2;

	//Verifica y da vuelta la direccion de los personajes si se pasan
	verificarDireccionDeLosPersonajes();

	// Los personajes realizan sus acciones
	personaje1->realizarAccion(inputs[1]);
	personaje2->realizarAccion(inputs[0]);
	// COLISIONES
	colisionador.resolverColisiones(personaje1,personaje2);

	//Se actualizan a los personajes
	cambio1 = actualizarPJ(personaje1);
	cambio2 = actualizarPJ(personaje2);

	//personaje1->rectanguloPj.p.mostrarPar();
	c.push_back(cambio1);
	c.push_back(cambio2);

	return c;
}


bool Mundo::huboGanador() {
	string mensaje;
	if(personaje1->vida == 0){
		mensaje = "Ganador: "+personaje2->nombre+" ---> Personaje 2";
		loguer->loguear(mensaje.c_str(),Log::LOG_DEB);
		return true;
	}
	if(personaje2->vida == 0){
		mensaje = "Ganador: "+personaje1->nombre+" ---> Personaje 1";
		loguer->loguear(mensaje.c_str(),Log::LOG_DEB);
		return true;
	}
	return false;
}



Mundo::~Mundo() {
	if(personaje1->vida == 0) loguer->loguear("El personaje 1 esta muerto",Log::LOG_DEB);
	else loguer->loguear("El personaje 1 sobrevivio",Log::LOG_DEB);
	if(personaje2->vida == 0) loguer->loguear("El personaje 2 esta muerto",Log::LOG_DEB);
	else loguer->loguear("El personaje 2 sobrevivio",Log::LOG_DEB);
	delete personaje1;
	delete personaje2;
	loguer->loguear("Se libero a los personajes", Log::LOG_DEB);
}

