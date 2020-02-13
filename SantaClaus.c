#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM 100
#define CUV 61

typedef struct
{
    char nume[CUV];   //numele orasului   
    char jucarie[CUV];   //numele jucariei
	int nr;    //numarul jucariilor
    char dir;   //directia
}Structura;

int interior (int x, int y, int N, int M) //verificam daca paraseste harta
{
   return x >= 0 && x < N && y >= 0 && y < M;
}


int main()
{

    Structura Oras[NUM][NUM]; //matricea cu structura regiunii Laponia
    Structura Rez[NUM]; // vector la structura regiunii Laponia 

    int N, M, startX, startY, nrPasi, copX, copY;
    scanf("%d %d", &N, &M);
    scanf("%d %d", &startX, &startY);
    copX = startX;
    copY = startY;

    scanf("%d", &nrPasi);

    int i, j;
    for (i = 0; i < N; i++)
        for (j = 0; j < M; j++)
        {
            scanf("%s ", Oras[i][j].nume);
            scanf("%s ", Oras[i][j].jucarie);
            scanf("%d ", &Oras[i][j].nr);
            scanf("%c", &Oras[i][j].dir);
        }

    int depasit = 0, pasiMos = 0, index = 0;

    for (i = 1; i < NUM; i++) Rez[i].nr = 0;
     //initializam campurile vectorului la numarul jucariilor cu 0

    if (Oras[startX][startY].nr)
    {    //verificam pentru punctul de start
        index++;
        Rez[index] = Oras[startX][startY];
        Rez[index].nr = 1;
        Oras[startX][startY].nr--;
    }

    while(nrPasi)
    {      //

        switch(Oras[startX][startY].dir)
        {  //ne deplasam pe harta verificand fiecare directie posibila
           
            case 'D': startX++; break;
            case 'U': startX--; break;
            case 'L': startY--; break;
            case 'R': startY++; break;
            default : break;
        }

        if( !interior(startX, startY, N, M)) { 
        	depasit = 1;  //verificam daca a parasit harta
            break; 
        }

        if (Oras[startX][startY].nr > 0)
        {  //verificam daca exista jucarii in regiunea respectiva
           
            index++;
            Oras[startX][startY].nr--;   //scadem cate o jucarie din regiune 
            Rez[index] = Oras[startX][startY];   //retinem tara si jucaria
            Rez[index].nr = 1;   //initializam numarul jucariilor la 1
        }
        pasiMos++;  //numaram pasii mosului
        nrPasi--;
    }

    Structura aux;   //variabila de tip structura  

     for (i = 1; i < index; i++)
        for (j = i+1; j <= index; j++)
        {
            if (strcmp(Rez[i].nume,Rez[j].nume) > 0)
            { //ordonam orasele in ordine lexicografica
               
                aux = Rez[i]; 
                Rez[i] = Rez[j];
                Rez[j] = aux;
            }
              else
            {  //daca au acelasi nume orasele(duplicatele), 
            	//ordonam dupa jucarii in ordine lexicografica
            	
              
                if (strcmp(Rez[i].nume,Rez[j].nume) == 0 && 
                	strcmp(Rez[i].jucarie,Rez[j].jucarie) > 0)
                {
                    aux = Rez[i];
                    Rez[i] = Rez[j];
                    Rez[j] = aux;
                }
            } 
        }


    int nrCadouri = 0;
    i = 1;
    while (i <= index)
    {  //verificam orasele consecutive identice din vector (ordonate lexicografic)
    	//stergem duplicatele (orasele identice cu aceleasi jucarii)
        
        if (strcmp(Rez[i].nume,Rez[i - 1].nume) == 0 &&
         strcmp(Rez[i].jucarie,Rez[i - 1].jucarie) == 0)
        {
            Rez[i - 1].nr += Rez[i].nr;  //adunam numarul jucariilor in primul
            for (j = i; j < index; j++)
                Rez[j] = Rez[j + 1];  //il stergem din vector pe cel in plus
            index--;
            i--;
        }
        i++;
    }

   for (i = 1; i <= index; i++)
        nrCadouri += Rez[i].nr;  //cadourile adunate in total

    for (i = 1; i < index; i++)
    {
        for (j = i+1; j <= index; j++)
        {
            if (strcmp(Rez[i].nume,Rez[j].nume) == 0)  
            {
                if (Rez[i].nr < Rez[j].nr)  
                {  //cadourile sunt ordonate descrescător după numărul de apariții
                   
                    aux = Rez[i];
                    Rez[i] = Rez[j];
                    Rez[j] = aux;
                }
                else
                {
                    if (Rez[i].nr == Rez[j].nr &&
                     strcmp(Rez[i].jucarie,Rez[j].jucarie) > 0){
                 //au același număr de apariții => se ordonează lexicografic jucariile 
                     
                        aux = Rez[i];
                        Rez[i] = Rez[j];
                        Rez[j] = aux;
                    }
                }
            }
        }
    }

    if(depasit){ //afisam mesajul in caz de parasire a hartii
        printf("TOO MUCH SNOW !\n");
    }
    
    printf("%d\n", pasiMos);

    if (pasiMos == 0)
    {
        if (Oras[copX][copY].nr > 0)
        {
            printf("%d\n", 1);  //aduna un singur cadou
            printf("%s:\n", Oras[copX][copY].nume);
            printf("  %d %s\n", Oras[copX][copY].nr, Oras[copX][copY].jucarie);
        }
        else
        {
            printf("0\n"); //nu exista cadou in regiune
        }
        return 0; //terminare executie
    }
    
    printf("%d\n", nrCadouri);
    strcpy(Rez[0].nume, ""); //initializam cu sirul NULL

    for (i = 1; i <= index; i++)
    {
        if(strcmp(Rez[i - 1].nume, Rez[i].nume) != 0)
        {
            printf("%s:\n", Rez[i].nume); 
            printf("  %d ", Rez[i].nr);
            printf("%s\n", Rez[i].jucarie);
        }
        else
        {
            printf("  %d " , Rez[i].nr);
            printf("%s\n", Rez[i].jucarie);
        }
    }

	return 0;
}
