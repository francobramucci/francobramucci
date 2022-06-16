  #ifndef INGRESO_H
#define INGRESO_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h> 

#define LARGO_MAXIMO_LINEA 100
#define LARGO_MAXIMO_PALABRA 60
#define CANT_PROVINCIAS 24
#define LARGO_MAXIMO_NUMERO 10 

typedef struct Datos {  //Estructura donde serán guardados los distintos datos del archivo
  char* provincia;      
  int vivPartHab;
  int vivPartDesh;
  int vivColec;
}Datos;

typedef struct _SNodo { //Estructura de la lista
  Datos* datos;
  struct _SNodo *sig;
} Snodo;


/*
 * Función utilizada para la transformación de datos del campo de tipo
 * Snodo*
 */
typedef Snodo* (*Transformacion)(Snodo* datos);

/*
 * Función utilizada para la operación con datos de tipo int
 */
typedef int (*Operador) (Snodo*, int resultado);

/*
 * Función visitante utilizada para recorrer los distintos 
 * campos del campo datos en la lista
 */
typedef void (*FuncionVisitante) (Datos* datos); 

/*
 * Función visitante utilizada para copiar los datos del archivo 
 * a una estructura para luego redireccionar a la lista
 */
typedef Datos* (*FuncionVisitante2) (FILE* datos_archivo);

/*
 * abrir_archivo toma la ruta de un archivo y el modo en el que
 * se quiere abrir y devuelve el archivo objeto resultado de
 * abrirlo en dicho modo
 */
FILE* abrir_archivo(const char *nombre_archivo, char *modo);

/*
 * crearLista crea una lista simplemente enlazada en la que guardamos NULL
 * y retorna el puntero Snodo
 */
Snodo* crearLista();

/*
 * guardarStruct lee linea por linea el archivo y guarda hasta encontrar 
 * una coma o terminar la linea en la variable temporal tb para luego
 * convertirlo de string al tipo de dato requerido (Ej: int con la función 
 * atoi) y almacenarlo en la estructura buffer que será retornada
 */
Datos* guardarStruct(FILE* datos_archivo);

/*
 * agregarNodoFinal agrega un nodo al final de la lista, y redirecciona 
 * la estructura de tipo Datos* en donde se almacenaron todos los campos en 
 * la función guardarStruct a el campo de datos de la lista, guardando así 
 * los datos de cada provincia en cada nodo de la lista
 */
void agregarNodoFinalArchivo(Snodo** lista, Datos* dato);

/*
 * imprimirStruct recorre cada campo de la estructura e imprime los datos 
 * de la misma, es decir provincia, viv. part. habitadas, viv. part. deshabitadas
 * y viviendas colectivas
 */
void imprimirStruct(Datos* datos);

/*
 * slist_print imprime cada dato almacenado en el campo datos de cada
 * nodo de la lista
 */
void slist_print(Snodo** list, FuncionVisitante imprimirDatos);

/*
 * sumaVivDesh suma el campo de las viviendas deshabitadas y lo retorna como
 * un entero 
 */
int sumaVivDesh(Snodo* nodos, int suma);

/*
 * sumaVivTotal suma las viviendas habitadas, deshabitadas y
 * colectivas para luego devolverlas como un dato de tipo int
 */
int sumaVivTotal(Snodo* nodos, int suma);

/*
 * fold_listas toma una lista, la recorre y realiza operaciones
 * con los elementos que componen a la misma
 */
int fold_listas(Snodo* lista, Operador operator);

/*
 * agregarNodoFinal agrega un nodo como elemento final de una lista
 */
void agregarNodoFinal(Snodo** lista, Datos* dato);

/*
 * duplicarDatos reserva espacio en memoria y crea los
 * datos de una lista ya existentes multiplicados por 2
 */
Snodo* duplicarDatos(Snodo* nodos);

/*
 * map_fold_listas toma una lista, la recorre, transforma sus datos
 * y vuelve a recorrerla aplicando la función fold_listas a la lista ya transformada
 * estp implica un doble recorrido de la lista, ya que primeramente se recorre para 
 * transformarla y luego para aplicarle el operador
 */
//int map_fold_listas(Snodo* list, Transformacion transformator, Operador operator);

/*
 * A diferencia de map_fold_listas, esta función no llama a fold_listas sino que 
 * inmediatamente después de transformar el dato de cada lista le aplica el operador
 * siendo más eficiente ya que en vez de recorrerla 2n nodos recorrera n nodos
 */
int map_fold_listas2(Snodo* list, Transformacion transformator, Operador operator);

/*
 * Funcion que libera tod
 */
void slist_destruir(Snodo* lista);

  #endif