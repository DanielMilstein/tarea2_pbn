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
void leer_archivo_s(int);
void faltan_args();
Cancion* crear_cancion(char*, char*, char*);
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

			leer_archivo_s(canciones);
			printf("%s\n", pp[2000].id);
			printf("%s\n", pp[1000].id);
			printf("%s\n", pp[2000].genero);
			printf("%s\n", pp[1000].genero);
			printf("%s\n", pp[2000].autor);
			printf("%s\n", pp[1000].autor);
			printf("%s\n", pp[2000].modo);
			printf("%s\n", pp[1000].modo);
			printf("%d\n", pp[2000].popularidad);
			printf("%d\n", pp[1000].popularidad);
			break;


		case 112: //p
			printf("Modo\n");
			break;
	}

	for (int i=0;i<canciones;i++){

		free(pp[i].id);
		free(pp[i].genero);
		free(pp[i].autor);
		free(pp[i].modo);

	}
	free(pp);

	return 0;
}

void faltan_args(){
		printf("\nFaltan argumentos\n");
		printf("Para consultar generos musicales usar -g <Genero> <Popularidad>\n");
		printf("Donde popularidad es un numero entre 0 y 100 y se muestra los artistas con popularidad mayor a esta\n");
		printf("\nPara consultar canciones por modo usar -p <Modo>\n");
		printf("Donde modo puede ser Major o Minor\n");
}








// Cancion crear_cancion(char * id ,char * autor, char * genero){
// 	can.id = malloc(sizeof(id));
// 	can.autor = malloc(sizeof(autor));
// 	can.genero = malloc(sizeof(genero));

// 	strcpy(can.id, id);
// 	strcpy(can.autor, autor);
// 	strcpy(can.genero, genero);

// 	return can;
// }




int leer_archivo_g(){
	// Parte archivo
	FILE* archivo;

	archivo = fopen("genres.txt", "r");


 	if (archivo == NULL) {
    		printf("No se pudo abrir el archivo, revise que esta en la carpeta correcta.\n");
    		return 0;
    	} 
    else {
  		int i=0;
  		while(!feof(archivo)){

  			pp = realloc(pp, ((i+1)*sizeof(Cancion)));
  			pp[i].genero = malloc(20*sizeof(char));
  			pp[i].id = malloc(30*sizeof(char));
  			pp[i].autor = malloc(50*sizeof(char));
  			pp[i].modo = malloc(7*sizeof(char));

 			fscanf(archivo, "%[^;];%[^;];%[^\n]", pp[i].genero, pp[i].id, pp[i].autor);

 			i++;



		}


	fclose(archivo);
	return i;
	}
}


void leer_archivo_s(int x){
	// Parte archivo
	FILE* archivo;
	
	archivo = fopen("songs.txt", "r");

 	
 	if (archivo == NULL) {
    		printf("No se pudo abrir el archivo, revise que esta en la carpeta correcta.\n");
    	} 
    else {
  		int i=0;
  		while(!feof(archivo)){
  			char* pop = malloc(4*sizeof(char));
  			char* id = malloc(30*sizeof(char));
  			char* modo = malloc(7*sizeof(char));



  			fscanf(archivo, "%[^;];%[^;];%[^\n]", id, pop, modo);
  			// printf("%s\n", id);
  			// printf("%s\n", pop);
  			// printf("%s\n", modo);


  			for (int k=0;k<x;k++){
  				if ((strcmp(pp[k].id,id))==0){
  					pp[k].popularidad = atoi(pop);
  					strcpy(pp[k].modo, modo);
  					printf("%d", pp[k].popularidad);
  					break;
  				}
  			}

  			free(pop);
  			free(id);
  			free(modo);
 			i++;
			}
		
		
	fclose(archivo);

	}
}