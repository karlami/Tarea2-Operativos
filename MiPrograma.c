#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <time.h>


#define ARRSZ   2   /* use 8 or more, set to 2 here to force realloc */
#define MAXC 1024

//////// COLORES /////
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define YEL "\e[0;33m"
#define BLU "\e[0;34m"
#define MAG "\e[0;35m"
#define CYN "\e[0;36m"
#define WHT "\e[0;37m"
//Reset de los colores
#define reset "\e[0m"

// Estructura para la tabla
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
            printf("Automatico - Filtrado de mapeo de  memoria \n");
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



    char buf[MAXC];
    size_t arrsz = ARRSZ, line = 0, row = 0;
    mydata_t *data = NULL;
    /* use filename provided as 1st argument (stdin by default) */
    FILE *fp = fopen ("trace2.txt", "r") ;

    if (!fp) {  /* validate file open for reading */
        perror ("file open failed");
        return 1;
    }

    /* allocate an 'arrsz' initial number of struct */
    if (!(data = malloc (arrsz * sizeof *data))) {
        perror ("malloc-data");
        return 1;
    }

    while (fgets (buf, MAXC, fp)) {         /* read each line from file */
        char c1[MAXC], c2[MAXC], c3[MAXC], c4[MAXC], c5[MAXC], c6[MAXC];  /* temp stringssize_t len = strlen (buf);sscanf C blank value for c1,2,5 */
        size_t len = strlen (buf);          /* length for validation */
        int i, contPalabras = 1;
        for(i = 0; i < strlen(buf); i++)
            if(buf[i] == ' ' && i > 0 && buf[i - 1] != ' ')
            contPalabras++;
        line++;     /* increment line count */

        /* validate line fit in buffer */
        if (len && buf[len-1] != '\n' && len == MAXC - 1) {
            fprintf (stderr, "error: line %zu exceeds MAXC chars.\n", line);
            return 1;
        }

        if (row == arrsz) { /* check if all pointers used */
            void *tmp = realloc (data, arrsz * 2 * sizeof *data);
            if (!tmp) {     /* validate realloc succeeded */
                perror ("realloc-data");
                break;      /* break, don't exit, data still valid */
            }
            data = tmp;     /* assign realloc'ed block to data */
            arrsz *= 2;     /* update arrsz to reflect new allocation */
        }
        if(contPalabras == 5){
            data[row].col5 = "0";
            /* parse buf into fields, handle error on invalid format of line */
            if (sscanf (buf, "%1023s %1023s %1023s %1023s %1023s", 
                        c1, c2, c3, c4, c6) != 5) {
                fprintf (stderr, "error: invalid format line %zu\n", line);
                continue;   /* get next line */
            }

            /* allocate copy strings, assign allocated blocks to pointers */
            if (!(data[row].col1 = strdup (c1))) { /* validate copy of c1 */
                fprintf (stderr, "error: malloc-c1 line %zu\n", line);
                break;      /* same reason to break not exit */
            }
            if (!(data[row].col2 = strdup (c2))) { /* validate copy of c2 */
                fprintf (stderr, "error: malloc-c1 line %zu\n", line);
                break;      /* same reason to break not exit */
            }
            if (!(data[row].col3 = strdup (c3))) { /* validate copy of c4 */
                fprintf (stderr, "error: malloc-c1 line %zu\n", line);
                break;      /* same reason to break not exit */
            }
            if (!(data[row].col4 = strdup (c4))) { /* validate copy of c4 */
                fprintf (stderr, "error: malloc-c1 line %zu\n", line);
                break;      /* same reason to break not exit */
            }
            if (!(data[row].col6 = strdup (c6))) { /* validate copy of c6 */
                fprintf (stderr, "error: malloc-c1 line %zu\n", line);
                break;      /* same reason to break not exit */
            }
                    /* increment number of row pointers used */
        }
        else{

            if (sscanf (buf, "%1023s %1023s %1023s %1023s %1023s %1023s", 
                        c1, c2, c3, c4, c5, c6) != 6) {
                fprintf (stderr, "error: invalid format line %zu\n", line);
                continue;   /* get next line */
            }

            /* allocate copy strings, assign allocated blocks to pointers */
            if (!(data[row].col1 = strdup (c1))) { /* validate copy of c1 */
                fprintf (stderr, "error: malloc-c1 line %zu\n", line);
                break;      /* same reason to break not exit */
            }
            if (!(data[row].col2 = strdup (c2))) { /* validate copy of c2 */
                fprintf (stderr, "error: malloc-c1 line %zu\n", line);
                break;      /* same reason to break not exit */
            }
            if (!(data[row].col3 = strdup (c3))) { /* validate copy of c4 */
                fprintf (stderr, "error: malloc-c1 line %zu\n", line);
                break;      /* same reason to break not exit */
            }
            if (!(data[row].col4 = strdup (c4))) { /* validate copy of c4 */
                fprintf (stderr, "error: malloc-c1 line %zu\n", line);
                break;      /* same reason to break not exit */
            }
            if (!(data[row].col5 = strdup (c5))) { /* validate copy of c4 */
                fprintf (stderr, "error: malloc-c1 line %zu\n", line);
                break;      /* same reason to break not exit */
            }
            if (!(data[row].col6 = strdup (c6))) { /* validate copy of c6 */
                fprintf (stderr, "error: malloc-c1 line %zu\n", line);
                break;      /* same reason to break not exit */
            }
                    /* increment number of row pointers used */
        }
        row++;
    }
    if (fp != stdin)    /* close file if not stdin */
        fclose (fp);
    

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
                    printf(GRN);
                    printf("%-15s | %-15s | %-15s\n", "Total",
                    data[con].col3, "100.00");
                    printf(reset);
                    break;
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



    char buf[MAXC];
    size_t arrsz = ARRSZ, line = 0, row = 0;
    mydata_t *data = NULL;
    /* use filename provided as 1st argument (stdin by default) */
    FILE *fp = fopen ("trace2.txt", "r") ;

    if (!fp) {  /* validate file open for reading */
        perror ("file open failed");
        return 1;
    }

    /* allocate an 'arrsz' initial number of struct */
    if (!(data = malloc (arrsz * sizeof *data))) {
        perror ("malloc-data");
        return 1;
    }

    while (fgets (buf, MAXC, fp)) {         /* read each line from file */
        char c1[MAXC], c2[MAXC], c3[MAXC], c4[MAXC], c5[MAXC], c6[MAXC];  /* temp stringssize_t len = strlen (buf);sscanf C blank value for c1,2,5 */
        size_t len = strlen (buf);          /* length for validation */
        int i, contPalabras = 1;
        for(i = 0; i < strlen(buf); i++)
            if(buf[i] == ' ' && i > 0 && buf[i - 1] != ' ')
            contPalabras++;
        line++;     /* increment line count */

        /* validate line fit in buffer */
        if (len && buf[len-1] != '\n' && len == MAXC - 1) {
            fprintf (stderr, "error: line %zu exceeds MAXC chars.\n", line);
            return 1;
        }

        if (row == arrsz) { /* check if all pointers used */
            void *tmp = realloc (data, arrsz * 2 * sizeof *data);
            if (!tmp) {     /* validate realloc succeeded */
                perror ("realloc-data");
                break;      /* break, don't exit, data still valid */
            }
            data = tmp;     /* assign realloc'ed block to data */
            arrsz *= 2;     /* update arrsz to reflect new allocation */
        }
        if(contPalabras == 5){
            data[row].col5 = "0";
            /* parse buf into fields, handle error on invalid format of line */
            if (sscanf (buf, "%1023s %1023s %1023s %1023s %1023s", 
                        c1, c2, c3, c4, c6) != 5) {
                fprintf (stderr, "error: invalid format line %zu\n", line);
                continue;   /* get next line */
            }

            /* allocate copy strings, assign allocated blocks to pointers */
            if (!(data[row].col1 = strdup (c1))) { /* validate copy of c1 */
                fprintf (stderr, "error: malloc-c1 line %zu\n", line);
                break;      /* same reason to break not exit */
            }
            if (!(data[row].col2 = strdup (c2))) { /* validate copy of c2 */
                fprintf (stderr, "error: malloc-c1 line %zu\n", line);
                break;      /* same reason to break not exit */
            }
            if (!(data[row].col3 = strdup (c3))) { /* validate copy of c4 */
                fprintf (stderr, "error: malloc-c1 line %zu\n", line);
                break;      /* same reason to break not exit */
            }
            if (!(data[row].col4 = strdup (c4))) { /* validate copy of c4 */
                fprintf (stderr, "error: malloc-c1 line %zu\n", line);
                break;      /* same reason to break not exit */
            }
            if (!(data[row].col6 = strdup (c6))) { /* validate copy of c6 */
                fprintf (stderr, "error: malloc-c1 line %zu\n", line);
                break;      /* same reason to break not exit */
            }
                    /* increment number of row pointers used */
        }
        else{

            if (sscanf (buf, "%1023s %1023s %1023s %1023s %1023s %1023s", 
                        c1, c2, c3, c4, c5, c6) != 6) {
                fprintf (stderr, "error: invalid format line %zu\n", line);
                continue;   /* get next line */
            }

            /* allocate copy strings, assign allocated blocks to pointers */
            if (!(data[row].col1 = strdup (c1))) { /* validate copy of c1 */
                fprintf (stderr, "error: malloc-c1 line %zu\n", line);
                break;      /* same reason to break not exit */
            }
            if (!(data[row].col2 = strdup (c2))) { /* validate copy of c2 */
                fprintf (stderr, "error: malloc-c1 line %zu\n", line);
                break;      /* same reason to break not exit */
            }
            if (!(data[row].col3 = strdup (c3))) { /* validate copy of c4 */
                fprintf (stderr, "error: malloc-c1 line %zu\n", line);
                break;      /* same reason to break not exit */
            }
            if (!(data[row].col4 = strdup (c4))) { /* validate copy of c4 */
                fprintf (stderr, "error: malloc-c1 line %zu\n", line);
                break;      /* same reason to break not exit */
            }
            if (!(data[row].col5 = strdup (c5))) { /* validate copy of c4 */
                fprintf (stderr, "error: malloc-c1 line %zu\n", line);
                break;      /* same reason to break not exit */
            }
            if (!(data[row].col6 = strdup (c6))) { /* validate copy of c6 */
                fprintf (stderr, "error: malloc-c1 line %zu\n", line);
                break;      /* same reason to break not exit */
            }
                    /* increment number of row pointers used */
        }
        row++;
    }
    if (fp != stdin)    /* close file if not stdin */
        fclose (fp);
    

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
            printf(GRN);
            printf("%-15s | %-15s | %-15s\n", "Total",
            data[con].col3, "100.00");
            printf(reset);
            break;
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
