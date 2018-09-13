/**
    Developed by 
        Chrystian Melo
        Gabriel Siroco
        Samuel Henrique
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "libraryGraphs.h"

graph *createNewGraph() {
 
    graph *g;
 
    g = (struct graphs *) malloc(sizeof(struct graphs));
 
    g->vertex = 0;
    g->list = NULL;
 
    return g;
}

int createId(graph g){
    int bigger = 1;
    struct node *li;
    if (g.list != NULL){
        bigger = g.list[0]->id + 1;
        li = searchOnGraph(g, bigger,"Doesn't exist");
        while(li != NULL){//searching for the bigger id existent
            bigger++;
            li = searchOnGraph(g, bigger,"Doesn't exist");
        }
    }else
        printf("We're having troubles to use this graph because it is NULL!!\n");
        
    return bigger;
}

lists *insertList(lists info) {
    lists *newElement;
    lists helpList;
    
    newElement = (lists *) malloc(sizeof(lists));

    newElement->height_come  = info.height_come;
    newElement->height_go    = info.height_go;

    newElement->current_node = info.current_node;
    strcpy(newElement->name, info.name);
    
    newElement->next = NULL;
    
    return newElement;
}

void insertGraph(graph *g, viaduct v, int id){

    if (g->vertex == 0)  g->list = (struct node **) malloc (sizeof(struct node *));
    else                g->list = (struct node **) realloc(g->list, (g->vertex+1) * sizeof(struct node *));

    g->vertex++;

    g->list[g->vertex-1] = NULL;

    g->list[g->vertex-1] = insertList(v);

    g->list[g->vertex-1]->id = createId(*g); 

    return;
}

int checkCityOrViaduct(lists *l) {
    if(l->current_node == 1)  return 1; // if current_node < 0 == city
    else                      return 0;
}

int strcomp(char s1[], char s2[]){

    /*
    // Compares char with char
    if (strlen(s1) ==  1 && strlen(s2) == 1)
        if (s1 == s2) return 0;
    
    if (strlen(s1) > 1 && strlen(s2) > 1)
        return strcmp(s1, s2);

    return 1; */

    int i, j;
    int isEqual = 0;

    if(strlen(s1) != strlen(s2)) return 1;

    for(i = 0; i < (strlen(s1) >= strlen(s2)? strlen(s1) : strlen(s2)); i++)
        if(s1[i] != '\0' && s2[i] != '\0' && s1[i] != s2[i]) isEqual = 1;

    return isEqual;
}

int **fillMatrix(int tam) {
    int i, j;

    int **matrix = (int **) malloc(tam * sizeof(int *));

    for(i = 0; i < tam; i++) {
        matrix[i] = (int *) malloc(tam * sizeof(int));

        for(j = 0; j < tam; j++)
            matrix[i][j] = -1; // -1 = There'isnt element
    }

    return matrix;
}

void freeMatrix(int **matrix, int tam) {
    int i;

    for(i = 0; i < tam; i++)
        free(matrix[i]);

    free(matrix);

    return;
}

