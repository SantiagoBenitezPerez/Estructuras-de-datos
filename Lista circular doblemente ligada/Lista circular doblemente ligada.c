//Evidencia 1
//IMPLEMENTACION DE LISTA CIRCULAR DOBLEMENTE LIGADA

//INTEGRANTES DEL EQUIPO:
//Valeria Martinez Martinez - A01782413
//Aleksei Dubovoy Mateos - A01782179
//Santiago Benitez Perez - A01782813

#include <stdio.h>
#include <stdlib.h>

struct nodo {
	int valor;
	struct nodo* anterior;
	struct nodo* siguiente;
};

struct nodo* inicio = NULL;
struct nodo* fin = NULL;



// función que determina si la lista circular está vacia
int listaVacia() {
	// si tanto inicio como fin apuntan a null, entonces 
	// la lista está vacia
	if(inicio == NULL && fin == NULL) {
	
		return 1;
	} else {
		return 0;
	}
}

// función que determina la cantidad de nodos en la lista circular
void numNodos() {
	if(listaVacia() == 1) {
		printf("No hay elementos en la lista circular\n");
	}
	else {
		int cantidad = 0;
	    struct nodo* temporal = inicio;
	// vamos a recorrer la lista mientras que el apuntador 
	// siguiente del temporal sea diferente al inicio
	// esto indica que ya se recorrió la lista una vez.
	    while(temporal -> siguiente != inicio) {
		  cantidad++;
		  temporal = temporal -> siguiente;
	  }
	   if(temporal == fin) {
		cantidad ++;
	   }
	   printf("la lista tiene %d nodos\n", cantidad);
	}  
}

// función que inserta un nodo al final de la lista circular
void insertarNodo(int valor) {
	// creamos el nodo a insertar dinámicamente
	struct nodo* elemento = malloc(sizeof(struct nodo));
	// checamos que se haya creado el nodo
	if(elemento == NULL) {
		printf("El elemento no se ha podido crear\n");
		return;
	}
	printf("insertando valor %d en la lista circular\n", valor);
	elemento -> valor = valor;
	
	// si la lista esta vacia, ambos apuntadores del elemento
	// apuntan a null
	if(listaVacia() == 1) {
    // si lista vacia entonces inicio y fin apuntan a nulo
        inicio = elemento;
		fin = elemento;
		elemento -> siguiente = inicio;
		elemento -> anterior = fin;
		
		
	} else {
	// si lista no vacia redefinimos los apuntadores
		fin -> siguiente = elemento;
		elemento -> anterior = fin;
		fin = elemento;
		fin -> siguiente = inicio;
		inicio -> anterior = fin;
	}
	
}

void borrarNodo(int valor) {
	if(listaVacia() == 1){
		printf("la lista esta vacia, no se puede borrar ese numero\n");
		return;
	}
	
	else if(inicio == fin) {
		// solo un elemento en la lista
		if(inicio -> valor == valor) {
			 printf("borrando %d de la lista circular\n", valor);
			 // si el unico valor en la lista
			 // es el valor a borrar
			 struct nodo* temporal = inicio;
		     inicio = NULL;
		     fin = NULL;
		     free(temporal);
		     return;
		}
	} else {
		// si hay dos o más nodos
	    
		struct nodo* temporal = inicio;
		while(temporal -> siguiente != inicio) {
		// recorrer lista para encontrar el nodo a borrar
		    if(temporal -> valor == valor) {
		    	printf("borrando %d de la lista circular\n", valor);
		    	if(temporal == inicio) {
				// si el nodo a borrar es el primero
			    inicio = inicio -> siguiente;
			    inicio -> anterior = fin;
		        fin -> siguiente = inicio;
			    free(temporal);
			    return;
			 } 
			 else {
			 	// en caso de que la ocurrencia este en algun elemento de en medio
				// hacemos el bypass
			 	temporal -> anterior -> siguiente = temporal -> siguiente;
		    	temporal -> siguiente -> anterior = temporal -> anterior;
		    	free(temporal);
		    	return;
			  }
			 }    
		    temporal = temporal -> siguiente;
			}
		// si el nodo a borrar es el fin
		if(fin -> valor == valor) {
			printf("borrando %d de la lista circular\n", valor);
			struct nodo* temporal = fin;
			fin = fin -> anterior;
			fin -> siguiente = inicio;
			free(temporal);
			return;
			}
	
	}
	
	printf("El valor %d no se encuentra en la lista circular\n", valor);
}

