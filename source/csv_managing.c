#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "csv_managing.h"


void leggi_riga(FILE *file, char *buffer);
char* record_path_composer(const char* nome);
void stampa_matrice(int **matrice, int righe, int colonne);

void init_csv(const char* nome,int righe){
    char* path_buf=malloc(MAX_LEN_PATH);
    memset(path_buf,0,MAX_LEN_PATH);
    strcat(path_buf,RECORD_PATH);
    strcat(path_buf,nome);
    FILE* file=fopen(path_buf,"w");
    if(file==NULL){
        perror("INIT_CSV: errore nell'inizializzazione del file csv\n");
    }
    
    fprintf(file,"%d\n",righe);
    for(int c1=0;c1<righe;c1++){
        for(int c2=0;c2<NUM_COLONNE;c2++){
            fprintf(file,"%d%d",c1,c2);
            if(c2!=(NUM_COLONNE-1)){
                fprintf(file,",");
            }
        }
        fprintf(file,"\n"); 
    }
    fclose(file);
    printf("ta da\n");
}

void print_csv(const char* nome){
    char* path_buf=malloc(MAX_LEN_PATH);
    memset(path_buf,0,MAX_LEN_PATH);
    strcat(path_buf,RECORD_PATH);
    strcat(path_buf,nome);
    int num_righe;
    FILE* file=fopen(path_buf,"r");
    if(file==NULL){
        perror("PRINT_CSV: errore nell'apertura del file csv\n");
    }

    char* buffer=(char*)malloc(sizeof(char)*MAX_LEN_RIGA);
    leggi_riga(file,buffer);
    num_righe=atoi((const char*)buffer);
    for (int i = 0; i < num_righe; i++) {
        leggi_riga(file,buffer);
        char *token = strtok(buffer, ",");
        int j = 0;
        while (token != NULL && j < NUM_COLONNE) {
            printf("%s",token);
            if(j!=NUM_COLONNE-1){
                printf("\t");
            }
            token = strtok(NULL, ",");
            j++;
        }
        printf("\n");
    }

    fclose(file);
    free(buffer);
}

void leggi_riga(FILE *file, char *buffer) {
    fgets(buffer,MAX_LEN_RIGA , file);
}

void insert_into_csv(const char* nome,int value,int row,int col){
    if(col<0 || col>23){
        perror("INSERT_INTO_CSV: valore ora non valido");
    }
    int num_righe=0;
   
    char* path_buf=malloc(MAX_LEN_PATH);
    memset(path_buf,0,MAX_LEN_PATH);
    strcat(path_buf,RECORD_PATH);
    strcat(path_buf,nome);
   
    FILE* file1=fopen(path_buf,"r");
    if(file1==NULL){
        perror("INSERT_INTO_CSV: errore nell'apertura in lettura del file csv\n");
    }

    char* buffer=(char*)malloc(MAX_LEN_RIGA);
    memset(buffer,0,MAX_LEN_RIGA);
    leggi_riga(file1,buffer);
    
    num_righe=atoi((const char*)buffer);
    if(row>num_righe || row<1){
        perror("INSERT_INTO_CSV: valore giorno non valido ");
    }
    
    
    int** mat=malloc(num_righe*sizeof(int*));
    for (int c1 = 0; c1 < num_righe; c1++) {        
        mat[c1] = (int*) malloc(NUM_COLONNE * sizeof(int));
        for (int c2 = 0; c2 < NUM_COLONNE; c2++) {
            mat[c1][c2] = -1; 
        }
    }

    for (int i = 0; i < num_righe; i++) {
        memset(buffer,0,MAX_LEN_RIGA);
        leggi_riga(file1,buffer);
        char *token = strtok(buffer, ",");
        int j = 0;
        while (token != NULL && j < NUM_COLONNE) {
            if((i==row) && (j==col)){
                mat[i][j]=value;
            }else{
                mat[i][j]=atoi(token);
            }
            
            token = strtok(NULL, ",");
            j++;
        }
    }
    fclose(file1);

    
    FILE* file2=fopen(path_buf,"w");
    if(file2==NULL){
        perror("INSERT_INTO_CSV: errore nell'apertura in scrittura del file csv\n");
    }
    fprintf(file2,"%d\n",num_righe);
    for(int c1=0;c1<num_righe;c1++){
        for(int c2=0;c2<NUM_COLONNE;c2++){
            fprintf(file2,"%d",mat[c1][c2]);
            if(c2!=(NUM_COLONNE-1)){
                fprintf(file2,",");
            }
        }
        fprintf(file2,"\n"); 
    }
    fclose(file2);
}

void stampa_matrice(int **matrice, int righe, int colonne) {
    printf("Matrice di stringhe:\n");
    for (int i = 0; i < righe; i++) {
        for (int j = 0; j < colonne; j++) {
                printf("%d\t", matrice[i][j]);
        }
        printf("\n");
    }
}
