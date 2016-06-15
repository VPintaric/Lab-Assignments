#include <stdio.h>
#include <string.h>

float slicnostNizova(char *niz1, char *niz2, int totlen)
{
    if ((*niz1 == 0) || (*niz2 == 0)) return 0;
    else if((*niz1 == *niz2)) return (2.f/totlen + slicnostNizova(niz1 + 1, niz2 + 1,totlen));
    else return slicnostNizova(niz1 + 1, niz2 + 1,totlen);
}

int main(void)
{
    char niz1[20+1], niz2[20+1];

    gets(niz1);
    gets(niz2);

    printf("slicnost = %f", slicnostNizova(niz1, niz2, strlen(niz1)+strlen(niz2)));
    return 0;
}
