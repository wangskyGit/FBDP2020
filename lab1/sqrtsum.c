#include <stdio.h>    
#include <mpi.h>   
#include <math.h>    
#define N 1002 
int main(int argc, char** argv) { 
    int myid, P, source, numprocs, C=0; 
    double  data[N], SqrtSum=0.0; 
    for (int i=0;i<N;i++)
        data[i]=i;
    MPI_Status status;   
    char message[100]; 
    MPI_Init(&argc, &argv); 
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);  
    MPI_Comm_size(MPI_COMM_WORLD,&numprocs);   
    - -numprocs; 
    double sum=0,inte;
    for (int k=0;k<N;k++)
        if(myid!=0){
            if(k%(numprocs-1)==myid-1)
                sum+=sqrt(k);
        }
    MPI_Reduce(&sum,&inte,1,MPI_DOUBLE,MPI_SUM, 0, MPI_COMM_WORLD);
    if(myid==0){
        printf("The total SqrtSum=%f.\n",inte); 
    }
    MPI_Finalize(); 
    }