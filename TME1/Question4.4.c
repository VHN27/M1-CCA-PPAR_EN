#include <stdio.h>
#include <string.h>
#include <mpi.h>
#include <unistd.h>

#define SIZE_H_N 50
int main(int argc, char* argv[])
{
  int my_rank; /* rank of the process */
  int p; /* number of processes */
  int source; /* rank of the source */
  int dest; /* rank of the receiver */
  int tag = 0; /* tag of the message */
  char message[100];
  MPI_Status status;
  char hostname[SIZE_H_N];
  gethostname(hostname, SIZE_H_N);
  /* Initialisation */
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  MPI_Comm_size(MPI_COMM_WORLD, &p);

  //Sending message to the successor:
  if (my_rank < p - 1){
    sprintf(message, "Coucou du processus #%d depuis %s!", my_rank, hostname);
    printf("Sending message..... at #%d to #%d\n", my_rank, my_rank+1);
    dest = my_rank + 1;
    MPI_Ssend(message, strlen(message)+1, MPI_CHAR, dest, tag, MPI_COMM_WORLD);
  }else{
    sprintf(message, "Coucou du processus #%d depuis %s!", my_rank, hostname);
    printf("Sending message..... at #%d to 0\n", my_rank);
    dest = 0;
    MPI_Send(message, strlen(message)+1, MPI_CHAR, dest, tag, MPI_COMM_WORLD);
  }

  //Recieving message from the predecessor:
  if (my_rank == 0){
    printf("Recieving message..... at #%d\n", my_rank);
    MPI_Recv(message, 100, MPI_CHAR, p-1, tag, MPI_COMM_WORLD, &status);
    printf("Sur %s, le processus #%d a recu le message : %s\n",hostname, my_rank, message);
  }else{
    printf("Recieving message..... at #%d\n", my_rank);
    MPI_Recv(message, 100, MPI_CHAR, my_rank-1, tag, MPI_COMM_WORLD, &status);
    printf("Sur %s, le processus #%d a recu le message : %s\n",hostname, my_rank, message);
  }
  

  MPI_Finalize();
}