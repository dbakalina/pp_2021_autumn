// Copyright 2021 TexHik620953
#include <mpi.h>
#include <gtest/gtest.h>
#include <vector>
#include <gtest-mpi-listener.hpp>
#include "../../../modules/task_2/rodionov_n_broadcast_message/broadcast_message.h"
#include <stdio.h>
#include <locale.h>
#include <conio.h>
int length = 5000;
int root = 0;
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    MPI_Init(&argc, &argv);

    ::testing::AddGlobalTestEnvironment(new GTestMPIListener::MPIEnvironment);
    ::testing::TestEventListeners& listeners =
        ::testing::UnitTest::GetInstance()->listeners();

    listeners.Release(listeners.default_result_printer());
    listeners.Release(listeners.default_xml_generator());

    listeners.Append(new GTestMPIListener::MPIMinimalistPrinter);

    return RUN_ALL_TESTS();
}


TEST(BroadCastTest, test1) {
    int commSize, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &commSize);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    //Create matrix
    double* linear_matrix = new double[commSize * length];
    double seq_sum = 0;
    for (int i = 0; i < commSize * length; i++) {
        linear_matrix[i] = rand();
        seq_sum += linear_matrix[i];
    }

    double mpi_result = 0;
    BroadcastSum(linear_matrix, &mpi_result, length, root, MPI_DOUBLE);
    //double seq_test = sumSeq(linear_matrix, commSize * length);
    if (rank == root) {
        ASSERT_EQ(mpi_result, 0);
    }

}