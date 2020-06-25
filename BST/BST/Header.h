#pragma once
#include<iostream>
#include <functional>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

class SimpleBST {
    struct Node {
        float element;
        Node* left;
        Node* right;

        Node(float elem)
            : element(elem), left(nullptr), right(nullptr) {}
    };

    Node* root;
public:
    SimpleBST() : root(nullptr) {}
    ~SimpleBST() {
        clear(root);
    }

    void clear() {
        clear(root);
    }

    void add(float elem) {
        add(root, elem);
    }

    bool find(float elem) {
        return find(root, elem);
    }

    void remove(float elem);

	void preorder(std::function<void(float)> proc) {
		void preorder(Node* node, std::function<void(float)> proc);
	}
	void postorder(std::function<void(float)> proc) {
		void postorder(Node* node, std::function<void(float)> proc);
	}
    void inorder(std::function<void(float)> proc){
		void inorder(Node* node, std::function<void(float)> proc);
	}

private:
    void clear(Node* node) {
        if (node != nullptr) {
            clear(node->left);
            clear(node->right);
            delete node;
            node = nullptr;
        }
    }

    void add(Node*& node, float elem) {
        if (node == nullptr) {
            node = new Node(elem);
        } else if (elem < node->element) {
            add(node->left, elem);
        } else if (elem > node->element) {
            add(node->right, elem);
        }
    }

    bool find(Node* node, float elem) {
        if (node != nullptr) {
            if (elem == node->element) {
                return true;
            } else if (elem < node->element) {
                return find(node->left, elem);
            } else {
                return find(node->right, elem);
            }
        }
        return false;
    }

	void preorder(Node* node, std::function<void(float)> proc) {
		if (node != nullptr) {
			proc(node->element);
			preorder(node->left, proc);
			preorder(node->right, proc);
		}
	}
    void postorder(Node* node, std::function<void(float)> proc){
		if (node != nullptr) {
			postorder(node->left, proc);
			postorder(node->right, proc);
			proc(node->element);
		}
	
	}
    void inorder(Node* node, std::function<void(float)> proc){
		if (node != nullptr) {
			inorder(node->left, proc);
			proc(node->element);
			inorder(node->right, proc);
		}
	}

	void remove(float elem) {
		// Encontrar elemento a eliminar;
		Node* aux = root;
		Node* auxParent = nullptr;
		bool leftChild;
		while (aux != nullptr) {
			if (elem == aux->element) {
				break;
			}
			else if (elem < aux->element) {
				auxParent = aux;
				leftChild = true;
				aux = aux->left;
			}
			else {
				auxParent = aux;
				leftChild = false;
				aux = aux->right;
			}
		}
		if (aux == nullptr) return;                 // No se encontró el elemento a eliminar

		// Ahora eliminamos en caso no tenga hijo izquierdo
		if (aux->left == nullptr) {                 // No tiene hijo izquierdo, sube el derecho
			if (auxParent == nullptr) {             // El elemento a eliminar es root
				root = aux->right;
			}
			else if (leftChild) {                 // El elemento a eliminar es el izq de parent
				auxParent->left = aux->right;
			}
			else {                                // es el derecho de parent
				auxParent->right = aux->right;
			}
			delete aux;
			return;
		}

		// En caso si exista hijo izquierdo, buscamos al mayor de dicho subárbol
		Node* aux2 = aux->left;
		Node* aux2Parent = aux;
		leftChild = true;
		while (aux2->right != nullptr) {
			aux2Parent = aux2;
			leftChild = false;
			aux2 = aux2->right;
		}
		aux->element = aux2->element;               // Reemplazamos al elemento a eliminar
		if (leftChild) {
			aux2Parent->left = aux2->left;
		}
		else {
			aux2Parent->right = aux2->left;
		}
		delete aux2;
	}

};


int main() {
	SimpleBST* bst = new SimpleBST();

	vector<int> v = { 34, 3, 1, 67, 69, 23, 4, 79, 43,
					 20, 14, 54, 12, 8, 99, 15, 62, 26 };

	for (auto num : v) {
		bst->add(num);
	}

	auto print = [](float x) { cout << x << " "; };

	bst->postorder(print); cout << endl;
	bst->preorder(print); cout << endl;
	bst->inorder(print); cout << endl;

	cout << bst->find(100) << endl;
	cout << bst->find(4) << endl;

	

	bst->remove(23);

	

	delete bst;
	return 0;
}