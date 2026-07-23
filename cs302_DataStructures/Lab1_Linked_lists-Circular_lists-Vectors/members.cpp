#include "class.h"

//menu2
void menu()
{
	cout <<"what kind of race would you like to compete in?" << endl;
	cout <<"\n(a) Snowboarding (b) Snowmobiling (c) Skiiing (d) View Recent Players (e) Quit Application:" << endl;
}

//Snowmobile Racing Functions LLL

//Data Initialization	

bool SnowmobileRace::setmobile(){   //Snowmobile Vehicle
	char mobile;
	cout <<"\n\n(A) yamaha (B) Arctic Cat (C) Polaris";
	cin >>mobile;
	cin.ignore(100, '\n');	
	mobile = tolower(mobile);
	switch(mobile){
		case 'a':
			snowmobile = new char[strlen("yamaha") + 1];
			strcpy(snowmobile, "Yamaha");
			break;
		case 'b':
			snowmobile = new char[strlen("Arctic Cat") + 1];
			strcpy(snowmobile, "Arctic Cat");
			break;
		case 'c':
			snowmobile = new char[strlen("Polaris") + 1];
			strcpy(snowmobile, "Polaris");
			break;

	}
	return true;
}

bool SnowmobileRace::addplayer(snowmobiling racer){ //Wrapper function for LLL adding
	Node * racernode = new Node(racer);
	if(!head){ //checks if our list is empty
		head = racernode;
		return true;
	}
	else{
		return addrecursive(racernode, head);
	}
}

bool SnowmobileRace::addrecursive(Node * data, Node* current){// Recursive function for LLL adding
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

// Displaying Functions LLL
bool SnowmobileRace::displayplayers(){ // Wrapper display function
	reorderlist();
	clearduplicates(head);
	if(!head){ //Empty list case
		cout <<"there are currently no players";
		return false;
	}
	else{
		cout <<"\nCurrent leaderboard" << endl;
		cout <<"\nVehicle: " << getsnowmobile() << endl << endl;
		return displayrecursive(head, 1); //Recursive Call
	}
}

bool SnowmobileRace::displayrecursive(Node* current, int num){ //Recursive display function
	if(!current){//we've reached the end of our list and displayed all players
		return true;
	}
	else{
		cout << current->getname() << " place : " << num<< " meters from beginning " <<  current->gettime() << endl;

		if(current->getnext()) //Checks for next node before traversing
		{
			return displayrecursive(current->getnext(), ++num);
		}
		else{
			return true;
		}

	}
}

//Removal Functions LLL
//
bool SnowmobileRace::removeone(string nameinput) //ri Remove one node wrapper function
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

bool SnowmobileRace::removerecursive(string name, Node*current, Node * previous) // Recursive remove one node function
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

bool SnowmobileRace::removeall(Node* current){ //Recursively remove all nodes in our list LLL
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
bool SnowmobileRace::retrieve(){ // Retrieve function wrapper LLL
	int num;
	if(!head){
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

bool SnowmobileRace::retrieverecursive(Node* current, int mover, int goal){ //Recursive retrieve LLL
	reorderlist();
	clearduplicates(head);
	if(current->getplace() == goal){
		//cases for each player instead of if statements
		switch(goal){
			case 1:
				cout <<"\nPlayer in 1st is " << current->getname();
				break;
			case 2:
				cout <<"\nPlayer in 2nd is " << current->getname();
				break;
			case 3: 
				cout <<"\nPlayerin 3rd is " << current->getname();
				break;
			case 4:
				cout <<"\nPlayer in 4th is " << current->getname();
				break;
			case 5:
				cout <<"\nPlayer in 5th is " << current->getname();
				break;
		}
		cout <<endl;
		return true;
	}
	else{//recursive call to traverse
	     	if(current->getnext() && mover < 5){ //Bounds check
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
int SnowmobileRace::findplace(Node *& data, Node *& current, int i, int travel){ //Reordering Leaderboard Places
	 if(travel > 0 && current){ //Bounds checking
		if(data != current && data->getData().gettime() > current->getData().gettime()){
			return findplace(data,current->getnext(), --i, --travel); //Recursive call with place decrement
		}
		return findplace(data, current->getnext(), i, --travel); //Recursive call with no place decrement
	}
	return i;
}
bool SnowmobileRace::checkduplicate(Node *& data, Node *& current){ //Duplicate Places check
	if( current != data && current->getData().gettime() == data->getData().gettime()){ //Duplicate Found
		return true;
	}
	else if(current->getnext() != nullptr){ //Bounds check
		return checkduplicate(data, current->getnext());
	}
	//last element check
	return false; //Not a duplicate
}

bool SnowmobileRace::clearduplicates(Node *& current){ //Duplicate Places Fix
	if(checkduplicate(head, current)){ //Find duplicate
			current->setplace(current->getplace() -1); //Decrement by 1
			return true;
	}
	else if(current->getnext() != nullptr){ //Bounds check
		return clearduplicates(current->getnext());
	}
	return true; 
}
bool SnowmobileRace::reorderlist(){ //Wrapper For Leaderboard Fix
	if(!head){
		cout <<"empty list";
		return false;
	}
	else{
		reorderlist(head);
	}
	return true;

}

bool SnowmobileRace::reorderlist(Node *& current){ //Recursive Leaderboard Fix
	if(current && current->getnext() != nullptr){
		current->setplace(findplace(current, head,5, 5));	
		return reorderlist(current->getnext());
	}
	if(current){
	current->setplace(findplace(current, head,5, 5));	
	}

	return true;
}


//Racing functions LLL

bool SnowmobileRace::progressrace(Node * current){ // Recursive function to increase each nodes distance
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

bool SnowmobileRace::racestart(){ //Racing Menu
	char gamebutton;
	bool start= true;
	while(start){
		racemenu();
		cin>>gamebutton;
		cin.ignore(100, '\n');
		if(toupper(gamebutton) =='A'){ //Proceed with race
			cout <<"\nRace progressed " << endl;
			if(!progressrace(head))
			{
				cout <<"\n\nRace over !" << endl;
				displayplayers();
				cout <<endl;
				start = false;
			}
		}
		if(toupper(gamebutton) =='B'){ //Calls display functions
			displayplayers();
		}
		if(toupper(gamebutton) =='C'){ //Retrieval
			retrieve();
		}
		if(toupper(gamebutton) =='D'){ //Removal
			char button;
			cout <<"(A) kick one person (B) remove all players : " << endl;
			cin >>button;
			cin.ignore(100, '\n');
			if(toupper(button) == 'A'){

				string name;
				displayplayers();
				cout <<"who would you like to kick?";
				cin >>name;
				cin.ignore(100, '\n');
				if(!removeone(name)){
					start = false;
				}

			}
			if(toupper(button) =='B'){
				removeall(head);
			}
			
		}
		if(toupper(gamebutton) =='E'){ //Unique Class Functions
			char button;
			cout <<"(A) Check Distance (B) Drift  (C) Turbo : " ;
			cin >> button;
			cin.ignore(100, '\n');
			if(toupper(button) =='A'){
				checkdistance(head);
				cout <<"\n\nENTER TO CONTINUE:";
				cin.get();
			}
			if(toupper(button) =='B'){
				driftvehicle(head);		
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
				turboboost(head);
				if(!progressrace(head))
				{
					cout <<"\n\nRace over !" << endl;
					displayplayers();
					cout <<endl;
					removeall(head);
				}
			}
			

		}
		if(toupper(gamebutton) == 'F'){ //Quit Race
			start = false;
		}
	}
	return true;
}

