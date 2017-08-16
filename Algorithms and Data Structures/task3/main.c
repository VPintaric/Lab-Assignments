#include<stdio.h>

typedef struct
    {
        char name[30+1];
        char IPadress[15+1];
    }defzapis;

#define BLOK 4096L
#define N 100000L
#define C ((int) BLOK/sizeof(defzapis))
#define M ((int) (N/C*1.3))
#define MNOZITELJ 25
#define POCETNA_VRIJEDNOST 80

unsigned long Hash(char * niz)
{
    unsigned long hash = POCETNA_VRIJEDNOST;
    char c;
    while (c = *niz++)
    hash = MNOZITELJ * hash + c;
    return hash;
}

int brojPreljeva(FILE *input)
{
    int* num = (int*)calloc(M, sizeof(int));
    int preljevi = 0;
    char name[30+1];
    int adress,poc;
    fseek(input, 0L, SEEK_SET);

    while(fscanf(input, "%31s %*s ", name) != EOF)
    {
        adress = Hash(name) % M;
        poc = adress;
        do{
            if(num[adress] < C){
                num[adress]++;
                if(adress != poc) preljevi++;
                break;
            }
            adress = (adress + 1) % M;
        }while(adress != poc);
    }
    free(num);
    return preljevi;
}

int upis(FILE *input, FILE *hashtablica){
    defzapis pretinac[C];
    defzapis zapis;
    int adress,poc,written=0,i;
    fseek(input, 0L, SEEK_SET);

    while(fscanf(input, "%31s %16s ", zapis.name, zapis.IPadress) != EOF){
        written = 0;
        adress = Hash(zapis.name) % M;
        poc = adress;

        do{
            fseek(hashtablica, (long) adress*BLOK, SEEK_SET);
            fread(pretinac, sizeof(pretinac),1,hashtablica);
            for(i=0; ((i<C) && (written == 0)); i++){
                if(pretinac[i].name[0] == 0){
                    pretinac[i] = zapis;
                    fseek(hashtablica, (long) adress*BLOK,SEEK_SET);
                    fwrite(pretinac, sizeof(pretinac),1,hashtablica);
                    written = 1;
                }
            }
            adress = (adress + 1) % M;
        }while((adress != poc) && (written == 0));
    }
    return 1;
}


int main(void){
    FILE *input;
    FILE *hashtablica;
    hashtablica = fopen("hash.bin", "w+b");
    input = fopen("domene.txt","r");
    printf("%d\n", brojPreljeva(input));
    if (upis(input, hashtablica) == 0) printf("Nije uspijelo zapisivanje u hash tablicu\n");
    else printf("Zapisivanje u hash tablicu je bilo uspjesno\n");
    fclose(input);
    fclose(hashtablica);
    return 0;
}
