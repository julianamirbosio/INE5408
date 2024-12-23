/* Copyright [2023] <Alexandre Gonçalves Silva> */
#include <stdexcept>
#include <string>
#include "gtest/gtest.h"
#include "./alocacoes.h"

Aluno *turma(std::string nomes[], int matriculas[], int N) {
    Aluno *t = new Aluno[N];
    for (int i = 0; i < N; i++) {
        t[i].escreveNome(nomes[i]);
        t[i].escreveMatricula(matriculas[i]);
    }
    return t;
}

int main(int argc, char* argv[]) {
    std::srand(std::time(NULL));
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

//! comment
class TestesAlocacoes: public ::testing::Test {
 protected:
    //! comment
    std::string nomes1[6] =
        {"Alana", "Arthur", "Lorena", "Maria", "Pedro", "Olivia"};
    int matriculas1[6] = {11, 22, 33, 44, 55};
    int N1 = 6;

    std::string nomes2[3] = {"Maria", "Pedro", "Olivia"};
    int matriculas2[3] = {33, 44, 55};
    int N2 = 3;

    int matriculas3[3] = {55};

    // A B C D E F G H I J K L M N O P Q R S T U V W X Y Z
    int A[26] = {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0,
                 0, 0, 0, 0, 0, 0};
    int B[26] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0,
                 0, 0, 0, 0, 0, 0};
};

TEST_F(TestesAlocacoes, TurmaFiltra) {
    Aluno *t1 = turma(nomes1, matriculas1, N1);
    Aluno *t2 = turma(nomes2, matriculas2, N2);
    Aluno *tf1 = turma_filtra(t1, N1, 33);
    for (int i = 0; i < 3; i++) {
        ASSERT_EQ(matriculas2[i], tf1[i].devolveMatricula());
    }
    Aluno *tf2 = turma_filtra(t2, N2, 50);
    for (int i = 0; i < 1; i++) {
        ASSERT_EQ(matriculas3[i], tf2[i].devolveMatricula());
    }
    delete [] t1;
    delete [] t2;
    delete [] tf1;
    delete [] tf2;
}

TEST_F(TestesAlocacoes, TurmaConta) {
    Aluno *t1 = turma(nomes1, matriculas1, N1);
    Aluno *t2 = turma(nomes2, matriculas2, N2);
    int *c1 = turma_conta(t1, N1);
    int *c2 = turma_conta(t2, N2);

    for (int i = 0; i < 26; i++) {
        ASSERT_EQ(A[i], c1[i]);
    }
    for (int i = 0; i < 26; i++) {
        ASSERT_EQ(B[i], c2[i]);
    }
    delete [] t1;
    delete [] t2;
    delete [] c1;
    delete [] c2;
}