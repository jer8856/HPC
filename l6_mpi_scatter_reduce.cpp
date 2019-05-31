#include <cstdlib>
#include <ctime>
#include <iostream>
#include <math.h>
#include <mpi.h>

using namespace std;

int main(int argc, char **argv)
{
    int id, nproc;
    int sum, startval, endval, accum;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &nproc); //get number of total nodes
    MPI_Comm_rank(MPI_COMM_WORLD, &id);    // get id of my node
    
    int x[] {10,4,5,6,7,8,23,2,3,4};
    int n = sizeof(x)/sizeof(int);
    int local_sum, global_sum;
    
    int i,from,to;

    from = id * n/nproc;
    to = (id+1) * n/nproc;
    
    MPI_Scatter(&x, from, MPI_INT, &x[to], to, MPI_INT, 0, MPI_COMM_WORLD);
    local_sum=0;
    for(i=from;i<to;i++)
    {
        local_sum+=x[i];
    }
    cout<<"local sum = " << local_sum<< " proc = " << id<<endl;

    MPI_Reduce(&local_sum, &global_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Finalize();

    if(id==0) cout<<"global sum = " << global_sum<< " proc = " << id<<endl;    
    return 0;
}