void linkNodesGraph(graph *g, int id){
    int i, j, checker = 1;
    char answ;
    lists *help, *otherHelp, *moreHelp;
    graph HelpGraph = *g;
    int **matriz = fillMatrix(g->vertex);

    if (id != 0){//link already exists -> ID != 0
        g = NULL;
        for(i = 0; i < g->vertex; i++){
            if (HelpGraph.list[i]->id == id)
                insertGraph(g, *g->list[i], id);//id== link
            else   
                insertGraph(g, *g->list[i], g->list[i]->next->id);//keep the same
        }
    }else{//First time putting links
        for(i = 0; i < g->vertex; i++) {
        	
        	help = g->list[i];
        	
        	// go to last element of the list
        	while(g->list[i]->next != NULL)
        		g->list[i] = g->list[i]->next;
        	
            if (checkCityOrViaduct(help)) {
                for(j = 0; j < g->vertex; j++) {
                
    				checker = 1;
    				
                	// Check if the current node exists already in the list
                	for(otherHelp = help; otherHelp != NULL; otherHelp = otherHelp->next)
                		if(!strcomp(HelpGraph.list[j]->name, otherHelp->name)) checker = 0;
                	
                	if(checker) {
    	                //city w/ city
    	                if (checkCityOrViaduct(HelpGraph.list[j]) && i != j && matriz[i][j] != 0){//city without equal name
    	                    printf("\n\tVocê quer linkar a cidade '%s' com  a cidade '%s' (s/n) : \n\n\t", help->name, HelpGraph.list[j]->name);
    	                    answ = getchar();
    	                    getchar();
    	 
    	                    if(answ == 's') {
                        
                                matriz[j][i] = 1;

                                moreHelp = g->list[j];

                                while(g->list[j]->next != NULL)
                                    g->list[j] = g->list[j]->next;

                                g->list[j]->next = insertList(*help);
                                g->list[j] = moreHelp;

    	                        g->list[i]->next = insertList(*HelpGraph.list[j]);
    	                        g->list[i] = g->list[i]->next;
    	                    } else matriz[j][i] = 0;
    	                }
    	 
    	                //city w/ viaduct
    	                else if (!checkCityOrViaduct(HelpGraph.list[j]) && i != j && matriz[i][j] != 0){//viaduct == 0
    	                    printf("\n\tVocê quer linkar a cidade '%s' com  o viaduto '%s' (s/n) : \n\n\t", help->name, HelpGraph.list[j]->name);
    	                    answ = getchar();
    	                    getchar();
    	 
    	                    if(answ == 's') {
                                moreHelp = g->list[j];

                                matriz[j][i] = 1;

                                while(g->list[j]->next != NULL)
                                    g->list[j] = g->list[j]->next;

                                g->list[j]->next = insertList(*help);
                                g->list[j] = moreHelp;
    	                        g->list[i]->next = insertList(*HelpGraph.list[j]);
    	                        g->list[i] = g->list[i]->next;
    	                    } else matriz[j][i] = 0;
    	                }
    	            }
                }
     
                printf("\n\n");
            } else {
     
                //viaduct w/ viaduct
                for(j = 0; j < g->vertex; j++) {
    				checker = 1;
    				
                	// Check if the current node exists already in the list
                	for(otherHelp = help; otherHelp != NULL; otherHelp = otherHelp->next)
                		if(!strcomp(HelpGraph.list[j]->name, otherHelp->name)) checker = 0;
                	
                	if(checker) {

    	                if ((!checkCityOrViaduct(HelpGraph.list[j])) && i != j && matriz[i][j] != 0){//viaduct
    	                    printf("\n\tVocê quer linkar o viaduto '%s' com  o viaduto '%s' (s/n) : \n\n\t", help->name, HelpGraph.list[j]->name);
    	                    answ = getchar();
    	                    getchar();
    	 
    	                    if(answ == 's') {
                                moreHelp = g->list[j];

                                matriz[j][i] = 1;

                                while(g->list[j]->next != NULL)
                                    g->list[j] = g->list[j]->next;

                                g->list[j]->next = insertList(*help);
                                g->list[j] = moreHelp;
    	                        g->list[i]->next = insertList(*HelpGraph.list[j]);
    	                        g->list[i] = g->list[i]->next;
    	                    } else matriz[j][i] = 0;
    	                }
    	 
    	                //city w/ viaduct
    	                else if (checkCityOrViaduct(HelpGraph.list[j]) && i != j && matriz[i][j] != 0){//city
    	                    printf("\n\tVocê quer linkar o viaduto '%s' com  a cidade '%s' (s/n) : \n\n\t", help->name, HelpGraph.list[j]->name);
    	                    answ = getchar();
    	                    getchar();

    	                    if(answ == 's') {
                                moreHelp = g->list[j];

                                matriz[j][i] = 1;

                                while(g->list[j]->next != NULL)
                                    g->list[j] = g->list[j]->next;

                                g->list[j]->next = insertList(*help);
                                g->list[j] = moreHelp;
    	                        g->list[i]->next = insertList(*HelpGraph.list[j]);
    	                        g->list[i] = g->list[i]->next;
    	                    } else matriz[j][i] = 0;
    	                }
                	}
                }
     
            }
     
            printf("\n\n");
     
            g->list[i] = help;
        }
    }

    freeMatrix(matriz, g->vertex);
}

