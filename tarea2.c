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
//Repositorio: https://github.com/DanielMilstein/tarea2_pbn

typedef struct Cancion{
	char * id;
	char * genero;
	char * autor;
	char * modo;
	int popularidad;
} Cancion;

typedef struct Artista{
	char * genero;
	char * nombre;
	int q_canciones;
	int suma_pop;
	float popularidad;
} Artista;



int leer_archivo_g();
void leer_archivo_s(int);
void faltan_args();
Cancion* crear_cancion(char*, char*, char*);
void liberar_cancion(Cancion);
void swap(int, int);
void Sort(int*, int);
int compare_pop(const void *p1, const void *p2);
int compare_modo(const void *p1, const void *p2);
int crear_artistas(Cancion*, int, char*);
int array_genero(Cancion*, int);
void pop_art(int);
int bin_search(float, float, int);




char** generos = NULL;
Artista * artistas = NULL;
Cancion * pp = NULL;

int main(int argc, char** argv)
{
	int canciones;
	int gens;
	int as;
	if (argc == 1){
		faltan_args();
		return 0;
	}


	switch (argv[1][1]){
		case 103: //g
			printf("Genero %s\n", argv[2]);
			canciones = leer_archivo_g();
			leer_archivo_s(canciones);
			as = crear_artistas(pp, canciones, argv[2]);
			pop_art(as);
			qsort(artistas, as, sizeof(Artista), compare_pop);


			int desde = bin_search(0, as, atoi(argv[3]));


			for (int i = desde; i<as; i++)
			{	
				printf("%s: ", artistas[i].nombre);
				printf("%.2f\n", artistas[i].popularidad);
			}


			break;


		case 112: //p
			printf("Modo %s\n", argv[2]);
			canciones = leer_archivo_g();
			leer_archivo_s(canciones);
			gens = array_genero(pp, canciones);
			// argv[2] es el modo
			for (int i=0;i<gens;i++){
				int can_x_gen = 0;

				for (int k=0;k<canciones;k++){
					if (strcmp(pp[k].modo, argv[2])==0){
						if (strcmp(pp[k].genero, generos[i])==0) can_x_gen+=1;
					}
				}
				printf("%s: %d\n", generos[i], can_x_gen);

			}
			break;
	}

	for (int i=0;i<canciones;i++){

		free(pp[i].id);
		free(pp[i].genero);
		free(pp[i].autor);
		free(pp[i].modo);

	}

	// for (int p=0; p<as; p++)
	// {
	// 	free(artistas[p].genero);
	// 	free(artistas[p].nombre);
	// }

	free(generos);
	free(pp);
	free(artistas);

	return 0;
}

void faltan_args(){
		printf("\nFaltan argumentos\n");
		printf("Para consultar generos musicales usar -g <Genero> <Popularidad>\n");
		printf("Donde popularidad es un numero entre 0 y 100 y se muestra los artistas con popularidad mayor a esta\n");
		printf("\nPara consultar canciones por modo usar -p <Modo>\n");
		printf("Donde modo puede ser Major o Minor\n");
}




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

 			fscanf(archivo, "%[^;];%[^;];%[^\n]\n", pp[i].genero, pp[i].id, pp[i].autor);

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

  			fscanf(archivo, "%[^;];%[^;];%[^\n]\n", id, pop, modo);

  			for (int k=0;k<x;k++){
  				if ((strcmp(pp[k].id,id))==0){

  					pp[k].popularidad = atoi(pop);
  					strcpy(pp[k].modo, modo);
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

int compare_pop(const void *p1, const void *p2)
{
	const Artista *a1 = p1;    
	const Artista *a2 = p2;

	if (a1->popularidad < a2->popularidad)
		return -1;
	else if (a1->popularidad > a2->popularidad)
		return 1;
	else
		return 0;
}


int compare_modo(const void *p1, const void *p2)
{
	const Cancion *c1 = p1;    
	const Cancion *c2 = p2;
	if (strcmp(c1->modo, "Minor")==0 && strcmp(c2->modo, "Major")==0)
		return -1;
	else if (strcmp(c1->modo, "Major")==0 && strcmp(c2->modo, "Minor")==0)
		return 1;
	else
		return 0;
}


int array_genero(Cancion * songs, int n_canciones){
	int n_generos = 0;
	for (int i=0; i<n_canciones;i++){
		if (i==0){
			generos = realloc(generos, (20*sizeof(char)));
			generos[0] = songs[i].genero;
			n_generos++;
			continue;
		}
		int f = 1;
		for (int k=0; k<n_generos; k++){
			if (strcmp(songs[i].genero, generos[k])==0){
				f = 0;
				break;
			}
		}

		if (f){
			generos = realloc(generos, n_generos* (20*sizeof(char)));
			generos[n_generos] = songs[i].genero;
			n_generos++;
		}
	}
	return n_generos;
}


int crear_artistas(Cancion* pp, int l_pp, char* genero){
	int q_artistas = 0;
	for (int i=0;i<l_pp;i++){
		if (!strcmp(pp[i].genero, genero)){
			if (artistas == NULL){
				artistas = realloc(artistas, sizeof(Artista));

				artistas[q_artistas].genero = malloc(20*sizeof(char));
	  			artistas[q_artistas].nombre = malloc(30*sizeof(char));

				artistas[q_artistas].genero = pp[i].genero;
				artistas[q_artistas].nombre = pp[i].autor;

				artistas[q_artistas].q_canciones = 1;
				artistas[q_artistas].suma_pop = pp[i].popularidad;
				q_artistas++;

			}
			else{
				int existe = 0;
				int indice = 0;
				for (int k = 0; k < q_artistas; k++)
				{
					if (strcmp(artistas[k].nombre, pp[i].autor)==0){
						existe = 1;
						indice = k;
					}
				}

				if (existe){
					artistas[indice].q_canciones +=1;
					artistas[indice].suma_pop += pp[i].popularidad;

				}
				else {

					artistas = realloc(artistas,q_artistas*4 * sizeof(Artista));

					artistas[q_artistas].genero = malloc(20*sizeof(char));
		  			artistas[q_artistas].nombre = malloc(30*sizeof(char));

					artistas[q_artistas].genero = pp[i].genero;
					artistas[q_artistas].nombre = pp[i].autor;
					artistas[q_artistas].q_canciones = 1;
					artistas[q_artistas].suma_pop = pp[i].popularidad;
					q_artistas++;
				}


			}

		}

	}

	return q_artistas;
}

void pop_art(int x){
	for (int i = 0; i < x; i++)
	{
		artistas[i].popularidad = (float)artistas[i].suma_pop/(float)artistas[i].q_canciones;
	}

}

int bin_search(float min, float max, int limite){
	int pivot = (min+max)/2;
	if (artistas[pivot].popularidad < limite){
		min = pivot;
		return bin_search(min, max, limite);
	}
	if (artistas[pivot].popularidad > limite){
		max = pivot;
		return bin_search(min, max, limite);
	}
	if (artistas[pivot].popularidad == limite){
		return pivot;
	}
	return pivot;
}