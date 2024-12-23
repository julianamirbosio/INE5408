/* Copyright [2022] <Alexandre Gonçalves Silva> */
#include <stdexcept>
#include <string>
#include "gtest/gtest.h"
#include "./edita_texto.h"

int main(int argc, char* argv[]) {
    std::srand(std::time(NULL));
    ::testing::InitGoogleTest(&argc, argv);
    // ::testing::FLAGS_gtest_death_test_style = "fast";
    return RUN_ALL_TESTS();
}

std::string constroiTexto(structures::ArrayQueue<char> fila) {
    std::string texto = "";
    while (!fila.empty()) {
        texto = texto + fila.dequeue();
    }
    return texto;
}

//! comment
/* comment */
class ArrayQueueTest: public ::testing::Test {
 protected:
    //! comment
    // structures::ArrayQueue<char> queue{500u};
};

TEST_F(ArrayQueueTest, Teste1) {
    std::string texto = "2022< Universidade <<Federal ->> Santa<< Catarina";
    structures::ArrayQueue<char> fila = editaTexto(texto);
    std::string saida = constroiTexto(fila);
    ASSERT_EQ(saida.compare("Universidade Federal --- Santa Catarina"), 0);
}

TEST_F(ArrayQueueTest, Teste2) {
    std::string texto = "abcdefg<<hij>><<<>k>lmn";
    structures::ArrayQueue<char> fila = editaTexto(texto);
    std::string saida = constroiTexto(fila);
    ASSERT_EQ(saida.compare("fghijjjjkklmn"), 0);
}

TEST_F(ArrayQueueTest, Teste3) {
    std::string texto = "ab><c><<<<";
    structures::ArrayQueue<char> fila = editaTexto(texto);
    std::string saida = constroiTexto(fila);
    ASSERT_EQ(saida.compare(""), 0);
}

TEST_F(ArrayQueueTest, Teste4) {
    std::string texto = "ab><c><<<<<";
    ASSERT_THROW(editaTexto(texto), std::out_of_range);
}