#include <stdio.h>
#include <stdlib.h>
#define hsize 65535
#include <string.h>
#include "malloc_count.h"
typedef struct {
    unsigned int indice_posh;
    unsigned int hsize_names;

} lmstab;
typedef struct {
    int *tab;
    int indice;
    int taille;
} htab;
typedef struct {
    char *car;
    unsigned short hpos;

}save;
typedef struct {
    save *mot;
    int indice;
    int taille;
} lms_div;

int myCompare2 (const void * a, const void * b ) {
    const lmstab pa = *(const lmstab*)a;
    const lmstab pb = *(const lmstab*)b;

    return (pa.indice_posh & 0x3FFFFFF)-(pb.indice_posh & 0x3FFFFFF);
}
int myCompare (const void * a, const void * b ) {
    const save pa = *(const save*)a;
    const save pb = *(const save*)b;

    return strcmp(pa.car,pb.car);
}
static int hfunc(int m, char *p)
{
    unsigned long x;
    unsigned int i;

    x = 0;
    for (i=0; i<m; i++) {

        x *= 101;

        x += *p++;
    }
    x %= hsize;

    return x;
}
//////////////////////////////////////////////////////
void set_lms_indice(int i ,int indice, lmstab *tablms)
{

    tablms[i].indice_posh |= indice ;

}
int get_lms_indice(int i, lmstab *tablms)
{

    return tablms[i].indice_posh & 0x3FFFFFF;
}
void set_lms_posh(int i, int posh,lmstab *tablms)
{

    tablms[i].indice_posh |= posh << 26 ;


}

