#include<stdio.h>
#include<stdlib.h> 
#include<stdbool.h>
#include<string.h>
//               _______					 _______	 _______	|_______					
//	|\      |	|       |		|		|	|			|		|	|		|		|					|
//	| \     |	|       |		|		|	|			|		|	|				|					|
//	|  \    |	|       |		|		|	|_______	|_______|	|				|					|
//	|   \   |	|       |		|		|			|	|		|	|				|			 _______|
//	|    \  |	|       |		|		|			|	|		|	| 				|			|		|
//	|     \ |	|       |		|		|			|	|		|	|  				|			|		|
//	|      \|	|_______|		|_______|	 _______|	|		|	|   			|_______	|_______|


typedef struct Cancion{
	char * id;
	char * genero;
	char * autor;
	char * modo;
	int popularidad;
} Cancion;

int leer_archivo_g();
void leer_archivo_s();
void faltan_args();
Cancion crear_cancion(char*, char*, char*);
void liberar_cancion(Cancion);





Cancion * pp = NULL;

int main(int argc, char** argv)
{
	if (argc == 1){
		faltan_args();
		return 0;
	}
	int canciones;
	switch (argv[1][1]){
		case 103: //g
			printf("Genero\n");
			canciones = leer_archivo_g();
			printf("%s\n", pp[0].id);
			printf("%s\n", pp[1].id);
			printf("%s\n", pp[0].genero);
			printf("%s\n", pp[1].genero);
			break;


		case 112: //p
			printf("Modo\n");
			break;
	}

	for (int i=0;i<canciones;i++){
		liberar_cancion(pp[i]);
	}

	return 0;
}

void faltan_args(){
		printf("\nFaltan argumentos\n");
		printf("Para consultar generos musicales usar -g <Genero> <Popularidad>\n");
		printf("Donde popularidad es un numero entre 0 y 100 y se muestra los artistas con popularidad mayor a esta\n");
		printf("\nPara consultar canciones por modo usar -p <Modo>\n");
		printf("Donde modo puede ser Major o Minor\n");
}








Cancion crear_cancion(char * id ,char * autor, char * genero){
	Cancion can;
	can.id = malloc(sizeof(id));
	can.autor = malloc(sizeof(autor));
	can.genero = malloc(sizeof(genero));

	strcpy(can.id, id);
	strcpy(can.autor, autor);
	strcpy(can.genero, genero);

	return can;
}


void liberar_cancion(Cancion can){
		free(can.id);
		free(can.genero);
		free(can.autor);
		//free(can->modo);

}


int leer_archivo_g(){
	// Parte archivo
	FILE* archivo;

	archivo = fopen("genres.txt", "r");
	char *genero = malloc(20*sizeof(char));
	char *id = malloc(30*sizeof(char));
	char *autor = malloc(50*sizeof(char));

 	if (archivo == NULL) {
    		printf("No se pudo abrir el archivo, revise que esta en la carpeta correcta.\n");
    		return 0;
    	} 
    else {
  		int i=0;
  		while(!feof(archivo)){





  			pp = realloc(pp, (sizeof(pp)+sizeof(Cancion)));

 			fscanf(archivo, "%[^;];%[^;];%[^\n]", genero, id, autor);
 			// printf("%d\n", i);
 			// printf("%s\n", genero);
 			// printf("%s\n", id);
 			// printf("%s\n", autor);



 			pp[i] = crear_cancion(id, autor, genero);
 			i++;



			}
		
	printf("hola\n");

		
	fclose(archivo);
	return i;
	}
}


// void leer_archivo_s(){
// 	// Parte archivo
// 	FILE* archivo;
	
// 	archivo = fopen("songs.txt", "r");

 	
//  	if (archivo == NULL) {
//     		printf("No se pudo abrir el archivo, revise que esta en la carpeta correcta.\n");
//     	} 
//     else {
//   		int i=0;
//   		while(!feof(archivo)){








//  			i++;
// 			}
		
		
// 	fclose(archivo);

// 	}
// }