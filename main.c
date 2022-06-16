#include "ingreso.h" 


int main(int argc, char const *argv[]) {

	if (argc != 2) {
    	printf("Ingrese el archivo con los datos %s", argv[0]);
    	return 1;
  	}

  	FILE* datos_archivo = abrir_archivo(argv[1], "r");
  	
  	char linea[100];
  	fgets(linea, LARGO_MAXIMO_LINEA, datos_archivo); // Primera linea titulo

	Snodo* lista = crearLista();

	for(int i = 0; i < CANT_PROVINCIAS; i++){
		Datos* datos = guardarStruct(datos_archivo); // Datos*
		agregarNodoFinalArchivo(&lista, datos);
	}

	printf("\nLa lista original es: ");
	slist_print(&lista, imprimirStruct);

	int total = fold_listas(lista, sumaVivDesh);	
	printf("\nEl total de viviendas deshabitadas es %i", total); 		 // caso para probar fold_listas


	int dobletotal = map_fold_listas2(lista, duplicarDatos, sumaVivDesh);
	printf("\nEl total de viviendas deshabitadas *2 es %i\n", dobletotal); // caso para probar map_fold_listas
	slist_print(&lista, imprimirStruct);								 // se imprime para mostrar que la lista NO fue modificada 
	//																	 // por el transformador	
	int vivtotal = fold_listas(lista, sumaVivTotal);
	printf("\nEl total de viviendas es %i\n\n", vivtotal); 					 // total de viviendas usando fold
	
	fclose(datos_archivo);
	slist_destruir(lista);
}