/* Copyright [2023] <Alexandre Gonçalves Silva> */
#include <stdexcept>
#include <string>
#include "gtest/gtest.h"
#include "./array_queue.h"
#include "./estacionamento.h"

int main(int argc, char* argv[]) {
    std::srand(std::time(NULL));
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

//! comment
class TestesEstacionamento: public ::testing::Test {
 protected:
    //! comment
    int N = 5;
    int carros_e[6] = {11, 44, 55, 22, 33};

    int k1 = 3;
    int carros1_s[6] = {22, 33, 11, 44};

    int k2 = 1;
    int carros2_s[6] = {44, 55, 22, 33};

    int k3 = 5;
    int carros3_s[6] = {11, 44, 55, 22};
};

TEST_F(TestesEstacionamento, RetiraVeiculo) {
    int i;
    structures::ArrayQueue<int> f1;
    structures::ArrayQueue<int> f2;
    structures::ArrayQueue<int> f3;
    for (i = 0; i < N; i++) {
        f1.enqueue(carros_e[i]);
        f2.enqueue(carros_e[i]);
        f3.enqueue(carros_e[i]);
    }
    retira_veiculo(&f1, k1);  // teste 1 da funcao 1 do estudante
    retira_veiculo(&f2, k2);  // teste 2 da funcao 1 do estudante
    retira_veiculo(&f3, k3);  // teste 3 da funcao 1 do estudante
    for (i = 0; i < N-1; i++) {
        ASSERT_EQ(carros1_s[i], f1.dequeue());
        ASSERT_EQ(carros2_s[i], f2.dequeue());
        ASSERT_EQ(carros3_s[i], f3.dequeue());
    }
}

TEST_F(TestesEstacionamento, MantenhaVeiculo) {
    int i;
    structures::ArrayQueue<int> f1;
    structures::ArrayQueue<int> f2;
    structures::ArrayQueue<int> f3;
    for (i = 0; i < N; i++) {
        f1.enqueue(carros_e[i]);
        f2.enqueue(carros_e[i]);
        f3.enqueue(carros_e[i]);
    }
    mantenha_veiculo(&f1, k1);  // teste 1 da funcao 2 do estudante
    mantenha_veiculo(&f2, k2);  // teste 2 da funcao 2 do estudante
    mantenha_veiculo(&f3, k3);  // teste 3 da funcao 2 do estudante
    ASSERT_EQ(55, f1.dequeue());
    ASSERT_EQ(11, f2.dequeue());
    ASSERT_EQ(33, f3.dequeue());
}
