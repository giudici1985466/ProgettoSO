#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "csv_managing.h"


void leggi_riga(FILE *file, char *buffer);
char* record_path_composer(const char* nome);
void stampa_matrice(int **matrice, int righe, int colonne);
void path_composer(char* path_buf,const char* nome);
void csv_to_mat(FILE* file,int** mat,int num_righe);
void mat_to_csv(FILE* file,int** mat,int num_righe);
void free_mat(int** mat,int num_righe);


void delete_csv(const char* nome){
    char* path_buf=malloc(MAX_LEN_PATH);
    path_composer(path_buf,nome);
    if(remove(path_buf)==-1){
        perror("Errore nella rimozione del file");
    }
    free(path_buf);

}

void init_csv(const char* nome,int righe){
    char* path_buf=malloc(MAX_LEN_PATH);
    path_composer(path_buf,nome);

    FILE* file=fopen(path_buf,"w");
    if(file==NULL){
        perror("INIT_CSV: errore nell'inizializzazione del file csv\n");
    }
    
    fprintf(file,"%d\n",righe);
    for(int c1=0;c1<righe;c1++){
        for(int c2=0;c2<NUM_COLONNE;c2++){
            fprintf(file,"%d",INIT_VALUE_CSV);
            if(c2!=(NUM_COLONNE-1)){
                fprintf(file,",");
            }
        }
        fprintf(file,"\n"); 
    }
    fclose(file);
}

void print_csv(const char* nome){
    char* path_buf=malloc(MAX_LEN_PATH);
    path_composer(path_buf,nome);
    
    int num_righe;
    FILE* file=fopen(path_buf,"r");
    if(file==NULL){
        perror("PRINT_CSV: errore nell'apertura del file csv\n");
    }

    char* buffer=(char*)malloc(MAX_LEN_RIGA);
    leggi_riga(file,buffer);
    num_righe=atoi((const char*)buffer);
    printf("+++%s+++\n{\n",nome);
    for (int i = 0; i < num_righe; i++) {
        leggi_riga(file,buffer);
        char *token = strtok(buffer, ",");
        int j = 0;
        while (token != NULL && j < NUM_COLONNE) {
            printf("%s",token);
            if(j!=NUM_COLONNE-1){
                printf(" ");
            }
            token = strtok(NULL, ",");
            j++;
        }
        printf("\n");
    }
    printf("}\n");
    printf("---------------------------------------------------------------------------------------------------------------------------------------\n");
    fclose(file);
    free(buffer);
    free(path_buf);
}


void insert_into_csv(const char* nome,int value,int giorno,int col){
    if(col<0 || col>23){
        perror("INSERT_INTO_CSV: valore ora non valido");
    }
    int row=giorno-1;
    int num_righe=0;
   
    char* path_buf=malloc(MAX_LEN_PATH);
    path_composer(path_buf,nome);
   
    FILE* file1=fopen(path_buf,"r");
    if(file1==NULL){
        perror("INSERT_INTO_CSV: errore nell'apertura in lettura del file csv\n");
    }

    char* buffer=(char*)malloc(MAX_LEN_RIGA);
    memset(buffer,0,MAX_LEN_RIGA);
    leggi_riga(file1,buffer);
    
    num_righe=atoi((const char*)buffer);
    if(row>num_righe || row<0){
        perror("INSERT_INTO_CSV: valore giorno non valido ");
    }
    
    
    int** mat=malloc(num_righe*sizeof(int*));
    csv_to_mat(file1,mat,num_righe);
    mat[row][col]=value;

    fclose(file1);

    
    FILE* file2=fopen(path_buf,"w");
    if(file2==NULL){
        perror("INSERT_INTO_CSV: errore nell'apertura in scrittura del file csv\n");
    }
   
    mat_to_csv(file2,mat,num_righe);
    
    fclose(file2);
    free(buffer);
    free_mat(mat,num_righe);
    free(path_buf);
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


void path_composer(char* path_buf,const char* nome){
    memset(path_buf,0,MAX_LEN_PATH);
    strcat(path_buf,RECORD_PATH);
    strcat(path_buf,nome);
    strcat(path_buf,CSV_EXTENSION);
}

void leggi_riga(FILE *file, char *buffer) {
    fgets(buffer,MAX_LEN_RIGA , file);
}

/*void csv_query_monthly(const char* nome, int pg, int ug, int po, int uo, int mode){
    int num_righe=0;
    char* path_buf=malloc(MAX_LEN_PATH);
    path_composer(path_buf,nome);
    FILE* file=fopen(path_buf,"r");
    if(file==NULL){
        perror("INSERT_INTO_CSV: errore nell'apertura in lettura del file csv\n");
    }

    char* buffer=(char*)malloc(MAX_LEN_RIGA);
    memset(buffer,0,MAX_LEN_RIGA);
    leggi_riga(file,buffer);
    
    num_righe=atoi((const char*)buffer);

    if(ug<pg){
        perror("Inserisci un range di giorni valido!\n");
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


}


void csv_query_annually(){

}
*/


void csv_to_mat(FILE* file,int** mat,int num_righe){

    char* buffer=(char*)malloc(MAX_LEN_RIGA);

    for (int c1 = 0; c1 < num_righe; c1++) {        
        mat[c1] = (int*) malloc(NUM_COLONNE * sizeof(int));
        for (int c2 = 0; c2 < NUM_COLONNE; c2++) {
            mat[c1][c2] = -1; 
        }
    }

    for (int i = 0; i < num_righe; i++) {
        memset(buffer,0,MAX_LEN_RIGA);
        leggi_riga(file,buffer);
        char *token = strtok(buffer, ",");
        int j = 0;
        while (token != NULL && j < NUM_COLONNE) {
            mat[i][j]=atoi(token);
            token = strtok(NULL, ",");
            j++;
        }
    }
    free(buffer);
}

void mat_to_csv(FILE* file,int** mat,int num_righe){
    fprintf(file,"%d\n",num_righe);
    for(int c1=0;c1<num_righe;c1++){
        for(int c2=0;c2<NUM_COLONNE;c2++){
            fprintf(file,"%d",mat[c1][c2]);
            if(c2!=(NUM_COLONNE-1)){
                fprintf(file,",");
            }
        }
        fprintf(file,"\n"); 
    }

}

void free_mat(int** mat,int num_righe){
    for(int i = 0; i < num_righe; i++){
        free(mat[i]);
    }
    free(mat);
}

