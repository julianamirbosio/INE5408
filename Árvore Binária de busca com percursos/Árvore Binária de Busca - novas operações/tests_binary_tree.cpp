// Copyright 2020 Alexandre Gonçalves Silva (Height, Leaves, Limits, Clone,
//                                           Filter, Balance)
// Copyright 2016 João Paulo Taylor Ienczak Zanette

#include <string>
#include <vector>
#include "gtest/gtest.h"
#include "binary_tree.h"

/**
 * Valores a serem inseridos na árvore de inteiros.
 */
const auto int_values = std::vector<int>{
    10, 5, 8, 20, 25, 15, -5, -10, 30, -15, 27, 23
};

/**
 * Teste unitário para árvore binária
 */
class BinaryTreeTest: public testing::Test {
 protected:
    /**
     * Lista para teste com inteiros.
     */
    structures::BinaryTree<int> int_list{};

    /**
     * Testa uma inserção simples em uma lista.
     */
    template <typename T, typename U>
    void simple_insertion(T& list, U& values) {
        ASSERT_TRUE(list.empty());
        list.insert(values[0]);
        ASSERT_FALSE(list.empty());
        ASSERT_EQ(1, list.size());
    }

    /**
     * Testa a inserção de múltiplos valores em uma lista.
     */
    template <typename T, typename U>
    void multiple_insertion(T& list, const U& values) {
        ASSERT_TRUE(list.empty());
        for (auto& value : values) {
            list.insert(value);
        }
        ASSERT_FALSE(list.empty());
        ASSERT_EQ(values.size(), list.size());
    }

    /**
     * Testa se todos os valores inseridos estão na lista.
     */
    template <typename T, typename U>
    void contains_all(const T& list, const U& values) {
        for (auto& value : values) {
            ASSERT_TRUE(list.contains(value));
        }
    }
};

/**
 * Testa altura.
 */
TEST_F(BinaryTreeTest, Height) {
    {
        multiple_insertion(int_list, int_values);
        ASSERT_EQ(4, int_list.height());
        int_list.remove(-15);
        int_list.remove(27);
        ASSERT_EQ(3, int_list.height());
    }
}

/**
 * Testa número de folhas.
 */
TEST_F(BinaryTreeTest, Leaves) {
    {
        multiple_insertion(int_list, int_values);
        ASSERT_EQ(5, int_list.leaves());
        int_list.remove(27);
        int_list.remove(30);
        ASSERT_EQ(4, int_list.leaves());
    }
}

/**
 * Testa limites.
 */
TEST_F(BinaryTreeTest, Limits) {
    {
        multiple_insertion(int_list, int_values);

        auto limits1 = int_list.limits();

        auto expected = {-15, 30};
        auto i = 0u;
        for (auto& value : expected) {
            ASSERT_EQ(value, limits1[i]);
            ++i;
        }

        int_list.remove(-15); int_list.remove(-10);
        int_list.remove(-5);
        int_list.remove(27); int_list.remove(30);

        auto limits2 = int_list.limits();

        auto expected2 = {5, 25};
        i = 0u;
        for (auto& value : expected2) {
            ASSERT_EQ(value, limits2[i]);
            ++i;
        }
    }
}

/**
 * Testa clone.
 */
TEST_F(BinaryTreeTest, Clone) {
    {
        multiple_insertion(int_list, int_values);
        auto clone_ = int_list.clone();

        auto preordered = clone_.pre_order();
        auto preexpected = int_list.pre_order();
        for (auto i = 0u; i < preexpected.size(); i++) {
            ASSERT_EQ(preexpected[i], preordered[i]);
        }

        auto postordered = clone_.post_order();
        auto postexpected = int_list.post_order();
        for (auto i = 0u; i < postexpected.size(); i++) {
            ASSERT_EQ(postexpected[i], postordered[i]);
        }
    }
}

/**
 * Testa filter
 */
TEST_F(BinaryTreeTest, Filter) {
    {
        multiple_insertion(int_list, int_values);
        auto clone1 = int_list.clone();
        auto clone2 = int_list.clone();

        auto int_list2 = int_list.clone();

        clone1.remove(-15); clone1.remove(8);
        clone1.remove(15); clone1.remove(23);
        clone1.remove(27);

        int_list.filter(0);

        auto preordered = clone1.pre_order();
        auto preexpected = int_list.pre_order();
        for (auto i = 0u; i < preexpected.size(); i++) {
            ASSERT_EQ(preexpected[i], preordered[i]);
        }

        auto postordered = clone1.post_order();
        auto postexpected = int_list.post_order();
        for (auto i = 0u; i < postexpected.size(); i++) {
            ASSERT_EQ(postexpected[i], postordered[i]);
        }

        // ---

        clone2.remove(-10); clone2.remove(-5);
        clone2.remove(30);

        int_list2.filter(1);

        auto preordered2 = clone2.pre_order();
        auto preexpected2 = int_list2.pre_order();
        for (auto i = 0u; i < preexpected2.size(); i++) {
            ASSERT_EQ(preexpected2[i], preordered2[i]);
        }

        auto postordered2 = clone2.post_order();
        auto postexpected2 = int_list2.post_order();
        for (auto i = 0u; i < postexpected2.size(); i++) {
            ASSERT_EQ(postexpected2[i], postordered2[i]);
        }
    }
}

/**
 * Testa balanceamento.
 */
TEST_F(BinaryTreeTest, Balance) {
    {
        multiple_insertion(int_list, int_values);
        auto balance_ = int_list.balance();

        auto inordered = balance_.in_order();
        auto expected = int_list.in_order();

        for (auto i = 0u; i < expected.size(); i++) {
            ASSERT_EQ(expected[i], inordered[i]);
        }

        ASSERT_EQ(3, balance_.height());
    }
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}