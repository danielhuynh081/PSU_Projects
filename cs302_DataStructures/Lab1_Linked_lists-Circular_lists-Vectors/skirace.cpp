#include "class.h"

//Ski Race Functions, LLL 


//Adding Functions

bool SkiRace::addplayer(skiing racer){ //Wrapper Add Function
	Node * racernode = new Node(racer);
	if(!head){
		head = racernode;
		return true;
	}
	else{
		return addrecursive(racernode, head);
	}
}

bool SkiRace::addrecursive(Node * data, Node* current){//Recursive Add Function
	if(!current){ //checks if we're in bounds
		return false;
	}
	else if(current->getnext() != nullptr){//progressing to last element
		return addrecursive(data, current->getnext());
	}
	else{
		current->setnext(data); //adds our new data
		return true;
	}
}

// Display Functions LLL
bool SkiRace::displayplayers(){ // Wrapper Display Function
	reorderlist();
	clearduplicates(head);
	if(!head){
		cout <<"there are currently no players";
		return false;
	}
	else{
		cout <<"\nCurrent leaderboard" << endl;
		return displayrecursive(head, 1);
	}
}

bool SkiRace::displayrecursive(Node* current, int num){ //Recursive Display Function
	if(!current){//we've reached the end of our list and displayed all players
		return true;
	}
	else{
		cout << current->getname() << " place : " << num<< " meters from beginning " <<  current->gettime() << endl;

		if(current->getnext()) //Bounds Check
		{
			return displayrecursive(current->getnext(), ++num);
		}
		else{
			return true;
		}

	}
}

//Removal Functions
bool SkiRace::removeone(string nameinput) //Remove One Racer Wrapper

{
	if(!head)// our list is empty
	{
		return false;
	}
	else if(head->getnext() == nullptr && strcmp(head->getname().c_str(), nameinput.c_str()) == 0) //one item list
	{
		delete head;
		head = nullptr;
		return true;
	}
	else{
		return removerecursive(nameinput, head, head); //calls our recursive function
	}
}

bool SkiRace::removerecursive(string name, Node*current, Node * previous) // Recursive Remove One Function LLL
{
	if(current->getnext() == nullptr) //checks if we're out of bounds
	{
		if(strcmp(current->getname().c_str(), name.c_str()) == 0){
			delete current;
			head =nullptr;
			return true;
		}
		return false;
	}
	else if(strcmp(current->getname().c_str(), name.c_str()) == 0) //looks for a match
	{
		if(current == head) //checks if our match is our head
		{
			previous = head->getnext();
			delete head;
			head = previous;
			return true;
		}
		else{//if not our head it will connect the prevous's next into the removed next
			previous->setnext(current->getnext());
			delete current;
			return true;
		}
	}
	else{ //if theres no match the function will progress down the list
		previous = current;
		return removerecursive(name, current->getnext(), previous);
	
}
}

//Recursively Remove All Nodes In Our List LLL
bool SkiRace::removeall(Node* current){
	if(!current){//checks if theres no more nodes left
		cout <<"\nour list is empty";
		return true;
	}
	else{ //recursively deletes nodes
		Node * temp = current->getnext();

		if(temp->getnext() != nullptr){
			current->setnext(temp->getnext());
			delete temp;
			return removeall(current);
		}
		else{
			delete temp;
			delete head;
			head = nullptr;
			return true;
		}
	}
}
//Retrieval Functions
//

bool SkiRace::retrieve(){ //Retrieval Wrapper Function
	int num;
	if(!head){ //Empty list case
		cout <<"our list is empty"<< endl;
		return false;
	}
	//input error checks
	do{
		cout <<"which place would you like to retrieve 1-5?:";
		cin >>num;
		cin.ignore(100, '\n');
		if(num >5 || num <= 0){
			cout <<"there are only 5 players, enter 1-5" << endl;
		}
	}
	while(num >5 || num < 0);
	return retrieverecursive(head, 1, num);
}

bool SkiRace::retrieverecursive(Node* current, int mover, int goal){ //Recursive Retrieval Function
	if(mover == goal){
		//cases for each player instead of if statements
		switch(goal){
			case 1:
				cout <<"\nPlayer in 1st is" << current->getname();
				break;
			case 2:
				cout <<"\nPlayer in 2nd is" << current->getname();
				break;
			case 3: 
				cout <<"\nPlayerin 3rd is" << current->getname();
				break;
			case 4:
				cout <<"\nPlayer in 4th is" << current->getname();
				break;
			case 5:
				cout <<"\nPlayer in 5th is" << current->getname();
				break;
		}
		cout <<endl;
	}
	else{//recursive call to traverse
		if(current->getnext() != head){
			return retrieverecursive(current->getnext(), ++mover, goal);
		}
		else{
			cout <<"\nno players at place : "<< goal << " players are tied" << "\n\nENTER TO CONTINUE : ";
			cin.get();
		}
	}
	return true;
}

