#include <stdio.h>
#include <string.h>

#define NOMBRE_ARCHIVO "texto.txt"
#define LONGITUD_MAXIMA_CADENA 1000

int main(void)
{
    FILE *archivo = fopen(NOMBRE_ARCHIVO, "r"); // Modo lectura
    char bufer[LONGITUD_MAXIMA_CADENA];         // Aquí vamos a ir almacenando cada línea
    while (fgets(bufer, LONGITUD_MAXIMA_CADENA, archivo))
    {
        // Aquí, justo ahora, tenemos ya la línea. Le vamos a remover el salto
        strtok(bufer, "\n");

////////////////////////// Extrae o que se necesita para el archivo de salida

    char delimitador[] = " ";
    char *vector[5];
    char *token = strtok(bufer, delimitador); // Separo el texto por espacios
    int con = 0;		
		
    if (token != NULL){
		// Ciclo para separar el texto
    	while(token != NULL){
		vector[con] =token; 
		token = strtok(NULL, delimitador);		
		con++;
	}	
    }
    char *needle = vector[4]; // 
    char *primera = vector[2]; //


    printf("%s\n", needle); 

/////////////////////////
///////// Linea comentada
        //printf("La línea es: '%s'\n", bufer);
    }
 




    return 0;
}
