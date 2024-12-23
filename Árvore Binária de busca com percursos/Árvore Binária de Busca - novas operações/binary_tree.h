//!  Copyright [2024] <Juliana Miranda Bosio>

#ifndef STRUCTURES_BINARY_TREE_H
#define STRUCTURES_BINARY_TREE_H

#include "./array_list.h"


namespace structures {

//! Classe Árvore binária
template<typename T>
class BinaryTree {
 public:
    //! ...
    BinaryTree();
    //! ...
    ~BinaryTree();
    //! ...
    void insert(const T& data);
    //! ...
    void remove(const T& data);
    //! ...
    bool contains(const T& data) const;
    //! ...
    bool empty() const;
    //! ...
    std::size_t size() const;
    //! ...
    ArrayList<T> pre_order() const;
    //! ...
    ArrayList<T> in_order() const;
    //! ...
    ArrayList<T> post_order() const;

    //******************************************************************
    // Prova prática - implementações necessárias:

    // (1) determinação da altura da árvore:
    int height();

    // (2) contagem do número de folhas:
    int leaves();

    // (3) criação de uma lista com o menor (mínimo) e o maior (máximo)
    //     valor da árvore:
    ArrayList<T> limits();

    // (4) criação de uma duplicação, em memória, da árvore:
    BinaryTree<T> clone();

    // (5) remove nós pelo número de seus filhos:
    void filter(int n_child);

    // (6) criação de um nova árvore que tenha todos os valores e a
    //     menor altura possível, ou seja, balanceada com base apenas
    //     no estabelecimento de uma nova ordem de inserção:
    BinaryTree<T> balance();

    //******************************************************************


 private:
    struct Node {
        //! Construtor
        explicit Node(const T& data_) :
        data{data_}
        {}

        //! Destrutor
        // ~Node() {
        //     delete left_;
        //     delete right_;
        // }

        T data;
        Node* left{nullptr};
        Node* right{nullptr};

        //! Inserção
        void insert(const T& data_) {
            if (data_ < data) {
                if (left == nullptr) {
                    left = new Node(data_);
                } else {
                    left->insert(data_);
                }
            } else {
                if (right == nullptr) {
                    right = new Node(data_);
                } else {
                    right->insert(data_);
                }
            }
        }

        //! Remoção
        bool remove(const T& data_, Node *parent) {
            if (data_ < data) {
                return left != nullptr && left->remove(data_, this);
            } else if (data_ > data) {
                return right != nullptr && right->remove(data_, this);
            } else {
                // Node* temp = this;
                if (left != nullptr && right != nullptr) {
                    data = right->minValue();
                    return right->remove(data, this);
                } else if (parent->left == this) {
                    parent->left = (left != nullptr) ? left : right;
                } else if (parent->right == this) {
                    parent->right = (left != nullptr) ? left : right;
                }
                delete this;
                return true;
            }
        }

        T minValue() const {
            return left == nullptr ? data : left->minValue();
        }

        T maxValue() const {
            return right == nullptr ? data : right->maxValue();
        }

        //! Contém
        bool contains(const T& data_) const {
            if (data_ == data) {
                return true;
            } else if (data_ < data) {
                return (left != nullptr) && left->contains(data_);
            } else {
                return (right != nullptr) && right->contains(data_);
            }
        }

        //! Pré ordem
        void pre_order(ArrayList<T>& v) const {
            v.push_back(data);
            if (left != nullptr)
                left->pre_order(v);
            if (right != nullptr)
                right->pre_order(v);
        }

        //! Em ordem
        void in_order(ArrayList<T>& v) const {
            if (left != nullptr) {
                left->in_order(v);
            }
            v.push_back(data);
            if (right != nullptr) {
                right->in_order(v);
            }
        }

        //! Pós ordem
        void post_order(ArrayList<T>& v) const {
            if (left != nullptr) {
                left->post_order(v);
            }
            if (right != nullptr) {
                right->post_order(v);
            }
            v.push_back(data);
        }

        int count_leaves(int cont) {
            if (left == nullptr && right == nullptr) {
                return cont + 1;
            } else if (left != nullptr && right != nullptr) {
                return left->count_leaves(cont) + right->count_leaves(cont);
            } else if (left != nullptr) {
                return left->count_leaves(cont);
            } else {
                return right->count_leaves(cont);
            }
        }
        
        int calc_height(int current) {
            if (left == nullptr && right == nullptr) {
                return current;
            }
            
            int left_height = 0;
            int right_height = 0;
            
            if (left != nullptr ) {
                left_height = left->calc_height(current + 1);
            }
            if (right != nullptr ) {
                right_height = right->calc_height(current + 1);
            }
            if (left_height > right_height) {
                return left_height;
            }
            return right_height;
        }

        void filter_nodes(int n_child, Node *parent) {
            int cont_child = 0;
            if (left != nullptr) {
                left->filter_nodes(n_child, this);
                cont_child++;
            }
            if (right != nullptr) {
                right->filter_nodes(n_child, this);
                cont_child++;
            }
            if (n_child == cont_child) {
                remove(data, parent);
            }
        }


