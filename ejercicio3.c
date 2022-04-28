#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Tarea{
    int TareaID; //Numerado en ciclo iterativo
    char *Descripcion; //
    int Duracion; // entre 10 – 100
};

struct Nodo{
    struct Tarea T;
    struct Nodo *Siguiente;
};

void insertarNodo(struct Nodo** start, int id, char* descripcion, int duracion);
void cargarListaTareasPendientes(struct Nodo** start, int cantidadDeTareas);
void mostrarLista(struct Nodo* start);
void cargarListaTareasRealizadas(struct Nodo** startPendientes, struct Nodo** startRealizadas);
void borrarNodoEspecifico(struct Nodo** startPendientes, int id);
void borrarLista(struct Nodo** start);
void buscarTareaPorID(struct Nodo* startPendientes, struct Nodo* startRealizadas);
void buscarTareaPorPalabra(struct Nodo* startPendientes, struct Nodo* startRealizadas);

int main() {
    srand(time(NULL));
    struct Nodo* startPendientes = NULL;
    struct Nodo* startRealizadas = NULL;
    int cantidadDeTareas;

    printf("\nIngrese la cantidad de tareas que se cargar%cn: ", 160);
    scanf("%d", &cantidadDeTareas);
    fflush(stdin);

    cargarListaTareasPendientes(&startPendientes, cantidadDeTareas);
    printf("\n__________________________");
    printf("\nLISTA DE TAREAS PENDIENTES\n");
    mostrarLista(startPendientes);

    cargarListaTareasRealizadas(&startPendientes, &startRealizadas);
    printf("\n__________________________");
    printf("\nLISTA DE TAREAS REALIZADAS\n");
     if (startRealizadas == NULL){
        printf("A%cn no realiz%c ninguna tarea\n", 163, 162);
    } else {
        mostrarLista(startRealizadas);
    }    

    printf("\n______________________________________");
    printf("\nLISTA DE TAREAS PENDIENTES ACTUALIZADA\n");
    if (startPendientes == NULL){
        printf("Ya no quedan tareas pendientes\n\n");
    } else {
        mostrarLista(startPendientes);
    }

    buscarTareaPorID(startPendientes, startRealizadas);
    buscarTareaPorPalabra(startPendientes, startRealizadas);

    borrarLista(&startPendientes);
    borrarLista(&startRealizadas);

    return 0;
}

struct Nodo* crearNodo(int id, char* descripcion, int duracion) {
    struct Nodo* nuevo = NULL;
    nuevo = (struct Nodo*)malloc(sizeof(struct Nodo));

    if (nuevo != NULL){
        nuevo->T.TareaID = id;
        nuevo->T.Descripcion = descripcion;
        nuevo->T.Duracion = duracion;
        nuevo->Siguiente = NULL;
    }

    return nuevo;
}

void insertarNodo(struct Nodo** start, int id, char* descripcion, int duracion){
    struct Nodo* nuevo = NULL;
    nuevo = crearNodo(id, descripcion, duracion);

    if (nuevo != NULL){
        nuevo->Siguiente = *start;
        *start = nuevo;
    }
}

void cargarListaTareasPendientes(struct Nodo** start, int cantidadDeTareas){
    char* descripcionAux = (char*)malloc(100*sizeof(char));

    for (int i = 0; i < cantidadDeTareas; i++){
        printf("\nDescripci%cn de tarea %d: ", 162, i+1);
        gets(descripcionAux);
        char* descripcion = (char*)malloc((strlen(descripcionAux)+1)*sizeof(char));
        strcpy(descripcion, descripcionAux);
        insertarNodo(start, i+1, descripcion, rand() % 91 + 10);
    }

    free(descripcionAux);
}

void mostrarLista(struct Nodo* start){
    struct Nodo* nodoAux = start;

    while (nodoAux != NULL){
        printf("\nTarea id = %d\ndescripcion: %s\nduracion = %d\n", nodoAux->T.TareaID, nodoAux->T.Descripcion, nodoAux->T.Duracion);
        nodoAux = nodoAux->Siguiente;
    } 

    free(nodoAux);
}

