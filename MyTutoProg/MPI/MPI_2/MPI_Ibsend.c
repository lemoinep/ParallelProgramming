/**
 * @author RookieHPC
 * @brief Original source code at https://rookiehpc.org/mpi/docs/mpi_ibsend/index.html
 **/

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

/**
 * @brief Illustrates how to send a message in a non-blocking asynchronous
 * fashion.
 * @details This program is meant to be run with 2 processes: a sender and a
 * receiver.
 **/
int main(int argc, char* argv[])
{
    MPI_Init(&argc, &argv);

    // Get the number of processes and check 2 processes are used
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if(size != 2)
    {
        printf("This application is meant to be run with 2 processes.\n");
        MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
    }

    // Get my rank and do the corresponding job
    enum role_ranks { SENDER, RECEIVER };
    int my_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    switch(my_rank)
    {
        case SENDER:
        {
            // Declare the buffer and attach it
            int buffer_attached_size = MPI_BSEND_OVERHEAD + sizeof(int);
            char* buffer_attached = malloc(buffer_attached_size);
            MPI_Buffer_attach(buffer_attached, buffer_attached_size);

            // Issue the MPI_Ibsend
            int buffer_sent = 12345;
            MPI_Request request;
            printf("MPI process %d sends value %d.\n", my_rank, buffer_sent);
            MPI_Ibsend(&buffer_sent, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &request);
            
            // Let's wait for the MPI_Ibsend to complete before progressing further.
            MPI_Wait(&request, MPI_STATUS_IGNORE);

            // Detach the buffer. It blocks until all messages stored are sent.
            MPI_Buffer_detach(&buffer_attached, &buffer_attached_size);
            free(buffer_attached);
            break;
        }
        case RECEIVER:
        {
            int received;
            MPI_Recv(&received, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("MPI process %d received value: %d.\n", my_rank, received);
            break;
        }
    }

    MPI_Finalize();

    return EXIT_SUCCESS;
}
