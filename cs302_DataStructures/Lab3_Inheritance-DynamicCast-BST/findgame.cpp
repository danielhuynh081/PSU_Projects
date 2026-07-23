#include "class.h"



//Daniel Huynh, CS302, Karla Fant, Program 3
//this file holds functions that help the user find the perfect game.



//This function allows users to search for a specific game, depending on type, age, players, and more.
bool tree::searchgame(){
	char choice, choice2, choice3, op1, op2;
	int age, players; 
	if(!root){
		cout <<"empty list" << endl;
		return false;
	}
	do{
		cout <<"\nWhat type of game would you like to play?\n(A) Sport | (B) Gambling | (C) Videogame" << endl;
		cin >>choice;
		cin.ignore(100, '\n');
	}while(toupper(choice) != 'A' && toupper(choice) != 'B' && toupper(choice) != 'C');
	switch(toupper(choice)){
		case 'A':
			do{
				cout <<"\n(A) Outdoor | (B) Indoor | (C) Hybrid: " << endl;
				cin >>op1;
				cin.ignore(100, '\n');
				cout <<"\n(A) Easy | (B) Medium | (C) Hard: " << endl;
				cin >>op2;
				cin.ignore(100, '\n');
			}while(toupper(op1) != 'A' && toupper(op1) != 'B' && toupper(op1)!='C' && toupper(op2)!='A' && toupper(op2)!='B' && toupper(op2) !='C');
			break;
		case 'B': //Gambling Game
			do{
				cout <<"\n(A) Cards | (B) Dice | (C) Game Board: " << endl;
				cin >>op1;
				cin.ignore(100, '\n');
				cout <<"\n(A) Low Risk| (B) Medium Risk | (C) Hard Risk: " << endl;
				cin >>op2;
				cin.ignore(100, '\n');
			}while(toupper(op1) != 'A' && toupper(op1) != 'B' && toupper(op1)!='C' && toupper(op2)!='A' && toupper(op2)!='B' && toupper(op2) !='C');
			break;
		case 'C': //Video Game
			do{
				cout <<"\n(A) Sandbox| (B) Shooter | (C) RPG: " << endl;
				cin >>op1;
				cin.ignore(100, '\n');
				cout <<"\n(A) 0-20 Hours | (B) 20-50 Hours | (C) 50+ Hours: " << endl;
				cin >>op2;
				cin.ignore(100, '\n');
			}while(toupper(op1) != 'A' && toupper(op1) != 'B' && toupper(op1)!='C' && toupper(op2)!='A' && toupper(op2)!='B' && toupper(op2) !='C');
			break;
	}
	do{
		cout <<"\nPick the required age for this game?\n(A) 10+ Everyone | (B) 13+ Teen | (C) 18+ Adult" << endl;
		cin >>choice2;
		cin.ignore(100, '\n');
	}while(toupper(choice2) != 'A' && toupper(choice2) != 'B' && toupper(choice2) != 'C');
	do{
		cout <<"\nWhat type of game would you like to play?\n(A) 1 Player | (B) 2 Players | (C) 3 Players | (D) 4 or more players" << endl;
		cin >>choice3;
		cin.ignore(100, '\n');
	}while(toupper(choice3) != 'A' && toupper(choice3) != 'B' && toupper(choice3) != 'C' && toupper(choice3) != 'D');
	switch(toupper(choice2)){
		case 'A':
			age =10;
			break;
		case 'B':
			age =13;
			break;
		case 'C':
			age =18;
			break;
	}
	switch(toupper(choice3)){
		case 'A':
			players = 1;
			break;

		case 'B':
			players =2;
			break;

		case 'C':
			players = 3;
			break;

		case 'D':
			players =4;
			break;
	}


	try{

	cout <<"\nSearching for games .. " << endl;
	bool result =displaysearch(root, choice, age, players, op1, op2);
	if(!result){
		cout <<"\nWe couldn't find a game that meets your needs" << endl;
	}

	}catch(const exception & e){
		cerr <<"Error : " << e.what() << endl; 
	}
	return true;
}




