#include <stdlib.h>
#include <stdio.h>
#include "csv_managing.h"



void init_csv(const char* nome,int righe){
    FILE* file=fopen(nome,"w");
    if(file==NULL){
        perror("errore nell'inizializzazione del file csv");
    }
    
    fprintf(file,"%d\n",righe);
    for(int c1=0;c1<righe;c1++){
        for(int c2=0;c2<24;c2++){
            fprintf(file,"%d_%d",c1,c2);
            if(c2!=23){
                fprintf(file,",");
            }
        }
        fprintf(file,"\n"); 
    }
    fclose(file);
    printf("ta da\n");
}