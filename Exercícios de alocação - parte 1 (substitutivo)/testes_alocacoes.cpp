/* Copyright [2022] <Alexandre Gonçalves Silva> */
#include <stdexcept>
#include <string>
#include "gtest/gtest.h"
#include "./alocacoes.h"

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

    std::string nomes2[3] = {"Mariana", "Viviane", "Zeca"};
    int matriculas2[3] = {99, 77, 66};
    int N2 = 3;
};

TEST_F(TestesAlocacoes, Turma) {
    Aluno *t1 = turma(nomes1, matriculas1, N1);
    for (int i = 0; i < N1; i++) {
        ASSERT_EQ(matriculas1[i], t1[i].devolveMatricula());
    }
    Aluno *t2 = turma(nomes2, matriculas2, N2);
    for (int i = 0; i < N2; i++) {
        ASSERT_EQ(matriculas2[i], t2[i].devolveMatricula());
    }
    delete [] t1;
    delete [] t2;
}

TEST_F(TestesAlocacoes, TurmasUniao) {
    Aluno *t1 = turma(nomes1, matriculas1, N1);
    Aluno *t2 = turma(nomes2, matriculas2, N2);
    Aluno *tu = turmas_uniao(t1, t2, N1, N2);
    for (int i = 0; i < N1; i++) {
        ASSERT_EQ(matriculas1[i], tu[i].devolveMatricula());
    }
    for (int i = 0; i < N2; i++) {
        ASSERT_EQ(matriculas2[i], tu[N1+i].devolveMatricula());
    }
    delete [] t1;
    delete [] t2;
    delete [] tu;
}

TEST_F(TestesAlocacoes, TurmasDivisao) {
    Aluno *t1_ = turma(nomes1, matriculas1, N1);
    Aluno *t2_ = turma(nomes2, matriculas2, N2);
    Aluno *tu = turmas_uniao(t1_, t2_, N1, N2);

    Aluno *t1, *t2;
    turmas_divisao(tu, 3, N1+N2, &t1, &t2);

    for (int i = 0; i < 3; i++) {
        ASSERT_EQ(matriculas1[i], t1[i].devolveMatricula());
    }
    for (int i = 3; i < N1; i++) {
        ASSERT_EQ(matriculas1[i], t2[i-3].devolveMatricula());
    }
    for (int i = 0; i < N2; i++) {
        ASSERT_EQ(matriculas2[i], t2[N1+i-3].devolveMatricula());
    }
    delete [] t1_;
    delete [] t2_;
    delete [] tu;
    delete [] t1;
    delete [] t2;
}