//Search Function To Find Specific Game
bool tree::displaysearch(unique_ptr<Node> & current, char type, int age, int players, char op1, char op2){
	if(current)
	{
		if(current->getleft())
		{
			displaysearch(current->getleft(), type, age, players, op1, op2);
		}
		if(checktype(current.get(), type, age, players, op1, op2))
		{
				current->display();
		}
		if(current->getright())
		{
			displaysearch(current->getright(), type, age, players, op1, op2);
		}
	}
	return true;
}

//Check Type For Specific Game
bool tree::checktype(Node* current, char typeinput, int age, int players, char op1, char op2)
{
	if(toupper(typeinput) =='A')
	{

		if(dynamic_cast<sport*>(current->getdata().get()) && current->getdata()->checkvalid(age, players, op1 ,op2))
		{
			return true;
		}
		else{
			return false;
		}
	}
	if(toupper(typeinput) =='B')
	{

		if(dynamic_cast<gambling*>(current->getdata().get()) && current->getdata()->checkvalid(age, players, op1, op2))
		{
			return true;
		}
		else{
			return false;
		}
	}
	if(toupper(typeinput) =='C')
	{

		if(dynamic_cast<videogame*>(current->getdata().get()) && current->getdata()->checkvalid(age, players, op1, op2))
		{
			return true;
		}
		else{
			return false;
		}
	}

	return true;
}



					




//Virutal Find Sport Game Check
bool sport::checkvalid(int age, int players, char op1, char op2){

	if(age >= getage() && players == getplayers()){
		switch(toupper(op1)){
			case 'A':
				if(getlocation() == "Outdoor"){
					break;
				}
				else{
					return false;
				}
			case 'B':
				if(getlocation() == "Indoor"){
					break;
				}
				else{
					return false;
				}
			case 'C':
				if(getlocation() == "Hybrid"){
					break;
				}
				else{
					return false;
				}
		}
		switch(toupper(op2)){
			case 'A':
				if(getdifficulty() =="Easy"){
					break;
				}else{
					return false;
				}
			case 'B':
				if(getdifficulty() == "Medium"){
					break;
				}
				else{
					return false;
				}
			case 'C':
				if(getdifficulty() == "Hard"){
					break;
				}else{
					return false;
				}
		}
		return true;

	}
	return false;

}

//Virtual Find Gamvling Game Check
bool gambling::checkvalid(int age, int players, char op1, char op2){

	if(age >= getage() && players == getplayers()){
		switch(toupper(op1)){
			case 'A':
				if(getmaterials() == "Deck Of Cards"){
					break;
				}
				else{
					return false;
				}
			case 'B':
				if(getmaterials() == "Dice"){
					break;
				}
				else{
					return false;
				}
			case 'C':
				if(getmaterials() == "Game Board"){
					break;
				}
				else{
					return false;
				}
		}
		switch(toupper(op2)){
			case 'A':
				if(getrisk() =="Low"){
					break;
				}else{
					return false;
				}
			case 'B':
				if(getrisk() == "Medium"){
					break;
				}
				else{
					return false;
				}
			case 'C':
				if(getrisk() == "High"){
					break;
				}else{
					return false;
				}
		}
		return true;

	}
	return false;

}

//Virtual Find Videogame Check
bool videogame::checkvalid(int age, int players, char op1, char op2){

	if(age >= getage() && players == getplayers()){
		switch(toupper(op1)){
			case 'A':
				if(getgenre() == "Sandbox"){
					break;
				}
				else{
					return false;
				}
			case 'B':
				if(getgenre() == "Shooter"){
					break;
				}
				else{
					return false;
				}
			case 'C':
				if(getgenre() == "RPG"){
					break;
				}
				else{
					return false;
				}
		}
		switch(toupper(op2)){
			case 'A':
				if(gethours() =="0-20 Hours"){
					break;
				}else{
					return false;
				}
			case 'B':
				if(gethours() == "20-50 Hours"){
					break;
				}
				else{
					return false;
				}
			case 'C':
				if(gethours() == "50+ Hours"){
					break;
				}else{
					return false;
				}
		}
		return true;

	}
	return false;

}
