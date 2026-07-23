
#include "class.h"

// Daniel Huynh, CS302 Data Structures, Karla Fant, Program 3
// This program manages and searches a collection of games using inheritance, dynamic casting, and a binary search tree.
//this file holds the main and is where the user navigates the program

int main(){
	//Variables
	char start, button, choice;

	//Data Structure
	tree mytree;

	do{
		cout <<"\nPress X to start : ";
		cin >>start;
		cin.ignore(100, '\n');
	}while(toupper(start) != 'X');
	while(toupper(start) =='X'){
		cout <<"\n(A) find game | (B) remove game | (C) add game | (D) Display | (E) end program " ;
		cin>>button;
		cin.ignore(100, '\n');
		if(toupper(button) == 'A'){ //Find Game
			mytree.adduser();
			mytree.searchgame();


		}
		if(toupper(button) =='B'){ //Remove All Games
			char r;
			cout <<"(A) remove one  | (B) remove all" << endl;
			cin >>r;
			cin.ignore(100, '\n');
			if(toupper(r) =='A'){
				mytree.removeone();
			}
			else{
				mytree.removeall();
			}	

		}
		if(toupper(button) =='C'){ //Create Game
			mytree.addnode();
		}
		if(toupper(button) == 'D'){ //Display Game
			cout <<"\n(A) display tree | (B) display recent users" << endl;
			cin >> choice;
			cin.ignore(100, '\n');
			switch(toupper(choice)){
				case 'A':
					mytree.displayhelper();
					break;
				case 'B':
					mytree.displayusers();
			}

		}
		if(toupper(button) =='E'){
			cout <<"\nClosing the application"<<endl;
			start ='c';
		}
	}
	return 0;
}