// función que añade multiples nodos a la lista
void insertarMultiples(int cantidad) {
	int valor;
	while(cantidad > 0) {
		printf("ingresa el valor:");
		scanf("%d", &valor);
		insertarNodo(valor);
		cantidad--;
	}
	
}

// función para borrar nodos consecutivos (todas las ocurrencias)
void borrarOcurrencias(int valor) {
	if(listaVacia() == 1){
		printf("la lista esta vacia, no se puede borrar ese numero\n");
		return;
	}
	else if(inicio == fin) {
		// solo un elemento en la lista
		if(inicio -> valor == valor) {
			 printf("borrrrrando todas las ocurrencias del valor %d en la lista circular\n", valor);
			 // si el unico valor en la lista
			 // es el valor a borrar
			 struct nodo* temporal = inicio;
		     inicio = NULL;
		     fin = NULL;
		     free(temporal);
		} else {
			printf("el valor %d no se encuentra en la lista\n", valor);
		}
		
	} 
	else {
		int i = 0;
		//recorrida de la lista para determinar ocurrencias del valor
		struct nodo* temporal = inicio;
		while(temporal -> siguiente != inicio) {
			if(temporal -> valor == valor) {
				// si el valor del temporal es igual al valor a borrar entonces checamos 
				// si es el primer elemento de la lista o los que le siguen
//				printf("ando todas las ocurrencias del valor %d en la lista circular\n", valor);
				if(temporal == inicio) {
					printf("borrando el valor %d en la posicion [%d]\n", valor, i);
					inicio = inicio -> siguiente;
					
					inicio -> anterior = fin;
					fin -> siguiente = inicio;
					free(temporal);
					i++;
					temporal = temporal -> siguiente;
				} 
				
				else {
					printf("borrando valor %d en la posicion [%d]\n", valor, i);
					// en caso de que la ocurrencia este en algun elemento de en medio
					// hacemos el bypass
					temporal -> anterior -> siguiente = temporal -> siguiente;
					temporal -> siguiente -> anterior = temporal -> anterior;
					free(temporal);
					i++;
					temporal = temporal -> siguiente;
				}
			}
			i++;
			temporal = temporal -> siguiente;	
		}
		
		if(fin -> valor == valor) {
			// si la ocurrencia a borrar es el ultimo elemento
			printf("elim todas las ocurrencias del valor %d en la lista circular\n", valor);
			fin = fin -> anterior;
			fin -> siguiente = inicio;
			inicio -> anterior = fin;
			free(temporal);
			
		} else {
			// si no existe el valor en la lista
			printf("el valor %d no se encuentra en la lista circular\n", valor);
		}
		
	}

}


// función para buscar un nodo de la lista

void buscaNodo(int valor) {
	if(listaVacia() == 1) {
		// si lista vacia
		printf("no se puede buscar el valor %d porque la lista esta vacia", valor);
		return;
	}
	else {
		// recorremos la lista en busqueda del nodo
		int i = 0;
		struct nodo* temporal = inicio;
		while(temporal -> siguiente != inicio) {
			if(temporal -> valor == valor) {
				printf("el valor %d si esta en la lista\n Su posicion es:\n", valor);
				printf("nodo[%d] = %d", i, temporal -> valor);
				return;
			} 
			i++;
			temporal = temporal -> siguiente;
		}
		if(fin -> valor == valor) {
			printf("el valor %d si esta en la lista\n Su posicion es:\n", valor);
			printf("nodo[%d] = %d", i, temporal -> valor);
			return;
		}
	}
	
	printf("el valor %d no se encuentra en la lista\n", valor);
	
}



// función que imprime los pares de la lista
void obtenerPares() {
	if(listaVacia() == 1) {
	    printf("No se pueden obtener pares, la lista esta vacia\n");
		return;
	} 
	else {
		// recorremos la lista para determinar los pares de la lista circular
		int i = 0;
	struct nodo* temporal = inicio;
	printf("Los valores pares en la lista son:\n");
	while(temporal -> siguiente != inicio) {
		if(temporal -> valor%2==0) {
			printf(" nodo[%d] = %d\n",i, temporal -> valor);
		}
		i++;
		temporal = temporal -> siguiente;
	}
	
	if(fin->valor%2==0) {
		printf("nodo[%d] = %d",i, fin -> valor);
	  }
	}	
}


