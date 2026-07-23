#include "info.h"

void tree::insertnode(int number){

	//Initialize node
	node * current = new node;
	current->data = number;

	//empty tree
	if(!root){
		root = current;
	}
	//Call recusrive function
	return insertrecursive(root, current);
}

void tree::insertrecursive(node* temp, node* current) {
    if (current->data < temp->data) {
        if (!temp->left) {
            temp->left = current;
        } else {
            insertrecursive(temp->left, current);
        }
    } else if (current->data > temp->data) {
        if (!temp->right) {
            temp->right = current;
        } else {
            insertrecursive(temp->right, current);
        }
    }
    // If equal, you can choose to ignore or allow duplicates in a side
}

void tree::deletenode(int number){
	return;
}
void tree::displaytree(){

	printTree(root, "", true);
	return;
}

void tree::printTree(node* current, string prefix, bool isLeft) {
    if (!current) return;

    if (current->right) {
        printTree(current->right, prefix + (isLeft ? "│   " : "    "), false);
    }

    cout << prefix;
    cout << (isLeft ? "└── " : "┌── ");
    cout << current->data << endl;

    if (current->left) {
        printTree(current->left, prefix + (isLeft ? "    " : "│   "), true);
    }
}