//Leaderboard Functions LLL
//
bool SkiRace::checkduplicate(Node *& data, Node *& current){ //Check Duplicate Places
	if( current != data && current->getData().gettime() == data->getData().gettime()){
		return true;
	}
	else if(current->getnext() != head){
		return checkduplicate(data, current->getnext());
	}
	//last element check
	return false;
}

bool SkiRace::clearduplicates(Node *& current){ //Fix Duplicate Places
	if(checkduplicate(head, current)){
			current->setplace(current->getplace() -1);
			return true;
	}
	else if(current->getnext() != head){
		return clearduplicates(current->getnext());
	}
	return true;
}
bool SkiRace::reorderlist(){ //Wrapper Leaderboard Fix Function
	if(!head){
		cout <<"empty list";
		return false;
	}
	else{
		reorderlist(head);
	}
	return true;

}

bool SkiRace::reorderlist(Node *& current){ //Recursive Leaderboard Fix
	if(current && current->getnext() != head){
		current->setplace(findplace(current, head,5, 5));	
		return reorderlist(current->getnext());
	}
	if(current){
	current->setplace(findplace(current, head,5, 5));	
	}

	return true;
}
int SkiRace::findplace(Node *& data, Node *& current, int i, int travel){ //Place Determining Function
	 if(travel > 0 && current){
		if(data != current && data->getData().gettime() > current->getData().gettime()){
			return findplace(data,current->getnext(), --i, --travel);
		}
		return findplace(data, current->getnext(), i, --travel);
	}
	return i;
}


//Racing functions LLL

bool SkiRace::progressrace(Node * current){ //Increment Each Nodes Distance
	if(current){
		current->increasetime(current);
		if(current->gettime() > 50){
			cout <<"\nWinner : " << current->getname() << "\nENTER TO CONTINUE" << endl;
			cin.get();
			return false;
		}
		if(current->getnext()){
			progressrace(current->getnext());
		}
		else{
			return true;
		}
	}
	return true;
}

bool SkiRace::racestart(){ //Racing Menu, User interacting
	char gamebutton;
	bool start= true;
	while(start){
		racemenu();
		cin>>gamebutton;
		cin.ignore(100, '\n');
		if(toupper(gamebutton) =='A'){ //Race Progression
			cout <<"\nRace progressed " << endl;
			if(!progressrace(head))
			{
				cout <<"\n\nRace over !" << endl;
				displayplayers();
				cout <<endl;
				start = false;
			}
		}
		if(toupper(gamebutton) =='B'){ //Display Function
			displayplayers();
		}
		if(toupper(gamebutton) =='C'){// Retrieve Function
			retrieve();
		}
		if(toupper(gamebutton) =='D'){ //Removal Functions
			string name;
			cout <<"who would you like to kick?";
			cin >>name;
			cin.ignore(100, '\n');
			removeone(name);
		}
		if(toupper(gamebutton) =='E'){ //Unique Class Functions
			char button;
			cout <<"(A) Lean forward (B) Decrease speed (C) Tuck elbows";
			cin >> button;
			cin.ignore(100, '\n');
			if(toupper(button) =='A'){
				leanforward(head);
				if(!progressrace(head))
				{
					cout <<"\n\nRace over !" << endl;
					displayplayers();
					cout <<endl;
					removeall(head);
					start = false;
				}
			}
			if(toupper(button) =='B'){
				decreasespeed(head);		
				if(!progressrace(head))
				{
					cout <<"\n\nRace over !" << endl;
					displayplayers();
					cout <<endl;
					removeall(head);
					start = false;
				}
			}
			if(toupper(button) =='C'){
				//
				tuckelbows(head);
				if(!progressrace(head))
				{
					cout <<"\n\nRace over !" << endl;
					displayplayers();
					cout <<endl;
					removeall(head);
				}
			}
			

		}
		if(toupper(gamebutton) =='F'){ //Race Ending Function
			start = false;
		}
	}
	return true;
}