    //  private:
    //     //! Complemento da funcão de remoção
    //     Node* remove(const T& data, Node* arv, bool& deleted) {
    //         Node* temp = nullptr;
    //         /*
    //             COPIE AQUI O CÓDIGO DO EXERCÍCIO ANTERIOR ...
    //         */
    //         return temp;
    //     }

    //     //! Encontrar o menor
    //     Node* minimum() {
    //         if (left_ == nullptr)
    //             return this;
    //         return left_->minimum();
    //     }
    };
    
    void clear(Node* node) {
        if (node != nullptr) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

    Node* root_{nullptr};
    std::size_t size_{0};
};




//******************************************************************
// Prova prática - implementações necessárias:

//! (1) determinação da altura da árvore:
template<typename T>
int BinaryTree<T>::height() {
    if (empty()) throw std::out_of_range("Empty tree!");
    return root_->calc_height(0);
}

//! (2) contagem do número de folhas:
template<typename T>
int BinaryTree<T>::leaves() {
    if (empty()) throw std::out_of_range("Empty tree!");
    return root_->count_leaves(0);
}

//! (3) criação de uma lista com o menor (mínimo) e o maior (máximo)
//!     valor da árvore:
template<typename T>
ArrayList<T> BinaryTree<T>::limits() {
    ArrayList<T> L(2);
    L.push_back(root_->minValue());
    L.push_back(root_->maxValue());
    return L;
}

//! (4) criação de uma duplicação, em memória, da árvore:
template<typename T>
BinaryTree<T> BinaryTree<T>::clone() {
    BinaryTree<T> C;
    ArrayList<T> L(size());
    root_->pre_order(L);
    for (size_t i = 0; i < L.size(); i++) {
        C.insert(L[i]);
    }
    return C;
}

//! (5) remove nós pelo número de seus filhos:
template<typename T>
void BinaryTree<T>::filter(int n_child) {
    root_->filter_nodes(n_child, nullptr);
}

//! (6) criação de um nova árvore que tenha todos os valores e a
//!     menor altura possível, ou seja, balanceada com base apenas
//!     no estabelecimento de uma nova ordem de inserção:
template<typename T>
BinaryTree<T> BinaryTree<T>::balance() {
    BinaryTree<T> B;
    ArrayList<T> L(size());
    root_->in_order(L);
    recursive_insert(B, L);
    return B;
}

template<typename T>
void recursive_insert(BinaryTree<T>& B, ArrayList<T>& L) {
    if (L.empty()) return;
    
    int median = (L.size())/2;
    ArrayList<T> Left(median);
    ArrayList<T> Right(median);
    
    B.insert(L[median]);
    
    for (int i = 0; i < median; i++) {
        Left.push_back(L[i]);
    }
    for (size_t i = median + 1; i < L.size(); i++) {
        Right.push_back(L[i]);
    }
    recursive_insert(B, Left);
    recursive_insert(B, Right);
}

//******************************************************************



//! Construtor
template<typename T>
BinaryTree<T>::BinaryTree()
{}

//! Destrutor
template<typename T>
BinaryTree<T>::~BinaryTree() {
    clear(root_);
}

//! Inserção
template<typename T>
void BinaryTree<T>::insert(const T& data) {
    if (empty()) {
        root_ = new Node(data);
        if (root_ == nullptr)
            throw std::out_of_range("FUll tree!");
    } else {
            root_->insert(data);
    }
    ++size_;
}

// Remoção
template<typename T>
void BinaryTree<T>::remove(const T& data) {
    if (empty())
        throw std::out_of_range("Empty tree");

    if (size() == 1) {
        delete root_;
        size_--;
        root_ = nullptr;
    } else if (root_ != nullptr && root_->remove(data, nullptr)) {
        size_--;
    }
}

//! Contém
template<typename T>
bool BinaryTree<T>::contains(const T& data) const {
    if (empty())
        return false;
    return root_->contains(data);
}

//! Vazio
template<typename T>
bool BinaryTree<T>::empty() const {
    return size() == 0;
}

//! Tamanho
template<typename T>
std::size_t BinaryTree<T>::size() const {
    return size_;
}

//! Pré ordem
template<typename T>
ArrayList<T> BinaryTree<T>::pre_order() const {
    ArrayList<T> v{size_};
    if (!empty())
        root_->pre_order(v);
    return v;
}

//! Em ordem
template<typename T>
ArrayList<T> BinaryTree<T>::in_order() const {
    ArrayList<T> v{size_};
    if (!empty())
        root_->in_order(v);
    return v;
}

//! Pós ordem
template<typename T>
ArrayList<T> BinaryTree<T>::post_order() const {
    ArrayList<T> v{size_};
    if (!empty())
        root_->post_order(v);
    return v;
}


}  // namespace structures

#endif
