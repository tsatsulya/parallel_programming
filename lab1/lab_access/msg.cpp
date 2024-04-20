#include <iostream>
#include <mpi.h>
#include <ctime>
#include <chrono>


int main(int argc, char** argv) {
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

    int num_of_proc, process_id;
    int msg = 0;
    MPI_Comm_size(MPI_COMM_WORLD, &num_of_proc);
    MPI_Comm_rank(MPI_COMM_WORLD, &process_id);

    // std::cout << "hello from process " << process_id << std::endl;
    if (process_id == 0) {
        auto start = std::chrono::system_clock::now();
        for (int i = 0; i < n; ++i) {
            MPI_Recv(&msg, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
        auto end = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = end - start;
        std::cout << "duration of single recv-send session: " <<
            elapsed_seconds.count() * 1000 / n << " (ms)" << std::endl;
    }
    else {
        for (int i = 0; i < n; ++i) {
            MPI_Send(&msg, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        }
    }
    MPI_Finalize();
    return 0;
}