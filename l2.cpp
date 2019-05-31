#include <cstdlib>
#include <ctime>
#include <iostream>
#include <math.h>
#include <mpi.h>

using namespace std;

int main(int argc, char **argv)
{
    int id, nproc, id_from;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &nproc); //get number of total nodes
    MPI_Comm_rank(MPI_COMM_WORLD, &id);    // get id of my node
    
    if(id != 0)
    {
        // Slave processes sending greetings:
        cout<<"Process id= "<<id<<" SENDING!"<<endl;
        MPI_Send(&id, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
    }
    else
    {
        // Master process receiving greetings:
        cout<<"Master process (id=0) RECEIVING"<<endl;
        for(int i=1;i<nproc;++i)
        {
            MPI_Recv(&id_from, 1, MPI_INT, MPI_ANY_SOURCE, 1, MPI_COMM_WORLD,
            &status);
            // After receiving the message, check the status to determine
            // how many numbers were actually received
            MPI_Get_count(&status, MPI_INT, &id_from);
            
            cout << "received from " << id_from<< ". Message source "<< status.MPI_SOURCE<<", tag = " <<status.MPI_TAG<<endl;
            
        }
    }
    MPI_Finalize();

    
    return 0;
}
