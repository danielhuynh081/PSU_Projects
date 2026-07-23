#pragma once

//This file is where I implemented my template functions

//Insertion
template <typename T>
bool DLL<T>::insertpet(const T & newpet){//Sorted Insert Wrapper
	try{
		Node<T> * temp = new Node<T>(newpet);
		if(!head){
			head = tail = temp;
			return true;
		}
		if(newpet <= head->getdata()){
			temp->setnext(head);
			head->setprevious(temp);
			head = temp;
			return true;
		}
		return insertpet(temp, head);
	}catch(const bad_alloc & e){
		cerr << "exception caught: " << e.what() << endl;
	}catch(...){
		cerr << "unknown error" << endl;
	}
	return false;
}

template <typename T>
bool DLL<T>::insertpet(Node<T> *& current,  Node<T> *& current2){ //Sorted Recursive Insert
	if(current2->getnext() == nullptr){
		current2->setnext(current);
		current->setprevious(current2);
		tail = current;
		return true;
	}
	if(current->getdata() <= current2->getdata()){
		Node<T> * temp = current2->getprevious();
		current->setnext(current2);
		temp->setnext(current);
		current2->setprevious(current);
		current->setprevious(temp);
		return true;
	}
	return insertpet(current, current2->getnext());
}

//Removal

template <typename T>
bool DLL<T>::removepet(){// Remove One Wrapper Function
	if(!head){
		cout <<"\nThis list is empty " << endl;
		return false;
	}	
	try{
		char button3;
		string nameinput;
		int ageinput;
		display();

		cout <<"\n(A) Remove One | (B) Remove All :";
		cin >>button3;
		cin.ignore(100, '\n');
		if(toupper(button3) =='A'){
			cout <<"\nWhat is the name of the pet? : ";
			cin>> nameinput;
			cin.ignore(100, '\n');

			cout <<"\nWhat is the age of the pet ? : ";
			cin >> ageinput;
			cin.ignore(100, '\n');
			return removepet(head, nameinput, ageinput);

		}
		if(toupper(button3) =='B'){
			cout <<"\nList removed" << endl;
			return removeall(head);
		}
		return true;
	}catch(const exception & e){
		cerr << "exception caught: " << e.what() << endl;
	}
	return false;
}

template <typename T>
bool DLL<T>::removepet(Node<T> *& current, string name, int age){ // Remove One Recurse Function
	if(!current){
		cout <<"\nPet not found " << endl;
		return false;
	}
	if(current->getdata().getname() == name && current->getdata().getage() == age){
		if(head == tail && strcmp(head->getdata().getname().c_str(), name.c_str()) ==0 && head->getdata().getage() == age){//one item case
			delete head;
			head = tail = nullptr;
			return true;
		}
		cout <<"\nRemoved " << name << endl;
		try{
			return removenode(current);
		}catch(const exception & e){
			cerr << "exception caught: " << e.what() << endl;
		}
		return false;
	}
	return removepet(current->getnext(), name, age);

}

template <typename T>
bool DLL<T>::removeall(){ //Remove All Wrapper
	if(!head){
		return false;
	}
	try{
		return removeall(head);
	}catch(const exception & e){
		cerr << "exception caught: " << e.what() << endl;
	}
	return false;
}


template <typename T>
bool DLL<T>::removeall(Node<T> *& current){ // Remove All Recursive Function
	if(!current){
		return true;
	}
	Node<T> * temp = current;
	current = current->getnext();
	delete temp;
	temp = nullptr;
	return removeall(current);
}

template <typename T>
bool DLL<T>::removenode(Node<T> *& current){ // Node Removal Function
	if(current == head){ //Head Case
		Node<T> * temp = current;
		current = current->getnext();
		delete temp;
		temp = nullptr;
		head = current;
		return true;
	}
	if(current == tail){ //Tail Case
		Node<T> * temp = current;
		current = current->getprevious();
		delete temp;
		temp = nullptr;
		tail = current;
		current->setnext(nullptr);
		return true;
	}
	//Middle of the list
	Node<T> * temp = current;
	current= current->getnext();
	temp->getprevious()->setnext(current);
	delete temp;
	temp = nullptr;
	return true;

}

//Display

template <typename T>
bool DLL<T>::display(){//Display Wrapper
	if(!head){
		cout <<"\nno list\n";
		return false;
	}
	return display(head);
}  
template <typename T>   
bool DLL<T>::display(Node<T> *& current){ //Display Recursive Function
	cout <<current->getdata();
	if(current->getnext()){
		return display(current->getnext());
	}
	return true;
}

template <typename T>
bool DLL<T>::displaynames(){ //Display Wrapper
	if(!head){
		cout <<"\nno list\n";
		return false;
	}
	return displaynames(head);
}
template <typename T>
bool DLL<T>::displaynames(Node<T> *& current){ //Display Recursive Function
	cout <<"\nName: " << current->getdata().getname() << endl;
	cout <<"Age: " << current->getdata().getage() << endl;
	if(current->getnext()){
		return displaynames(current->getnext());
	}
	return true;
}

//Retrieve
template <typename T>
Node<T> * DLL<T>::retrieve(){ //Retrieve Wrapper Function
	string nameinput;
	int ageinput;
	if(!head){
		cout <<"\nNo list exists" << endl;
		return nullptr;
	}

	try{
		cout <<"\nEnter Pet Name : " ;
		cin >> nameinput;
		cin.ignore(100, '\n');

		cout <<"\nenter Pet Age : ";
		cin >>ageinput;
		cin.ignore(100, '\n');


		return retrieve(head, nameinput, ageinput);
	}catch(const exception & e){
		cerr << "exception caught: " << e.what() << endl;
	}
	return nullptr;
}

template <typename T>
Node<T> * DLL<T>::retrieve(Node<T> *& current, string nameinput, int ageinput){ //Retrieve Recursive Function
	if(!current){
		cout <<"\n Couldnt find pet " << endl;
		return nullptr;
	}
	if(current->getdata().getname() == nameinput.c_str() && current->getdata().getage() == ageinput){
		return current;
	}
	return retrieve(current->getnext(), nameinput, ageinput);
}


