#include <mpi.h>
#include <stdio.h>

#define PRINT 2
#define PRINT_END 3

#define MAX_MESSAGE_SIZE 500

int main(int argc, char **argv){
    int nr_philosophers;
    int done_philosophers = 0;

    MPI_Init (&argc, &argv);
    MPI_Comm_size (MPI_COMM_WORLD, &nr_philosophers);
    nr_philosophers--;

    while(done_philosophers < nr_philosophers){
        MPI_Status status;
        char msg[MAX_MESSAGE_SIZE] = {0};

        MPI_Recv(msg, MAX_MESSAGE_SIZE, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

        switch(status.MPI_TAG){
            case PRINT:
                printf("%s", msg);
                break;
            case PRINT_END:
                done_philosophers++;
                break;
            default:
                printf("PRINTING MASTER: Unknown tag\n");
        }
    }


    MPI_Finalize();
    return 0;
}