// matrix-vector multiplication
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <math.h>
#include <mpi.h>

using namespace std;

int main(int argc, char **argv)
{
    int id, nproc;
    // int sum, startval, endval, accum;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &nproc); //get number of total nodes
    MPI_Comm_rank(MPI_COMM_WORLD, &id);    // get id of my node
    int n=6;
    int A[n][n] = {{1,2,3,1,2,3}, {1,2,3,1,2,3}, {1,2,3,1,2,3}, 
                   {1,2,3,1,2,3}, {1,2,3,1,2,3}, {1,2,3,1,2,3}};
    int x[n] = {1,2,3,1,2,3};
    int s[n]{};
    int i,j,k,from,to;

    from = id * n/nproc;
    to = (id+1) * n/nproc;

    MPI_Bcast(&A, n*n, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(&x, n/nproc, MPI_INT, A[from], n/nproc, MPI_INT, 0, MPI_COMM_WORLD);

    cout<<"computing slice " << id<< " from row "<< from << " to "<< to-1 << endl;
    for (i=from; i<to; i++)
    {
        for (j=0; j<n; j++)
        {
            s[i]=0;
            for (k=0; k<n; k++)	s[i] += A[i][k]*x[k];
        }
    }

    MPI_Gather(&s[from], n/nproc, MPI_INT, s, n/nproc, MPI_INT, 0, MPI_COMM_WORLD);
    
    if(id==0)
    {
        for(const auto &elem:s) cout<< elem<< " ";
        cout << endl;
    }   
    MPI_Finalize();

    
    return 0;
}
