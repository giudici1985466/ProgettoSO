#include "csv_managing.h"
#include <stdio.h>

int main(){
    const char* prova="prova.csv";
    int righe=4;
    init_csv(prova,righe);
    print_csv(prova);
    printf("----------------------------------------\n");
    insert_into_csv(prova,126,1,1);
    insert_into_csv(prova,126,2,2);
    insert_into_csv(prova,126,3,3);
    print_csv(prova);
}