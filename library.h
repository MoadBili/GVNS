//
// Created by moad on 12/13/19.
//

#ifndef VN_SEARCH_LIBRARY_H
#define VN_SEARCH_LIBRARY_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>


struct Array{
    int size;
    int *get;
};
typedef struct Array* Array;

struct Sequence{
    int size;
    int *values;
    int cost;
};
typedef struct Sequence* Sequence;

struct Data{
    int n;
    int m;
    int *duration;
    int *loading;
};
typedef struct Data* Data;

Sequence new_Sequence(int length);

void show_Sequence(Sequence sequence);
void initialize_Sequence(Sequence sequence,Data data);
void free_Sequence(Sequence);
void copy_sequence(Sequence source,Sequence cible);
Array new_array(int length);
Array free_array(Array array);

Data getData(FILE*);
void showData(Data);
void freeData(Data);

int cost(Sequence policy,Data data);
int index_of(Sequence vec,int value);
int max(Sequence vec);
int min(Sequence vec);
void swap(int* a,int* b);
void Shaking(Sequence policy,int k,Sequence out,Data data);
Sequence Two_opt(Sequence policy,Data data);
Sequence Two_swap(Sequence policy,Data data);
void Shuffle(Array policy);
Sequence Swap(Sequence policy,Data data);
Sequence Insertion(Sequence policy,Data data);
Sequence Neighborhood(Sequence sequence,Data data,int k);
Sequence GVNS(Sequence sequence,Data data,Array neighborhood,int iter_max,int iter_nip);
#endif //VN_SEARCH_LIBRARY_H
