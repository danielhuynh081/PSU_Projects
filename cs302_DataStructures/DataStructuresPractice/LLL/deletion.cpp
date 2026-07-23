#include "list.h"


//Delete Front

void list::deletefront(){
	cout <<"\nRemoving front node" << endl;
	if(!head){
		cout <<"Empty List" << endl;
		return;
	}
	else if(!head->next){
		cout <<"One Item List" << endl;
		delete head;
		return;
	}else{
		node * current = head;
		head = head->next;
		delete current;
	}
}


//Delete End
void list::deleteback(){
	cout <<"\nRemoving back  node" << endl;
	if(!head){
		cout <<"Empty List" << endl;
		return;
	}
	else if(!head->next){
		cout <<"One Item List" << endl;
		delete head;
		return;
	}else{
		node* temp = head;
		node* previous = temp;
		while(temp->next){
			previous = temp;
			temp = temp->next;
		}
		delete temp;
		previous->next = nullptr;
	}

}



//Delete Middle
void list::deletemiddle(int number){
	cout <<"\nRemoving nidddle  node" << endl;

	//Empty list case
	if(!head){
		return;
	}
	//One item case
	else if(head->next == nullptr){
		if(head->data == number){
			delete head;
		}
		return;
	}
	//Look for node
	else{
		node * current = head;
		node* previous = current;
		if(current->next){
			previous = current;
			current = current->next;
			if(current->data==number){
				deletenode(current, previous);
				return;
			}
		}	
		if(current->data == number){
			delete current;
		}else{
			cout <<"Number not found" << endl;
		}
	}
}

void list::deletenode(node *current, node * previous){
	if(current->next){
		previous->next = current->next;
		delete current;
	}else{
		previous->next= nullptr;
		delete current;
	}
}

//Delete Duplicates
bool list::checkduplicate(node * check, node * current){
	if(!current){
		return false;
	}
	if(current->data == check->data){
		return true;
	}
	return checkduplicate(check, current->next);
}

void list::deleteduplicates(){
	node * temp = head;
	bool dup=false;
	while(temp){
		if(checkduplicate(temp, temp->next)){
			cout <<"This is a duplicate:" << temp->data << endl;
			dup=true;
			//Head is a duplicate
			if(temp == head){;
				node * current = head;
				head = head->next;
				temp=head;
				delete current;
			}
			//end of list will always not be a duplicate so we can work on middle removal
			else{
				//Find duplicate
				node*current=temp->next;
				node*previous = temp;
				while(current){
					if(current->data == temp->data){
						//Match found
						node * toDelete = current;
						current=current->next;
						previous->next=current;
						delete toDelete;
					}else{
					previous=current;
					current=current->next;
					}
				}
			}
			
		}
		temp=temp->next;

	}
	if(!dup){
		cout<<"No dusplicates found" << endl;
	}	
}

//Create delete node helper
