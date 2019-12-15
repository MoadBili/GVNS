//
// Created by moad on 12/13/19.
//

#include <zconf.h>
#include "library.h"
#define MAX(x,y) ((x)<(y)?(y):(x))
#define MIN(x,y) ((x)>(y)?(y):(x))



Sequence new_Sequence(int length){
    Sequence sequence=(Sequence)malloc(sizeof(struct Sequence));
    sequence->size = length;
    sequence->cost = 0;
    sequence->values =(int*)calloc(length,sizeof(int));
    return sequence;
}

void initialize_Sequence(Sequence sequence,Data data){
    for (int i = 0; i < sequence->size; i++) {
        sequence->values[i]=i;
    }
    sequence->cost=cost(sequence,data);
}
void show_Sequence(Sequence sequence){
    printf("Cost : %d  , [ ",sequence->cost);

    for (int i = 0; i < sequence->size; ++i) {
        printf("%d ",sequence->values[i]);
        if(i!= sequence->size - 1)
            printf(",");
    }
    printf("] \n");
}
Array new_array(int length){
    Array array=(Array)malloc(sizeof(struct Array));
    array->size = length;
    array->get =(int*)calloc(length,sizeof(int));
    return array;
}
Array free_array(Array array){
    free(array->get);
    free(array);
}
void free_Sequence(Sequence sequence){
    free(sequence->values);
    free(sequence);
}

Data getData(FILE *file){
    Data data = (Data)malloc(sizeof(struct Data));
    int n,m;
    fscanf(file,"%i %i",&n,&m);

    data->duration =(int*)malloc(n*sizeof(int));
    data->loading = (int*)malloc(n*sizeof(int));

    for (int i=0;i<n;i++){
        fscanf(file,"%i",data->duration+i);
    }

    for (int i=0;i<n;i++){
        fscanf(file,"%i",data->loading+i);
    }
    data->n = n;
    data->m = m;
    return data;
}


void showData(Data d){
    printf("### Data loaded ###\n");
    printf(" %i %i \n",d->n,d->m);

    for(int i=0;i<d->n;i++){
        printf(" %i ",d->duration[i]);
    }
    printf("\n");
    for(int i=0;i<d->n;i++){
        printf(" %i ",d->loading[i]);
    }
    printf("\n");

}

void freeData(Data d){
    free(d->duration);
    free(d->loading);
    free(d);
}

int max(Sequence vec){
    int value = vec->values[0];
    for(int i=1;i<vec->size; i++){
        if( value < vec->values[i])
            value = vec->values[i];
    }
    return value;
}

int min(Sequence vec){
    int value = vec->values[0];
    for(int i=1;i<vec->size; i++){
        if( value > vec->values[i])
            value = vec->values[i];
    }
    return value;
}

int index_of(Sequence vec,int value){
    for(int i=0;i < vec->size; i++){
        if(vec->values[i]== value)
            return i;
    }
}


int cost(Sequence policy,Data data){
    Sequence m = new_Sequence(data->m);
    int cost = 0;
    int index;
    for(int i=0;i < policy->size; i++){
        index = index_of(m,min(m));
        cost = data->loading[ policy->values[i] ] + MAX(cost,m->values[index]);
        m->values[index] = cost + data->duration[ policy->values[i] ];
    }
    int return_value = max(m);
    free_Sequence(m);
    return return_value;
}

void swap(int *a,int *b){
    *a = *a + *b;
    *b = *a - *b;
    *a = *a - *b;
}
void copy_sequence(Sequence source,Sequence cible){
    cible->size=source->size;
    cible->cost=source->cost;
    for(int i=0;i<source->size; i++){
        cible->values[i] = source->values[i];
    }
}
Sequence Swap(Sequence policy,Data data){
    int n=policy->size;
    Sequence temp=new_Sequence(n);
    copy_sequence(policy,temp);
    int temp1=-1;
    int temp2=-1;
    for(int k=0;k<n;k++){
        if(temp1>=0){
            swap(temp->values+temp1,temp->values+temp2);
        }
        int j=rand()%n;
        while(k==j)
            j=rand()%n;
        temp1=k;
        temp2=j;
        swap(temp->values+k,temp->values+j);
        temp->cost=cost(temp,data);
        temp->cost=cost(temp,data);
        if(temp->cost<policy->cost){
            copy_sequence(temp,policy);
            free_Sequence(temp);
            return policy;
        }
    }
    free_Sequence(temp);
    return policy;
}

Sequence Insertion(Sequence policy,Data data){
    int n=policy->size;
    Sequence temp=new_Sequence(n);
    copy_sequence(policy,temp);
    int temp1=-1;
    int temp2=-1;
    for (int i = 0; i < n-1; ++i) {
        if(temp1>=0){
            for(int k=temp2;k>temp2-temp1;k--){
                swap(temp->values+k,temp->values+k-1);
            }
        }
        int j=rand()%n;
        while(i==j)
            j=rand()%n;
        temp2=MAX(i,j);
        temp1=MIN(i,j);
        for(int k=temp1;k<temp2;k++){
            swap(temp->values+k,temp->values+k+1);
        }
        temp->cost=cost(temp,data);
        if(temp->cost<policy->cost){
            copy_sequence(temp,policy);
            free_Sequence(temp);
            return policy;
        }
    }
    free_Sequence(temp);
    return policy;
}
//[0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15]