void printGraph(graph *g){

    int i;
	struct node *helpList;

    if (g->list == NULL) {

        printf("\a\n\tO Grafo está vazio\n");

        return;
    }

	printf("\n");

    for(i = 0; i < g->vertex; i++) {

        if(g->list[i] != NULL) {
            printf("%s ->", g->list[i]->name);

            for(helpList = g->list[i]->next; helpList != NULL; helpList = helpList->next)
                printf(" %s ", helpList->name);
            
            printf("\n");
        }
    }

    return;
}

viaduct writeNodesGraph(){
 

    viaduct v;
    char c;
    int lenght_string;
 
    printf("\n\n\tO nó que será inserido é viaduto ou cidade? (v/c)\n\n\tDigite : ");
    scanf("%c",&c);
    getchar();
 
    if(c == 'v') {
 
        printf("\n\tAltura do viaduto na ida: ");
        scanf ("%i", &v.height_go);
        getchar();

        printf("\tAltura do viaduto na volta: ");
        scanf ("%i", &v.height_come);
        getchar();
 
        printf("\n\tNome do viaduto: ");
        fgets(v.name, 100, stdin);
    
        //remove \n and insert \0
        lenght_string = strlen(v.name);
        v.name[lenght_string-1] = '\0';
 
        v.current_node = 0;
         
    } else {

        printf("\n\tNome da cidade: ");
        fgets(v.name, 100, stdin);
 
        //remove \n and insert \0
        lenght_string = strlen(v.name);
        v.name[lenght_string-1] = '\0';
 
        v.current_node = 1;

        v.height_go = 2000000;
        v.height_come = 2000000;
    }
 

    return v;
}

void freeGraph(graph *g){
	
	int i;
	struct node *helpList;

    if (g->list == NULL) return;

    for(i = 0; i < g->vertex; i++) {
        for(; g->list[i] != NULL; g->list[i] = g->list[i]->next) {
        	helpList = g->list[i];
            free(helpList);
            helpList = NULL;
        }
    }

    free(g->list);
	free(g);

    return;
}

lists *searchOnGraph(graph g, int id, char name[100]){

    if(g.list == NULL){

        printf("\n\tO Programa não tem nenhuma cidade nem viaduto\n");
        return NULL;
    }

    int i;

    if(id != -1) {

        for (i = 0; i < g.vertex; i++)
            if(id == g.list[i]->id) return g.list[i];

    } else {

        for (i = 0; i < g.vertex; i++)
            if(!strcomp(g.list[i]->name, name)) return g.list[i];

    }

    return NULL;

}

int otherSearch(graph g, int id, char name[100]){

    if(g.list == NULL){

        printf("\n\tO Programa não tem nenhuma cidade nem viaduto\n");

        return -1;
    }

    int i;

    if(id != -1) {

        for (i = 0; i < g.vertex; i++)
            if(id == g.list[i]->id) return i;

    } else {

        for (i = 0; i < g.vertex; i++)
            if(!strcomp(g.list[i]->name, name)) return i;

    }

    return -1;

}

