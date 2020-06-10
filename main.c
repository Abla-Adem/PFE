/*rendre en fonction tous les ajout a la liste des sous chaine
 continuer la parralelisation de coupoure
 rendre en fonction le traitement de la premiere boucle paralele*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>
#include <time.h>
typedef struct LC LC;
struct LC{
    int x;
    LC* s;
};
typedef struct Liste Liste;
struct Liste
{
    LC *premier;
};


typedef char* ch[200];
void init(int tab[],int fin){
#pragma omp parallel for
    for (int j = 0; j <fin ; ++j) {
        tab[j]=-1;
    }
}
void getAlphabet(int alphabet[],int taille,char* alpha){
    char t;
    char* test;


    alpha[0]=' ';
    int indice=1;
    int total=0;
    int tempo;
    for (int n = 0; n <258 ; ++n) {
        if (alphabet[n]!=0)
        {

            tempo=alphabet[n];
            alphabet[n]=total;
            total=total+tempo;
            t=n;

            alpha[indice]=t;

            indice++;


        }
    }
}
void extratcSstar(char* btw,Liste* s_etoile_tab[],char* schaine[],int nbr,int nbr_thread,int position[])
{

    int etoile=0;
    int debut;

    int indice=0;
    int positionindice=0;

    for (int l = 0; l <nbr_thread ; ++l) {

        LC *temp=s_etoile_tab[l]->premier;

        while (temp!=NULL)
        {
            printf("ici %i",l);
            if (etoile==0)
            {

                debut=temp->x;
                etoile=1;
            } else
            {
                int taille=((temp->x-debut))+1;
                schaine[indice]=malloc(sizeof(char)*(taille+2));
                strncpy(schaine[indice],btw+debut,taille);
                char test=0;
                if (schaine[indice][taille] !=test ) {
                    printf("\n rah %s\n",schaine[indice]);
                    schaine[indice][taille] = 0;
                }

                printf("\n %s \n",schaine[indice]);

                printf("\n taille %i %i %i %i",taille,debut,strlen(btw),strlen(schaine[indice]));
                position[positionindice]=debut;
                positionindice++;
                debut=temp->x;

                printf("\n %s \n",schaine[indice]);
                indice=indice+1;
                printf("ici");


            }
            temp=temp->s;

        }


    }



    schaine[indice]=malloc(sizeof((strlen(btw)-debut+2)));

    strncpy(schaine[indice],btw+debut,(strlen(btw)-debut)+1);

    position[positionindice]=debut;

}
void addsubstring(int j,int fin,Liste* s_etoile_tab[],int direction)
{

    int existedeja=0;
    LC *pointeur=s_etoile_tab[j]->premier;
    int test=0;
    LC *nouveau = malloc(sizeof(LC)+1);
    if(direction==0) {
        if (pointeur != NULL) {

            while (pointeur->s != NULL) {

                test = 1;

                pointeur = pointeur->s;

            }


            nouveau->s = NULL;
            nouveau->x = fin;
            pointeur->s = nouveau;


        } else {


            nouveau->s = NULL;

            nouveau->x = fin;
            s_etoile_tab[j]->premier = nouveau;

        }
    } else
    {
        if (pointeur != NULL) {




            nouveau->s = pointeur;
            nouveau->x = fin;
            pointeur->s = NULL;
            s_etoile_tab[j]->premier = nouveau;


        } else {


            nouveau->s = NULL;

            nouveau->x = fin;
            s_etoile_tab[j]->premier = nouveau;

        }
    }
}
int cornercase(char* btw,int alphabet[],int variable[],Liste* s_etoile_tab[],int tab[],int f,int coupoure[],int j){


    int reusefonction=0;
    int fin = f * (j);
    int temporaire = btw[fin];
    if (alphabet[temporaire] == 0) {
        variable[0]++;
    }
    alphabet[temporaire]++;

    if(btw[fin]>btw[fin+1])
    {

        tab[fin]=0;
    } else if (btw[fin]<btw[fin+1])
    {

        if(tab[fin-1]==0)
        {
            printf("\nici %i %i %i\n",j,tab[fin-1],fin-1);
            addsubstring(omp_get_thread_num(),fin,s_etoile_tab,0);

            tab[fin]=2;
            variable[1]++;
            printf("\n ici 0 \n");
        }
        else if(tab[fin-1]==-1)
        {

            tab[fin]=1;
            reusefonction=fin;
        }
        else
        {

            tab[fin]=1;

        }
    } else {
        if (j == 0) {

            if(tab[fin+1]==1){
                addsubstring(j, fin, s_etoile_tab,0);
                tab[fin] = 2;
                variable[1]++;
                printf("\n ici 1 \n");
            }
            else if(tab[fin+1]==2)
            {
                tab[fin]=1;
            }
            else if(tab[fin+1]==0){
                tab[fin]=0;
            } else{
                coupoure[j] = fin;
            }

        }

        else
            {
            if (tab[fin + 1] == 1 & tab[fin - 1] == 0) {
                printf("zebi");
                addsubstring(j, fin, s_etoile_tab,0);

                tab[fin] = 2;
                variable[1]++;
            } else if (tab[fin + 1] == -1 ) {


                coupoure[j] = fin;
            } else {
                tab[fin] = tab[fin + 1];
            }

        }

    }
    if(tab[fin+1]==1 & tab[fin]==0)
    {

        addsubstring(j, fin + 1, s_etoile_tab,0);

        tab[fin+1]=2;
        variable[1]++;
        printf("\n  ici 3 \n");
    }
    return reusefonction;
}
void maincase(char* btw,int alphabet[],int variable[],Liste* s_etoile_tab[],int tab[],int f,int coupoure[],int j,int nbr_thread,int taille,int barsup){
    int flash;
    int nonajout=0;

        barsup=f*(j+1);

    if(coupoure[j]!=-1)
    {
        if(j!=(nbr_thread-1))
        {

            if(coupoure[j+1]==f*(j+1))
            {
                flash=tab[coupoure[j+1]];
                while(flash==-1)
                {
                    flash=tab[coupoure[j+1]];


                #pragma omp flush(flash)
                }




            }

            for (int i = coupoure[j]; i <barsup ; ++i) {
                //printf(" \nlabas %i %i %i\n",j,tab[f*(j+1) ],i);
                if(tab[f*(j+1) ]==2){

                    tab[i]=1;
                    nonajout=1;
                }
                else {
                    tab[i] = tab[f * (j + 1)];
                }
                }
            if(coupoure[j]>0){
                if (tab[coupoure[j]]==1 & tab[coupoure[j]-1]==0 && nonajout==0)
                {

                    addsubstring(j, coupoure[j], s_etoile_tab,0);

                    tab[coupoure[j]]=2;
                    variable[1]++;
                    printf("zebi 2");

                }
            }



        } else{
            for (int i = coupoure[j]; i <taille ; ++i) {
                tab[i]=0;
            }
        }
    }

}

int traitementpar(int debut,int fin,char* btw,int alphabet[],int tab[],int variable[],int egal,int temporaire,int d,Liste* s_etoile_tab[],int j)
{   int coup=0;


for (int i = fin-1; i > debut-1; --i) {

        temporaire=btw[i];
        if(alphabet[temporaire]==0)
        {
            variable[0]++;
        }
        alphabet[temporaire]++;
        if (btw[i] > btw[i + 1]) {
            tab[i] = 0;

            if(tab[i+1]==1  )
            {

                addsubstring(d, i+1, s_etoile_tab,1);

                variable[1]++;

                tab[i+1]=2;
            }
            //printf("traite %i ",i);
        } else if (btw[i] < btw[i + 1]) {
            tab[i] = 1;



        } else{

            if(i==fin-1){
                coup=1;
                egal=i;
            } else if (coup==1 && egal==(i+1))
            {
                if(btw[i]==btw[egal]){

                    egal=i;
                }

            }

            else
            {
                if(tab[i+1]==2)
                {
                  //  printf("traite %i",i);
                    tab[i]=1;
                } else
                {

                    tab[i]=tab[i+1];
                }
            }
        }



    }

    return egal;
}

void tychar(char* btw,Liste* s_etoile_tab[],int tab[],int alphabet[],int variable[],int nrb_thread) {


    int coupoure[nrb_thread];
    variable[0] = 0;
    variable[1] = 0;
    int f;
    f = strlen(btw) / nrb_thread;

    printf("\n");
    init(coupoure, nrb_thread);
    init(tab, strlen(btw));

    if (nrb_thread*2>strlen(btw)) {

        for (int i = 0; i <nrb_thread ; ++i) {
            printf("peut etre ici %i %i \n",i,nrb_thread);
            s_etoile_tab[i] = malloc(sizeof(Liste)+1);
            s_etoile_tab[i]->premier = NULL;
        }

        int temp;
        int egl=100;
        traitementpar(0, strlen(btw), btw, alphabet, tab, variable, egl, temp, 0,
                      s_etoile_tab, 0);
        printf(" fini?");
    } else {



#pragma omp parallel num_threads(nrb_thread)
    {

        int premier = 0;
        LC *pointeur = malloc(sizeof(LC)+1);
        pointeur->s = NULL;
        LC *precedent;
        int f, d, egal;
        egal = 100;
        int init = 0;
        int temporaire;
        f = strlen(btw) / nrb_thread;
        d = omp_get_thread_num();

        s_etoile_tab[d] = malloc(sizeof(Liste)+1);
        s_etoile_tab[d]->premier = NULL;

        if (d == (nrb_thread - 1)) {
            egal = traitementpar(f * d + 1, strlen(btw), btw, alphabet, tab, variable, egal, temporaire, d,
                                 s_etoile_tab, d);

        } else {

            egal = traitementpar(f * d + 1, f * (d + 1), btw, alphabet, tab, variable, egal, temporaire, d,
                                 s_etoile_tab, d);

        }
        if (egal != 100) {
            coupoure[d] = egal;
        }


/*
        #pragma omp master
        {
        printf(" \ntab \n");
        for (int i = 0; i <strlen(btw) ; ++i) {
            printf("%i ",tab[i]);
        }
        printf(" \ntab \n");
    }
    */
    }
    int nbrstop[nrb_thread];
