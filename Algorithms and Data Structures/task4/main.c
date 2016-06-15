#include<stdio.h>
#include<string.h>
#include "datoteka.h"


typedef struct at Atom;

struct at {
	Datoteka element;
	struct at *sljed;
};

typedef struct {
    Atom *ulaz;
    Atom *izlaz;
} Red;



void init_red(Red *r){
    (r->ulaz) = (r->izlaz) = NULL;
}

int dodaj_red(Datoteka file, Red *r){
    Atom *novi;
    novi = (Atom *) malloc(sizeof(Atom));
    if (novi == NULL) return 0;
    novi->element = file;
    novi->sljed = NULL;

    if((r->ulaz) == NULL) r->izlaz = novi;
    else r->ulaz->sljed = novi;
    r->ulaz = novi;
    return 1;
}

int skini_red(Datoteka *file, Red *r){
    Atom *pom;

    if((r->izlaz) == NULL) return 0;
    *file = r->izlaz->element;
    pom = r->izlaz;
    r->izlaz = r->izlaz->sljed;
    free(pom);

    if((r->izlaz) == NULL) r->ulaz = NULL;
    return 1;
}

void ispisiRed(Red *r){
    Red temp;
    Datoteka file;
    init_red(&temp);

    while(skini_red(&file, r)){
        printf("%c %40s %10d\n", file.vrsta, file.putanja, file.velicina);
        dodaj_red(file, &temp);
    }
    while(skini_red(&file, &temp))
        dodaj_red(file, r);
}

void vratiSveMape(char *mapa, Red *r){
    int N,i;
    Datoteka *files = NULL;

    N = vratiDatoteke(mapa, &files);
    for(i=0; i<N; i++){
        if((files + i)->vrsta == 'D'){
            dodaj_red(*(files + i), r);
            vratiSveMape((files + i)->putanja, r);
        }
    }
    free(files);
}

void ispisiStog(Stog *stog){      //obavezna funkcija
    Stog temp;
    Datoteka element;
    init_stog(&temp);

    while((skini(&element, stog))){
        printf("%c %40s %10d\n", element.vrsta, element.putanja, element.velicina);
        dodaj(element, &temp);
    }

    while((skini(&element, &temp)))
        dodaj(element, stog);
}

void najveceDatoteke(char *mapa, Stog *s){ //obavezna funkcija
        int i, N, MAXsize=-1;
        Datoteka *files = NULL;
        Datoteka MAXfile;

        N = vratiDatoteke(mapa, &files);
        for(i=0; i < N; i++){
            if( ((files + i)->vrsta == 'F') && ((files + i)->velicina > MAXsize)){
                    MAXsize = (files + i)-> velicina;
                    MAXfile = *(files + i);
                }
            else if((files + i)->vrsta == 'D') najveceDatoteke((files + i)->putanja, s);
        }
        if(MAXsize >= 0) dodaj(MAXfile, s);
        free(files);
    }

void nadjiNajmanjuDatoteku(Stog *s){  //dodatna funkcija
    Stog temp1;
    Datoteka imm, minFILE;

    minFILE.velicina = -1;
    init_stog(&temp1);

    while(skini(&imm, s)){
        if((imm.velicina < minFILE.velicina) || (minFILE.velicina == -1))
                minFILE = imm;
        dodaj(imm, &temp1);
    }
    while(skini(&imm, &temp1)){
            if((imm.velicina != minFILE.velicina) || (imm.vrsta != minFILE.vrsta)
                || (strcmp(imm.putanja, minFILE.putanja))) dodaj(imm, s);
    }
    dodaj(minFILE, s);
}

int main(void){
    Stog stog;
    Red red;
    Datoteka test;

    init_red(&red);
    init_stog(&stog);

    printf("Obavezan dio labosa, funkcija za stavljanje najvecih datoteka na stog\n");
    najveceDatoteke("G:", &stog);
    ispisiStog(&stog);

    printf("\nDodatna funkcija za stavljanje najmanje datoteke na vrh stoga\n");

    nadjiNajmanjuDatoteku(&stog);
    ispisiStog(&stog);

    printf("\nDodatna funkcija za vracanje svih mapa pomocu reda\n");

    vratiSveMape("G:", &red);
    ispisiRed(&red);


    return 0;
}
