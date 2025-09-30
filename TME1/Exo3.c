#include <stdio.h>
#include <mpi.h>

int main(int argc, char* argv[])
{
  int rank, p, value, tag = 10;
  MPI_Status status;
  /* Initialisation */
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &p);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  if (rank == 1) {
    value = 18;
    MPI_Send(&value, 1, MPI_INT, 0, tag, MPI_COMM_WORLD);
  } else if (rank == 0) {
    MPI_Recv(&value, 1, MPI_INT, 1, tag, MPI_COMM_WORLD, &status);
    printf("I have received the value %d from the process of rank 1.\n", value);
  }
  MPI_Finalize();
}