#pragma omp parallel for num_threads(nrb_thread)
    for (int j = 0; j < nrb_thread; ++j) {
        nbrstop[j] = cornercase(btw, alphabet, variable, s_etoile_tab, tab, f, coupoure, j);
    }


#pragma omp parallel for num_threads(nrb_thread)
    for (int j = 0; j < nrb_thread; ++j) {
        maincase(btw, alphabet, variable, s_etoile_tab, tab, f, coupoure, j, nrb_thread, strlen(btw), nbrstop[j]);
    }
}


            /*
        if (reusefonction==1)
        {

            reusefonction=cornercase(btw,alphabet,variable,s_etoile_tab,tab,f,coupoure,d);
        }
        */


    /*

    #pragma omp parallel for
    for (int i = 0; i < nrb_thread; ++i) {
    }
    */






    printf(" \ntab fin \n");
    for (int i = 0; i <strlen(btw) ; ++i) {
        printf("%i ",tab[i]);
    }


}
//a optimiser
int getname(int tab[],int taille, char* t[],char* name)
{
    int unique=1;
    int stop,indice,egal,boucle;
    printf("\n%i tab indice getname \n",taille);
    for (int i = 0; i <taille ; ++i) {
        printf("%i ",tab[i]);

    }
    char sch;
    int precedent=1;
    name[tab[0]]=1;
    if(taille==1){
    name[1]=0;
    name[2]=0;
    }
    for (int m = 1; m <taille ; ++m) {

        int indice=strlen(t[m])-1;
        if(indice==(strlen(t[m-1])-1))
        {int egal=1;


            while (indice>0 & egal==1)
            {
                if(t[m][indice]!=t[m-1][indice])
                {
                    egal=0;
                }
                indice--;
            }
            if (egal==1)
            {name[tab[m]]=precedent;
            unique=0;
                }
            else{
                precedent=m+1;
                name[tab[m]]=m+1;
                }

        } else{
            precedent=m+1;
            name[tab[m]]=(m+1);

        }

    }
    for (int j = taille; j <strlen(name) ; ++j) {
        name [j]=0;

    }
    printf("name %s %i %i",name,strlen(name),taille);
    return unique;
}

