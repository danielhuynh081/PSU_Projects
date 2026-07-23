#include <iostream>

using namespace std;

struct node{
	int data;
	node * left = nullptr;;
	node * right = nullptr;
};

class tree{

	public:
		tree(){
			root=nullptr;
		}
		~tree(){}
		void insertnode(int number);
		void insertrecursive(node* temp, node * current);
		void deletenode(int number);
		void displaytree();
		void printTree(node* current, string prefix, bool isLeft);
		node * fetchnode(int number);

	private:
		node * root;
};