Sequence Two_swap(Sequence policy,Data data){
    int n=policy->size;
    Sequence temp=new_Sequence(n);
    copy_sequence(policy,temp);
    int temp1=-1;
    int temp2=-1;
    for(int k=0;k<n-3;k++){
        if(temp1>=0){
            swap(temp->values+temp2,temp->values+temp1);
            swap(temp->values+temp2+1,temp->values+temp1+1);
        }
        int j=k+1+rand()%(n-2-k);
        while(k==j)
            j=k+1+rand()%(n-2-k);
        temp1=k;
        temp2=j;
        swap(temp->values+temp2,temp->values+temp1);
        swap(temp->values+temp2+1,temp->values+temp1+1);
        temp->cost=cost(temp,data);
        if(temp->cost<policy->cost){
            copy_sequence(temp,policy);
            free_Sequence(temp);
            return policy;
        }}
    free_Sequence(temp);
    return policy;
}

Sequence Two_opt(Sequence policy,Data data){
    int n=policy->size;
    int e=0;
    Sequence temp=new_Sequence(n);
    copy_sequence(policy,temp);
    int temp1=-1;
    int temp2=-1;
    for (int k = 0; k < n-3; ++k) {
        if(temp1>=0){
            for(int i=temp1+1,j=temp2-1;i<j;i++,j--){
                swap(temp->values+i,temp->values+j);
            }
        }
        e = k+3+rand()%(n-k-3);
        temp1=k;
        temp2=e;
        for(int i=k+1,j=e-1;i<j;i++,j--){
            swap(temp->values+i,temp->values+j);
        }
        temp->cost=cost(temp,data);
        if(temp->cost<policy->cost){
            copy_sequence(temp,policy);
            free_Sequence(temp);
            return policy;
        }
    }
    free_Sequence(temp);
    return policy;
}

void Shaking(Sequence policy,int k,Sequence out,Data data){
    if(k==0){
        int i=rand()%policy->size;
        int j=rand()%policy->size;
        while(i==j)
            j=rand()%policy->size;
        copy_sequence(policy,out);
        swap(out->values+i,out->values+j);
        out->cost=cost(out,data);
    }
    if(k==1){
        copy_sequence(policy,out);
        int i=rand()%policy->size;
        int j=rand()%(policy->size);
        while(i==j)
            j=rand()%(policy->size);
        int mx,mn;
        mx=MAX(i,j);
        mn=MIN(i,j);
        for(int u=mn;u<mx;u++){
            swap(out->values+u,out->values+u+1);
        }
        out->cost=cost(out,data);
    }
    if(k==2){
        copy_sequence(policy,out);
        int u=rand()%(policy->size - 4);
        int e = u+3+rand()%(policy->size - u - 3);
        while(u==e){
            e = u+3+rand()%(policy->size - u - 3);
        }
        for(int i=u+1,j=e-1;i<j;i++,j--){
            swap(out->values+i,out->values+j);
        }
        out->cost=cost(out,data);
    }
    if(k==3){
        int i=rand()%(policy->size - 4);
        int j= i+2+rand()%(policy->size - 3 - i);
        while(i==j)
            j= i+2+rand()%(policy->size - 3 - i);
        copy_sequence(policy,out);
        swap(out->values+i,out->values+j);
        swap(out->values+i+1,out->values+j+1);
        out->cost=cost(out,data);
    }
}

void Shuffle(Array policy){
    int n=policy->size;
    if(n<=1)
        return;
    for (int i = 0; i < n ; ++i) {
        int k=rand()%n;
        int j=rand()%n;
        while(k==j)
            j=rand()%n;
        swap(policy->get+j,policy->get+k);
    }
}
Sequence Neighborhood(Sequence sequence,Data data,int k){
    if(k==0){
        return Swap(sequence,data);
    }
    if(k==1){
        return Insertion(sequence,data);
    }
    if(k==2){
        return Two_opt(sequence,data);
    }
    if(k==3){
        return Two_swap(sequence,data);
    }
}

Sequence LocalSearch(Sequence sequence,Data data,Array neighborhood){
    bool improvement=true;
    Sequence sequence1=new_Sequence(sequence->size);
    Sequence sequence2=new_Sequence(sequence->size);
    int kmax=neighborhood->size;
    Shuffle(neighborhood);
    while(improvement==true){
        int k=0;
        improvement = false;
        while(k<kmax && improvement==false){
            copy_sequence(sequence,sequence2);
            copy_sequence(Neighborhood(sequence2,data,neighborhood->get[k]),sequence1);
            if (sequence1->cost<sequence->cost){
                copy_sequence(sequence1,sequence);
                improvement=true;
            } else{
                k++;
            }
        }
    }
    free_Sequence(sequence1);
    free_Sequence(sequence2);
    return sequence;
}

Sequence GVNS(Sequence sequence,Data data,Array neighborhood,int iter_max,int iter_nip){
    Sequence solution=new_Sequence(sequence->size);
    bool changed=false;
    Sequence sequence1=new_Sequence(sequence->size);
    int iter_1=0;
    int iter_2=0;
    int iter_3=0;
    int nip=(int)(0.5*iter_nip);
    int k=0;
    while(iter_1<iter_max && iter_2<iter_nip) {
        Shaking(sequence, neighborhood->get[k],sequence1,data);
        Shuffle(neighborhood);
        sequence1 = LocalSearch(sequence1, data, neighborhood);
        if (sequence1->cost < sequence->cost) {
            copy_sequence(sequence1, sequence);
            iter_2 = 0;
            iter_3 = 0;
        } else {
            iter_2++;
            iter_3++;
        }
        k=(k+1)%neighborhood->size;
        iter_1++;
        if(iter_2<iter_nip && iter_3>nip){
            if(changed){
                if(sequence->cost<solution->cost){
                    copy_sequence(sequence,solution);
                }
            }else{
                copy_sequence(sequence,solution);
            }
            Shaking(sequence,rand()%sequence->size,sequence,data);
            changed=true;
            iter_3=0;
        }
    }
    if(!changed){
        copy_sequence(sequence,solution);
    }
    return solution;
}