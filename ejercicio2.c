#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Tarea {
int TareaID; //Numerado en ciclo iterativo
char *Descripcion; //
int Duracion; // entre 10 – 100
}tarea;

void cargarListaDeTareas(tarea** tareasPorHacer, int cantidadDeTareas);
void preguntarYCargarTareasRealizadas(tarea** tareasPorHacer, tarea** tareasRealizadas, int cantidadDeTareas);
void mostrarTareasRealizadasYPendientes(tarea** tareasPorHacer, tarea** tareasRealizadas, int cantidadDeTareas);
void buscarTareaPorID(tarea** tareasPorHacer, tarea** tareasRealizadas, int cantidadDeTareas);
void buscarTareaPorPalabra(tarea** tareasPorHacer, tarea** tareasRealizadas, int cantidadDeTareas);

int main(){
    srand(time(NULL));
    int cantidadDeTareas;
    printf("\nIngrese la cantidad de tareas a cargar: ");
    scanf("%d", &cantidadDeTareas);
    fflush(stdin);

    tarea** tareasPorHacer = (tarea**)malloc(cantidadDeTareas*sizeof(tarea*));
    tarea** tareasRealizadas = (tarea**)malloc(cantidadDeTareas*sizeof(tarea*));

    cargarListaDeTareas(tareasPorHacer, cantidadDeTareas);
    preguntarYCargarTareasRealizadas(tareasPorHacer, tareasRealizadas, cantidadDeTareas);
    mostrarTareasRealizadasYPendientes(tareasPorHacer, tareasRealizadas, cantidadDeTareas);
    buscarTareaPorID(tareasPorHacer, tareasRealizadas, cantidadDeTareas);
    buscarTareaPorPalabra(tareasPorHacer, tareasRealizadas, cantidadDeTareas);

    return 0;
}

void cargarListaDeTareas(tarea** tareasPorHacer, int cantidadDeTareas){
    tarea *pTareaIndividual;
    char* descripcionAux = (char*)malloc(150*sizeof(char));
    pTareaIndividual = (tarea*)malloc(sizeof(tarea));

    for (int i = 0; i < cantidadDeTareas; i++){
        tareasPorHacer[i] = pTareaIndividual;
        pTareaIndividual->TareaID = i+1;
        printf("Ingrese la descripci%cn de la tarea %d: ",162,i+1);
        gets(descripcionAux);
        pTareaIndividual->Descripcion = (char*)malloc((strlen(descripcionAux)+1)*sizeof(char));
        strcpy(pTareaIndividual->Descripcion,descripcionAux);
        pTareaIndividual->Duracion = rand() % 91 + 10;
        pTareaIndividual++;
    }
    free(descripcionAux);
    free(pTareaIndividual);
}

void preguntarYCargarTareasRealizadas(tarea** tareasPorHacer, tarea** tareasRealizadas, int cantidadDeTareas){
    char respuesta;

    printf("_____________________________");
    printf("\nCONSULTA POR TAREA\n");

    for (int i = 0; i < cantidadDeTareas; i++){
        tareasRealizadas[i] = NULL;
    }

    for (int i = 0; i < cantidadDeTareas; i++){

        printf("\nTarea %d ", tareasPorHacer[i]->TareaID);
        printf("\nDescripci%cn: %s\n", 162,tareasPorHacer[i]->Descripcion);
        printf("Duraci%cn: %d", 162,tareasPorHacer[i]->Duracion);

        printf("\nRealiz%c esta tarea? (s/n): ", 162);
        scanf("%c", &respuesta);
        fflush(stdin);

        if (respuesta == 's'){
            tareasRealizadas[i] = tareasPorHacer[i];
            tareasPorHacer[i] = NULL;
        }
    }
}

void mostrarTareasRealizadasYPendientes(tarea** tareasPorHacer, tarea** tareasRealizadas, int cantidadDeTareas){

    printf("_____________________________");
    printf("\nLISTAS DE TAREAS\n");

    puts("\nTAREAS REALIZADAS: ");
    for (int i = 0; i < cantidadDeTareas; i++){
        if (tareasRealizadas[i] != NULL){
            printf("Tarea %d ", tareasRealizadas[i]->TareaID);
            printf("\nDescripci%cn: %s\n", 162,tareasRealizadas[i]->Descripcion);
            printf("Duraci%cn: %d\n\n", 162,tareasRealizadas[i]->Duracion);
        }
    }

    puts("TAREAS PENDIENTES: ");
    for (int i = 0; i < cantidadDeTareas; i++){
        if (tareasPorHacer[i] != NULL){
            printf("Tarea %d ", tareasPorHacer[i]->TareaID);
            printf("\nDescripci%cn: %s\n", 162,tareasPorHacer[i]->Descripcion);
            printf("Duraci%cn: %d\n\n", 162,tareasPorHacer[i]->Duracion);
        }
    }
}

void buscarTareaPorID(tarea** tareasPorHacer, tarea** tareasRealizadas, int cantidadDeTareas){
    int id;

    printf("_____________________________");
    printf("\nIngrese el ID de la tarea solicitada: ");
    scanf("%d", &id);
    fflush(stdin);

    printf("TAREA POR ID ELEGIDO\n");

    for(int i = 0 ; i < cantidadDeTareas ; i++){
        if(tareasPorHacer[i] != NULL && tareasPorHacer[i]->TareaID == id){
            printf("\nTarea %d ", tareasPorHacer[i]->TareaID);
            printf("\nDescripci%cn: %s\n", 162,tareasPorHacer[i]->Descripcion);
            printf("Duraci%cn: %d", 162,tareasPorHacer[i]->Duracion);
        }
        if(tareasRealizadas[i] != NULL && tareasRealizadas[i]->TareaID == id){
            printf("\nTarea %d ", tareasRealizadas[i]->TareaID);
            printf("\nDescripci%cn: %s\n", 162,tareasRealizadas[i]->Descripcion);
            printf("Duraci%cn: %d", 162,tareasRealizadas[i]->Duracion);
        }
    }
}

void buscarTareaPorPalabra(tarea** tareasPorHacer, tarea** tareasRealizadas, int cantidadDeTareas){
    char* palabra = (char *)malloc(10*sizeof(char));

    printf("\n_____________________________\n");
    printf("Ingrese la palabra clave: ");
    gets(palabra);
    char* palabra2 = (char *)malloc((strlen(palabra)+1)*sizeof(char));
    strcpy(palabra2,palabra);

    printf("TAREA POR PALABRA CLAVE\n");

    for(int i = 0 ; i < cantidadDeTareas ; i++){
        if(tareasPorHacer[i] != NULL && strcmp(tareasPorHacer[i]->Descripcion,palabra2) == 0){
            printf("\nTarea %d ", tareasPorHacer[i]->TareaID);
            printf("\nDescripci%cn: %s\n", 162,tareasPorHacer[i]->Descripcion);
            printf("Duraci%cn: %d", 162,tareasPorHacer[i]->Duracion);
        }
        if(tareasRealizadas[i] != NULL && strcmp(tareasRealizadas[i]->Descripcion,palabra2) == 0){
            printf("\nTarea %d ", tareasRealizadas[i]->TareaID);
            printf("\nDescripci%cn: %s\n", 162,tareasRealizadas[i]->Descripcion);
            printf("Duraci%cn: %d", 162,tareasRealizadas[i]->Duracion);
        }
    }

    free(palabra);
    free(palabra2);
}