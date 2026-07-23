#include "class.h"

//Daniel Huynh, CS302, Karla Fant, Program 3
//This file defines our functions that set and display our games depending on our type



// **Base Class Game setting **
void game::setgame(){
	char ageinput, playerinput;
	cout <<"\nEnter the activity name: ";
	cin >> name;
	cin.ignore(100, '\n');
	do{
		cout <<"\n(A) Everyone 10+ | (B) Teen 13+ | (C) Adult 18+  : ";
		cin >>ageinput;
		cin.ignore(100, '\n');
	}while(toupper(ageinput) != 'A' && toupper(ageinput) != 'B' && toupper(ageinput) != 'C');
	switch (toupper(ageinput)){
		case 'A': 
			age = 10;
			break;
		case 'B':
			age = 13;
			break;
		case 'C':
			age = 18;
			break;
	}
	do{
		cout <<"\nEnter the max players:\n(A) 1 Player | (B) 2 Player | (C) 3 Player | (D) 4 Players or more : ";
		cin >> playerinput;
		cin.ignore(100, '\n');
	}while(toupper(playerinput) != 'A' && toupper(playerinput) != 'B' && toupper(playerinput) != 'C' && toupper(playerinput) != 'D');
	switch(toupper(playerinput)){
		case 'A':
			players = 1;
			break;
		case 'B':
			players =2;
			break;
		case 'C':
			players= 3;
			break;
		case 'D':
			players= 4;
			break;
	}
	return;
}

// **Sport Game Display and Setting **
void sport::display(){
	cout <<"\nSport Game" << endl;
	cout <<"Sport: " << name << endl;
	cout <<"Age : " << age << "+"<<endl;
	if(players == 4){
		cout <<"Players : "<< players << " or more " << endl;
	}else{
		cout <<"Players : "<< players << endl;
	}
	cout <<"Location: " << location << endl;
	cout <<"Difficulty : " << difficulty << endl;
}

void sport::setgame(){
	char locationinput, difficultyinput;
	//Base Class Function
	game::setgame();
	//Pick Location
	do{
		cout <<"\nEnter the location:\n(A) Outdoor | (B) Indoor | (C) Hybrid ";
		cin >> locationinput;
		cin.ignore(100, '\n');
	}while(toupper(locationinput) != 'A' && toupper(locationinput) != 'B' && toupper(locationinput) != 'C');
	//Pick Difficulty
	do{
		cout <<"\nEnter the difficulty:\n(A) Easy | (B) Medium | (C) Hard ";
		cin >> difficultyinput;
		cin.ignore(100, '\n');
	}while(toupper(difficultyinput) != 'A' && toupper(difficultyinput) != 'B' && toupper(difficultyinput) != 'C');
	//Set Location
	switch(toupper(locationinput)){
		case 'A':
			location = "Outdoor";
			break;
		case 'B':
			location ="Indoor";
			break;
		case 'C':
			location ="Hybrid";
			break;
	}
	//Set Difficulty
	switch(toupper(difficultyinput)){
		case 'A':
			difficulty = "Easy";
			break;
		case 'B':
			difficulty = "Medium";
			break;
		case 'C':
			difficulty = "Hard";
			break;
	}
}

// ** Gambling Game Display and Setting **
void gambling::display(){
	cout <<"\nGambling Game" << endl;
	cout <<"Title: " << name << endl;
	cout <<"Age : " << age << endl;
	cout <<"Players : "<< players << endl;
	cout <<"Materials : " << materials << endl;
	cout <<"Risk : " << risk << endl;
}

void gambling::setgame(){
	//Base Class Function
	game::setgame();
	char riskinput, materialinput;
	do{
		cout <<"\nEnter the materials: \n(A) Deck of cards | (B) Dice | (C) Game Board  ";
		cin >> materialinput;
		cin.ignore(100, '\n');
	}while(toupper(materialinput) != 'A' && toupper(materialinput) != 'B' && toupper(materialinput) != 'C');
	do{
		cout <<"\nEnter the risk:\n(A) Low Risk | (B) Medium Risk | (C) High Risk ";
		cin >> riskinput;
		cin.ignore(100, '\n');
	}while(toupper(riskinput) != 'A' && toupper(riskinput) != 'B' && toupper(riskinput) != 'C');
	switch(toupper(materialinput)){
		case 'A':
			materials = "Deck of cards";
			break;
		case 'B':
			materials = "Dice";
			break;
		case 'C':
			materials = "Game Board";
			break;
	}
	switch(toupper(riskinput)){
		case 'A':
			risk= "Low Risk";
			break;
		case 'B':
			risk ="Medium Risk";
			break;
		case 'C':
			risk = "High Risk";
			break;
	}
}

// **Video Game Display and Setting **
void videogame::display(){
	cout <<"\nVideoGame" << endl;
	cout <<"Title: " << name << endl;
	cout <<"Genre : " << genre << endl;
	cout <<"Minimum age : " << age << endl;
	cout <<"Players : "<< players << endl;
	cout <<"Hours to complete : " << hours << endl;
}
void videogame::setgame(){
	char hourinput, genreinput;
	//Base Class Function
	game::setgame();
	do{
		cout <<"\nHow many hours does it take to complete? (A) 0-20 Hours | (B) 20-50 Hours | (C) 50+ Hours" << endl;
		cin >> hourinput;
		cin.ignore(100, '\n');
	}while(toupper(hourinput) != 'A' && toupper(hourinput) != 'B' && toupper(hourinput) != 'C');
	do{
		cout <<"What is the genre ? :\n(A) Sandbox | (B) Shooter | (C) RPG " << endl;
		cin >> genreinput;
		cin.ignore(100, '\n');
	}while(toupper(genreinput) != 'A' && toupper(genreinput) != 'B' && toupper(genreinput) != 'C');
	switch(toupper(genreinput)){
		case 'A':
			genre = "Sandbox";
			break;
		case 'B':
			genre = "Shooter";
			break;
		case 'C':
			genre = "RPG";
			break;
	}
	switch(toupper(hourinput)){
		case 'A':
			hours= "0-20 Hours";
			break;
		case 'B':
			hours ="20-50 Hours";
			break;
		case 'C':
			hours = "50+ Hours";
			break;
	}
}






