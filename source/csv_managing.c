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
int arr_mean(int* arr,int start,int end);
void csv_to_arr(FILE* file,int* arr,int num_righe);
void delete_csv(const char* nome);
void init_csv(const char* nome,int righe);
void print_csv(const char* nome);
void insert_into_csv(const char* nome,int value,int giorno,int col);
int csv_query_monthly(const char* nome, int pg, int ug, int po, int uo);


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

int csv_query_monthly(const char* nome, int pg, int ug, int po, int uo){
    if(ug<pg){
        perror("Seleziona un range di giorni valido");
    }
    if(ug==pg){
        if(uo<po){
            perror("Seleziona un range orario valido");
        }
    }
    int result=0;
    int* arr;
    int frow=pg-1;
    printf("PRIMA RIGA: %d\n",frow);
    int lrow=ug-1;
    printf("ULTIMA RIGA: %d\n",lrow);
    int fposition=(frow*24)+po;
    printf("PRIMA POSIZIONE: %d\n",fposition);
    int lposition=(lrow*24)+uo;
    printf("ULTIMA POSIZIONE: %d\n", lposition);
    
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

   
    
    arr=(int*)malloc(num_righe*24*sizeof(int));
    memset(arr,0,num_righe*24*sizeof(int));
    csv_to_arr(file,arr,num_righe);
    
    fclose(file);
   

    result=arr_mean(arr,fposition,lposition);
    return result;



}



void csv_to_mat(FILE* file,int** mat,int num_righe){

    char* buffer=(char*)malloc(MAX_LEN_RIGA);

    for (int c1 = 0; c1 < num_righe; c1++) {        
        mat[c1] = (int*) malloc(NUM_COLONNE * sizeof(int));
        for (int c2 = 0; c2 < NUM_COLONNE; c2++) {
            mat[c1][c2] = INVALID_VALUE; 
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

void csv_to_arr(FILE* file,int* arr,int num_righe){
    char* buffer=(char*)malloc(MAX_LEN_RIGA);
    int positions=num_righe*24;
    memset(arr,0,positions*sizeof(int));
    int j = 0;
    
    for (int i = 0; i < num_righe; i++) {
        memset(buffer,0,MAX_LEN_RIGA);
        leggi_riga(file,buffer);
        char *token = strtok(buffer, ",");
        
        while (token != NULL && j < positions) {
            arr[j]=atoi(token);
            printf("VALORE INSERITO NELL'ARRAY: %d IN POSIZIONE %d\n",arr[j],j);
            token = strtok(NULL, ",");
            j++;
        }
    }
    free(buffer);

}

void free_mat(int** mat,int num_righe){
    for(int i = 0; i < num_righe; i++){
        free(mat[i]);
    }
    free(mat);
}


int arr_mean(int* arr,int start,int end){
    int flag=1;
    int result=-1;
    int num_values=0;
    for(int c1=start; c1<end ;c1++){
        if(arr[c1]!=INVALID_VALUE){
            if(flag==1){
                flag=0;
                result=0;
            }
            result+=arr[c1];
            num_values++;
        }
    }
    if(num_values!=0){
        result=result/num_values;
    }
    
    return result;
}

