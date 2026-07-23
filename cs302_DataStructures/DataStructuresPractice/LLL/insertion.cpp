#include "list.h"

// Setup Functions
void list::initialize(){

	//Fill in w/data
	for(int i =0; i <5; ++i){
		node * current = new node;
		current->data = i*2;
		current->next = NULL;

		//Empty list case
		if(head == nullptr){
			head = current;
		}else{
			node * current2=head;
			while(current2->next){
				current2=current2->next;
			}
			current2->next = current;
		}

	}
}
void list::display(){

	node * current = head;
	while(current->next){
		cout << current->data << endl;
		current=current->next;
	}
	cout << current->data << endl;
}

//Insert Front
void list::insertfront(int number){
	//Create node
	node * current = new node;
	current->data = number;
	if(!head){
		head=current;
		head->next=nullptr;
		return;
	}
	//Insertion part
	current->next = head;
	head = current;	
}


//Insert Back
void list::insertback(int number){
	node * current = new node;
	current->data = number;
	current->next = nullptr;
	//insertion
	if(!head){
		head=current;
		head->next=nullptr;
	}else{
		node * temp = head;
		while(temp->next){
			temp = temp->next;
		}
		temp->next = current;
	}
}


//Insert Middle
void list::insertmiddle(int number){
	node * current = new node;
	current->data = number;
	current->next = nullptr;
	//insertion
	if(!head){
		head=current;
		head->next=nullptr;
	}else{
		node*temp = head;
		node*previous = temp;
		//Travel 2 places up 
		for(int i =0; i<2; ++i){
			previous=temp;
			temp=temp->next;
		}
		// this should look like [1] [2] [3] [4] [5]
		// 		         PT
		// 		         P    T		
		// 			      P   T
	
		// Complete insertion with new previous and temp node
		current->next = temp;
		previous->next = current;
	}

}

//Insert In Order
void list::insertorder(int number){

	node * current = new node;
	current->data = number;
	current->next = nullptr;
	// Case 1: Empty list or insert at beginning
	if (!head || number < head->data) {
		current->next = head;
		head = current;
		return;
	}
	// Case 2: Find position in middle or end
	// 1 2 3 5 6 
	node* temp = head;
	while (temp->next && temp->next->data < number) {
		temp = temp->next;
	}

	current->next = temp->next;
	temp->next = current;
}


//Reorganize List
list list::reorganize(){
	//initliaze new list
	list newlist;
	for (node* cur = head; cur; cur = cur->next) {
		newlist.insertorder(cur->data);
	}
	return newlist;
}

list::list(const list & oldlist){
	head = nullptr;

	if(oldlist.head == nullptr){
		return;
	}

	head = new node;
	head->data = oldlist.head->data;
	head->next = nullptr;

	node * current = head;
	node * current2 = oldlist.head->next;
	while(current2){
		node * newNode = new node;
		newNode->data = current2->data;
		newNode->next = nullptr;

		//move it to other list
		current->next = newNode;
		current = newNode;
		current2 = current2->next;
	}

}


