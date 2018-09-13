#include "libraryGraphs.h"
#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define setacod 27
#define setacima 65
#define setabaixo 66
#define enter 10
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_RESET   "\x1b[0m"

void menu (int state){

	system("date");

	switch(state) {
		case 0:

		    printf("\n\n");
		    printf("\tBem Vindo ao Safe Getway Corporation (SGC)\n\n");
		    printf(ANSI_COLOR_RED "\t\t->  Inserir  \n" ANSI_COLOR_RESET);
		    printf("\t\t  Conectar  \n");
		    printf("\t\t  Remover  \n");
		    printf("\t\t  Buscar  \n");
		    printf("\t\t  Imprimir  \n");
		    printf("\t\t  Sair  \n");

			break;
		case 1:

		    printf("\n\n");
		    printf("\tBem Vindo ao Safe Getway Corporation (SGC)\n\n");
		    printf("\t\t  Inserir  \n");
		    printf(ANSI_COLOR_RED "\t\t->  Conectar  \n" ANSI_COLOR_RESET);
		    printf("\t\t  Remover  \n");
		    printf("\t\t  Buscar  \n");
		    printf("\t\t  Imprimir  \n");
		    printf("\t\t  Sair  \n");

			break;
		case 2:

		    printf("\n\n");
		    printf("\tBem Vindo ao Safe Getway Corporation (SGC)\n\n");
		    printf("\t\t  Inserir  \n");
		    printf("\t\t  Conectar  \n");
		    printf(ANSI_COLOR_RED "\t\t->  Remover  \n" ANSI_COLOR_RESET);
		    printf("\t\t  Buscar  \n");
		    printf("\t\t  Imprimir  \n");
		    printf("\t\t  Sair  \n");

			break;
		case 3:

		    printf("\n\n");
		    printf("\tBem Vindo ao Safe Getway Corporation (SGC)\n\n");
		    printf("\t\t  Inserir  \n");
		    printf("\t\t  Conectar  \n");
		    printf("\t\t  Remover  \n");
		    printf(ANSI_COLOR_RED "\t\t->  Buscar  \n" ANSI_COLOR_RESET);
		    printf("\t\t  Imprimir  \n");
		    printf("\t\t  Sair  \n");

			break;
		case 4:

		    printf("\n\n");
		    printf("\tBem Vindo ao Safe Getway Corporation (SGC)\n\n");
		    printf("\t\t  Inserir  \n");
		    printf("\t\t  Conectar  \n");
		    printf("\t\t  Remover  \n");
		    printf("\t\t  Buscar  \n");
		    printf(ANSI_COLOR_RED "\t\t->  Imprimir  \n" ANSI_COLOR_RESET);
		    printf("\t\t  Sair  \n");

			break;
		case 5:

		    printf("\n\n");
		    printf("\tBem Vindo ao Safe Getway Corporation (SGC)\n\n");
		    printf("\t\t  Inserir  \n");
		    printf("\t\t  Conectar  \n");
		    printf("\t\t  Remover  \n");
		    printf("\t\t  Buscar  \n");
		    printf("\t\t  Imprimir  \n");
		    printf(ANSI_COLOR_RED "\t\t->  Sair  \n" ANSI_COLOR_RESET);

			break;
	}

}


static struct termios old, new;

/* Initialize new terminal i/o settings */
void initTermios(int echo) 
{
  tcgetattr(0, &old); /* grab old terminal i/o settings */
  new = old; /* make new settings same as old settings */
  new.c_lflag &= ~ICANON; /* disable buffered i/o */
  if (echo) {
      new.c_lflag |= ECHO; /* set echo mode */
  } else {
      new.c_lflag &= ~ECHO; /* set no echo mode */
  }
  tcsetattr(0, TCSANOW, &new); /* use these new terminal i/o settings now */
}

/* Restore old terminal i/o settings */
void resetTermios(void) 
{
  tcsetattr(0, TCSANOW, &old);
}

/* Read 1 character - echo defines echo mode */
char getch_(int echo) 
{
  char ch;
  initTermios(echo);
  ch = getchar();
  resetTermios();
  return ch;
}

char getch() {
  return getch_(0);
}

int getrow(){
	char c;
	c=getch();
	if (c == setacod){
		c=getch();
		c=getch();
	}
	return c;
}

int cfileexists(const char * filename){
    /* try to open file to read */
    FILE *file;
    if (file = fopen(filename, "r")){
        fclose(file);
        return 1;
    }
    return 0;
}

