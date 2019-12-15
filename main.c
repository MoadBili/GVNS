#include "library.h"
#include <time.h>

#define Default_url "./c500t3.csv"
#define MAX_NO_IMPROVEMENT 80
#define MAX_ITERATION 300
int main() {
    srand(time(NULL));

    char path[100];
    printf("file path : ");
    scanf("%s",path);


    FILE* file=fopen(path,"r");
    if(file==NULL){
        perror("main");
        exit(EXIT_FAILURE);
    }
    Data data=getData(file);
    fclose(file);
    Sequence sequence=new_Sequence(data->n);
    initialize_Sequence(sequence,data);
    Array neighborhood=new_array(3);
    neighborhood->get[0]=0;
    neighborhood->get[1]=1;
    neighborhood->get[2]=2;
    neighborhood->get[3]=3;

    initialize_Sequence(sequence,data);
    sequence=GVNS(sequence,data,neighborhood,MAX_ITERATION,MAX_NO_IMPROVEMENT);
    printf(" Optimal Value : %d \n",sequence->cost);
    show_Sequence(sequence);
    free_array(neighborhood);
    free_Sequence(sequence);
    freeData(data);

    return 0;
}