/* Ejecutar comandos de linea en C, basado en el trabajo de Kik_padodo
https://www.codegrepper.com/code-examples/c/run+a+command+in+cmd+with+c

Comando strace -c basado en el trabajo de Himanshu Arora
https://www.howtoforge.com/linux-strace-command/#q-how-to-use-strace-command

Argumentos en el ejecutable basado en el trabajo del canal de Youtube WhileTrueThenDream
https://www.youtube.com/watch?v=0Nmg6gDW1i0

Recorrer por columnas un archivo, guardarlo en una estructura e imprimirlo, 
basado en la respuesta de David C. Rankin
https://stackoverflow.com/questions/53237280/how-to-read-columns-from-a-text-file-and-save-to-separate-arrays-in-c

Imprimir en consola con colores basado en el trabajo de Vitor Matias
https://medium.com/@vitorcosta.matias/print-coloured-texts-in-console-a0db6f589138

Comando strace para el filtrado de llamadas de procesos y memoria,
basado en el trabajo de Karim Buzdar
https://linuxways.net/centos/11-strace-command-with-example-in-linux/

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <time.h>

//Se duplica el almacenamiento cada vez que se alcanza el límite de asignación en la lectura de filas
#define ARRSZ   2 
// Se define el máximo que guarda el bufer de lectura de filas. 
#define MAXC 1024

//////// COLORES /////
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define YEL "\e[0;33m"
#define MAG "\e[0;35m"
#define CYN "\e[0;36m"
//Reset de los colores
#define reset "\e[0m"

// Estructura para la tabla, ya que el archivo con las llamadas se lee por columnas
typedef struct {
    char *col1, *col2, *col3, *col4, *col5, *col6;
} mydata_t;


// Definicion de las funciones del programa
int checkIfFileExists(const char *filename);
void modoSeteo(int want_key);
int obtenerTecla();
int interactivo();
int automatico1();

// Main
int main(int argc, char *argv[]){

    for (int i = 0; i < argc; i++){ // Descompone el comando que se ingresa en la consola

    }
    char *a1 = argv[0]; // Ejecutable del programa
    char *a2 = argv[1]; // Ejecutable al que se le quiere sacar las llamadas al sistema
    char *a3 = argv[2]; // Modo de ejecucion: interactivo o automatico
    char *a4 = argv[3]; // Tipo de filtro si asi lo quieren

    // Variables para el comando
    char *ejecutable = a2;
    char *automatico = "strace -S calls -c -o trace2.txt "; // Comando para obtener todas las llamadas
    char *procesos = "strace -c -e trace=process -o trace2.txt  "; // Comando para obtener todas las llamadas de procesos
    char *memoria = "strace -c -e trace=memory -o trace2.txt  "; // Comando para obtener todas las llamadas de memoria
    char* name_with_extension;

    //////////////////////


    if(checkIfFileExists(a2)){ // Verifica si el ejecutable al que se le quieren sacar las llamadas al sistema existen
        printf("El archivo existe\n");

////////////////////////////////////////////
// Automatico
////////////////////////////////////////////

///////////// Todo, automatico, sin filtros
        if ((argc == 4) && (!strcmp( a3, "-a")) &&  (!strcmp( a4, "-0"))){
            printf(MAG);
            printf("Automatico - Sin filtrado \n");
            printf(reset);
            name_with_extension = malloc(strlen(ejecutable)+50); 
            strcpy(name_with_extension, automatico); 
            strcat(name_with_extension, ejecutable); 
            system(name_with_extension);
            usleep(1000);
            automatico1();
        }

        else if((argc == 3) && (!strcmp( a3, "-a"))){
            printf(MAG);
            printf("Automatico \n");
            printf(reset);
            name_with_extension = malloc(strlen(ejecutable)+50); 
            strcpy(name_with_extension, automatico); 
            strcat(name_with_extension, ejecutable); 
            system(name_with_extension);
            usleep(1000);
            automatico1();
        }

        else if((argc == 2)){
            printf(MAG);
            printf("Automatico \n");
            printf(reset);
            name_with_extension = malloc(strlen(ejecutable)+50); 
            strcpy(name_with_extension, automatico); 
            strcat(name_with_extension, ejecutable); 
            system(name_with_extension);
            usleep(1000);
            automatico1();
        }
///////////// Todo, automatico, procesos
        else if((argc == 4) && (!strcmp( a3, "-a")) &&  (!strcmp( a4, "-1"))){
            printf(MAG);
            printf("Automatico - Filtrado de procesos \n");
            printf(reset);
            name_with_extension = malloc(strlen(ejecutable)+50); 
            strcpy(name_with_extension, procesos); 
            strcat(name_with_extension, ejecutable); 
            system(name_with_extension);
            usleep(1000);
            automatico1();
        }
///////////// Todo, automatico, memoria
        else if((argc == 4) && (!strcmp( a3, "-a")) &&  (!strcmp( a4, "-2"))){
            printf(MAG);
            printf("Automatico - Filtrado de mapeo de memoria \n");
            printf(reset);
            name_with_extension = malloc(strlen(ejecutable)+50); 
            strcpy(name_with_extension, memoria); 
            strcat(name_with_extension, ejecutable); 
            system(name_with_extension);
            usleep(1000);
            automatico1();
        }

////////////////////////////////////////////
// Interactivos
////////////////////////////////////////////

///////////// Interactivo, sin filtro
        else if((argc == 4) && (!strcmp( a3, "-A")) &&  (!strcmp( a4, "-0"))){
            printf(MAG);
            printf("Interactivo - Sin filtrado \n");
            printf(reset);
            name_with_extension = malloc(strlen(ejecutable)+50); 
            strcpy(name_with_extension, automatico); 
            strcat(name_with_extension, ejecutable); 
            system(name_with_extension);
            usleep(1000);
            interactivo();
        }
///////////// Interactivo, procesos
        else if((argc == 4) && (!strcmp( a3, "-A")) &&  (!strcmp( a4, "-1"))){
            printf(MAG);
            printf("Interactivo - Filtrado de procesos \n");
            printf(reset);
            name_with_extension = malloc(strlen(ejecutable)+50); 
            strcpy(name_with_extension, procesos); 
            strcat(name_with_extension, ejecutable); 
            system(name_with_extension);
            usleep(1000);
            interactivo();
        }
///////////// Interactivo, memoria
        else if((argc == 4) && (!strcmp( a3, "-A")) &&  (!strcmp( a4, "-2"))){
            printf(MAG);
            printf("Interactivo - Filtrado de mapeo de memoria \n");
            printf(reset);
            name_with_extension = malloc(strlen(ejecutable)+50); 
            strcpy(name_with_extension, memoria); 
            strcat(name_with_extension, ejecutable); 
            system(name_with_extension);
            usleep(1000);
            interactivo();
        }
///////////// Interactivo, sin filtro
        else if((argc == 3) && (!strcmp( a3, "-A"))){
            printf(MAG);
            printf("Interactivo - Sin filtro \n");
            printf(reset);
            name_with_extension = malloc(strlen(ejecutable)+50); 
            strcpy(name_with_extension, automatico); 
            strcat(name_with_extension, ejecutable); 
            system(name_with_extension);
            usleep(1000);
            interactivo();
        }

/////////// Mensaje de error
        else{
            printf(RED);
            printf("Ingrese un comando valido, los modos son: \n");
            printf("Automatico (-a) e interactivo (-A) \n");
            printf("Y los filtros son: sin filtro (-0) \n");
            printf("filtro de procesos (-1) y filtro de memoria (-2) \n");
            printf(reset);
        }
    }

    else if(!checkIfFileExists(a2)){ // Si el ejecutable no existe, imprime que no esta ese ejecutable
        printf("No existe el ejecutable escrito \n");
    }

    else{
        printf("Error, ingrese un comando valido \n");
    }


    return 0;

}
///////Terminan las validaciones///////////


//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////                                ////////////////////////////////////////////////
//////////////////       Modo Interactivo         ////////////////////////////////////////////////
//////////////////                                ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////

int interactivo(){

    //Inicializar variables para la lectura del archivo de texto con las llamadas del sistema
    char buf[MAXC];
    size_t arrsz = ARRSZ, line = 0, row = 0;
    mydata_t *data = NULL;
    // Abre el archivo para solo lectura
    FILE *fp = fopen ("trace2.txt", "r") ;

    //Verifica si el archivo ha podido ser leido
    if (!fp) {
        perror ("No se ha podido abrir el archivo");
        return 1;
    }

    // Se aloja en data el puntero a la memoria asignada y verifica si se puede asignar
    if (!(data = malloc (arrsz * sizeof *data))) {
        perror ("malloc-data");
        return 1;
    }

    while (fgets (buf, MAXC, fp)) {  //Lee cada linea del archivo y la guarda en buf
        char c1[MAXC], c2[MAXC], c3[MAXC], c4[MAXC], c5[MAXC], c6[MAXC]; 
        size_t len = strlen (buf); // Para validar el largo en el bufer

        //Se valida la cantidad de palabras en el bufer, para verificar posteriormente
        //si hay alguna columna vacia, como en el caso de Error en la tabla de llamadas
        //creada por strace
        int i, contPalabras = 1;
        for(i = 0; i < strlen(buf); i++)
            if(buf[i] == ' ' && i > 0 && buf[i - 1] != ' ')
            contPalabras++;

        //Incrementa el conteo de líneas
        line++; 

        //Valida que la linea leida del archivo cabe en el bufer
        if (len && buf[len-1] != '\n' && len == MAXC - 1) {
            fprintf (stderr, "error: line %zu exceeds MAXC chars.\n", line);
            return 1;
        }

        //Valida si las lineas antes reservadas ya estan ocupadas y debe ser realocadas 
        //(aumentando el tamaño para que la estructura data vaya creciendo dinamicamente)
        if (row == arrsz) {
            void *tmp = realloc (data, arrsz * 2 * sizeof *data);
            if (!tmp) { //Valida si realloc fue exitoso
                perror ("realloc-data");
                break;  //break, dado que data aun almacena datos, pero no se pudo ampliar
            }
            data = tmp;     /* assign realloc'ed block to data */
            arrsz *= 2;     /* update arrsz to reflect new allocation */
        }

        //Caso cuando el comando strace no devuelve ningun error para alguna llamada en  
        //especifico, por lo que igual agregamos un valor de "0" para esa columna de Error
        if(contPalabras == 5){
            data[row].col5 = "0";
            //Verifica que cada valor de la linea para las 6 columnas, tiene el formato
            //adecuado de char, tambien que los almacena en los chars antes creados
            if (sscanf (buf, "%1023s %1023s %1023s %1023s %1023s", 
                        c1, c2, c3, c4, c6) != 5) {
                fprintf (stderr, "error: invalid format line %zu\n", line);
                continue;    //Continuar a la siguiente linea del archivo
            }
            //Asigna el valor de la columna de la linea actual del bufer a la estructura
            if (!(data[row].col1 = strdup (c1))) { //Valida la copia de c1 */
                fprintf (stderr, "error: malloc-c1 line %zu\n", line);
                break;       
            }
            if (!(data[row].col2 = strdup (c2))) { //Valida la copia de c2 */
                fprintf (stderr, "error: malloc-c1 line %zu\n", line);
                break;       
            }
            if (!(data[row].col3 = strdup (c3))) { //Valida la copia de c4 */
                fprintf (stderr, "error: malloc-c1 line %zu\n", line);
                break;       
            }
            if (!(data[row].col4 = strdup (c4))) { //Valida la copia de c4 */
                fprintf (stderr, "error: malloc-c1 line %zu\n", line);
                break;       
            }
            if (!(data[row].col6 = strdup (c6))) { //Valida la copia de c6 */
                fprintf (stderr, "error: malloc-c1 line %zu\n", line);
                break;       
            }
        }

        else if (contPalabras == 4){
            data[row].col3 = "0";
            data[row].col5 = "0";
            //Verifica que cada valor de la linea para las 6 columnas, tiene el formato
            //adecuado de char, tambien que los almacena en los chars antes creados
            if (sscanf (buf, "%1023s %1023s %1023s %1023s", 
                        c1, c2, c4, c6) != 4) {
                fprintf (stderr, "error: invalid format line %zu\n", line);
                continue;    //Continuar a la siguiente linea del archivo
            }

            //Asigna el valor de la columna de la linea actual del bufer a la estructura
            if (!(data[row].col1 = strdup (c1))) { //Valida la copia de c1 */
                fprintf (stderr, "error: malloc-c1 line %zu\n", line);
                break;       
            }
            if (!(data[row].col2 = strdup (c2))) { //Valida la copia de c2 */
                fprintf (stderr, "error: malloc-c1 line %zu\n", line);
                break;       
            }
            if (!(data[row].col4 = strdup (c4))) { //Valida la copia de c4 */
                fprintf (stderr, "error: malloc-c1 line %zu\n", line);
                break;       
            }
            if (!(data[row].col6 = strdup (c6))) { //Valida la copia de c6 */
                fprintf (stderr, "error: malloc-c1 line %zu\n", line);
                break;       
            }
        }

        else{

            if (sscanf (buf, "%1023s %1023s %1023s %1023s %1023s %1023s", 
                        c1, c2, c3, c4, c5, c6) != 6) {
                fprintf (stderr, "error: invalid format line %zu\n", line);
                continue;    //Continuar a la siguiente linea del archivo
            }

            //Asigna el valor de la columna de la linea actual del bufer a la estructura
            if (!(data[row].col1 = strdup (c1))) { //Valida la copia de c1 */
                fprintf (stderr, "error: malloc-c1 line %zu\n", line);
                break;       
            }
            if (!(data[row].col2 = strdup (c2))) { //Valida la copia de c2 */
                fprintf (stderr, "error: malloc-c1 line %zu\n", line);
                break;       
            }
            if (!(data[row].col3 = strdup (c3))) { //Valida la copia de c4 */
                fprintf (stderr, "error: malloc-c1 line %zu\n", line);
                break;       
            }
            if (!(data[row].col4 = strdup (c4))) { //Valida la copia de c4 */
                fprintf (stderr, "error: malloc-c1 line %zu\n", line);
                break;       
            }
            if (!(data[row].col5 = strdup (c5))) { //Valida la copia de c4 */
                fprintf (stderr, "error: malloc-c1 line %zu\n", line);
                break;       
            }
            if (!(data[row].col6 = strdup (c6))) { //Valida la copia de c6 */
                fprintf (stderr, "error: malloc-c1 line %zu\n", line);
                break;       
            }
        }
        row++;/* increment number of row pointers used */
    }
    

    // Printea los titulos de las columnas
    char *row1[] = {"Syscall", "Cantidad", "Porcentaje de Tiempo"};
    printf(GRN);
    printf("%*s | %*s | %*s\n", -15, row1[0], -15, row1[1], -15, row1[2]);
    // Printea las lineas de arriba de la tabla
    printf(CYN);
    printf("%*s | %*s | %*s\n", -15, "-----", -15, "-----", -15, "-----");
    printf(reset);
    


