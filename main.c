#include <stdio.h>
#include <stdlib.h>
//#include "Types.h"

#define NB_BLOCK  10 /*16777215*/
#define NB_PAGES 63
#define NB_SEGMENT 3


int main(int argc, char **argv){
	
}
/*
int main(int argc, char **argv)
{
	printf("hello world\n");
	NAND_FTL_free();
	return 0;
}

void NAND_FTL_free( void ){
	
	int i = 0, j =0;
	FILE* fichier = NULL;
	
	for(i = 0; i < NB_BLOCK; i++){
		char buf[64] = "";
		sprintf(buf, "%d", i);
		fichier = fopen(buf, "w+");
		
		for(j = 0; j < NB_PAGES; j++){
			fputs("0000\n0000\n0000\n0000\n", fichier);
		}
		fclose(fichier);
	}
}

*/
/*
 char str[10] = "";
    int nombre = 12345;
    sprintf(str, "%d", nombre);
    printf("%d", nombre);*/