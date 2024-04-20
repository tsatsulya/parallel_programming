#include <iostream>
#include <stdexcept>
#include "mpi.h"
#include <cmath>

int main(int argc, char **argv) {

    if (argc < 2) {
        std::cout << "Please specify the _number of iterations_" << std::endl;
        return 1;
    }

    if (int err_code = MPI_Init(&argc, &argv)) {
        return err_code;
    }

    const unsigned int n = strtoul(argv[1], NULL, 10);

    if (n == 0) {
        std::cout << "Invalid _number of iterations_" << std::endl;
        MPI_Finalize();
        return 1;
    }

    int root_id = 0, num_of_proc, process_id;
    long double term, result = 0, local_result = 0;

    MPI_Comm_rank(MPI_COMM_WORLD, &process_id);
    MPI_Comm_size(MPI_COMM_WORLD, &num_of_proc);
    for (int i = process_id; i < n; i += num_of_proc) {
        term = 1.0/(i+1)/(i+1);
        result += term;
    }

    if (process_id < num_of_proc - 1) {
        MPI_Recv(&local_result, 1, MPI_LONG_DOUBLE, process_id + 1, 0, MPI_COMM_WORLD,
             MPI_STATUS_IGNORE);
        result += local_result;
    }
    if (process_id > 0) {
        MPI_Send(&result, 1, MPI_LONG_DOUBLE, process_id - 1, 0, MPI_COMM_WORLD);
    }

    MPI_Barrier(MPI_COMM_WORLD);

    if (process_id == 0) {
        result = local_result + 1; // + 1/(1^2)
        std::cout << sqrt(result * 6);
    }
    MPI_Finalize();
    return 0;
}