///////////////////////////////////////////////////////////////////////////
//             Imprime los valores de la tabla con la tecla enter
///////////////////////////////////////////////////////////////////////////


    int f; // Se inicializa una variable para verificar el valor de la tecla enter
    int con = 2; // Contador para empezar a imprimir las llamadas al sistema

	// Se ejecuta siempre
	while(1) {
		modoSeteo(1); // Espera que haya una interrupcion en el teclado
		while (!(f = obtenerTecla())) usleep(10); // Obtiene el valor de la tecla seleccionada
		
        if(con!= row){ // Se ejecuta mientras con sea diferente de row
            if (f == 10){ // Tecla enter -> 10

                if(con == row-2){ // Printea las rayas del final
                    printf(CYN);
                    printf("%*s | %*s | %*s\n", -15, "-----", -15, "-----", -15, "-----");
                    printf(reset);
                    con++;
                }
                if(con == row -1){ // Printea la ultima linea
                    //Cuando la columna de Error esta vacia, entonces el total de llamadas
                    //se guarda en la columna 4
                    if(data[con].col3 == "0"){
                        printf(GRN);
                        printf("%-15s | %-15s | %-15s\n", "Total",
                        data[con].col4, "100.00");
                        printf(reset);
                        break;
                    }
                    else{
                        printf(GRN);
                        printf("%-15s | %-15s | %-15s\n", "Total",
                        data[con].col3, "100.00");
                        printf(reset);
                        break;
                    }
                }
                // Imprime todas las llamadas del sistema
                printf(YEL);
                printf("%-15s | %-15s | %-15s\n", data[con].col6,
                    data[con].col4, data[con].col1);
                printf(reset);
            }

        
            con = con + 1; // Se aumenta el contador
        }	

        else{
            return 0; // Sale de la ejecucion
        }
	}

}

