#include "class.h"

// Daniel Huynh, CS302 Data Structures Karla Fant Program 2, February 15th 2024
// This program manages a collection of pets using a sorted doubly linked list, templates, and operator overloading.
// This file contains the main function and menu used to navigate the program.

int main(){

	//Variable Declaration
	char x, button, button2= '\0';
	string name, type, strength;

	//STL list 
	list pets;


	//Class Objects;
	workingPet Wpet;
	competitivePet Cpet;
	breedingPet Bpet;

	//Data Structures
	DLL<workingPet> Wlist;
	DLL<competitivePet> Clist;
	DLL<breedingPet> Blist;

	//Start Loop
	do{
		cout <<"welcome to the pet program, press x to start";
		cin >> x;
		cin.ignore(100, '\n');
		if(toupper(x) != 'X'){
			cout <<"\nYou must press x, try again" << endl;
		}


	}while(toupper(x) != 'X');
	//Main Program
	while(toupper(x) == 'X')
	{
		menu();
		cin >> button;
		cin.ignore(100, '\n');
		if(toupper(button) == 'A'){//Adding Nodes 
			char button2;
			cout <<"\nWhat type of pet will you be adding? \n(A) Working Pet (B) Competitive Pet (C) Breeding Pet : ";
			cin >> button2;
			cin.ignore(100, '\n');
			if(toupper(button2) == 'A'){ //Working Pet
				cin >>Wpet;
				pets + Wpet;
				Wlist.insertpet(Wpet);
			}
			if(toupper(button2) == 'B'){ //Competitive Pet

				cin >> Cpet;
				pets + Cpet;
				Clist.insertpet(Cpet);

			}
			if(toupper(button2) == 'C'){ //Breeding Pet
				cin >> Bpet;
				pets + Bpet;
				Blist.insertpet(Bpet);

			}
		}
		if(toupper(button) =='B'){ //Pet Removal
			cout <<"\nRemove from which list? \n(A) Working Pet | (B) Competitive Pet | (C) Breeding Pet :";
			cin >> button2;
			cin.ignore(100, '\n');
			if(toupper(button2) =='A'){
				Wlist.removepet();
			}
			if(toupper(button2) =='B'){
				Clist.removepet();

			}
			if(toupper(button2) =='C'){
				Blist.removepet();
			}
		}
		if(toupper(button) =='C'){ //Pet Display
			cout <<"\n**Pick a list**\n\n(a) Working Pets | (b) Competitive Pets | (c) Breeding pets | (d) All Pets: ";
			cin >>button2;
			cin.ignore(100, '\n');
			if(toupper(button2) == 'A'){ //Working Pet List
				Wlist.display();
			}
			if(toupper(button2) == 'B'){ //Competitive Pet List
				Clist.display();
			}
			if(toupper(button2) == 'C'){ //Breeding Pet List
				Blist.display();
			}	
			if(toupper(button2) == 'D'){ //Breeding Pet List
				pets.display();
			}	
		}
		if(toupper(button) =='D'){ //Pet Interaction
			cout <<"\nWhich pets would you like to interact with? \n(A) Working Pets (B) Competitive Pets (C) Breeding Pets " ;
			cin >> button2;
			cin.ignore(100, '\n');
			if(toupper(button2) == 'A'){
				Wlist.interact();
			}
			if(toupper(button2) == 'B'){
				Clist.interact();
			}
			if(toupper(button2) == 'C'){
				Blist.interact();
			}
		}
		if(toupper(button) =='E'){ //Pet Interaction
			cout <<"\nWhich list?\n(A) Working Pets (B) Competitive Pets (C) Breeding Pets" << endl;
			cin >> button2;
			cin.ignore(100, '\n');
			if(toupper(button2) == 'A'){
				Node<workingPet> * temp =Wlist.retrieve();
				if(temp){
					cout <<temp->getdata() << endl;
				}
			}
			if(toupper(button2) == 'B'){
				Node<competitivePet> * temp =Clist.retrieve();
				if(temp){
					cout <<temp->getdata() << endl;
				}
			}
			if(toupper(button2) == 'C'){
				Node<breedingPet> * temp =Blist.retrieve();
				if(temp){
					cout <<temp->getdata() << endl;
				}
			}

		}

		if(toupper(button) =='F'){ // End Program
			cout <<"\nClearing lists\n";
			Wlist.removeall();
			Blist.removeall();
			Clist.removeall();
			x = 'a';
		}


	}
	return 0;
}