int radix(char* t[],char* alphabet,int taille,int position[],char* name)
{
    int tab[taille];
    int tp[taille];
    char *s;
    char *c;
    int borne_inferieur;
    char u=' ';
    int compteurtabbleau,position_char;
    borne_inferieur=u;
    int temporaire;
    for (int l = 0; l < taille; ++l) {
        tp[l]=l;
    }
    //a revoir pk 84??
    int tableau_frequence[84]={ };
    int max=strlen(t[0]);

    for (int i = 1; i <taille ; ++i) {

        if(strlen(t[i])>max)
        {

            max=strlen(t[i]);
        }
    }



    max=max-1;


    int temp;

    for (int i = max; i>-1 ; --i) {
        //a optimiser

        int tableau_frequence[84]={ };

        for (int j = 0; j <taille ; ++j) {

            if (strlen(t[j])-1 >=i)
            {

                temp= t[j][i];
                tableau_frequence[temp-borne_inferieur]=tableau_frequence[temp-borne_inferieur]+1;
            } else{
                tableau_frequence[0]++;
            }

        }

        position_char=0;

        for (int k = 0; k <strlen(alphabet) ; ++k) {
            temp=alphabet[k];
            temporaire=tableau_frequence[temp-borne_inferieur];
            tableau_frequence[temp-borne_inferieur]=position_char;
            position_char =position_char+temporaire;
        }
        for (int l = 0; l <taille ; ++l) {
            if(i>=strlen(t[l])){
                tab[l]=tableau_frequence[0];
                tableau_frequence[0]++;
            } else
            {
                temp=t[l][i];

                tab[l]=tableau_frequence[temp-borne_inferieur];
                tableau_frequence[temp-borne_inferieur]++;
            }
        }

        int inter=0;
        int inter2;
        compteurtabbleau=0;
        inter=tp[0];
        char* temp=t[0];
        char* temp2;
        for (int n = 0; n <taille ; ++n) {
            temp2=t[tab[compteurtabbleau]];
            inter2=tp[tab[compteurtabbleau]];
            tp[tab[compteurtabbleau]]=inter;
            t[tab[compteurtabbleau]]=temp;
            temp=temp2;
            inter=inter2;
            if(compteurtabbleau==tab[compteurtabbleau])
            {

                compteurtabbleau++;
                temp=t[compteurtabbleau];
                inter=tp[compteurtabbleau];
            } else
            {
                compteurtabbleau=tab[compteurtabbleau];
            }

        }

        printf("tab :\n");
        for (int m = 0; m <taille ; ++m) {
            printf("%i / %i |",tp[m],tab[m]);
        }
        printf("\n");
        printf("trie :\n");
        for (int m = 0; m <taille ; ++m) {
            printf("%s ",t[m]);
        }
        printf("\n");

    }


    return getname(tp,taille,t,name);

}
char* induced_first_iteration(char* btw,int nbr_thread,int tab[])
{

    Liste* s_etoile_tab[nbr_thread];

    int nbr;
    int alphabet[258]={ };
    int variable[2];
    double duration;
    int taille;
    //affectation type car

    tychar(btw,s_etoile_tab,tab,alphabet,variable,nbr_thread);

    nbr=variable[1];
    taille=variable[0];
    //fin
    //extraction des sous chaine
    printf("nbr %i",nbr);
    char* newchar="";
    newchar=malloc(taille* sizeof(char));
    char* schaine[nbr];
    int position[nbr];

    extratcSstar(btw,s_etoile_tab,schaine,nbr,nbr_thread,position);

    //fin extraction

    //extraction alphabet
    char alpha[taille+1];
    getAlphabet(alphabet,taille,alpha);
    printf("\n alhabet:%s %i fin\n",alpha,strlen(alpha));
    //fin
    //affichage sous chaine
    printf("\n debut sous chaine \n");
    for (int m = 0; m <nbr ; ++m) {
        printf("%i",m);
        printf(" [%s] ",schaine[m]);

    }

    printf("fin sous chaine \n");
    //fin
    //creation nouvelle sous chaine
    if(nbr!=0 ) {
     int unique   = radix(schaine, alpha, nbr, position,newchar);
        printf("newchar: %s %i \n", newchar,unique);


    return newchar;
    }
    else {
        return " ";
    }
}




