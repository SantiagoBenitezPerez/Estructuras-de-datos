//Evidencia 1
//IMPLEMENTACION DE COLA CON PRIORIDAD

//INTEGRANTES DEL EQUIPO:
//Valeria Martinez Martinez - A01782413
//Aleksei Dubovoy Mateos - A01782179
//Santiago Benitez Perez - A01782813



#include <stdio.h>
#include <stdlib.h>

// estructura de un nodo en la cola con prioridad
struct nodo {
	int prioridad;
	int valor;
	struct nodo* siguiente;
};

//inicialmente la cola esta vacia
struct nodo* frente = NULL;
struct nodo* atras = NULL;


// funcion para checar si la cola con prioridad esta vacia
int colaVacia() {
	if(frente == NULL && atras == NULL) {

		return 1;
	} else {
		return 0;
	}
}

//funcion para agregar valores a la cola con prioridad
void queue(int valor, int prioridad) {
	// mientras que el usuario ingrese un valor erroneo de la prioridad
	// se le seguirá pidiendo que ingrese la prioridad dentro del rango definido
	while(prioridad > 5 || prioridad < 1) {
		printf("La prioridad debe ser un valor entre 1 y 5 incluidos\n");
		printf("ingresa la prioridad nuevamente: ");
		scanf("%d", &prioridad);
		queue(valor, prioridad);
		return;
	}
	
	// creamos el nuevo nodo a agregar
	struct nodo* elemento = malloc(sizeof(struct nodo));
	if(elemento == NULL) printf("el elemento no se pudo crear\n");
	
	// le asignamos al nodo el valor y la prioridad
	elemento -> valor = valor;
	elemento -> prioridad = prioridad;
	elemento -> siguiente = NULL;
	
	// si la cola esta vacia frente y atras apunta a ese elemento
	if(colaVacia() == 1) {	
		frente = elemento;
		atras = elemento;
	} else { // si la cola no esta vacia comparamos la prioridad de los valores que estan en la cola para determinar el lugar en donde insertar el nuevo valor
		struct nodo* actual = frente;
		
		while(actual != NULL) { // recorremos la cola
			if(elemento -> prioridad < actual -> prioridad) { // si la prioridad del elemento a insertar es menor a la prioridad de actual
				if(actual == frente) {
					elemento -> siguiente = frente;
					frente = elemento;
					return;
				}
			}
			
			// si la prioridad del elemento a insertar es igual o mayor a la prioridad de actual
			else if((elemento -> prioridad == actual -> prioridad) || (elemento -> prioridad > actual -> prioridad)) {
				 if(actual == atras) { // si actual es atras, redefinimos atras
				 	atras -> siguiente = elemento;
				 	atras = elemento;
				 	return;
				 } 
				 /*  checamos que  la prioridad del elemento a 
				    agregar sea menor a la prioridad del siguiente 
				    de actual o que el siguiente de actual sea nulo */
				 else if(elemento -> prioridad < actual -> siguiente -> prioridad || actual -> siguiente == NULL) { 
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

// funcion que inserta multiples valores
void queueMultiples(int cantidad) {
	int valor, prioridad;
	// agregamos tantos valores a la cola con prioridad como indique el usuario
	while (cantidad > 0) {
		printf("Valor a agregar a la cola:");
		scanf("%d", &valor);
		printf("Prioridad del valor (1-5):");
		scanf("%d", &prioridad);
		queue(valor, prioridad);
		cantidad--;
	}
}

// funcion que busca un nodo en la lista y entrega su posicion
void buscaNodo(int valor) {
	if(colaVacia() == 1) { // si cola vacia
		printf("no se pueden buscar valores porque la cola esta vacia\n");
		return;
	}
	else { // recorremos la lista para encontrar el valor que se indica en el argumento
		int i = 0;
	    struct nodo* temporal = frente;
	    while(temporal != NULL) {
		 if(temporal -> valor == valor) {
			printf("el valor %d se encuentra en la posicion [%d]", valor, i); // imprimimos el primer valor encontrado
			return;
		  }
		  i++;
		  temporal = temporal -> siguiente;
	    }
	}
	printf("el valor %d no se ha encontrado", valor); // si no se encuentra el valor
	
}


//funcion que determina el numero de nodos
int numNodos() {
	int cantidad = 0;
	if(colaVacia() == 1) { // si cola vacia
		printf("No hay elementos en la cola\n");
	} else { // recorremos la lista y por cada valor aumentamos la valor cantidad
		struct nodo* temporal = frente;
		while(temporal != NULL) {
			cantidad++;
			temporal = temporal -> siguiente;
		}
		return cantidad;
	}
	
}

// funcion dequeue
void dequeue() {
	if(colaVacia() == 1) { // si cola vacia
		printf("No se pueden quitar elementos de la cola con prioridad porque esta vacia");
		return;
	} 
	else if(frente == atras) { // si solo hay un elemento mandamos frente y atras a nulo
		printf("borrando (dequeue) el valor %d de la cola con prioridad\n", frente -> valor);
		struct nodo* temporal = frente;
		frente = NULL;
		atras = NULL;
		free(temporal);
	}
	else { // si hay dos o más elementos, redefinimos el apuntador frente y borramos el que era frente
		printf("borrando (dequeue) el valor %d de la cola con prioridad\n", frente -> valor);
		struct nodo* temporal = frente;
		frente = frente -> siguiente;
		free(temporal);
	}
}


//funcion que borra toda la cola
void dequeueAll() {
	if(colaVacia() == 1) { // si cola vacia
		printf("la cola ya esta vacia\n");
		return;
	}
	else { 
		int cantidad = numNodos();
		printf("Borrando todos los elementos de la cola con prioridad....\n");
		do { // llamamos a la funcion dequeue conociendo la cantidad de nodos que tiene la cola
			printf("\n");
			dequeue();
			cantidad--;
		} while(cantidad > 0);
		printf("\n");
		
		printf("LA COLA SE HA BORRADO CON EXITO.\n");
	}
}

// funcion para mostrar la cola
void mostrarCola() {  
	if(colaVacia() == 1) { // si cola vacia
		printf("la cola con prioridad esta vacia\n");
		return;
	}
	else { // recorremos la lista e imprimimos los valores
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
    	printf(" 1.Agregar (queue) valor a la cola con prioridad\n 2.Agregar (queue) multiples valores a la cola con prioridad\n 3.Borrar (dequeue) de la cola con prioridad\n 4.Borrar toda la cola con prioridad\n 5.Buscar un valor en la cola con prioridad\n 6.Mostrar la cola con prioridad\n 7.Ver la cantidad de elementos en la cola con prioridad\n 8.SALIR\n");
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
    	
	} while(opcion != 8); // opcion 8 indica salir
  
    
	return 0;
}

