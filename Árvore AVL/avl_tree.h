// Copyright [2024] <Juliana Miranda Bosio>

#include "array_list.h"

namespace structures {

template<typename T>
class AVLTree {
 public:
    AVLTree();

    ~AVLTree();

    void insert(const T& data);

    void remove(const T& data);

    bool contains(const T& data) const;

    bool empty() const;

    std::size_t size() const;

    int height() const;

    ArrayList<T> pre_order() const;

    ArrayList<T> in_order() const;

    ArrayList<T> post_order() const;

 private:
    struct Node {
        explicit Node(const T& data_) {
            data = data_;
            height_ = 0;
            left = nullptr;
            right = nullptr;
        }

        ~Node() {
            delete left;
            left = nullptr;
            delete right;
            right = nullptr;
        }

        Node* insert(const T& data_) {
            if (data_ < data) {
                if (left == nullptr) {
                    left = new Node(data_);
                } else {
                    left = left->insert(data_);
                }
            } else if (data_ > data) {
                if (right == nullptr) {
                    right = new Node(data_);
                } else {
                    right = right->insert(data_);
                }
            }
            updateHeight();
            return balance();
        }

        Node* remove(const T& data_) {
            if (data_ < data) {
                if (left != nullptr) {
                    left = left->remove(data_);
                }
            } else if (data_ > data) {
                if (right != nullptr) {
                    right = right->remove(data_);
                }
            } else { 
                if (left == nullptr && right == nullptr) {
                    delete this;
                    return nullptr;
                } else if (left == nullptr) {
                    Node* temp = right;
                    right = nullptr;
                    delete this;
                    return temp;
                } else if (right == nullptr) {
                    Node* temp = left;
                    left = nullptr;
                    delete this;
                    return temp;
                } else {  
                    Node* temp = right;
                    while (temp->left != nullptr) {
                        temp = temp->left;
                    }
                    data = temp->data;
                    right = right->remove(data);
                }
            }
            updateHeight();
            return balance();
        }

        bool contains(const T& data_) const {
            if (data_ == data) {
                return true;
            } else if (data_ < data) {
                return left == nullptr ? false : left->contains(data_);
            } else {
                return right == nullptr ? false : right->contains(data_);
            }
        }

        void updateHeight() {
            int left_height = left == nullptr ? -1 : left->height_;
            int right_height = right == nullptr ? -1 : right->height_;
            height_ = 1 + std::max(left_height, right_height);
        }
        
        int getBalanceFactor() const {
            int left_height = left == nullptr ? -1 : left->height_;
            int right_height = right == nullptr ? -1 : right->height_;
            return left_height - right_height;
        }

        Node* balance() {
            int balance_factor = getBalanceFactor();

            if (balance_factor > 1) { 
                if (left->getBalanceFactor() < 0) {
                    left = left->rotateLeft();
                }
                return rotateRight();
            } else if (balance_factor < -1) {  
                if (right->getBalanceFactor() > 0) {
                    right = right->rotateRight();
                }
                return rotateLeft();
            }
            return this;
        }

        Node* rotateLeft() {
            Node* new_root = right;
            right = new_root->left;
            new_root->left = this;
            updateHeight();
            new_root->updateHeight();
            return new_root;
        }

        Node* rotateRight() {
            Node* new_root = left;
            left = new_root->right;
            new_root->right = this;
            updateHeight();
            new_root->updateHeight();
            return new_root;
        }

        void pre_order(ArrayList<T>& v) const {
            v.push_back(data);
            if (left != nullptr) {
                left->pre_order(v);
            }
            if (right != nullptr) {
                right->pre_order(v);
            }
        }

        void in_order(ArrayList<T>& v) const {
            if (left != nullptr) {
                left->in_order(v);
            }
            v.push_back(data);
            if (right != nullptr) {
                right->in_order(v);
            }
        }

        void post_order(ArrayList<T>& v) const {
            if (left != nullptr) {
                left->post_order(v);
            }
            if (right != nullptr) {
                right->post_order(v);
            }
            v.push_back(data);
        }

        T data;
        int height_;
        Node* left;
        Node* right;
    };

    Node* root;
    std::size_t size_;
};

}  //  namespace structures

// -----

template<typename T>
structures::AVLTree<T>::AVLTree() {
    root = nullptr;
    size_ = 0;
}

template<typename T>
structures::AVLTree<T>::~AVLTree() {
    delete root;
}

template<typename T>
void structures::AVLTree<T>::insert(const T& data) {
    if (root == nullptr) {
        root = new Node(data);
    } else {
        root = root->insert(data);
    }
    size_++;
}

template<typename T>
void structures::AVLTree<T>::remove(const T& data) {
    if (root == nullptr) return;
    if (contains(data)) {
        root = root->remove(data);
        size_--;
    }
}

template<typename T>
bool structures::AVLTree<T>::contains(const T& data) const {
    return root == nullptr ?  false : root->contains(data);
}


template<typename T>
bool structures::AVLTree<T>::empty() const {
    return size_ == 0;
}

template<typename T>
std::size_t structures::AVLTree<T>::size() const {
    return size_;
}

template<typename T>
int structures::AVLTree<T>::height() const {
    return root == nullptr ? -1 : root->height_;
}

template<typename T>
structures::ArrayList<T> structures::AVLTree<T>::pre_order() const {
    structures::ArrayList<T> L;
	if (root != nullptr) {
		root->pre_order(L);
	}
	return L;
}

template<typename T>
structures::ArrayList<T> structures::AVLTree<T>::in_order() const {
    structures::ArrayList<T> L;
    if (root != nullptr) {
        root->in_order(L);
    }
    return L;
}

template<typename T>
structures::ArrayList<T> structures::AVLTree<T>::post_order() const {
    structures::ArrayList<T> L;
    if (root != nullptr) {
        root->post_order(L);
    }
    return L;
}
