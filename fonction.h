//
// Created by adem on 21/05/2020.
//

#ifndef UNTITLED9_FONCTION_H
#define UNTITLED9_FONCTION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>
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

            if (etoile==0)
            {

                debut=temp->x;
                etoile=1;
            } else
            {

                schaine[indice]=malloc(sizeof((temp->x-debut)));
                strncpy(schaine[indice],btw+debut+1,(temp->x-debut));
                position[positionindice]=debut;
                positionindice++;
                debut=temp->x;
                indice=indice+1;


            }
            temp=temp->s;

        }


    }

    schaine[indice]=malloc(sizeof((strlen(btw)-debut)));
    strncpy(schaine[indice],btw+debut,(strlen(btw)-debut));
    position[positionindice]=debut;

}
void addsubstring(int j,int fin,Liste* s_etoile_tab[])
{

    LC *pointeur=s_etoile_tab[j]->premier;
    int test=0;
    LC *nouveau = malloc(sizeof(LC));

    if(pointeur!=NULL) {
        while (pointeur->s != NULL) {

            test=1;
            pointeur = pointeur->s;
        }

        if(test==1){

            nouveau->s = NULL;
            nouveau->x = fin;
            pointeur->s = nouveau;
        } else
        {

            pointeur->x=fin;
            pointeur->s=NULL;

        }

    } else
    {
        if(pointeur==NULL){

        }

        nouveau->s = NULL;

        nouveau->x=fin;
        s_etoile_tab[j]->premier=nouveau;

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
            addsubstring(omp_get_thread_num(),fin,s_etoile_tab);

            tab[fin]=2;
            variable[1]++;
        }
        else if(tab[fin-1]==-1)
        {
            reusefonction=1;
        }
        else
        {

            tab[fin]=1;

        }
    } else
    {

        if(tab[fin+1]==1 & tab[fin-1]==0)
        {

            addsubstring(j, fin, s_etoile_tab);

            tab[fin]=2;
            variable[1]++;
        } else if(tab[fin+1]==-1)
        {
            coupoure[j]=fin;
        } else
        {
            tab[fin]=tab[fin+1];
        }


    }
    if(tab[fin+1]==1 & tab[fin]==0)
    {

        addsubstring(j, fin + 1, s_etoile_tab);

        tab[fin+1]=2;
        variable[1]++;
    }
    return reusefonction;
}
void maincase(char* btw,int alphabet[],int variable[],Liste* s_etoile_tab[],int tab[],int f,int coupoure[],int j,int nbr_thread){

    if(coupoure[j]!=-1)
    {
        if(j!=(nbr_thread-1))
        {
            if(coupoure[j+1]==f*(j+1))
            {
                while(tab[coupoure[j+1]]==-1 )
                {
#pragma omp flush
                }


            }

            for (int i = coupoure[j]; i <f*(j+1) ; ++i) {
                tab[i]=tab[f*(j+1) ];
            }
            if(coupoure[j]>0){
                if (tab[coupoure[j]]==1 & tab[coupoure[j]-1]==0)
                {

                    addsubstring(j, coupoure[j], s_etoile_tab);

                    tab[coupoure[j]]=2;
                    variable[1]++;
                }
            }



        } else{
            //a traiter
        }
    }

}

int traitementpar(int debut,int fin,char* btw,int alphabet[],int tab[],int variable[],int egal,int temporaire,int d,Liste* s_etoile_tab[])
{
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

                addsubstring(d, i+1, s_etoile_tab);

                variable[1]++;
                tab[i+1]=2;
            }

        } else if (btw[i] < btw[i + 1]) {
            tab[i] = 1;



        } else
        if(i<egal ){
            egal=i;
        }

    }
    return egal;
}