//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////                                ////////////////////////////////////////////////
//////////////////       Modo Automatico         ///////////////////////////////////////////////// 
//////////////////                                ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////


int automatico1(){

    //Inicializar variables para la lectura del archivo de texto con las llamadas del sistema
    char buf[MAXC];
    size_t arrsz = ARRSZ, line = 0, row = 0;
    mydata_t *data = NULL;
    // Abre el archivo para solo lectura
    FILE *fp = fopen ("trace2.txt", "r") ;

    //Verifica si el archivo ha podido ser leido
    if (!fp) {
        perror ("No se ha podido abrir el archivo");
        return 1;
    }

    // Se aloja en data el puntero a la memoria asignada y verifica si se puede asignar
    if (!(data = malloc (arrsz * sizeof *data))) {
        perror ("malloc-data");
        return 1;
    }

    while (fgets (buf, MAXC, fp)) {  //Lee cada linea del archivo y la guarda en buf
        char c1[MAXC], c2[MAXC], c3[MAXC], c4[MAXC], c5[MAXC], c6[MAXC]; 
        size_t len = strlen (buf); // Para validar el largo en el bufer

        //Se valida la cantidad de palabras en el bufer, para verificar posteriormente
        //si hay alguna columna vacia, como en el caso de Error en la tabla de llamadas
        //creada por strace
        int i, contPalabras = 1;
        for(i = 0; i < strlen(buf); i++)
            if(buf[i] == ' ' && i > 0 && buf[i - 1] != ' ')
            contPalabras++;

        //Incrementa el conteo de líneas
        line++; 

        //Valida que la linea leida del archivo cabe en el bufer
        if (len && buf[len-1] != '\n' && len == MAXC - 1) {
            fprintf (stderr, "error: line %zu exceeds MAXC chars.\n", line);
            return 1;
        }

        //Valida si las lineas antes reservadas ya estan ocupadas y debe ser realocadas 
        //(aumentando el tamaño para que la estructura data vaya creciendo dinamicamente)
        if (row == arrsz) {
            void *tmp = realloc (data, arrsz * 2 * sizeof *data);
            if (!tmp) { //Valida si realloc fue exitoso
                perror ("realloc-data");
                break;  //break, dado que data aun almacena datos, pero no se pudo ampliar
            }
            data = tmp;     /* assign realloc'ed block to data */
            arrsz *= 2;     /* update arrsz to reflect new allocation */
        }

        //Caso cuando el comando strace no devuelve ningun error para alguna llamada en  
        //especifico, por lo que igual agregamos un valor de "0" para esa columna de Error
        if(contPalabras == 5){
            data[row].col5 = "0";
            //Verifica que cada valor de la linea para las 6 columnas, tiene el formato
            //adecuado de char, tambien que los almacena en los chars antes creados
            if (sscanf (buf, "%1023s %1023s %1023s %1023s %1023s", 
                        c1, c2, c3, c4, c6) != 5) {
                fprintf (stderr, "error: invalid format line %zu\n", line);
                continue;    //Continuar a la siguiente linea del archivo
            }
            //Asigna el valor de la columna de la linea actual del bufer a la estructura
            if (!(data[row].col1 = strdup (c1))) { //Valida la copia de c1 */
                fprintf (stderr, "error: malloc-c1 line %zu\n", line);
                break;       
            }
            if (!(data[row].col2 = strdup (c2))) { //Valida la copia de c2 */
                fprintf (stderr, "error: malloc-c1 line %zu\n", line);
                break;       
            }
            if (!(data[row].col3 = strdup (c3))) { //Valida la copia de c4 */
                fprintf (stderr, "error: malloc-c1 line %zu\n", line);
                break;       
            }
            if (!(data[row].col4 = strdup (c4))) { //Valida la copia de c4 */
                fprintf (stderr, "error: malloc-c1 line %zu\n", line);
                break;       
            }
            if (!(data[row].col6 = strdup (c6))) { //Valida la copia de c6 */
                fprintf (stderr, "error: malloc-c1 line %zu\n", line);
                break;       
            }
        }

        else if (contPalabras == 4){
            data[row].col3 = "0";
            data[row].col5 = "0";
            //Verifica que cada valor de la linea para las 6 columnas, tiene el formato
            //adecuado de char, tambien que los almacena en los chars antes creados
            if (sscanf (buf, "%1023s %1023s %1023s %1023s", 
                        c1, c2, c4, c6) != 4) {
                fprintf (stderr, "error: invalid format line %zu\n", line);
                continue;    //Continuar a la siguiente linea del archivo
            }

            //Asigna el valor de la columna de la linea actual del bufer a la estructura
            if (!(data[row].col1 = strdup (c1))) { //Valida la copia de c1 */
                fprintf (stderr, "error: malloc-c1 line %zu\n", line);
                break;       
            }
            if (!(data[row].col2 = strdup (c2))) { //Valida la copia de c2 */
                fprintf (stderr, "error: malloc-c1 line %zu\n", line);
                break;       
            }
            if (!(data[row].col4 = strdup (c4))) { //Valida la copia de c4 */
                fprintf (stderr, "error: malloc-c1 line %zu\n", line);
                break;       
            }
            if (!(data[row].col6 = strdup (c6))) { //Valida la copia de c6 */
                fprintf (stderr, "error: malloc-c1 line %zu\n", line);
                break;       
            }
        }

        else{

            if (sscanf (buf, "%1023s %1023s %1023s %1023s %1023s %1023s", 
                        c1, c2, c3, c4, c5, c6) != 6) {
                fprintf (stderr, "error: invalid format line %zu\n", line);
                continue;    //Continuar a la siguiente linea del archivo
            }

            //Asigna el valor de la columna de la linea actual del bufer a la estructura
            if (!(data[row].col1 = strdup (c1))) { //Valida la copia de c1 */
                fprintf (stderr, "error: malloc-c1 line %zu\n", line);
                break;       
            }
            if (!(data[row].col2 = strdup (c2))) { //Valida la copia de c2 */
                fprintf (stderr, "error: malloc-c1 line %zu\n", line);
                break;       
            }
            if (!(data[row].col3 = strdup (c3))) { //Valida la copia de c4 */
                fprintf (stderr, "error: malloc-c1 line %zu\n", line);
                break;       
            }
            if (!(data[row].col4 = strdup (c4))) { //Valida la copia de c4 */
                fprintf (stderr, "error: malloc-c1 line %zu\n", line);
                break;       
            }
            if (!(data[row].col5 = strdup (c5))) { //Valida la copia de c4 */
                fprintf (stderr, "error: malloc-c1 line %zu\n", line);
                break;       
            }
            if (!(data[row].col6 = strdup (c6))) { //Valida la copia de c6 */
                fprintf (stderr, "error: malloc-c1 line %zu\n", line);
                break;       
            }
        }
        row++;/* increment number of row pointers used */
    }

    // Printea los titulos de las columnas
    char *row1[] = {"Syscall", "Cantidad", "Porcentaje de Tiempo"};
    printf(GRN);
    printf("%*s | %*s | %*s\n", -15, row1[0], -15, row1[1], -15, row1[2]);
    // Printea las lineas de arriba de la tabla
    printf(CYN);
    printf("%*s | %*s | %*s\n", -15, "-----", -15, "-----", -15, "-----");
    printf(reset);
    

///////////////////////////////////////////////////////////////////////////
//             Imprime los valores de la tabla
///////////////////////////////////////////////////////////////////////////


    int con = 2; // Contador para empezar a imprimir las llamadas al sistema

	while (con!= row){ // Ejecutese siempre que contador sea diferente de row
        
        if(con == row-2){ // Printea las rayas del final
            printf(CYN);
            printf("%*s | %*s | %*s\n", -15, "-----", -15, "-----", -15, "-----");
            printf(reset);
            con++;
        }
        if(con == row -1){ // Printea la ultima linea
            //Cuando la columna de Error esta vacia, entonces el total de llamadas
            //se guarda en la columna 4
            if(data[con].col3 == "0"){
                printf(GRN);
                printf("%-15s | %-15s | %-15s\n", "Total",
                data[con].col4, "100.00");
                printf(reset);
                break;
            }
            else{
                printf(GRN);
                printf("%-15s | %-15s | %-15s\n", "Total",
                data[con].col3, "100.00");
                printf(reset);
                break;
            }
        }

        // Imprime todas las llamadas del sistema
        printf(YEL);
        printf("%-15s | %-15s | %-15s\n", data[con].col6,
            data[con].col4, data[con].col1);
        printf(reset);
    
        con = con + 1; // Se aumenta el contador
    }	

        return 0; // Sale de la ejecucion
}


// Funcion para verificar que existe el ejecutable
int checkIfFileExists(const char * filename)
{
    FILE *file;
    if (file = fopen(filename, "r"))
    {
        fclose(file);
        return 1;
    }
    return 0;
}

// Funcion que espera por una entrada en el teclado
void modoSeteo(int want_key) {
	static struct termios old, new;
	if (!want_key) {
		tcsetattr(STDIN_FILENO, TCSANOW, &old);
		return;
	}

	tcgetattr(STDIN_FILENO, &old);
	new = old;
	new.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &new);
}


// Funcion para saber que tecla se presiona por el teclado
int obtenerTecla()
{
	int f = 0;
	struct timeval tv;
	fd_set fs;
	tv.tv_usec = tv.tv_sec = 0;

	FD_ZERO(&fs);
	FD_SET(STDIN_FILENO, &fs);
	select(STDIN_FILENO + 1, &fs, 0, 0, &tv);

	if (FD_ISSET(STDIN_FILENO, &fs)) {
		f = getchar();
		modoSeteo(0);
	}
	return f;
}