/**
 * @author RookieHPC
 * @brief Original source code at https://rookiehpc.org/mpi/docs/mpi_ibcast/index.html
 **/

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

/**
 * @brief Illustrates how to broadcast a message in a non-blocking way.
 * @details This code picks a process as the broadcast root, and makes it
 * broadcast a specific value. Other processes participate to the broadcast as
 * receivers. These processes then print the value they received via the 
 * broadcast.
 **/
int main(int argc, char* argv[])
{
    MPI_Init(&argc, &argv);

    // Get my rank in the communicator
    int my_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    // Determine the rank of the broadcast emitter process
    int broadcast_root = 0;

    int buffer;
    if(my_rank == broadcast_root)
    {
        buffer = 12345;
        printf("[MPI process %d] I am the broadcast root, and send value %d.\n", my_rank, buffer);
    }
    MPI_Request request;
    MPI_Ibcast(&buffer, 1, MPI_INT, broadcast_root, MPI_COMM_WORLD, &request);

    // Do some computation ...

    MPI_Wait(&request, MPI_STATUS_IGNORE);

    if(my_rank != broadcast_root)
    {
        printf("[MPI process %d] I am a broadcast receiver, and obtained value %d.\n", my_rank, buffer);
    }

    MPI_Finalize();

    return EXIT_SUCCESS;
}