// función para borrar toda la lista
void borrarLista() {
	if(listaVacia() == 1) {
		// si lista vacia
		printf("La lista ya esta vacia\n");
		return;
	}
	else {
		// creamos un temporal, iteramos la lista y vamos borrando los temporales
		struct nodo* temporal = inicio;
    
	    while(temporal -> siguiente != inicio) {
		
	      free(temporal);
		  temporal = temporal -> siguiente;
	 }
	    
	    inicio = NULL;
	    fin = NULL;
	    free(temporal);
	    temporal = NULL;
	    printf("La lista se ha borrado satisfactoriamente\n");
	}
	
    
}

// función que muestra los elementos en la lista circular
void mostrar() {
    int i = 0;
    
    if(listaVacia() == 1) {
		printf("la lista esta vacia\n");
		return;
	}
	else {
		struct nodo* temporal = inicio;
	// vamos a recorrer la lista mientras que el apuntador 
	// siguiente del temporal sea diferente al inicio
	// esto indica que ya se recorrió la lista una vez.
	    printf("los elementos de la lista circular son:\n");
	    printf("nodo[%d] = %d\n", i, temporal -> valor);
	    while(temporal -> siguiente != inicio) {
		 i++;
	     printf("nodo[%d] = %d\n", i , temporal -> siguiente -> valor);
		 temporal = temporal -> siguiente;
	 } 
	}	
}

int main() {
	int opcion, valor, cantidad;
	
	printf("EVIDENCIA 1- LISTA CIRCULAR DOBLEMENTE LIGADA\n");
	printf("\n");
	printf("Estado inicial de la lista circular doblemente ligada:\n");
	// mostrar la lista vacia inicialmente
	mostrar();
	printf("\n\n");
	
	// INICIA MENU 
	do {
		printf("***************** MENU ******************\n\n 1.Insertar valor (entero) a la lista circular\n 2.Insertar multiples valores (elementos) consecutivos a la lista\n 3.Borrar valor de la lista circular\n 4.Borrar todas las ocurrencias de un valor en la lista circular\n 5.Eliminar toda la lista circular\n 6.Mostrar la lista circular\n 7.Buscar un valor en la lista circular\n 8.Ver la cantidad de elementos en la lista circular\n 9.SALIR\n");
		printf("Selecciona la opcion que deseas: ");
		scanf("%d", &opcion);
		// dependiendo la opcion hacemos lo correspondiente
		switch(opcion) {
			case 1:
			   printf("\n");
			   printf("ingresa el valor a insertar: ");
			   scanf("%d", &valor);
			   insertarNodo(valor);
			   mostrar();
			   printf("\n");
			   break;
			case 2:
			   printf("\n");
			   printf("¿Cuantos numeros quieres agregar a la lista?:");
             scanf("%d", &cantidad);
	           insertarMultiples(cantidad);
	           mostrar();
	           printf("\n");
	           break;
	        case 3:
	           printf("\n");
	           printf("Ingresa el valor a borrar: ");
	           scanf("%d", &valor);
	           borrarNodo(valor);
	           mostrar();
	           printf("\n");
	           break;
	        case 4: 
	           printf("\n");
	           printf("Ingresa el valor del que desea borrar todas sus ocurrencias:");
	           scanf("%d", &valor);
	           borrarOcurrencias(valor);
	           mostrar();
	           printf("\n");
	           break;
	        case 5:
	           printf("\n");
	           borrarLista();
	           printf("\n");
	           break;
	        case 6:
	           printf("\n");
	           mostrar();
	           printf("\n");
	           break;
	        case 7:
	           printf("\n");
	           printf("ingresa el valor que te gustaria buscar en la lista: ");
	           scanf("%d", &valor);
	           buscaNodo(valor);
	           printf("\n");
	           break;
	        case 8:
	           printf("\n");
	           numNodos();
	           printf("\n");
	           break;
	        case 9: 
			   break;
	        default:
	           printf("\n");
	           printf("%d no es una opcion, intente de nuevo.\n", opcion);
	           printf("\n");
	           break;
			 
		}
		
	} while(opcion!= 9); // opcion 9 es salir

//    printf("\n");
//	printf("¿Cuantos numeros quieres agregar a la lista?:");
//    scanf("%d", &cantidad);
//	insertarMultiples(cantidad);
//	mostrar();
//	
//	borrarOcurrencias(1);
//	
//	mostrar();
//	
//	printf("\n");
//	printf("¿Cuantos numeros quieres agregar a la lista?:");
//    scanf("%d", &cantidad);
//	insertarMultiples(cantidad);
//	mostrar();
//	
//	borrarOcurrencias(1);
//	
//	mostrar();

	return 0;
}
