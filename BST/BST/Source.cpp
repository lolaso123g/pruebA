
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
		Node*pp;

		Node(float elem)
			: element(elem), left(nullptr), right(nullptr),pp(nullptr) {}
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

	int find(float elem) {
		return find(root, elem);
	}

	void remove(float elem) {
		remove(root, elem);
	}

	void preorder(std::function<void(float)> proc) {
		 preorder(root, proc);
	}
	void postorder(std::function<void(float)> proc) {
		 postorder(root, proc);
	}
	void inorder(std::function<void(float)> proc) {
		 inorder(root, proc);
	}
	int mayor() {
		return mayor(root);
	}
	Node* arbolespejo(std::function<void(float)> proc) {
		return arbolespejo(root, proc);
	}
	int menor() {
		return menor(root);
	}
	int prom() {
		return prom(root);
	}
	void eliminaravl(int elem) {
		eliminaravl(root, elem);
	}
	
private:
	void eliminaravl(Node*node, int elem) {
		Node* p=nullptr;
		Node* pp;
		Node *h;
		Node* abue;
		Node*hh;
		if (node != nullptr) {
			if (elem < node->element) {
				p = node;
				eliminaravl(node->left, elem);

			}
			else if (elem > node->element) {
				p = node;
				eliminaravl(node->right, elem);
			}

			else {
				if (node->left == nullptr&&node->right == nullptr) {
					if (p->left == node) {
						p->left = nullptr;
						delete(node);
					}
					else {
						p->right = nullptr;
						delete(node);
					}
				}
				else {//1
					if ((node->left == nullptr&&node->right != nullptr) || (node->left != nullptr&&node->right == nullptr)) {

						if (node->left == nullptr&&node->right != nullptr) {
							h = node->right;

							if (p->left == node) {
								p->left = h;
								h->pp = p;
								delete(node);
							}
							else {
								p->right = h;
								h->pp = p;
								delete(node);
							}
						}
						else {
							h = node->left;
							if (p->left == node) {
								p->left = h;
								h->pp = p;
								delete(node);
							}
							else {
								p->right = h;
								h->pp = p;
								delete(node);
							}
						}
					}//2
					else {
						if (node->left != nullptr&&node->right != nullptr) {
							abue = node->left;
							if (abue->left == nullptr&&abue->right == nullptr) {
								node->element = abue->element;
								node->left = nullptr;
								delete(abue);
							}
							else {
								abue = node->right;
								if (abue->left == nullptr&&abue->right == nullptr) {
									node->element = abue->element;
									node->right = nullptr;
									delete(abue);
								}
								else {
									abue = node->left;
									if (abue->right == nullptr) {
										node->element = abue->element;
										node->right = abue->right;
										h = abue->right;
										h->pp = node;
										delete(abue);

									}
									else {
										abue = node->left;
										h = abue;
										while (h->right != nullptr) {
											abue = h; h = h->right;
										}
									}node->element = h->element;
									abue->right = h->left;
									hh = h->left;
									hh->pp = abue;
									delete(h);
								}
							}
						}

					}
				}
			}
		}
		else {
			cout<<"no hayl"<<endl;
		}
	}


	int prom(Node*node) {
		if (node != NULL) {
			int centro = node->element;
			int izq = prom(node->left);
			int der = prom(node->right);
			return izq + centro + der;
		}
		return 0;
		
	}
	Node* arbolespejo(Node* node, std::function<void(float)> proc) {

		Node* aux;
		if (node != NULL)
		{
			aux = node->left;
			node->left = arbolespejo(node->right, proc);
			node->right = arbolespejo(aux, proc);
			proc(node->element);
				;
		}
		return node;
	}
	int menor(Node*node) {
		if (node->left != nullptr) {

			return mayor(node->left);
		}
		return node->element;
	}
	int mayor(Node*node) {
		if (node->right != nullptr) {

			return mayor(node->right);
		}
		return node->element;
	}
		
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
		}
		else if (elem < node->element) {
			add(node->left, elem);
		}
		else if (elem > node->element) {
			add(node->right, elem);
		}
	}

	int find(Node* node, int elem) {
		int sum = 0;
		
		if (node != nullptr) {
			
			 if (elem < node->element) {
				 find(node->left, elem);
				 if (node->element == elem) {
					 sum++;
				 }
			}
			 else{
				find(node->right, elem);
					if (node->element = elem) {
						sum++;
					}
				 
			}
		}
		return sum;
	}

	void preorder(Node* node, std::function<void(float)> proc) {
		if (node != nullptr) {
			proc(node->element);
			preorder(node->left, proc);
			preorder(node->right, proc);
		}
	}
	void postorder(Node* node, std::function<void(float)> proc) {
		if (node != nullptr) {
			postorder(node->left, proc);
			postorder(node->right, proc);
			proc(node->element);
		}

	}
	void inorder(Node* node, std::function<void(float)> proc) {
		if (node != nullptr) {
			inorder(node->left, proc);
			proc(node->element);
			inorder(node->right, proc);
		}
	}

	void remove(Node*aux,float elem) {
		// Encontrar elemento a eliminar;
		//Node* aux = root;
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

	vector<int> v = { 8,7,5,3,9,5,1 };

	for (auto num : v) {
		bst->add(num);
	}

	auto print = [](int x) { cout << x << " "; };

	/*bst->postorder(print); cout << endl;
	bst->preorder(print); cout << endl;
	bst->inorder(print); cout << endl;
	bst->arbolespejo(print); cout << endl;
	cout<<bst->prom() << endl;
	cout << bst->find(100) << endl;
	cout << bst->find(4) << endl;*/
	cout << endl; cout << endl;
	cout<<bst->find(2);
	cout << endl; cout << endl;
	/*cout<<bst->mayor()<<endl;
	bst->remove(23);*/
	bst->inorder(print); cout << endl;
	bst->eliminaravl(8);
	bst->inorder(print);

	delete bst;
	return 0;
}