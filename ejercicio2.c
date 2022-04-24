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
    
    puts("\nTAREAS REALIZADAS:\n ");
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