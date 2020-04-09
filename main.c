#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>
typedef char* ch[5];
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
void radix(ch t);












int main() {
    /*
    ch t;
    t[0]=malloc(strlen("aggtg"));
    strcpy(t[0],"aggtg");
    t[1]=malloc(strlen("aaggc"));
    strcpy(t[1],"aaggc");
    t[2]=malloc(strlen("aaaaaaaaa"));
    strcpy(t[2],"aaaaaaaaa");
    t[3]=malloc(strlen("cccccccc"));
    strcpy(t[3],"cccccccc");
    t[4]=malloc(strlen("aaggca"));
    strcpy(t[4],"aaggca");


    printf("le tableau avant trie :");
    for (int i = 0; i <5 ; ++i) {
        printf("%s ",t[i]);
    }
    printf("\n");

    radix(t);
    printf("resultat final :");
    for (int i = 0; i <5 ; ++i) {
        printf("%s ",t[i]);
    }
    printf("\n");
    */
    int s_etoile=0;
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
    printf("tab debut \n");
    /*
    for (int k = 0; k <strlen(btw) ; ++k) {
        printf("%i ",tab[k]);

    }
    */
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
        f = strlen(btw) / omp_get_num_threads();
        d = omp_get_thread_num();
        s_etoile_tab[d]=malloc(sizeof(Liste));
        s_etoile_tab[d]->premier=pointeur;
        if(d==7)
        {

            for (int i = f * d; i < strlen(btw); ++i) {

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
    printf("\n debut sous chaine \n");
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

                teste=malloc(sizeof((temp->x-debut)));
                strncpy(teste,btw+debut,(temp->x-debut));
                printf("%s \n",teste,l);
                debut=temp->x;
            }
            temp=temp->s;
        }


    }
    teste=malloc(sizeof((strlen(btw)-debut)));
    strncpy(teste,btw+debut,(strlen(btw)-debut));
    printf("%s\n",teste);

    printf("fin sous chaine \n");
    return 0;
}


















































void radix(ch t)
{


    char *s;
    char alphabet[]=" acgt";
    int borne_inferieur;
    char u=' ';
    int compteurtabbleau,position_char;
    borne_inferieur=u;
    int temporaire;

    int tableau_frequence[116]={ };
    int max=strlen(t[0]);

    for (int i = 1; i <5 ; ++i) {

        if(strlen(t[i])>max)
        {

            max=strlen(t[i]);
        }
    }



    max=max-1;


    int temp;

    for (int i = max; i>-1 ; --i) {
    //a optimiser
        int tableau_frequence[116]={ };

        for (int j = 0; j <5 ; ++j) {

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


        compteurtabbleau=0;
        while (compteurtabbleau<5)
        {

            if(i>=strlen(t[compteurtabbleau]))
            {
                if(compteurtabbleau==tableau_frequence[0])
                {
                    compteurtabbleau++;
                    tableau_frequence[0]++;
                } else if(tableau_frequence[0]<5)
                {
                    s=t[compteurtabbleau];
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
                } else if(tableau_frequence[temp-borne_inferieur]<5)
                {
                    s=t[compteurtabbleau];
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
}
