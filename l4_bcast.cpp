#include <mpi.h>
#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char **argv)
{
    int myid, numprocs;
    
    MPI_Status status;
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);
    string sms("Hi im the sms!!");;
    
    if(myid != 0)
    {        
        cout << "im in proc "<< myid << "\nThe sms is: " << sms<<endl;

    }else
    {
        MPI_Bcast(&sms, 1, MPI_INT, 0, MPI_COMM_WORLD);
    }
    
    MPI_Finalize();
    return 0;
}