int get_lms_posh(int i , lmstab *tablms)
{
    return tablms[i].indice_posh >> 26;
}
//////////////////////////////////////////////////////
void set_lms_hsize(int i, int hs,lmstab *tablms)
{

    tablms[i].hsize_names |= hs;

}
int get_lms_hsize(int i , lmstab *tablms)
{
    return tablms[i].hsize_names & 0xFFFF;
}
void  set_lms_names(int i ,int name , lmstab *tablms)
{
    tablms[i].indice_posh << 16;
}
int get_lms_names(int i , lmstab *tablms)
{
    return tablms[i].indice_posh >> 16;
}
void init_hash_tab(htab *h)
{

    for (int i = 0; i <hsize ; ++i) {
        h[i].indice=0;
        h[i].tab=malloc(sizeof(int)*10);
        h[i].taille=10;
    }
}
void init_lms_div(lms_div *mot_div)
{
    mot_div->mot=malloc(sizeof(save)*100000);
    mot_div->taille=100000;
    mot_div->indice=0;
}
void init_lms_tab(lmstab *stab)
{

    for (int i = 0; i <1000000 ; ++i) {
        stab[i].indice_posh=0;
        stab[i].hsize_names=0;
    }

}
int addlms(htab *h,lmstab *stab,int indicestab,int taillech,char *chaine,int indicechar,int taillestab, lms_div *mot_div)
{


    //pour table de hash

    //pour lms_div
    int provisoire;
    int posh=0;
    int hvalue=hfunc(taillech,chaine);
    //printf("%d \n",hvalue);
    int s=h[hvalue].indice;
    int k=0,k1;

    //pour lms_tab


    // printf("hash is %d \n",hvalue);
    if (h[hvalue].indice!=0)//
    {

        int bool=1,bool2=1;
        int ind=-1;
        int i=0;



        while (i< h[hvalue].indice && bool==1){
            //printf("  %s  %s %d \n" ,mot_div->mot[h[hvalue].tab[i]],debch,strcmp(debch,mot_div->mot[h[hvalue].tab[i]]) );

            int w=strlen(mot_div->mot[h[hvalue].tab[i]].car);
            k=indicechar;k1=0;
            bool2=1;
            while (k<(taillech+indicechar) && k1<w && bool2==1)
            {
                //printf("(%c %c)",mot_div->mot[h[hvalue].tab[i]].car[k1],chaine[k]);
                if(mot_div->mot[h[hvalue].tab[i]].car[k1]!=chaine[k])
                {

                    bool2=0;
                    posh=i;
                }
                k++;
                k1++;
            }
            if(k==(taillech+indicechar))
            {
                posh=i;
                bool=0;
            }
          //  printf("pos:%d",posh);
            /*
            if(strcmp(chaine,mot_div->mot[h[hvalue].tab[i]].car) == 0)
            {

                //mathch
                bool=1;
                posh=i;


                // printf("match \n");

            }*/
            i++ ;
        }


        //printf("bool:%d",bool);

        if (bool==1)
        {
            //printf("ici ");
            posh=i;
            //insertion
            mot_div->mot[mot_div->indice].car=malloc(sizeof(char)*(taillech+1));
            provisoire=i;

            for (int i = 0; i <taillech; ++i) {
                //printf("%c",chaine[i+indicechar]);
                    mot_div->mot[mot_div->indice].car[i]=chaine[i+indicechar];


            }
            //printf("\n");

            //insertion_posh
            //mot_div->mot[mot_div->indice][taillech]=provisoire;
            //int alpha=mot_div->mot[mot_div->indice][taillech-1];

            //printf("%d ",alpha);
            set_lms_posh(indicestab,posh,stab);
            //mot_div->mot[h[hvalue].tab[i]].hpos=i;

            if (h[hvalue].indice==h[hvalue].taille)
            {
                // printf("once been here hash");
                h[hvalue].tab=realloc(h[hvalue].tab, sizeof(int)*(h[hvalue].taille+10));
                h[hvalue].taille=h[hvalue].taille+10;
            }


            h[hvalue].tab[h[hvalue].indice]=mot_div->indice;
            h[hvalue].indice++;
            mot_div->indice++;
        } else{
            //nesha9ouha

            set_lms_posh(indicestab,posh,stab);
            //posh=-1;
        }


    } else
    {

        //insertion
        mot_div->mot[mot_div->indice].car=malloc(sizeof(char)*(taillech+2));

        for (int i = 0; i <taillech; ++i) {
               // printf("%c",chaine[i+indicechar]);

                mot_div->mot[mot_div->indice].car[i]=chaine[i+indicechar];

        }
       // printf("\n");

        //mot_div->mot[mot_div->indice][taillech]=0;
        //int alpha=mot_div->mot[mot_div->indice][taillech-1];
        //printf("%d ",alpha);
        set_lms_posh(indicestab,0,stab);
        //mot_div->mot[mot_div->indice].hpos=0;
        h[hvalue].tab[h[hvalue].indice]=mot_div->indice;
        h[hvalue].indice++;
        mot_div->indice++;
    }

    //


    // free(chaine);
    stab[indicestab].indice_posh=0;
    stab[indicestab].hsize_names=0;
    set_lms_indice(indicestab,indicechar,stab);

    //set_lms_posh(indicestab,s,stab);
    set_lms_hsize(indicestab,hvalue,stab);
    ///
    //printf("poseh %d %s",h[hvalue].tab[posh]);

    //printf("posh:%d\n",posh);
    return posh;
}
int main(void)
{
    int posh;
    int debutch=0;
    int taillech=6;
    //char *debch="moumen";
    int indice=0;
    int taillestab=10;
    //lms_tab
    lmstab *stab;
    stab=malloc(sizeof(lmstab)*100000);
    taillestab=100000;
    //init_lms_tab(stab);
    //init tab hash
    htab *h;
    h=malloc(sizeof(htab)*hsize);
    init_hash_tab(h);
    //init lms_div
    lms_div *mot_div;
    mot_div =malloc(sizeof(lms_div)*1);

    init_lms_div(mot_div);


    //FILE *file = fopen("DNAdataset.txt", "r");
    //FILE *file = fopen("C:\\Users\\adem\\CLionProjects\\untitled\\DNAdataset.txt", "r");
/*
    if (file == NULL) {
        fprintf(stderr, "Error: Can't open file '%s'.", "DNAdataset.txt");
        exit(EXIT_FAILURE);
    }
    fseek(file, 0, SEEK_END);
    long n = ftell(file);
    fseek(file, 0, SEEK_SET);
    char *btw = malloc(sizeof(char) * (n + 1));
    btw[n] = '\0';
    fread(btw, sizeof(char), n, file);
    fclose(file);
    printf("%d \n",n);*/
    ////////////////////



    char btw[]="mmiissiissiippii";
    strcat(btw,"0");

    int type=0;
    int hvalue;
    int n=strlen(btw);
    posh=addlms(h,stab,debutch,1,btw,n-1,taillestab,mot_div);
    printf("%d \n",posh);
    mot_div->mot[mot_div->indice-1].hpos=posh;
    debutch++;
    int indiceS=n-1;
    for (int i=n-2; i>=0; i--) {
//compter le nombre de caractere?

        if (btw[i]< btw[i+1]) { // TYPE_S
            type=1;
        } else if (btw[i]> btw[i+1]) { // TYPE_L
            if (type==1) {
//lahna tinsici la chaine li tebda men hada lindice taile ta3ha (indiceS-i)
                //printf("%i %i \n",i,indiceS);
                /* char *sous_chaine=malloc(sizeof(char)*(indiceS-i));
                 int l=0;
                 for (int j = i+1; j <indiceS+1 ; ++j) {
                     sous_chaine[l]=btw[j];
                     l++;
                 }*/
                //char *chaine=malloc(sizeof(char)*(indiceS-i+1));
                /*int l=0;
                for (int j = i+1; j <indiceS+1 ; ++j) {
                    chaine[l]=btw[j];
                    l++;
                }*/
                //printf("[%s]",chaine);
                //set_lms_indice(debutch,16,stab);
                posh=addlms(h,stab,debutch,indiceS-i+1,btw,i+1,taillestab,mot_div);
                    //printf("%d \n",posh);
                    mot_div->mot[mot_div->indice-1].hpos=posh;


                if (mot_div->taille==mot_div->indice)
                {
                    //printf("once been here lmsdiv");
                    mot_div->mot=realloc(mot_div->mot, sizeof(save)*(mot_div->taille+10000));
                    mot_div->taille=mot_div->taille+10000;
                }


                debutch=debutch+1;
                if(debutch==taillestab)
                {
                    //printf("once been here lmstab \n");
                    stab=realloc(stab, sizeof(lmstab)*(taillestab+100000));
                    taillestab+=100000;


                }
                //
                //



                indiceS=i+1;

            }
            type=0;
        }



    }

    /* int stringLen = sizeof(mot_div->mot) / sizeof(char *);

     qsort(mot_div->mot,mot_div->indice, sizeof(*mot_div->mot),myCompare);
     printf("%d %d\n",mot_div->taille,mot_div->indice );
     for (int m = 0; m <1000 ; ++m) {
         printf("%s \n",mot_div->mot[m]);
     }*/
    //const char *input[] = {"a","orange","apple","mobile","car","arnab"};




    qsort(mot_div->mot, mot_div->indice, sizeof(save), myCompare);
    //qsort(stab, debutch, sizeof(lmstab), myCompare2);
    int i=debutch-1;
    lmstab inter;

    for (int i1 = 0; i1 <debutch/2 ; ++i1) {
        //printf("%d ",i1);
        inter=stab[i1];
        stab[i1]=stab[i];
        stab[i]=inter;
        i--;
    }
    /*
    for (int k = 0; k <500 ; ++k) {
        // mot_div->mot[k][strlen( mot_div->mot[k])-1]='?';

            printf("%d   %s  %d\n", mot_div->mot[k].hpos, mot_div->mot[k].car, strlen(mot_div->mot[k].car));
    }
     */


    for (int k = 0; k <mot_div->indice; ++k) {
        //printf("%s ",mot_div->mot[k].car);
        int hash_function =hfunc(strlen(mot_div->mot[k].car),mot_div->mot[k].car);
        h[hash_function].tab[mot_div->mot[k].hpos]=k;

    }

    for (int m = 0; m <debutch ; ++m) {

        int hash_function =get_lms_hsize(m,stab);
        printf("%d ",h[hash_function].tab[get_lms_posh(m,stab)]);
        set_lms_names(m,h[hash_function].tab[get_lms_posh(m,stab)],stab);

    }

  //set_lms_posh(0,5,stab);


}