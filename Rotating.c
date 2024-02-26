#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>


/*
    -Lo mejor es primero escalar, luego rotar y por ultimo trasladar 
    (Rscalar y rotar lo hacen seguin su posiciòn y no la figura en sì)
    -Para màs comodidad que todas las imagenes sean cuadradas y del mismo tamaño 
    (Ayuda al momento de escalar)
    !!!Cuando compila se ocupa poner al final -lm para que añada math.h!!!!
*/


/**
 * Estructura para almacenar las coordenadas de manera mas sencilla
 */
 struct coordenadas{
    long double  coordenada_x;
    long double coordenada_y;
};


/**
 * Estructura para almacenar los datos de manera mas sencilla
 */
struct imagen{
    struct coordenadas* coordenadas;
    struct escala* escalar;
    struct rotacion* rotar;
};
 
struct escala{
    struct coordenadas* arriba_izq;
    struct coordenadas* arriba_der;
    struct coordenadas* abajo_izq;
    struct coordenadas* abajo_der;

 };

struct rotacion{
    struct coordenadas* arriba_izq;
    struct coordenadas* arriba_der;
    struct coordenadas* abajo_izq;
    struct coordenadas* abajo_der;

 };

/**
 * Funcion que genera un numero aleatorio dentro de un rango, primero lo escoge dentro de 0 y 1 y luego lo escala al rango 
 */

double aleatorio(double min, double max){
    return min+((float)rand()/RAND_MAX)*(max-min);
}



/**
 * Funcion para escalar las 4 esquinas de la imagen suponiendo que el centro de la imagen sea el punto 0,0
 * Primero consigue las coordenadas de las 4 esquinas de la imagen original 
 * Luego saca el factor escalar
 * Y por ultimo almacena la multiplicacion del factor escalar por las esquinas.
*/
struct imagen* escalar(int ancho_imagen, struct imagen *imagen, double escala){
   
    imagen->escalar->arriba_izq->coordenada_x=(-ancho_imagen/2)*escala;
    imagen->escalar->arriba_izq->coordenada_y=(ancho_imagen/2)*escala;

    imagen->escalar->arriba_der->coordenada_x=(ancho_imagen/2)*escala;
    imagen->escalar->arriba_der->coordenada_y=(ancho_imagen/2)*escala;

    imagen->escalar->abajo_izq->coordenada_x=(-ancho_imagen/2)*escala;
    imagen->escalar->abajo_izq->coordenada_y=(-ancho_imagen/2)*escala;

    imagen->escalar->abajo_der->coordenada_x=(ancho_imagen/2)*escala;
    imagen->escalar->abajo_der->coordenada_y=(-ancho_imagen/2)*escala;

    return imagen; 

}


/**
*Funcion para rotar una imagen de la posicion desde donde se encuentre siguiendo el metodo de matriz de rotacion
*Rotar(P,Grado)=(x*cos(grado)-y*sin(grado), x*sin(grado)+y*sin(grado))
*Se utiliza en los puntos que corresponden a las esquinas de la imagen 
*En escalar estan las direcciones de las esquinas ya escaladas, por eso primero se debe escalar la imagen
*/

struct imagen* rotar(struct imagen *imagen, double grado){
    //Punto de arriba a la izquierda
    imagen->rotar->arriba_izq->coordenada_x=(imagen->escalar->arriba_izq->coordenada_x*cos(grado)-imagen->escalar->arriba_izq->coordenada_y*sin(grado));
    imagen->rotar->arriba_izq->coordenada_y=(imagen->escalar->arriba_izq->coordenada_x*sin(grado)+imagen->escalar->arriba_izq->coordenada_y*cos(grado));
    
    //Punto de arriba a la derecha
    imagen->rotar->arriba_der->coordenada_x=(imagen->escalar->arriba_der->coordenada_x*cos(grado)-imagen->escalar->arriba_der->coordenada_y*sin(grado));
    imagen->rotar->arriba_der->coordenada_y=(imagen->escalar->arriba_der->coordenada_x*sin(grado)+imagen->escalar->arriba_der->coordenada_y*cos(grado));

