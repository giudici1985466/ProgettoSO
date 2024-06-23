#include "csv_managing.h"
#include <stdio.h>

int main(){
    const char* prova="prova";
    const char* file1="luglio";
    const char* file2="giugno";
    int righe=4;
    int result=0;
    init_csv(prova,righe);
    init_csv(file1,31);
    init_csv(file2,30);
    print_csv(prova);
    insert_into_csv(prova,126,1,1);
    insert_into_csv(prova,126,2,2);
    insert_into_csv(prova,126,3,3);
    result=csv_query_monthly(prova,1,3,0,23);
    printf("QUERY RESULT %d\n",result);

    /*print_csv(prova);
    init_csv(prova,righe);
    print_csv(prova);
    print_csv(file1);
    print_csv(file2);
    delete_csv(file2);*/
}
    