void removeGraph(graph *g, char name[], char otherName[], int choice) {
    if(g == NULL) return;
 
    graph l;
    int i, position;
    struct node *help;
    struct node *otherHelp;
    struct node *moreHelp;
    struct node *previousNode = NULL;
  
    help = searchOnGraph(*g, -1, name);

    if(help == NULL) return;

    if(choice == 1) {

        // Search the adjacents nodes
        for(i = 0; i < g->vertex; i++) {
             
            previousNode = NULL;
     
            for(otherHelp = g->list[i]->next; otherHelp != NULL; otherHelp = otherHelp->next) {

                if(!strcomp(otherHelp->name, help->name)) {
                    if(previousNode == NULL) g->list[i]->next   = otherHelp->next;
                    else                     previousNode->next = otherHelp->next;
     
                    free(otherHelp);
                    otherHelp = NULL;
     
                    break;
                }

                previousNode = otherHelp;
            }
        }

        position = otherSearch(*g, -1, help->name);

        for(otherHelp = g->list[position]->next; otherHelp != NULL; otherHelp = otherHelp->next) {
            previousNode = otherHelp;
            free(previousNode);
        }

        free(help);

        g->list[position] = NULL;

        for(i = position; i < g->vertex; i++)
            g->list[i] = g->list[i+1];
            
        g->vertex--;

    } else {

        moreHelp = searchOnGraph(*g, -1, otherName);

        if(choice == 2) {

           // Search the adjacents nodes
            for(i = 0; i < g->vertex; i++) {

                if(!strcomp(g->list[i]->name, name)) {

                    previousNode = NULL;

                    for(otherHelp = g->list[i]->next; otherHelp != NULL; otherHelp = otherHelp->next) {
                        if(!strcomp(otherHelp->name, moreHelp->name)) {

                            if(previousNode == NULL) g->list[i]->next   = otherHelp->next;
                            else                     previousNode->next = otherHelp->next;
             
                            free(otherHelp);
                            otherHelp = NULL;

                            return;
                        }

                        previousNode = otherHelp;
                    }
                }
            }

        } else if(choice == 3) {

            for(i = 0; i < g->vertex; i++) {

                if(!strcomp(g->list[i]->name, otherName)) {

                    previousNode = NULL;

                    for(otherHelp = g->list[i]->next; otherHelp != NULL; otherHelp = otherHelp->next) {
                        if(!strcomp(otherHelp->name, help->name)) {

                            if(previousNode == NULL) g->list[i]->next   = otherHelp->next;
                            else                     previousNode->next = otherHelp->next;
             
                            free(otherHelp);
                            otherHelp = NULL;

                            return;
                        }

                        previousNode = otherHelp;
                    }
                }
            }
        }
    }

    return;
}

int check_open_node(int *exp, int tam){
    int i;

    for(i = 0; i < tam; i++){
        if(exp[i]== 0){
            return 1;
        }

    }

    return -1;
}

void update_path(int *p, int *d, int current, int pred, int peso_aresta){
    if(d[current] > (peso_aresta + d[pred])){
        d[current] = peso_aresta + d[pred];
        p[current] = pred;
    }
}

int minDistance(int *exp, int *d, int tam){
    int i;

    for(i = 0; i < tam; i++){
        if(exp[i]==0){
            break;
        }
    }
    if(i == tam){
        return -1;
    }
    int menor = i;
    for(i = menor +1; i < tam; i++){
        if(exp[i]==0 && (d[menor] > d[i])){
            menor = i;
        }
    }
    return menor;
}

