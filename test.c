//
// Created by adem on 28/03/2020.
//


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>
typedef char* ch[200];
typedef struct LC LC;
typedef int tableau[];
struct LC{
    int x;
    LC* s;
};
typedef struct Liste Liste;
struct Liste
{
    LC *premier;
};
char* radix(ch t,char* alpha,int taille);
char* getname(int tab[],int taille, ch t);











int main() {
    int s_etoile=0;
    int nbr=0;
    int s_etoile_debut;
    char btw[]="mmiissiissiippii";
    int tab[strlen(btw)];
    Liste *liste = malloc(sizeof(Liste));
    LC *chaine=malloc(sizeof(LC));
    chaine->s=NULL;
    liste->premier=chaine;
    int deb,fin;
    int coupoure[8];
    Liste* s_etoile_tab[8];
    //a optimiser
    int alphabet[258]={ };
    int taille;
    //fin
    printf("tab debut \n");
    printf("\n");
#pragma omp parallel for
    for (int j = 0; j <omp_get_num_threads() ; ++j) {
        coupoure[j]=-1;
    }
#pragma omp parallel for
    for (int j = 0; j <strlen(btw) ; ++j) {
        tab[j]=-1;
    }

#pragma omp parallel
    {
        int premier=0;
        LC *pointeur=malloc(sizeof(LC));
        pointeur->s=NULL;
        LC *precedent;
        int f, d,egal;
        egal=100;
        int init=0;
        int temporaire;
        f = strlen(btw) / omp_get_num_threads();
        d = omp_get_thread_num();
        s_etoile_tab[d]=malloc(sizeof(Liste));
        s_etoile_tab[d]->premier=pointeur;
        if(d==7)
        {

            for (int i = f * d; i < strlen(btw); ++i) {
                temporaire=btw[i];
                if(alphabet[temporaire]==0)
                {
                    taille++;
                }
                alphabet[temporaire]++;
                if (btw[i] > btw[i + 1]) {
                    tab[i] = 0;

                    if(egal!=100)
                    {
                        for (int j = egal; j <i ; ++j) {
                            tab[j]=0;
                            egal=100;
                        }
                    }
                } else if (btw[i] < btw[i + 1]) {
                    tab[i] = 1;
                    if (egal != 100) {
                        while(tab[egal-1]==-1 & coupoure[d-1]==-1)
                        {
#pragma omp flush
                        }
                        if (tab[egal - 1] == 0 ) {
                            pointeur->x=i;
                            LC *temp=malloc(sizeof(LC));
                            temp->s=NULL;
                            pointeur->s=temp;
                            precedent=pointeur;
                            pointeur=pointeur->s;
                            init=1;
                            tab[egal] = 2;
                            nbr=nbr+1;



                        } else {
                            tab[egal] = 1;
                        }
                        for (int j = egal+1; j < i; ++j) {
                            tab[j] = 1;

                        }



                        egal = 100;



                    }

                    while(tab[i-1]==-1 & coupoure[d-1]==-1)
                    {
#pragma omp flush
                    }
                    if(tab[i]==1  && tab[i-1]==0)
                    {

                        pointeur->x=i;
                        LC *temp=malloc(sizeof(LC));
                        temp->s=NULL;
                        pointeur->s=temp;
                        precedent=pointeur;
                        pointeur=pointeur->s;
                        nbr=nbr+1;
                        tab[i]=2;
                        init=1;



                    }

                } else
                if(i<egal ){
                    egal=i;
                }

            }

        } else {


            for (int i = f * d; i < (f) * (d + 1); ++i) {
                temporaire=btw[i];
                if(alphabet[temporaire]==0)
                {
                    taille++;
                }
                alphabet[temporaire]++;

                if (btw[i] > btw[i + 1]) {
                    tab[i] = 0;

                    if (egal != 100) {
                        for (int j = egal; j < i; ++j) {
                            tab[j] = 0;
                            egal = 100;
                        }
                    }
                } else if (btw[i] < btw[i + 1]) {

                    tab[i] = 1;
                    if (egal != 100) {

                        while(tab[egal-1]==-1 & coupoure[d-1]==-1)
                        {
#pragma omp flush
                        }
                        if (tab[egal - 1] == 0) {
                            pointeur->x=i;
                            LC *temp=malloc(sizeof(LC));
                            temp->s=NULL;
                            pointeur->s=temp;
                            precedent=pointeur;
                            pointeur=pointeur->s;
                            tab[egal] = 2;
                            init=1;
                            nbr=nbr+1;


                        } else {
                            tab[egal] = 1;
                        }
                        for (int j = egal + 1; j < i; ++j) {
                            tab[j] = 1;

                        }



                        egal = 100;

                    }

                    while(tab[i-1]==-1 &coupoure[d-1]==-1 )
                    {
#pragma omp flush
                    }


                    if (tab[i] == 1 && tab[i - 1] == 0) {
                        pointeur->x=i;
                        LC *temp=malloc(sizeof(LC));
                        temp->s=NULL;
                        pointeur->s=temp;
                        precedent=pointeur;
                        pointeur=pointeur->s;
                        tab[i] = 2;
                        init=1;
                        nbr=nbr+1;
                    }

                } else if (i < egal) {
                    egal = i;
                }

            }
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
    }

    printf("tab coupoure \n");
    for (int k = 0; k <8; ++k) {
        printf("%i ",coupoure[k]);

    }
    printf("\n");

    int f,d,saut;

    for (int j = 6; j >-1 ; --j) {
        saut=0;

        f = strlen(btw) / 8;

        if (coupoure[j]!=-1) {

            int fin = f * (j + 1);
            int result, compteur;
            saut = 0;
#pragma omp parallel sections
            {
#pragma omp section
                {
                    while (btw[coupoure[j]] == btw[fin] && tab[fin] == -1) {
                        fin++;


                    }

                    compteur = coupoure[j];
                }
#pragma omp section
                {

                    while (btw[coupoure[j]] == btw[compteur]) {
                        compteur--;
                        if (compteur == coupoure[j - saut - 1]) {
                            saut++;

                        }
                    }
                }

            }
            if (tab[fin] != 0 && btw[coupoure[j]] == btw[fin]) {
                result = tab[fin];

            } else if (btw[coupoure[j]] < btw[fin]) {
                result = 1;

                tab[fin]=1;

            } else {
                result = 0;
                tab[fin]=0;
            }

#pragma omp parallel for
            for (int i = compteur+1; i < fin; ++i) {


                tab[i] = result;

                if (i != 0) {
                    if (tab[i] == 1 && tab[i - 1] == 0) {
                        int temoraire=i/f;

                        if(temoraire>=7)
                        {
                            LC *pointeur=s_etoile_tab[7]->premier;
                            LC *nouveau = malloc(sizeof(LC));
                            nouveau->s = NULL;
                            nouveau->x = i;
                            if(pointeur!=NULL) {
                                while (pointeur->s != NULL) {
                                    pointeur = pointeur->s;
                                }

                                pointeur->s = nouveau;
                            } else{
                                s_etoile_tab[7]->premier=nouveau;
                            }
                        } else
                        {

                            LC *pointeur=s_etoile_tab[temoraire]->premier;
                            LC *nouveau = malloc(sizeof(LC));
                            nouveau->s = NULL;
                            nouveau->x = i;
                            if(pointeur!=NULL) {
                                while (pointeur->s != NULL) {
                                    pointeur = pointeur->s;
                                }


                                pointeur->s = nouveau;
                            } else
                            {
                                s_etoile_tab[temoraire]->premier=nouveau;
                            }
                        }
                        tab[i] = 2;
                        nbr=nbr+1;
                    }
                }
            }

        }

        j=j-saut;

    }
    printf("tab fin \n");
    for (int k = 0; k <strlen(btw) ; ++k) {
        printf("%i ",tab[k]);

    }

    int etoile=0;
    int debut;
    char *teste;

    char* schaine[nbr];
    int indice=0;
    for (int l = 0; l <8 ; ++l) {
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
                strncpy(schaine[indice],btw+debut,(temp->x-debut));
                debut=temp->x;
                indice=indice+1;
            }
            temp=temp->s;

        }


    }
    schaine[indice]=malloc(sizeof((strlen(btw)-debut)));
    strncpy(schaine[indice],btw+debut,(strlen(btw)-debut));


    char t;
    char* test;
    char alpha[taille+1];
    ;
    alpha[0]=' ';
    indice=1;
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
    printf("alhabet:%s \n",alpha);
    printf("\n debut sous chaine \n");
    for (int m = 0; m <nbr ; ++m) {
        printf("%s ",schaine[m]);

    }

    printf("fin sous chaine \n");
    char* stexte;
    stexte=radix(schaine,alpha,nbr);
    printf("schaine %s",stexte);

    return 0;
}


















































char* radix(ch t,char* alphabet,int taille)
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

        int inter;
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

    for (int m = 0; m <taille ; ++m) {
        printf("%i ",tab[m]);
    }
    return getname(tab,taille,t);


}
char* getname(int tab[],int taille, ch t)
{
    int stop,indice,egal,boucle;
    char* name;
    name=malloc(taille* sizeof(char));

    char sch;
    for (int m = 0; m <taille-1 ; ++m) {
        stop=m;
        while (strlen(t[m])==strlen(t[m+1]) && m<taille-1)
        {

            m=m+1;
        }
        indice=strlen(t[stop]);
        if (m!=stop){
            egal=0;

        } else
        {
            egal=1;

            name[tab[m]]=m+1;

        }

        while (indice>-1 && egal==0)
        {

            boucle=stop;
            while (egal==0 && boucle<=m-1 )
            {
                if(t[boucle][indice]!=t[boucle+1][indice])
                {
                    egal=1;
                }
                boucle++;
            }
            indice=indice-1;
        }
        if(egal==0 )
        {

            for (int i = stop; i <=m ; ++i) {

                name[tab[i]]=stop+1;


            }
        }
    }

    return name;
}