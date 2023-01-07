/**Florencia Gabriela Giusti
DNI:42.341.987
asignatura: EDA 1
curso: MARTES 18 HS
FECHA DE ENTREGA: SABADO 18 DE JUNIO
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct info
{
    short med_num;/** medicion numero 1, 2, 3, 4... */
    float temperatura;/** la temperatura medida */
    char nom_maquina[10];/** la temperatura medida */
};

short menu();///menu para poder acceder a las opciones
void escribirArchivo(struct info*, short);///esta funcion escribe el vector a un archivo binario
void fecha();///visualizo la fecha de hoy

int main(void)
{
    struct info maquina;///estructura usada para leer el archivo binario
    char path[150]="C:\\Users\\Win7\\Desktop\\universidad\\";///ruta de acceso al archivo binario
    short cantidad=0;///variable usada para contar datos

    short flag=0;///utilizado para poder completar opciones
    short op;///variable para poder usar el menu de opciones
    struct info *puntero=NULL;///aqui guardo los datos del archivo binario en la estructura

     FILE *archivo;/// puntero a FILE

    strncat(path, "temperaturas.bin", 149),///funcion para concatenar desde la cadena2: "temperaturas.bin" hacia la cadena1: "path", devuelve la cadena1.
    archivo=fopen(path, "rb");///abro el archivo con su rura y su modo

    if(archivo!=NULL)///compruebo si el archivo tiene contenido
        {
            fread(&maquina, sizeof(maquina),1,archivo);///leemos el archivo

            while(!feof(archivo))///lee hasta encontrar el final del archivo
                {
                    cantidad++;
                    fread(&maquina, sizeof(maquina),1,archivo);
                }
            printf("\nArchivo creado en %s!!!\n",path);
            printf("\nfecha de hoy ");
            fecha();
        }
    else
        printf("Error de escritura!!!\n");
        fclose(archivo);///cierro el archivo

    while (op<5)
    {
        op=menu();

        if(op==1)
        {
            archivo=fopen(path, "rb");

            if(archivo!=NULL)
                {
                    fread(&maquina, sizeof(maquina),1,archivo);
                    while(!feof(archivo))
                    {
                        printf("%hd_______%2f_____%s\n", maquina.med_num, maquina.temperatura, maquina.nom_maquina); ///leemos el archivo binario
                        fread(&maquina, sizeof(maquina),1,archivo);
                    }
               }
               fclose(archivo);
        }

        if(op==2)
        {
            archivo=fopen(path, "rb");
            if(archivo!=NULL)
                {
                    puntero=(struct info*)malloc((cantidad)*sizeof(struct info));///use malloc porque a medida que se fue leyendo el archivo binario utilice la varible cantidad++
                    for(short i=0; i<cantidad; i++)
                        {
                            fread(&maquina, sizeof(maquina),1,archivo);
                            puntero[i].med_num= maquina.med_num;
                            puntero[i].temperatura= maquina.temperatura;
                            strcpy(puntero[i].nom_maquina,maquina.nom_maquina);
                        }
                    flag++;
                }
            for(short i=0; i<cantidad; i++)
                {
                    printf("%hd_______%2f_____%s\n", puntero[i].med_num, puntero[i].temperatura, puntero[i].nom_maquina);///archivo binario guardado en el puntero
                }
            printf("\nArchivo binario guardado en el vector!!!");
            printf("\nSe han almacenado %hd datos\n",cantidad);
            fclose(archivo);
        }

        if(op==3)
        {
            if(flag==0)
                printf("\nPRIMERO TIENE DEBE GUARDAR EL ARCHIVO\n");

            if(flag>0)
                escribirArchivo(puntero, cantidad);
        }

        if(op==4)
        {
            printf("\nMuchas gracias!!!\n");
            printf("fecha de fin ");
            fecha();
            return 0;
        }
    }
}

short menu()
{
    short flag=0, op;

    do{
        if(flag!=0){
            printf("opcion invalida\n");
          }
        printf("\nOPCIONES: ");
        printf("\n1-leer el archivo binario creado por el operario\n");
        printf("2-Guardar cada dato del archivo en un vector indicando al final cuantos datos se han almacenado.\n");
        printf("3-ingrese el nombre de una maquina para guardar sus datos en un archivo de texto");
        printf("4-salir\n");;
        flag=1;
        scanf("%hd", &op);
      }while(op<1 || op>5);
}

void escribirArchivo(struct info *puntero, short cantidad)
{
    short cuantos=0;
    float promedio=0;
    float suma=0;
    char ingrese[10];///para ingresar el nombre de la maquina

    FILE *archivo1;
    archivo1=fopen("C:\\Users\\Win7\\Desktop\\universidad\\texto.txt","wt");///aqui cree un archivo de texto y su ruta

        if(archivo1==NULL)
        {
            printf("error en la creacion");
            exit (0);
        }
         printf("\ningrese la maquina que desea guardar\n");
         fflush(stdin);
         scanf("%s", &ingrese);

        for(short i=0; i<cantidad; i++)
         {
             if(strcmp(ingrese,puntero[i].nom_maquina)==0)///aqui comparo dos strings
             {
                 cuantos++;
                 fprintf(archivo1,"Medicion N°: %hd____ Temperatura: %2f_______ nombre: %s\n", puntero[i].med_num, puntero[i].temperatura, puntero[i].nom_maquina);///vector de estructuras guardado en un archivo txt
                 suma+=puntero[i].temperatura;
             }
         }

         if(cuantos==0)
         {
             printf("\nNo se ha encontrado el nombre de la maquina!!!\n");
         }

    if(cuantos>0)
    {
        promedio=suma/cuantos;
        fprintf(archivo1,"\n\nel promedio es %2f", promedio);
        fprintf(archivo1,"\nhay ingresados %hd datos", cuantos);
        printf("\nSe a copiado contenido al archivo de texto\n");
    }

    fclose(archivo1);///cierro el archivo de texto
}

void fecha(int argc, char*argv[])
{
    time_t tiempo=time(0);
    struct tm*tlocal=localtime(&tiempo);
    char output[128];
    strftime(output, 128, "%d/%m/%y %H:%M:%S", tlocal);
    printf("%s\n", output);
}





