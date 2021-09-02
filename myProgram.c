#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>

#define ARRSZ   2   /* use 8 or more, set to 2 here to force realloc */
#define MAXC 1024

// Estructura para la tabla
typedef struct {
    char *col1, *col2, *col3, *col4, *col5, *col6;
} mydata_t;


int checkIfFileExists(const char *filename);
void modoSeteo(int want_key);
int obtenerTecla();

int main(int argc, char *argv[]){

    char *vector[5] = {"Hola","Victor","Viento","en","Popa"};

    for (int i = 0; i < argc; i++){
        ///printf("Argumento %d %s \n", i, argv[i]);
    }
    char *a1 = argv[0];
    char *a2 = argv[1];
    char *a3 = argv[2];
    char *a4 = argv[3];




    if(checkIfFileExists(a2)){
        printf("El archivo existe\n");

////////////////////////////////////////////
// Automatico
////////////////////////////////////////////
///////////// Todo, automatico, sin filtros
        if ((argc == 4) && (!strcmp( a3, "-a")) &&  (!strcmp( a4, "-0"))){
            printf("Automatico - Sin filtrado \n");
        }

        else if((argc == 3) && (!strcmp( a3, "-a"))){
            printf("Automatico \n");
        }

        else if((argc == 2)){
            printf("Automatico \n");
        }
///////////// Todo, automatico, procesos
        else if((argc == 4) && (!strcmp( a3, "-a")) &&  (!strcmp( a4, "-1"))){
            printf("Automatico - Filtrado de procesos \n");
        }
///////////// Todo, automatico, memoria
        else if((argc == 4) && (!strcmp( a3, "-a")) &&  (!strcmp( a4, "-2"))){
            printf("Automatico - Filtrado de mapeo de  memoria \n");
        }

////////////////////////////////////////////
// Interactivos
////////////////////////////////////////////
///////////// Interactivo, sin filtro
        else if((argc == 4) && (!strcmp( a3, "-A")) &&  (!strcmp( a4, "-0"))){
            printf("Interactivo - Sin filtrado \n");
        }
///////////// Interactivo, procesos
        else if((argc == 4) && (!strcmp( a3, "-A")) &&  (!strcmp( a4, "-1"))){
            printf("Interactivo - Filtrado de procesos \n");
        }
///////////// Interactivo, memoria
        else if((argc == 4) && (!strcmp( a3, "-A")) &&  (!strcmp( a4, "-2"))){
            printf("Interactivo - Filtrado de mapeo de memoria \n");
        }
///////////// Interactivo, sin filtro
        else if((argc == 3) && (!strcmp( a3, "-A"))){
            printf("Automatico \n");
        }

        else{
            printf("Ingrese un comando valido, los modos son: \n");
            printf("Automatico (-a) e interactivo (-A) \n");
            printf("Y los filtros son: sin filtro (-0) \n");
            printf("filtro de procesos (-1) y filtro de memoria (-2) \n");
        }
    }

    else if(!checkIfFileExists(a2)){
        printf("No existe el ejecutable escrito \n");
    }

    else{
        printf("Error, ingrese un comando valido \n");
    }

///////Terminan las validaciones///////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////// Read File 


char buf[MAXC];
    size_t arrsz = ARRSZ, line = 0, row = 0;
    mydata_t *data = NULL;
    /* use filename provided as 1st argument (stdin by default) */
    FILE *fp = fopen ("trace2.txt", "r");

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
        char c1[MAXC], c2[MAXC], c3[MAXC], c4[MAXC], c5[MAXC], c6[MAXC];  /* temp strings for c1,2,5 */
        size_t len = strlen (buf);          /* length for validation */

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

        /* parse buf into fields, handle error on invalid format of line */
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
        row++;      /* increment number of row pointers used */
    }
    if (fp != stdin)    /* close file if not stdin */
        fclose (fp);

    puts ("values stored in struct\n");
   // for (size_t i = 0; i < row; i++)
   //     printf ("%-10s %-10s %-10s\n", data[i].col1, data[i].col4, data[i].col6);


////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////// Tecla Enter ////////////////////////

    int f;
    int con = 1;

	// Se ejecuta siempre
	while(1) {
		modoSeteo(1);
		while (!(f = obtenerTecla())) usleep(10);
		
        if(con!= row){
            if (f == 10){ // Tecla enter -> 10
                /// printf("vector %s\n", vector[con]);
                printf ("%-10s %-10s %-10s\n", data[con].col6, data[con].col4, data[con].col1);
            }
        
            con = con + 1;
        }	

        else{
            return 0;
        }
	}



    return 0;

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
