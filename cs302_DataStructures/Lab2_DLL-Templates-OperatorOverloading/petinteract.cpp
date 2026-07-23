#include "class.h"

//CS302 Karla Fant Program 2, February 15th 2024 Daniel Huynh,
//this file is where i created interaction functions for each type of pet
//I separated this from the tpp file for easier access and readability





//Derived Class 1 Functions
template <>
bool DLL<workingPet>::interact(){
	char button;
	displaynames();
	cout <<"\nPick a pet to interact with : " << endl;
	Node<workingPet> * pet;
	do{
		pet = retrieve();
	}while(!pet);

	cout <<"(A) Compare Strength | (B) Feed Treat | (C) Walk Pet";
	cin>>button;
	cin.ignore(100, '\n');
	if(toupper(button) =='A'){
		if(head->getnext() != nullptr){
			cout <<"Enter infomration for second pet:" << endl;;
			Node<workingPet> * pet2 = retrieve();
			if(pet->getdata()< pet2->getdata()){
				cout <<pet2->getdata().getname() <<" is stronger than " << pet->getdata().getname() << endl;
			}
			else if(pet->getdata()>= pet2->getdata()){
				cout <<pet2->getdata().getname() << " is equally strong as " << pet->getdata().getname() << endl;
			}

			else{
				cout <<pet->getdata().getname() << " is stronger than " << pet2->getdata().getname() << endl;
			}

			return true;
		}
		else{
			cout <<"Theres only one pet in this list " << endl;
			return false;
		}

		return true;
	}
	if(toupper(button) =='B'){
		int treat;
		cout <<"\nHow many treats would you like to feed";
		cin >> treat;
		cin.ignore(100, '\n');
		pet->getdata() += treat;

		return true;
	}
	if(toupper(button) =='C'){
		int minutes;
		cout <<"\nHow many minutes would you like to walk your pet?";
		cin>>minutes;
		cin.ignore(100, '\n');
		pet->getdata() == minutes;

	}
	return true;
}

//Derived Class 2 Functions
template <>
bool DLL<competitivePet>::interact(){
	char button;
	displaynames();
	cout <<"\nPick a pet to interact with : " << endl;
	Node<competitivePet> * pet;

	do{
		pet = retrieve();
	}while(!pet);

	cout <<"(A) Compare Speed | (B) Feed Treat | (C) Walk Pet";
	cin>>button;
	cin.ignore(100, '\n');

	if(toupper(button) =='A'){
		if(head->getnext() != nullptr){
			cout <<"Enter infomration for second pet:" << endl;;
			Node<competitivePet> * pet2 = retrieve();
			if(pet2){
				int compare = pet->getdata() > pet2->getdata();
				if(compare ==0){
					cout <<"\n" << pet->getdata().getname() << " is faster than " << pet2->getdata().getname() << endl;
				}
				else if(compare == 1){
					cout <<"\n" << pet->getdata().getname() << " is slower than " << pet2->getdata().getname() << endl;
				}
				else{

					cout <<"\n" << pet->getdata().getname() << " is equally fast as " << pet2->getdata().getname() << endl;

				}
			}
			return true;
		}
		else{
			cout <<"Theres only one pet in this list " << endl;
			return false;
		}
	}		
	if(toupper(button) =='B'){
		int treat;
		cout <<"\nHow many treats would you like to feed";
		cin >> treat;
		cin.ignore(100, '\n');
		pet->getdata() += treat;

		return true;
	}
	if(toupper(button) =='C'){
		int minutes;
		cout <<"\nHow many minutes would you like to walk your pet?";
		cin>>minutes;
		cin.ignore(100, '\n');
		pet->getdata() == minutes;
	}
	return true;
}


//Derived Class 3 Functions
template <>
bool DLL<breedingPet>::interact(){
	char button;
	displaynames();
	cout <<"\nPick a pet to interact with : " << endl;
	Node<breedingPet> * pet;
	do{
		pet = retrieve();
	}while(!pet);

	cout <<"(A) Compatibility Check | (B) Feed Treat | (C) Walk Pet";
	cin>>button;
	cin.ignore(100, '\n');

	if(toupper(button) =='A'){
		if(head->getnext() != nullptr){
		cout <<"Enter infomration for second pet:" << endl;;
		Node<breedingPet> * pet2 = retrieve();
		if(pet2){
			pet->getdata() != pet2->getdata();
		}
		return true;
		}
		else{
			cout <<"Theres only one pet in this list " << endl;
			return false;
		}
	}
	if(toupper(button) =='B'){
		int treat;
		cout <<"\nHow many treats would you like to feed";
		cin >> treat;
		cin.ignore(100, '\n');
		pet->getdata() += treat;

		return true;
	}
	if(toupper(button) =='C'){
		int minutes;
		cout <<"\nHow many minutes would you like to walk your pet?";
		cin>>minutes;
		cin.ignore(100, '\n');
		pet->getdata() == minutes;
	}

	return true;
}









