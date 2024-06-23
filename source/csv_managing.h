#pragma once

#define NUM_COLONNE 24
#define MAX_LEN_RIGA 1024
#define RECORD_PATH "../record/"
#define MAX_LEN_PATH 100
#define MAX_VALUE_LEN 5
#define INIT_VALUE_CSV -1
#define CSV_EXTENSION ".csv"
#define INVALID_VALUE -1


void init_csv(const char* nome,int righe);
void print_csv(const char* nome);
void insert_into_csv(const char* nome,int value,int row,int col);
void csv_query(const char* nome, int pg, int ug, int po, int uo, int mode);
void delete_csv(const char* nome);
