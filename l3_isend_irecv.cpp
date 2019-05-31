#include <mpi.h>
#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char **argv)
{
    int myid, numprocs, left, right;
    string buffer("Im the message");
    MPI_Request request;
    MPI_Status status;

    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);
    
    MPI_Irecv(&buffer, buffer.size(), MPI_INT, MPI_ANY_SOURCE, 1, MPI_COMM_WORLD, &request);
    cout<<"recv from "<<myid<<", the sms is "<< buffer<<endl;
    
    MPI_Isend(&buffer, buffer.size(), MPI_INT, 0, 1, MPI_COMM_WORLD, &request);
    cout<<"send from "<<myid<<endl;

    MPI_Wait(&request, &status);
    // MPI_Wait(&request2, &status);
    MPI_Finalize();
    return 0;
}