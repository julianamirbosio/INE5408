/* Copyright [2022] <Alexandre Gonçalves Silva> */
#include <stdexcept>
#include "gtest/gtest.h"
#include "./iniciais.h"

int main(int argc, char* argv[]) {
    std::srand(std::time(NULL));
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

//! comment
class TestesIniciais: public ::testing::Test {
 protected:
    //! comment
    int A[5] = {10, 50, 30, 70, 20};
    int B[5] = {50, 90, 30, 40, 10};
    int N = 5;
};

TEST_F(TestesIniciais, Maximo) {
    ASSERT_EQ(70, maximo(A, N));
    ASSERT_EQ(90, maximo(B, N));
}

TEST_F(TestesIniciais, Posicao) {
    ASSERT_EQ(3, posicao(A, N));
    ASSERT_EQ(1, posicao(B, N));
}

TEST_F(TestesIniciais, MaximoPosicao) {
    maxpos MP1 = maximo_posicao(A, N);
    ASSERT_EQ(70, MP1.max);
    ASSERT_EQ(3, MP1.pos);
    maxpos MP2 = maximo_posicao(B, N);
    ASSERT_EQ(90, MP2.max);
    ASSERT_EQ(1, MP2.pos);
}

TEST_F(TestesIniciais, MaximoVetores) {
    int C[5] = {50, 90, 30, 70, 20};
    maximo_vetores(A, B, N);
    for (int i = 0; i < N; i++) {
        ASSERT_EQ(C[i], A[i]);
    }
}

TEST_F(TestesIniciais, Inversao) {
    int C[5] = {20, 70, 30, 50, 10};
    inversao(A, N);
    for (int i = 0; i < N; i++) {
        ASSERT_EQ(C[i], A[i]);
    }
    int D[5] = {10, 40, 30, 90, 50};
    inversao(B, N);
    for (int i = 0; i < N; i++) {
        ASSERT_EQ(D[i], B[i]);
    }
}