//Evidencia 1
//IMPLEMENTACION DE COLA CON PRIORIDAD

//INTEGRANTES DEL EQUIPO:
//Valeria Martinez Martinez - A01782413
//Aleksei Dubovoy Mateos - A01782179
//Santiago Benitez Perez - A01782813

#include <stdio.h>
#include <stdlib.h>

struct nodo {
	int prioridad;
	int valor;
	struct nodo* siguiente;
};

struct nodo* frente = NULL;
struct nodo* atras = NULL;

int colaVacia() {
	if(frente == NULL && atras == NULL) {

		return 1;
	} else {
		return 0;
	}
}

void queue(int valor, int prioridad) {
	if(prioridad > 5 || prioridad < 1) {
		printf("La prioridad debe ser un valor entre 1 y 5 incluidos\n");
		return;
	}
	
	struct nodo* elemento = malloc(sizeof(struct nodo));
	if(elemento == NULL) printf("el elemento no se pudo crear\n");
	
	elemento -> valor = valor;
	elemento -> prioridad = prioridad;
	elemento -> siguiente = NULL;
	
	if(colaVacia() == 1) {
		// si la cola esta vacia frente y atras apunta a ese elemento
		frente = elemento;
		atras = elemento;
//		elemento -> siguiente = NULL;
	}
	else {
		struct nodo* actual = frente;
		
		while(actual != NULL) {
			if(elemento -> prioridad < actual -> prioridad) {
				if(actual == frente) {
					elemento -> siguiente = frente;
					frente = elemento;
					return;
				}
			}
			
			else if((elemento -> prioridad == actual -> prioridad) || (elemento -> prioridad > actual -> prioridad)) {
				 if(actual == atras) {
				 	atras -> siguiente = elemento;
				 	atras = elemento;
				 	return;
				 } else if(elemento -> prioridad < actual -> siguiente -> prioridad || actual -> siguiente == NULL) {
				 	elemento -> siguiente = actual -> siguiente;
				 	actual -> siguiente = elemento;
				 	return;
				 }
				 else {
				 	actual = actual -> siguiente;
				 }
			} 
		}
	}
        
}

void queueMultiples(int cantidad) {
	int valor, prioridad;
	
	while (cantidad > 0) {
		printf("Valor a agregar a la lista:");
		scanf("%d", &valor);
		printf("Prioridad del valor (1-5):");
		scanf("%d", &prioridad);
		queue(valor, prioridad);
		cantidad--;
	}
}


void buscaNodo(int valor) {
	if(colaVacia() == 1) {
		printf("no se pueden buscar valores porque la lista esta vacia\n");
		return;
	}
	else {
		int i;
	    struct nodo* temporal = frente;
	    while(temporal != NULL) {
		 if(temporal -> valor == valor) {
			printf("el valor %d se encuentra en la posicion [%d]", valor, i);
			return;
		  }
		  i++;
		  temporal = temporal -> siguiente;
	    }
	}
	printf("el valor %d no se ha encontrado", valor);
	
}

//funcion que determina el numero de nodos

int numNodos() {
	int cantidad = 0;
	if(colaVacia() == 1) {
		printf("No hay elementos en la cola\n");
	} else {
		struct nodo* temporal = frente;
		while(temporal != NULL) {
			cantidad++;
			temporal = temporal -> siguiente;
		}
		return cantidad;
	}
	
}

void dequeue() {
	if(colaVacia() == 1) {
		printf("No se pueden quitar elementos de la cola con prioridad porque esta vacia");
		return;
	} 
	else if(frente == atras) {
		printf("borrando (dequeue) el valor %d de la cola con prioridad\n", frente -> valor);
		struct nodo* temporal = frente;
		frente = NULL;
		atras = NULL;
		free(temporal);
	}
	else {
		printf("borrando (dequeue) el valor %d de la cola con prioridad\n", frente -> valor);
		struct nodo* temporal = frente;
		frente = frente -> siguiente;
		free(temporal);
	}
}


//funcion que borra toda la cola

void dequeueAll() {
	if(colaVacia() == 1) {
		printf("la cola ya esta vacia\n");
		return;
	}
	else {
		int cantidad = numNodos();
		printf("Borrando todos los elementos de la cola con prioridad....\n");
		do {
			printf("\n");

			dequeue();
			cantidad--;
		} while(cantidad > 0);
		printf("\n");
		
		printf("LA COLA SE HA BORRADO CON EXITO.\n");
	}
}

void mostrarCola() {
	if(colaVacia() == 1) {
		printf("la cola con prioridad esta vacia\n");
		return;
	}
	else {
		struct nodo* temporal = frente;
	    int i = 0;
	    printf("Los elementos de la cola con prioridad son los siguientes:\n");
	    while(temporal != NULL) {
		 printf("valor[%d] = %d\tPrioridad: %d\n",i, temporal -> valor, temporal -> prioridad);
		 temporal = temporal -> siguiente;
		 i++;
	  }
	}
	
}



int main() {
	int opcion, valor, prioridad, cantidad;
    printf("EVIDENCIA 1. COLA CON PRIORIDAD\n");
    printf("\n");
    printf("Estado inicial de la Cola con prioridad: \n");
    mostrarCola();
    printf("\n");
    
    do {
    	printf("********************* MENU ***********************");
        printf("\n");
    	printf("1.Agregar (queue) valor a la cola con prioridad\n 2.Agregar (queue) multiples valores a la cola con prioridad\n 3.Borrar (dequeue) de la cola con prioridad\n 4.Borrar toda la cola con prioridad\n 5.Buscar un valor en la cola con prioridad\n 6.Mostrar la cola con prioridad\n 7.Ver la cantidad de elementos en la cola con prioridad\n 8.SALIR\n");
    	printf("Selecciona una opcion: ");
    	scanf("%d", &opcion);
    	switch(opcion) {
    		case 1:
    		   printf("\n");
    		   printf("ingrese el valor a agregar en la cola: ");
    		   scanf("%d", &valor);
    		   printf("ingrese la prioridad (del 1 al 5) del valor que acaba de ingresar: ");
    		   scanf("%d", &prioridad);
    		   queue(valor, prioridad);
    		   mostrarCola();
    		   printf("\n");
    		   break;
    		case 2:
    		   printf("\n");
    		   printf("¿Cuantos elementos quieres agregar a la cola?: ");
               scanf("%d", &cantidad);
               queueMultiples(cantidad);
               mostrarCola();
               printf("\n");
               break;
            case 3:
               printf("\n");
               dequeue();
               mostrarCola();
               printf("\n");
               break;
            case 4:
            	printf("\n");
            	dequeueAll();
            	printf("\n");
            	mostrarCola();
            	printf("\n");
            	break;
            case 5:
            	printf("\n");
            	printf("ingresa el valor a buscar en la cola: ");
            	scanf("%d", &valor);
            	buscaNodo(valor);
            	printf("\n");
            	break;
            case 6:
            	printf("\n");
            	mostrarCola();
            	printf("\n");
            	break;
            case 7:
            	printf("\n");
            	cantidad = numNodos();
            	printf("Hay %d elementos en la cola con prioridad\n", cantidad);
            	printf("\n");
            	break;
    		case 8:
			   break;
    		default: 
    		   printf("\n");
    		   printf("Esa no es una opcion valida, intente de nuevo");
    		   printf("\n");
    		   break;
		}
    	
	} while(opcion != 8);
    
	return 0;
}

