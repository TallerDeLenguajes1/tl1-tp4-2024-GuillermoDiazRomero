#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define LISTA 5

typedef struct Tarea
{
    int TareaID;       // Numérico autoincremental comenzando en 1000
    char *Descripcion; //
    int Duracion;      // entre 10 – 100
} Tarea;

typedef struct TNodo
{
    Tarea tarea;
    struct TNodo *siguiente;
} TNodo;


//Declaración de funciones
TNodo *crearLista();
TNodo *crearTNodo(Tarea t);
void InsertarFinal(TNodo **lista, Tarea t);
TNodo *buscarNodo(TNodo *lista, int idBuscado);
void EliminarNodo(TNodo *Start, TNodo **ok, int dato);
void mostrarNodos(TNodo *start);


void main()
{
    // Declaración de variables
    TNodo *lista, *realizado;
    int id = 1000;
    char aux[100];
    int respuesta, buscando;
    Tarea tareas;

    // CÓDIGO
    srand(time(NULL));
    lista = crearLista(); // Creo la lista vacía

    printf("Bienvenido al menu de tareas pendientes: ");
    do
    {
        printf("\n=========Ingrese su tarea numero %d=========", id);
        printf("\nDescripcion de la tarea: ");
        gets(aux);
        fflush(stdin);
        tareas.Descripcion = (char *)malloc(strlen(aux) * sizeof(char));
        strcpy(tareas.Descripcion, aux);

        tareas.Duracion = 10 + rand() % 90;
        tareas.TareaID = id;

        InsertarFinal(&lista, tareas);

        id++;
        printf("\nDesea seguir ingresando tareas? (ingrese 1 para si)");
        scanf("%d", &respuesta);
        fflush(stdin);

    } while (respuesta == 1);

    //Punto 2
    realizado = crearLista(); // Creo la lista vacía
    printf("\nDesea marcar alguna tarea como realizada?(1 para si) ");
    scanf("%d", &respuesta);
    while (respuesta == 1)
    {
        do{
            printf("\nIngrese el id para marcar: ");
            scanf("%d", &buscando);
        } while (buscando< 1000 || buscando > id);
        
        EliminarNodo(lista,realizado,buscando);
        printf("\nDesea marcar otra tarea como realizada?(1 para si) ");
        scanf("%d", &respuesta);
    }
    printf("\nLista de tareas pendientes: ");
    mostrarNodos(lista);

    printf("\nLista de tareas realizadas: ");
    mostrarNodos(realizado);
}

TNodo *crearLista()
{
    return NULL;
}
TNodo *crearTNodo(Tarea t)
{
    TNodo *nodo = (TNodo *)malloc(sizeof(TNodo));
    nodo->tarea = t;
    nodo->siguiente = NULL;
    return nodo;
}
void InsertarFinal(TNodo **lista, Tarea t){
    TNodo *nuevoNodo = crearTNodo(t);
    if (*lista == NULL)
    {
        lista = nuevoNodo;
    }
    else
    {
        TNodo *aux = *lista;
        while (aux->siguiente)
        {
            aux = aux->siguiente;
        }
        aux->siguiente = nuevoNodo;
    }
}

TNodo *buscarNodo(TNodo *lista, int idBuscado)
{
    TNodo *aux = lista;
    while (aux && aux->tarea.TareaID != idBuscado)
    {
        aux = aux->siguiente;
    }
    return aux;
}

void EliminarNodo(TNodo *Start, TNodo **ok, int dato){
    TNodo *aux;
    // Iteramos sobre la lista hasta encontrar el dato o alcanzar 
   
    aux = buscarNodo(Start,dato);

    // Si encontramos el nodo con el dato especificado, lo 
    if (aux){
        TNodo *temp = aux; // Guardamos el nodo a eliminar en una variable temporal.
            aux = aux->siguiente; // Desvinculamos el nodo de la lista.
            InsertarFinal(ok, temp->tarea);
        free(temp);             // Liberamos la memoria ocupada por el nodo.
    }
}


void mostrarNodos(TNodo *start)
{
    printf("\n");
    if(start == NULL){
        printf("----------LA LISTA ESTA VACIA------\n");
    }
    else{
    TNodo *Aux = start;
    while(Aux != NULL){
        printf("id: %d\n", Aux->tarea.TareaID);
        printf("descripcion: ");
        puts(Aux->tarea.Descripcion);
        printf("duracion: %d\n", Aux->tarea.Duracion);
        printf("--------------------------------------\n");
        Aux = Aux->siguiente;
    }
    }
    printf("\n");
}