int main() {
    //premiere iteration
    int nbr_thread=2;
    clock_t start, finish;

    double duration;
    char btw[]="mmiissiissiippiiiiiii";
    int tab[strlen(btw)];

    start=clock();
    char* seconditeration=induced_first_iteration(btw,nbr_thread,tab);
    finish = clock();
    duration = (double)(finish - start) / CLOCKS_PER_SEC;
    printf( " \n%f seconds\n", duration );
    printf("fin premiere iteration %s\n",seconditeration);

    //fin
    //fin premiere iteration
    int tab2[strlen(seconditeration)];
    char* test=induced_first_iteration(seconditeration,nbr_thread,tab2);

    //debut deuxieme iteration (ajout d'une condition pour voir si il faut faire une deuxieme iteration)
 /*
    Liste* s_etoile_tab2[8];
    int alphabet2[258]={ };

    int variable2[2];

    tychar(seconditeration,s_etoile_tab2,tab2,alphabet2,variable2,nbr_thread);
    printf("nbr %i",variable2[1]);
    char* schaine2[variable2[1]];
    int position2[variable2[1]];
    printf("ici");
    extratcSstar(seconditeration,s_etoile_tab2,schaine2,variable2[1],nbr_thread,position2);

    char alpha2[variable2[0]+1];
    getAlphabet(alphabet2,variable2[0],alpha2);
    for (int m = 0; m <variable2[1] ; ++m) {
        printf("\n%i",m);
        printf(" [%s] ",schaine2[m]);

    }

    printf("fin sous chaine \n");
    //fin
    printf("\n alhabet:%s %i\n",alpha2,strlen(alpha2));

    //creation nouvelle sous chaine

    char* newchar2=radix(schaine2,alpha2,variable2[1],position2);
    printf("newchar: %s \n",newchar2);
 */
    return 0;
}