int main() {
	
	int row, state = 0;
	FILE *fp;
	graph *g;

	g = createNewGraph();
	if (cfileexists("Dados.txt")) file_to_graph(g);
	
	int choice = -1, id, height_load;
	int isViaduct, choose;
	char c = 's',f,name[100], character = 's', otherName[100];

	lists *sad;

	system("clear");
	printf(ANSI_COLOR_RED"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\tPARA UMA MELHOR ULTILIZAÇÃO DO NOSSO PROGRAMA SUGERIMOS QUE VOCE EXEXUTE O PROGRAMA EM TELA MAXIMIZADA!!"ANSI_COLOR_RESET);
   	printf("\n\t\t\t\t\t\t\t\t\t\t\tDigite alguma tecla!!");
	getch();
	system("clear");
	system("cat AsciiArt/logo.txt");
	getchar();
	system("clear");

	while(1) {

		system("clear");

		menu(state);
		row = getrow();

		switch(row) {
			case setabaixo:

				state++;

				if(state > 5) state = 0;

				break;
			case setacima:

				state--;

				if(state < 0) state = 5;

				break;

			case enter:

				switch(state) {
					case 0:

						c = 's';

						while(c == 's') {

							system("clear");

							insertGraph(g, writeNodesGraph(),0);

							printf("\n\tQuer inserir mais nós? (s/n) ");
							scanf("%c",&c);
							getchar();

						}

					break;

					case 1:

						system("clear");

						linkNodesGraph(g, 0);

					break;
				
					case 2:

						system("clear");

						printf("\n\tDigite o nome do viaduto/cidade: ");
						fgets (name, 100, stdin);
						name[strlen(name)-1] = '\0';

						printf("\n\tDeseja deletar o nó(1) as adjacências dele com outros(2) ou as adjacencias dos outros com eles (3)? : ");
						scanf ("%i", &choose);
						getchar();
						
						if(choose != 1) {

							character = 's';

							while(character == 's') {

								system("clear");

								printGraph(g);

								if(choose == 3) printf("\n\tDigite o nome do viaduto/cidade que faz aresta com %s: ", name);
								else			printf("\n\tDigite o nome do viaduto/cidade que tem aresta com %s: ", name);
								
								fgets (otherName, 100, stdin);
								name[strlen(otherName)-1] = '\0';

								removeGraph(g, name, otherName, choose);

								printGraph(g);

								printf("\n\tDeseja remover mais alguma coisa? (s/n): ");
								character = getchar(); getchar();
							}

						} else removeGraph(g, name, otherName, choose);


					break;
				
					case 3:

						system("clear");

						printf("\n\tDeseja buscar o menor caminho(1) ou algum dado(2)?: ");
						scanf ("%i", &choose);
						getchar();

						if(choose == 2) {
							printf("\n\tDeseja buscar por id ou nome (i/n) : ");
							scanf("%c",&f);
							getchar();

							id = -1;

							if(f == 'i'){

								printf("\n\tDigite o identificador : ");
								scanf("%i",&id);
								getchar();
								//name = "paranaue";
			 
							}else if(f == 'n'){

								printf("\n\tDigite o nome : ");
								fgets(name,100,stdin);
								name[strlen(name)-1] = '\0';
								id = -1;


							}

							sad = searchOnGraph(*g,id,name);

							if(sad != NULL){

								if (sad->current_node){

									printf("\n\tO que você pesquisou é uma cidade\n");
									printf("\n\tNome : %s\n", sad->name);
									printf("\tId : %i\n", sad->id);
									printf("\tCurrent_node: %i\n", sad->current_node);

								} else {

									printf("\n\tO que você pesquisou é um viatuto\n");
									printf("\n\tNome : %s\n", sad->name);
									printf("\tAltura de ida : %i\n",sad->height_go);
									printf("\tAltura de volta : %i\n",sad->height_come);

								}

							} else printf("\n\t Nada encontrado!");
						} else if(choose == 1) {
							printGraph(g);

							printf("\n\tDigite o nome da(s) cidade(s)/viaduto(s)\n");
							fgets(name, 100, stdin);
							name[strlen(name)-1] = '\0';

							fgets(otherName, 100, stdin);
							otherName[strlen(otherName)-1] = '\0';

							printf("\n\tDigite a altura da carga: ");
							scanf ("%i", &height_load);
							getchar();

							if(searchOnGraph(*g, -1, name)->id > searchOnGraph(*g, -1, otherName)->id) height_load *=-1;

							dijkstra(g, otherSearch(*g, -1, name), otherSearch(*g, -1, otherName), height_load);
						}

						printf("\n\nDigite enter para continuar .  .  .   ");

						getchar();

					break;

					case 4:

						system("clear");

						printGraph(g);

						printf("\n\tDigite enter para continuar .  .  .   ");

						getchar();


					break;

					case 5:

						system("clear");
						
						printf("\n\n\t\tObrigado por utilizar o nosso programa\n\n\n");
						
						if (g->vertex != 0) graph_to_file(*g);//anything to write?

						freeGraph(g);

						system("clear");
						system("cat AsciiArt/créditos.txt");
						getchar();
						system("clear");

						return 0;

					break;
				}

			break;
		}

	}
}