void cargarListaTareasRealizadas(struct Nodo** startPendientes, struct Nodo** startRealizadas){
    struct Nodo* nodoAuxPendientes = *startPendientes;
    int respuesta;

    printf("\n_____________________________");
    printf("\nCONSULTA DE TAREAS REALIZADAS\n");

    for (nodoAuxPendientes ; nodoAuxPendientes != NULL ; nodoAuxPendientes = nodoAuxPendientes->Siguiente){
        printf("Realiz%c la tarea: %s? (1: s%c):", 162, nodoAuxPendientes->T.Descripcion, 161);
        scanf("%d", &respuesta);
        fflush(stdin);

        if (respuesta == 1){
            insertarNodo(startRealizadas, nodoAuxPendientes->T.TareaID, nodoAuxPendientes->T.Descripcion, nodoAuxPendientes->T.Duracion);
            borrarNodoEspecifico(startPendientes, nodoAuxPendientes->T.TareaID);
        }
    }

    free(nodoAuxPendientes);
}

void borrarNodoEspecifico(struct Nodo** startPendientes, int id){
    struct Nodo* auxPendientes = *startPendientes;

    if (auxPendientes->T.TareaID == id){
        *startPendientes = auxPendientes->Siguiente;
        free(auxPendientes);
    } else {
        while ((auxPendientes->Siguiente)->T.TareaID != id){
            auxPendientes = auxPendientes->Siguiente;
        }
        free(auxPendientes->Siguiente);
        auxPendientes->Siguiente = (auxPendientes->Siguiente)->Siguiente;
    }
}

void borrarLista(struct Nodo** start){
	struct Nodo* aux;
	while(*start != NULL){
		aux = *start;
		*start = aux->Siguiente;
		free(aux);
	}
}

void buscarTareaPorID(struct Nodo* startPendientes, struct Nodo* startRealizadas){
    int id;
    struct Nodo* auxPendientes = startPendientes;
    struct Nodo* auxRealizadas = startRealizadas;

    printf("\n_____________________");
    printf("\nBUSCAR TAREA POR ID\n");
    printf("Ingrese el ID de la tarea buscada: ");
    scanf("%d", &id);
    fflush(stdin);

    while(auxPendientes != NULL){
        if(auxPendientes->T.TareaID == id){
            printf("\nTarea id = %d\ndescripcion: %s\nduracion = %d\n", auxPendientes->T.TareaID, auxPendientes->T.Descripcion, auxPendientes->T.Duracion);
        }
        auxPendientes = auxPendientes->Siguiente;
    }

    while(auxRealizadas != NULL){
        if(auxRealizadas->T.TareaID == id){
            printf("\nTarea id = %d\ndescripcion: %s\nduracion = %d\n", auxRealizadas->T.TareaID, auxRealizadas->T.Descripcion, auxRealizadas->T.Duracion);
        }
        auxRealizadas = auxRealizadas->Siguiente;
    }

    free(auxPendientes);
    free(auxRealizadas);
}

void buscarTareaPorPalabra(struct Nodo* startPendientes, struct Nodo* startRealizadas){
    char* palabraClaveAux = (char*)malloc(15*sizeof(char));
    struct Nodo* auxPendientes = startPendientes;
    struct Nodo* auxRealizadas = startRealizadas;

    printf("\n_____________________");
    printf("\nBUSCAR TAREA POR PALABRA\n");
    printf("Ingrese la palabra clave: ");
    gets(palabraClaveAux);
    char* palabraClave = (char*)malloc((strlen(palabraClaveAux)+1)*sizeof(char));
    strcpy(palabraClave, palabraClaveAux);

    while(auxPendientes != NULL){
        if(strcmp(auxPendientes->T.Descripcion,palabraClave) == 0){
            printf("\nTarea id = %d\ndescripcion: %s\nduracion = %d\n", auxPendientes->T.TareaID, auxPendientes->T.Descripcion, auxPendientes->T.Duracion);
        }
        auxPendientes = auxPendientes->Siguiente;
    }

    while(auxRealizadas != NULL){
        if(strcmp(auxRealizadas->T.Descripcion,palabraClave) == 0){
            printf("\nTarea id = %d\ndescripcion: %s\nduracion = %d\n", auxRealizadas->T.TareaID, auxRealizadas->T.Descripcion, auxRealizadas->T.Duracion);
        }
        auxRealizadas = auxRealizadas->Siguiente;
    }

    free(auxPendientes);
    free(auxRealizadas);
}