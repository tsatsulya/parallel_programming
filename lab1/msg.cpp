#include <iostream>
#include <mpi.h>

int main() {
    MPI_Init(NULL, NULL);

    // Number of processes
    int cluster_size;
    MPI_Comm_size(MPI_COMM_WORLD, &cluster_size);

    // Number of current process
    int process_id;
    MPI_Comm_rank(MPI_COMM_WORLD, &process_id);

    std::cout << "Hello! - sent from process " << process_id << std::endl;

    MPI_Finalize();
    std::cout << "myau";
    return 0;
}