void tychar(char* btw,Liste* s_etoile_tab[],int tab[],int alphabet[],int variable[],int nrb_thread){

    Liste *liste = malloc(sizeof(Liste));
    LC *chaine=malloc(sizeof(LC));
    chaine->s=NULL;
    liste->premier=chaine;
    int coupoure[nrb_thread];
    variable[0]=0;
    variable[1]=0;
    int f;
    f = strlen(btw) / nrb_thread;
    printf("\n");
    init(coupoure,nrb_thread);
    init(coupoure,strlen(btw));

#pragma omp parallel num_threads(nrb_thread)
    {

        int premier=0;
        LC *pointeur=malloc(sizeof(LC));
        pointeur->s=NULL;
        LC *precedent;
        int f, d,egal;
        egal=100;
        int init=0;
        int temporaire;
        f = strlen(btw) / nrb_thread;
        d = omp_get_thread_num();

        s_etoile_tab[d]=malloc(sizeof(Liste));
        s_etoile_tab[d]->premier=pointeur;
        if(d==(nrb_thread-1))
        {
            egal=traitementpar(f*d+1,strlen(btw),btw, alphabet, tab, variable,egal,temporaire,d,s_etoile_tab);

        } else {

            egal=traitementpar(f*d+1,f*(d+1),btw, alphabet, tab, variable,egal,temporaire,d,s_etoile_tab);

        }
        if(egal!=100)
        {
            coupoure[d]=egal;
        }
        if (init==0)
        {
            s_etoile_tab[d]->premier=NULL;
        } else
        {
            precedent->s=NULL;
        }

#pragma omp barrier
        int reusefonction=cornercase(btw,alphabet,variable,s_etoile_tab,tab,f,coupoure,d);
        maincase(btw,alphabet,variable,s_etoile_tab,tab,f,coupoure,d,nrb_thread);
        if (reusefonction==1)
        {
            printf("ici");
            reusefonction=cornercase(btw,alphabet,variable,s_etoile_tab,tab,f,coupoure,d);
        }
    }
    /*

    #pragma omp parallel for
    for (int i = 0; i < nrb_thread; ++i) {
    }
    */







    printf("tab fin \n");
    for (int k = 0; k <strlen(btw) ; ++k) {
        printf("%i ",tab[k]);
    }

}
//a optimiser
char* getname(int tab[],int taille, char* t[])
{
    int stop,indice,egal,boucle;
    char* name;
    name=malloc(taille* sizeof(char));

    char sch;
    name[tab[0]]=1;
    for (int m = 1; m <taille ; ++m) {

        int indice=strlen(t[m]);
        if(indice==strlen(t[m-1]))
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
            {name[tab[m]]=m;}
            else{
                name[tab[m]]=m+1;
            }

        } else{
            name[tab[m]]=m+1;
        }

    }


    return name;
}
char* radix(char* t[],char* alphabet,int taille,int position[])
{
    int tab[taille];
    char *s;
    int borne_inferieur;
    char u=' ';
    int compteurtabbleau,position_char;
    borne_inferieur=u;
    int temporaire;
    for (int l = 0; l < taille; ++l) {
        tab[l]=l;
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

        int inter,inter2;
        compteurtabbleau=0;

        while (compteurtabbleau<taille)
        {

            if(i>=strlen(t[compteurtabbleau]))
            {
                if(compteurtabbleau==tableau_frequence[0])
                {

                    compteurtabbleau++;
                    tableau_frequence[0]++;
                } else if(tableau_frequence[0]<taille)
                {
                    s=t[compteurtabbleau];
                    inter=tab[compteurtabbleau];
                    tab[compteurtabbleau]=tab[tableau_frequence[0]];

                    tab[tableau_frequence[0]]=inter;

                    inter2=position[compteurtabbleau];
                    position[compteurtabbleau]=position[tableau_frequence[0]];

                    position[tableau_frequence[0]]=inter2;

                    t[compteurtabbleau]=t[tableau_frequence[0]];
                    t[tableau_frequence[0]]=s;
                    tableau_frequence[0]++;
                }
                else
                {
                    compteurtabbleau++;
                }

            } else
            {

                temp=t[compteurtabbleau][i];

                if(compteurtabbleau==tableau_frequence[temp-borne_inferieur])
                {

                    compteurtabbleau++;
                    tableau_frequence[temp-borne_inferieur]++;
                } else if(tableau_frequence[temp-borne_inferieur]<taille)
                {
                    s=t[compteurtabbleau];
                    inter=tab[compteurtabbleau];
                    tab[compteurtabbleau]=tab[tableau_frequence[temp-borne_inferieur]];
                    tab[tableau_frequence[temp-borne_inferieur]]=inter;

                    inter2=position[compteurtabbleau];
                    position[compteurtabbleau]=position[tableau_frequence[temp-borne_inferieur]];
                    position[tableau_frequence[temp-borne_inferieur]]=inter2;

                    t[compteurtabbleau]=t[tableau_frequence[temp-borne_inferieur]];
                    t[tableau_frequence[temp-borne_inferieur]]=s;
                    tableau_frequence[temp-borne_inferieur]++;
                }
                else
                {
                    compteurtabbleau++;
                }


            }
        }

    }


    return getname(tab,taille,t);

}

#endif //UNTITLED9_FONCTION_H