void dijkstra(graph *gf, int part, int dest, int height_load){

    int i,u, count;
    int *path;

    //cria o vetor de distancias
    int *d = (int *)malloc(gf->vertex*sizeof(int));

    //cria o vetor de precedentes
    int *p = (int*)malloc(gf->vertex*sizeof(int));

    //cria vetor para indicar se o no foi visitado ou nao
    int *exp = (int*)calloc(gf->vertex,sizeof(int));

    path = (int *)malloc(gf->vertex*sizeof(int));

    for(i = 0; i < gf->vertex; i++){
        d[i] = INT_MAX;
        p[i] = -1;
    }

    d[part] = 0;

    lists *adj;

    while(check_open_node(exp,gf->vertex)!=-1){

        int u = minDistance(exp, d,gf->vertex);
        exp[u] = 1;

        if(height_load > 0) {
            if(gf->list[u]->height_go >= height_load) {

                adj = (lists*)malloc(sizeof(lists));

                adj = gf->list[u]->next;

                count = 0;
                while(adj != NULL){
                    count++;

                    // if(height_load > 0) {
                        if(adj->height_go >= height_load) {
                            update_path(p, d, otherSearch(*gf, -1, adj->name), u, count);
                        }

                    // } else
                        // if(adj->height_come >= (height_load * -1)) update_path(p, d, otherSearch(*gf, -1, adj->name), u, count);

                    adj = adj->next;

                }
            }
        } else {
            if(gf->list[u]->height_come >= (height_load * -1)) {

                adj = (lists*)malloc(sizeof(lists));

                adj = gf->list[u]->next;

                count = 0;
                while(adj != NULL){
                    count++;

                    // if(height_load > 0) {
                        // if(adj->height_go >= height_load) {
                            // update_path(p, d, otherSearch(*gf, -1, adj->name), u, count);
                        // }

                    // } else
                        if(adj->height_come >= (height_load * -1)) update_path(p, d, otherSearch(*gf, -1, adj->name), u, count);

                    adj = adj->next;

                }

            }
        }
    }
    free(adj);

    printf("\n\nOs caminhos de %s a %s: \n\n\t", gf->list[part]->name, gf->list[dest]->name);
    count = 0;
    path[count] = dest;

    for(i = dest; i != part;){
        count++;
        i = p[i];
        path[count] = i;
        
        if(path[count] == -1) {
            printf("\n\n\tNenhum caminho encontrado!!!\n\n\n");
            return;
        }
    }

    for(i = count; i > -1; i--)
        printf("%s ", gf->list[path[i]]->name);

    printf("\n");

    free(path);
    free(exp);
    free(d);
    free(p);

}

//file

/*
    City:
    id
    Name
    Current_node//doesnt appear
    next(#id)

    Viaduct:
    id
    Name
    Current
    height go
    height come
    next(#id)

*/

int findLineOnFile(FILE *arq, int n) {
    int i;
    char help[100];
    int line = 0;

    arq = fopen("Dados.txt", "r");

    for(i = 0; i < n; i++)
        fgets(help, 100, arq);

    fclose(arq);
    return atoi(help);
}

int returnID(graph gr,char name[]) {
    int i;

    for(i = 0; i < gr.vertex; i++)
        if(!strcomp(name, gr.list[i]->name)) return gr.list[i]->id;

    return 0;
}

