/* Copyright [2022] <Alexandre Gonçalves Silva> */
#include <stdexcept>
#include <string>
#include "gtest/gtest.h"
#include "./chaves.h"

int main(int argc, char* argv[]) {
    std::srand(std::time(NULL));
    ::testing::InitGoogleTest(&argc, argv);
    // ::testing::FLAGS_gtest_death_test_style = "fast";
    return RUN_ALL_TESTS();
}

//! comment
/* comment */
class ArrayStackTest: public ::testing::Test {
 protected:
    //! comment
    // structures::ArrayStack<int> stack{500u};
};

TEST_F(ArrayStackTest, Teste1) {
    std::string trecho_programa = "int main() {\n    std::string trecho_programa = \"{UFSC}\";\n    bool ok = verificaChaves(trecho_programa);\n    if (ok) {\n        std::cout << \"Tudo certo\" << std::endl;\n    } else {\n        std::cout << \"Há problema\" << std::endl;\n    }\n    return 0;\n}\n";
    bool ok = verificaChaves(trecho_programa);
    ASSERT_TRUE(ok);
}

TEST_F(ArrayStackTest, Teste2) {
    std::string trecho_programa = "int main() {\n    std::string trecho_programa = \"{UFSC}\";\n    bool ok = verificaChaves(trecho_programa);\n    if (ok) \n        std::cout << \"Tudo certo\" << std::endl;\n    } else {\n        std::cout << \"Há problema\" << std::endl;\n    }\n    return 0;\n}\n";
    bool ok = verificaChaves(trecho_programa);
    ASSERT_FALSE(ok);
}

TEST_F(ArrayStackTest, Teste3) {
    std::string trecho_programa = "int main() {\n    std::string trecho_programa = \"{UFSC}\";\n    bool ok = verificaChaves(trecho_programa);\n    if (ok) {\n        std::cout << \"Tudo certo\" << std::endl;\n    }} else {\n        std::cout << \"Há problema\" << std::endl;\n    }\n    return 0;\n}\n";
    bool ok = verificaChaves(trecho_programa);
    ASSERT_FALSE(ok);
}

TEST_F(ArrayStackTest, Teste4) {
    std::string trecho_programa = "int main() {{\n    std::string trecho_programa = \"{UFSC}\";\n    bool ok = verificaChaves(trecho_programa);\n    if (ok) {\n        std::cout << \"Tudo certo\" << std::endl;\n    } else {\n        std::cout << \"Há problema\" << std::endl;\n    }\n    return 0;\n}\n}";
    bool ok = verificaChaves(trecho_programa);
    ASSERT_TRUE(ok);
}

TEST_F(ArrayStackTest, Teste5) {
    std::string trecho_programa = "int main() {\n    std::string trecho_programa = \"{UFSC}\";\n    bool ok = verificaChaves(trecho_programa);\n    if (ok) {\n        std::cout << \"Tudo certo\" << std::endl;\n    } else {\n        std::cout << \"Há problema\" << std::endl;\n    }\n    return 0;\n}\n}";
    bool ok = verificaChaves(trecho_programa);
    ASSERT_FALSE(ok);
}