    //Punto de abajo a la derecha
    imagen->rotar->abajo_der->coordenada_x=(imagen->escalar->abajo_der->coordenada_x*cos(grado)-imagen->escalar->abajo_der->coordenada_y*sin(grado));
    imagen->rotar->abajo_der->coordenada_y=(imagen->escalar->abajo_der->coordenada_x*sin(grado)+imagen->escalar->abajo_der->coordenada_y*cos(grado));

    //Punto de abajo a la izquierda
    imagen->rotar->abajo_izq->coordenada_x=(imagen->escalar->abajo_izq->coordenada_x*cos(grado)-imagen->escalar->abajo_izq->coordenada_y*sin(grado));
    imagen->rotar->abajo_izq->coordenada_y=(imagen->escalar->abajo_izq->coordenada_x*sin(grado)+imagen->escalar->abajo_izq->coordenada_y*cos(grado));
    return imagen;
}



/**
*Funcion para mover una imagen que recibe como parametros la imagen y un vector direcciòn, 
*(x,Y), representado como direccion_x y direccion_y.
*Devuelve las nuevas coordenas del punto para la imagen. 
*/
struct imagen* trasladar(struct imagen *imagen, double direccion_x, double direccion_y){
    
    imagen->coordenadas->coordenada_x+=direccion_x;
    imagen->coordenadas->coordenada_y+=direccion_y;

    imagen->escalar->arriba_izq->coordenada_x+=direccion_x;
    imagen->escalar->arriba_izq->coordenada_y+=direccion_y;

    imagen->escalar->arriba_der->coordenada_x+=direccion_x;
    imagen->escalar->arriba_der->coordenada_y+=direccion_y;

    imagen->escalar->abajo_izq->coordenada_x+=direccion_x;
    imagen->escalar->abajo_izq->coordenada_y+=direccion_y;

    imagen->escalar->abajo_der->coordenada_x+=direccion_x;
    imagen->escalar->abajo_der->coordenada_y+=direccion_y;
    
    return imagen; 
}

void rotating_caliper(){

}



int main(){
    srand(time(NULL)); //Semilla para inicializar el random
    struct imagen *prueba =calloc(1, sizeof(struct imagen));
    prueba->coordenadas->coordenada_x=0;
    prueba->coordenadas->coordenada_y=0;

    prueba->escalar->abajo_der->coordenada_x=0;
    prueba->escalar->abajo_der->coordenada_y=0;

    prueba->escalar->abajo_izq->coordenada_x=0;
    prueba->escalar->abajo_izq->coordenada_y=0;

    prueba->escalar->arriba_der->coordenada_x=0;
    prueba->escalar->arriba_der->coordenada_y=0;

    prueba->escalar->arriba_izq->coordenada_x=0;
    prueba->escalar->arriba_izq->coordenada_y=0;

    prueba->rotar->abajo_der->coordenada_x=0;
    prueba->rotar->abajo_der->coordenada_y=0;

    prueba->rotar->abajo_izq->coordenada_x=0;
    prueba->rotar->abajo_izq->coordenada_y=0;

    prueba->rotar->arriba_der->coordenada_x=0;
    prueba->rotar->arriba_der->coordenada_y=0;

    prueba->rotar->arriba_izq->coordenada_x=0;
    prueba->rotar->arriba_izq->coordenada_y=0;
}

/*
Cosas por hacer: 
-El rotating caliper ( minima area rectangulo) e implementarlo
-Donde se va a tener la informaciòn de la posicion de todas las cartas y sus puntos para el rotating
-Poner las primeras 3 imagenes lo mas cerca posible del origen
-Que la salida sea un script con los datos
-Extraer los megadatos de la base
-Calcular que abarque el 75% de la carta
-Girar la carta entre 0 y 359 grados. (Creo que se puede hacer usando un for con el rotar actual)

*/