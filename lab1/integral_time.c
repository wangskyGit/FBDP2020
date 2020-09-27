#define N 100000000
#define  a 0 
#define  b 10
#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
#include "mpi.h"
int main(int argc, char** argv) 
{ 
    int myid,numprocs; 
    int i; 
    double time;
    clock_t start,finish;
    start=clock();
    double local=0.0, dx=(double)(b-a)/N;   
    double inte, x; 
    MPI_Status status;
    MPI_Init(&argc, &argv); 
    MPI_Comm_rank(MPI_COMM_WORLD, &myid); 
    MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
    for(i=myid;i<N;i=i+numprocs) {
        x = a + i*dx +dx/2; 
        local +=x*x*dx; 
    }
    double p=local;
    if(myid!=0){
        MPI_Send(&local,1,MPI_DOUBLE,0,1,MPI_COMM_WORLD); 
    }
    else if(myid==0)
    {   
        for(int source=1;source<numprocs;source++) 
        {
	double local1;	
	MPI_Recv(&local1,1,MPI_DOUBLE,source,1,MPI_COMM_WORLD,&status); 
        p=p+local1;
        }
	finish=clock();
	time=(double)(finish-start)/CLOCKS_PER_SEC;//计算运行时间
	printf("time=%lf\n",time);//输出运行时间
        printf("The integal of x*x in region [%d,%d] =%16.15f\n", a, b, p); 
    }
    MPI_Finalize(); 
} 
 
