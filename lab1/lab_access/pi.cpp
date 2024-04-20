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

    unsigned int n = strtoul(argv[1], NULL, 10);

    if (n == 0) {
        std::cout << "Invalid _number of iterations_" << std::endl;
        MPI_Finalize();
        return 1;
    }

    int root_id = 0, num_of_proc, process_id;
    long double term, local_result = 0, result = 0;

    MPI_Comm_rank(MPI_COMM_WORLD, &process_id);
    MPI_Comm_size(MPI_COMM_WORLD, &num_of_proc);

    for (int i = process_id; i <= n; i += num_of_proc) {
        term = 1.0/(i+1)/(i+1);
        local_result += term;
    }
    MPI_Reduce(&local_result, &result, 1, MPI_LONG_DOUBLE, MPI_SUM, root_id, MPI_COMM_WORLD);

    if (process_id == 0) {
        std::cout << sqrt(result * 6);
    }
    MPI_Finalize();
    return 0;
}