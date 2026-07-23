#include "list.h"

// Setup Functions
void list::display(){
	if(!head){
		return;
	}
    node* temp = head;
    while (temp != tail) {
        cout << temp->data << endl;
        temp = temp->next;
    }
    cout << temp->data << endl;
}
//Insert Front
void list::insertfront(int number){
	node *  current = new node;
	current->data = number;
	if(!head){
		head = tail =  current;
		current->next=current;
	}else{
		current->next=head;
		head=current;
		tail->next=head;;
	}
}


//Insert Back
void list::insertback(int number){
	if(!head) return;
	node * current = new node;
	current->data = number;
	current->next = head;
	tail->next = current;
	tail = current;
}


//Insert Middle
void list::insertmiddle(int number){

}

//Insert In Order
void list::insertorder(int number){
}


//Reorganize List