void graph_to_file(graph gr){
    FILE *arq;
    arq = fopen("Dados.txt", "wt"); 
    int i;
    int result;

    lists* next;
 
    if (arq == NULL) // Se nào conseguiu criar
    {
     printf("Problemas na CRIACAO do arquivo\n");
     return;
    }
    for(int count = 0; count < (gr.vertex); count++){
        fprintf(arq,"%i\n", gr.list[count]->current_node);//first line refer to what it is: 1 - city 0 - viaduct 
        if(checkCityOrViaduct(gr.list[count])){//city
            
            result = fprintf(arq,"%i\n",gr.list[count]->id);
            // printf("%i\n",gr.list[count]->id);                       
            if (result == EOF) printf("Erro na Gravacao00\n");
            
            result = fprintf(arq,"%s\n",gr.list[count]->name);
            // printf("%s\n",gr.list[count]->name);
            if (result == EOF) printf("Erro na Gravacao01\n");

            result = fprintf(arq,"%i\n",gr.list[count]->height_go);                      
            if (result == EOF) printf("Erro na Gravacao13\n");

            result = fprintf(arq,"%i\n",gr.list[count]->height_come);                      
            if (result == EOF) printf("Erro na Gravacao14\n");
            
           if (gr.list[count]->next ==  NULL) {//Does not exists link
                result = fprintf(arq,"#%i\n",0);//next = #id
                // printf("#%i\n",0);
            } else{
                next = gr.list[count]->next;
                while(next != NULL){//exists link 
                    result = fprintf(arq,"#%i\n",returnID(gr,next->name));//next = #id
                    // printf("#%i\n",returnID(gr,next->name));
                    removeGraph(&gr, next->name, gr.list[count]->name, 3);//remover adjacencia para ler a proxima
                    next = gr.list[count]->next;
                }
            }
            if (result == EOF) printf("Erro na GravacaoID\n");

        }else {//viaduct
            result = fprintf(arq,"%i\n",gr.list[count]->id);                       
            if (result == EOF) printf("Erro na Gravacao10\n");

            result = fprintf(arq,"%s\n",gr.list[count]->name);
            if (result == EOF) printf("Erro na Gravacao11\n");

            result = fprintf(arq,"%i\n",gr.list[count]->height_go);                      
            if (result == EOF) printf("Erro na Gravacao13\n");

            result = fprintf(arq,"%i\n",gr.list[count]->height_come);                      
            if (result == EOF) printf("Erro na Gravacao14\n");

            if (gr.list[count]->next == NULL)//Does not exists link == 0
                result = fprintf(arq,"#%i\n",0);//next = #id
            else{
                next = gr.list[count]->next;
                while(next != NULL){//exists link == 1 
                    result = fprintf(arq,"#%i\n",returnID(gr,next->name));//next = #id  
                    removeGraph(&gr, next->name, gr.list[count]->name, 3);//remover adjacencia para ler a proxima
                    next = gr.list[count]->next;
                }
            }
            if (result == EOF) printf("Erro na GravacaoID\n");
        }
    }

    // scanf("%i", &i);

    fclose(arq);
}

void printMatrix(int **matrix, int tam) {
    int i, j;

    for(i = 0; i < tam; i++) {
        for(j = 0; j < tam; j++) {
            printf(" %i ", matrix[i][j]);
        }

        printf("\n");
    }
}

void speciaLink(graph *g, int current_node, int link_node) {

    if(link_node == -1) return;

    lists *help;

    // Go to the last element
    for(help = g->list[current_node]; g->list[current_node]->next != NULL; g->list[current_node] = g->list[current_node]->next);

    g->list[current_node]->next = insertList(*g->list[link_node]);

    g->list[current_node] = help;

    return;
}

int specialSearch(graph g, int id){

    if(g.list == NULL) return -1;

    int i;

    for (i = 0; i < g.vertex; i++)
        if(id == g.list[i]->id) return i;

    return -1;

}

