#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
const double PI = 3.14159265358979323846;


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
    double lado;
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
    double grado;
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
   
    imagen->escalar->arriba_izq->coordenada_x*=(ancho_imagen)*escala;
    imagen->escalar->arriba_izq->coordenada_y*=(ancho_imagen)*escala;

    imagen->escalar->arriba_der->coordenada_x*=(ancho_imagen)*escala;
    imagen->escalar->arriba_der->coordenada_y*=(ancho_imagen)*escala;

    imagen->escalar->abajo_izq->coordenada_x*=(ancho_imagen)*escala;
    imagen->escalar->abajo_izq->coordenada_y*=(ancho_imagen)*escala;

    imagen->escalar->abajo_der->coordenada_x*=(ancho_imagen)*escala;
    imagen->escalar->abajo_der->coordenada_y*=(-ancho_imagen)*escala;

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

//Corregir una vez que cambie el struct de las coordenadas
double distancia_puntos(struct imagen* imagen1, struct imagen* imagen2){
    double distancia;
    distancia= sqrt(pow((imagen1->coordenadas->coordenada_x - imagen2->coordenadas->coordenada_x), 2) + pow((imagen1->coordenadas->coordenada_y - imagen2->coordenadas->coordenada_y), 2));
    
    return distancia;
}

/**
 * Ocupo que el angulo sea entre 0 y 45 grados, para saber si el angulo es mayor o menor a la diagonal
*/
double angulo(struct imagen* imagen1, struct imagen* imagen2){
    double pendiente=((imagen2->coordenadas->coordenada_y - imagen1->coordenadas->coordenada_y) / (imagen2->coordenadas->coordenada_x - imagen1->coordenadas->coordenada_x));
    // Calcular el ángulo de inclinación en radianes usando atan2
    double angulo = atan2(pendiente, 1); // La segunda entrada (1) representa el eje x

    // Convertir el ángulo a grados
    double angulo_en_grados = angulo * 180.0 / PI;

    while (angulo_en_grados>=45 || angulo <=0)
    {
        angulo_en_grados=fabs(90-angulo_en_grados);
    }
    
        // Imprimir el resultado
    //printf("El ángulo de inclinación es: %.2f radianes\n", angulo);
    printf("El ángulo de inclinación es: %.2f grados\n", angulo_en_grados);


    return angulo_en_grados;
}


/**
 * Al momento de rotar la imagen cambia el angulo, por ende se tiene que sumar el angulo
 * de la nueva rotacion.
*/

double obtener_distancia_diagonal(struct imagen* imagen, double angulo){
    double diagonal;
    diagonal = (imagen->lado)/(2*cos(angulo));
    return diagonal;
}

/**
 * Funcion que verifica que las imagenes no choquen, modifica el angulo de cada 
 * imagen individualmente para tener en cuenta la rotacion que tiene cada imagen. Si 
 * la suma de las dos diagonales de las imagenes son menores que la distancia entre ambs puntos
 * no chocan, pero en caso contrario signfica que lo hacen.
 * */
int colision_imagen(struct imagen* imagen1, struct imagen* imagen2){
    int ang=angulo(imagen1,imagen2); //Angulo de la pendiente de ambas imagenes
    
    int angulo_rotado1=ang+imagen1->rotar->grado; //Angulo con la rotacion de la imagen 1
    while (angulo_rotado1>=45 || angulo_rotado1 <=0)
    {
        angulo_rotado1=fabs(90-angulo_rotado1);
    }

    double diagonal1=obtener_distancia_diagonal(imagen1,ang); //Angulo con la rotacin de la imagen 2
    int angulo_rotado2=ang+imagen2->rotar->grado;
    while (angulo_rotado2>=45 || angulo_rotado2 <=0)
    {
        angulo_rotado2=fabs(90-angulo_rotado2);
    }

    double diagonal2=obtener_distancia_diagonal(imagen2,ang);
    double suma_diagonales = diagonal1 + diagonal2;
    double distancia = distancia_puntos(imagen1, imagen2);

    if(suma_diagonales<distancia){
        return 0; //No choca
    }
    else if (suma_diagonales>distancia)
    {
        return 1; //Choca
    }
    
}


/**
 * Función para crear una matriz de tamaño 450x450(Para que alcancen 9 imagenes de 150x150) 
 * e inicializarla con todo en 0.
 * Acà se van a guardar donde estan las imagenes.
 * */ 
int** crearMatriz() {
    int filas = 450;
    int columnas = 450;
    int valorInicial = 0;
    int **matriz = (int** )malloc(filas * sizeof(int *));
    if (matriz == NULL) {
        fprintf(stderr, "Error: No se pudo asignar memoria para la matriz\n");
        exit(1);
    }
    for (int i = 0; i < filas; i++) {
        matriz[i] = (int *)malloc(columnas * sizeof(int));
        if (matriz[i] == NULL) {
            fprintf(stderr, "Error: No se pudo asignar memoria para la fila %d\n", i);
            exit(1);
        }
        for (int j = 0; j < columnas; j++) {
            matriz[i][j] = valorInicial;
        }
    }
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
    return matriz;
}

// Función para imprimir una matriz de tamaño filas x columnas (No termina de funcar)
void imprimirMatriz(int **matriz) {
    int filas = 450;
    int columnas = 450;
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}

