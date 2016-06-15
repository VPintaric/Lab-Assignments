#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char *nadovezi(void){
	char string[20+1];
	char *retstring=NULL;
	int size=1;
    retstring = (char*) malloc((unsigned) size);
    *retstring = 0;

	scanf("%s", string);

	while(!((string[0] == '.') && (string[1] == 0))){
        printf("%s\n",retstring);
		size += strlen(string);
		retstring = (char*) realloc(retstring, (unsigned) size);
		strcat(retstring, string);
		scanf("%s", string);
	}

	return retstring;
}

int main(void){
		char *niz=NULL;
		niz = nadovezi();

		puts(niz);

		free(niz);

		return 0;
}