void file_to_graph(graph *gr){
    FILE *arq, *bak;
    arq = fopen("Dados.txt", "r"); 

    int element=1, result, link, choice;
    int i, j;

    lists errors;

    char wordLink[10] = "INEXISTENT", cpy[10];

    viaduct vi, aux;
    
    int option;//1= city 0 - viaduct

    choice = 1;

    int **matrix;

    result = fscanf(arq,"%i",&vi.current_node);//first line refer to what it is: 1 - city /0 - viaduct
    option = vi.current_node;

    while(!feof(arq)){
        element++;
        if (result == EOF) printf("Erro na Leitura0\n");
        if(vi.current_node){//city
            result = fscanf(arq, "%i", &vi.id);//id

            if (result == EOF) printf("Erro na Leitura01\n");
            result = fscanf(arq, "%s", vi.name);//name

            if (result == EOF) printf("Erro na Leitura02\n");

            result = fscanf(arq,"%i\n",&vi.height_go);                      
            if (result == EOF) printf("Erro na Leitura14\n");

            result = fscanf(arq,"%i\n",&vi.height_come);                      
            if (result == EOF) printf("Erro na Leitura15\n");

            do {//still being a link
                result = fscanf(arq, "%s", wordLink);//name
                if (result == EOF) break;//end of wordlink
            }while(wordLink[0] == '#');

            vi.current_node = atoi(wordLink);

        }else{ //beggining of viaduct
            result = fscanf(arq, "%i", &vi.id);                        
            if (result == EOF) printf("Erro na Leitura11\n");

            result = fscanf(arq, "%s", vi.name);                        
            if (result == EOF) printf("Erro na Leitura12\n");

            result = fscanf(arq,"%i\n",&vi.height_go);                      
            if (result == EOF) printf("Erro na Leitura14\n");

            result = fscanf(arq,"%i\n",&vi.height_come);                      
            if (result == EOF) printf("Erro na Leitura15\n");

            do {//still being a link
                result = fscanf(arq, "%s", wordLink);//name
                if (result == EOF) break;//end of wordlink
            }while(wordLink[0] == '#');

            vi.current_node = atoi(wordLink);
        }
        insertGraph(gr,vi,0);
    }

    matrix = fillMatrix(gr->vertex);

    fclose(arq);

    // Start linking nodes
    arq = fopen("Dados.txt", "r"); //open again
    
    i = 0;

    result = fscanf(arq,"%i",&vi.current_node);//first line refer to what it is: 1 - city /0 - viaduct

    while(!feof(arq)){ 
        if (result == EOF) printf("Erro na Leitura0\n");
        if(vi.current_node){//city
            result = fscanf(arq, "%i", &vi.id);//id
            if (result == EOF) printf("Erro na Leitura01\n");
            result = fscanf(arq, "%s", vi.name);//name

            result = fscanf(arq,"%i\n",&vi.height_go);                      
            if (result == EOF) printf("Erro na Leitura14\n");

            result = fscanf(arq,"%i\n",&vi.height_come);                      
            if (result == EOF) printf("Erro na Leitura15\n");

            if (result == EOF) printf("Erro na Leitura02\n");
            result = fscanf(arq, "%s", wordLink);//link     
            if (result == EOF) printf("Erro na Leitura03\n");
            j = 0;
            while(wordLink[0] == '#'){//still being a link

                wordLink[0] = '0';
                matrix[i][j] = atoi(wordLink);

                result = fscanf(arq, "%s", wordLink);
                if(result == EOF) break;
                j++;
            }

            vi.current_node = atoi(wordLink);

        }else{ //beggining of viaduct
            result = fscanf(arq, "%i", &vi.id);                        
            if (result == EOF) printf("Erro na Leitura11\n");

            result = fscanf(arq, "%s", vi.name);                        
            if (result == EOF) printf("Erro na Leitura12\n");

            result = fscanf(arq,"%i\n",&vi.height_go);                      
            if (result == EOF) printf("Erro na Leitura14\n");

            result = fscanf(arq,"%i\n",&vi.height_come);                      
            if (result == EOF) printf("Erro na Leitura15\n");
            result = fscanf(arq, "%s", wordLink);//name 
            if (result == EOF) printf("Erro na Leitura03\n");     
            j = 0;
            while(wordLink[0] == '#'){//still being a link

                wordLink[0] = '0';
                matrix[i][j] = atoi(wordLink);

                result = fscanf(arq, "%s", wordLink);
                if(result == EOF) break;
                j++;
            }

            vi.current_node = atoi(wordLink);
        }
        i++;
    }

    for(i = 0; i < gr->vertex; i++) {
        for(j = 0; j < gr->vertex; j++) {
            if(matrix[i][j] != -1) speciaLink(gr, i, specialSearch(*gr, matrix[i][j]));
        }
    }

    freeMatrix(matrix, gr->vertex);

    if (arq = NULL) gr = createNewGraph();

}
 
//file