// Función para liberar la memoria de la matriz
void liberarMatriz(int **matriz) {
    int filas = 450;
    for (int i = 0; i < filas; i++) {
        free(matriz[i]);
    }
    free(matriz);
}




void rotating_caliper(){

}



int main(){
    srand(time(NULL)); //Semilla para inicializar el random
    struct imagen *prueba =calloc(1, sizeof(struct imagen));
    prueba->coordenadas=calloc(1, sizeof(struct coordenadas));
    prueba->escalar=calloc(1, sizeof(struct escala));
    prueba->rotar=calloc(1, sizeof(struct rotacion));

    prueba->escalar->arriba_izq = calloc(1, sizeof(struct coordenadas));
    prueba->escalar->arriba_der = calloc(1, sizeof(struct coordenadas));
    prueba->escalar->abajo_izq = calloc(1, sizeof(struct coordenadas));
    prueba->escalar->abajo_der = calloc(1, sizeof(struct coordenadas));

    prueba->rotar->arriba_izq = calloc(1, sizeof(struct coordenadas));
    prueba->rotar->arriba_der = calloc(1, sizeof(struct coordenadas));
    prueba->rotar->abajo_izq = calloc(1, sizeof(struct coordenadas));
    prueba->rotar->abajo_der = calloc(1, sizeof(struct coordenadas));

    prueba->coordenadas->coordenada_x=0;
    prueba->coordenadas->coordenada_y=0;

    prueba->escalar->abajo_der->coordenada_x=1;
    prueba->escalar->abajo_der->coordenada_y=-1;

    prueba->escalar->abajo_izq->coordenada_x=-1;
    prueba->escalar->abajo_izq->coordenada_y=-1;

    prueba->escalar->arriba_der->coordenada_x=1;
    prueba->escalar->arriba_der->coordenada_y=1;

    prueba->escalar->arriba_izq->coordenada_x=-1;
    prueba->escalar->arriba_izq->coordenada_y=1;

    prueba->rotar->abajo_der->coordenada_x=0;
    prueba->rotar->abajo_der->coordenada_y=0;

    prueba->rotar->abajo_izq->coordenada_x=0;
    prueba->rotar->abajo_izq->coordenada_y=0;

    prueba->rotar->arriba_der->coordenada_x=0;
    prueba->rotar->arriba_der->coordenada_y=0;

    prueba->rotar->arriba_izq->coordenada_x=0;
    prueba->rotar->arriba_izq->coordenada_y=0;




    struct imagen *prueba2 =calloc(1, sizeof(struct imagen));
    prueba2->coordenadas=calloc(1, sizeof(struct coordenadas));
    prueba2->escalar=calloc(1, sizeof(struct escala));
    prueba2->rotar=calloc(1, sizeof(struct rotacion));

    prueba2->escalar->arriba_izq = calloc(1, sizeof(struct coordenadas));
    prueba2->escalar->arriba_der = calloc(1, sizeof(struct coordenadas));
    prueba2->escalar->abajo_izq = calloc(1, sizeof(struct coordenadas));
    prueba2->escalar->abajo_der = calloc(1, sizeof(struct coordenadas));

    prueba2->rotar->arriba_izq = calloc(1, sizeof(struct coordenadas));
    prueba2->rotar->arriba_der = calloc(1, sizeof(struct coordenadas));
    prueba2->rotar->abajo_izq = calloc(1, sizeof(struct coordenadas));
    prueba2->rotar->abajo_der = calloc(1, sizeof(struct coordenadas));

    prueba2->coordenadas->coordenada_x=7;
    prueba2->coordenadas->coordenada_y=7;

    prueba2->escalar->abajo_der->coordenada_x=1;
    prueba2->escalar->abajo_der->coordenada_y=-1;

    prueba2->escalar->abajo_izq->coordenada_x=-1;
    prueba2->escalar->abajo_izq->coordenada_y=-1;

    prueba2->escalar->arriba_der->coordenada_x=1;
    prueba2->escalar->arriba_der->coordenada_y=1;

    prueba2->escalar->arriba_izq->coordenada_x=-1;
    prueba2->escalar->arriba_izq->coordenada_y=1;

    prueba2->rotar->abajo_der->coordenada_x=0;
    prueba2->rotar->abajo_der->coordenada_y=0;
    
    double distancia;
    crearMatriz();

    //distancia=angulo(prueba,prueba2);
    
    
    //escalar(10,prueba,0.5);
    //printf("%LF, %LF",prueba->escalar->arriba_der->coordenada_x,prueba->escalar->arriba_der->coordenada_y);
    //rotar(prueba,90);
    //printf("%LF, %LF",prueba->rotar->arriba_der->coordenada_x,prueba->rotar->arriba_der->coordenada_y);
    
}

/*
Cosas por hacer: 
-El rotating caliper ( minima area rectangulo) e implementarlo
-Donde se va a tener la informaciòn de la posicion de todas las cartas y sus puntos para el rotating
-Poner las primeras 3 imagenes lo mas cerca posible del origen
-Que la salida sea un script con los datos
-Extraer los megadatos de la base ->EN PROCESO
-Calcular que abarque el 75% de la carta 
-IDEA: Hacerlo con angulos complementarios para encajar la 2 imagen de manera màs eficiente
*/