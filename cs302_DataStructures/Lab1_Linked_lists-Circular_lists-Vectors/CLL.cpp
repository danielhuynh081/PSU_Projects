#include "class.h"

//Snowboading Race functions CLL

//Adding Functions 
//
bool SnowboardingRace::addplayer(const snowsport & racer){ // Wrapper Add Node
	Node * racernode = new Node(racer);
	if(!head){
		head = racernode;
		tail = head;
		tail->setnext(head);
		return true;
	}
	else{
		return addrecursive(racernode, head);
	}
}

bool SnowboardingRace::addrecursive(Node * data, Node * current){// Recursive Add Function
	if(!current){
		return false;
	}
	else if(current->getnext() != head){
		return addrecursive(data, current->getnext());
	}
	else{
		current->setnext(data);
		tail = data;
		tail->setnext(head);
		return true;
	}
}

//Displaying functions

bool SnowboardingRace::displayplayers(){ //Wrapper Display Function
	reorderlist();
	clearduplicates(head);
	if(!head){ //Empty list case
		cout <<"there are currently no players";
		return false;
	}
	else{
		cout <<"\nCurrent leaderboard" << endl;
		return displayrecursive(head);
	}
}

bool SnowboardingRace::displayrecursive(Node* current){ //Recursive Add Function
	if(current->getnext() == head){//we've reached the end of our list and displayed all players
		cout << current->getname() << " place : " << current->getplace() << " meters from beginning " << current->gettime() << endl;
		return true;
	}
	else{
		cout << current->getname() << " place : " << current->getplace() << " meters from beginning " <<  current->gettime() << endl;
		if(current->getnext()) //Bounds check
		{
			return displayrecursive(current->getnext());
		}
		else{
			return true;
		}
	}
}


// Removal Functions
bool SnowboardingRace::removeone(string nameinput) // Remove One Racer Wrapper
{
	if(!head)// our list is empty
	{
		return false;
	}
	else if(head == tail && strcmp(head->getname().c_str(), nameinput.c_str()) == 0) //one item list
	{
		delete head;
		head=tail=nullptr;
		return true;
	}
	else{
		return removerecursive(nameinput, head, head); //calls our recursive function
	}
}

bool SnowboardingRace::removerecursive(string name, Node*current, Node * previous) // Recursive Remove One Racer Function
{
	if(strcmp(head->getname().c_str(), name.c_str()) == 0){
		cout <<"you've removed yourself, race over!\n" << endl;
		removeall(head);
		return false;
	}
	if(current == tail) //Last Element Check
	{
		if(strcmp(current->getname().c_str(), name.c_str()) == 0) //looks for a match
		{
			previous->setnext(current->getnext());
			delete current;
			tail = previous;
			return true;
		}
		else{
			return false;
		}
	}
	else if(strcmp(current->getname().c_str(), name.c_str()) == 0) //looks for a match
	{
		if(current == head) //checks if our match is our head
		{
			tail->setnext(head->getnext());
			delete head;
			head = tail->getnext();
			return true;
		}
		else{//if not our head it will connect the prevous's next into the removed next
			previous->setnext(current->getnext());
			delete current;
			return true;
		}
	}
	else{ //if theres no match the function will progress down the list
		return removerecursive(name, current->getnext(), current);
	}
}

//Recursive Remove All Function
bool SnowboardingRace::removeall(Node* current){
	if(!current){//checks if theres no more nodes left
		cout <<"\nour list is empty";
		return true;
	}
	else{ //recursively deletes nodes
		Node * temp = current->getnext();

		if(temp->getnext() != head){
			current->setnext(temp->getnext());
			delete temp;
			return removeall(current);
		}
		else{
			delete temp;
			delete current;
			head = tail =nullptr;
			return true;
		}


	}
}

// Retrieval Functions

bool SnowboardingRace::retrieve(){ //Retrieval Function Wrapper
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

bool SnowboardingRace::retrieverecursive(Node* current, int mover, int goal){// Recursive Retrieval Function
	reorderlist();
	clearduplicates(head);
	cout <<"current :" << current->getplace() << "goal : " << goal << endl;
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
				cout <<"\nPlayer in 3rd is " << current->getname();
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

//Leaderboard functions

int SnowboardingRace::findplace(Node *& data, Node *& current, int i, int travel){ //Place Correction
	if(travel > 0 && current){
		if(data != current && data->getData().gettime() > current->getData().gettime()){
			return findplace(data,current->getnext(), --i, --travel);
		}
		return findplace(data, current->getnext(), i, --travel);
	}
	return i;
}
bool SnowboardingRace::checkduplicate(Node *& data, Node *& current){ // Place Duplicate Check
	if( current != data && current->getData().gettime() == data->getData().gettime()){
		return true;
	}
	else if(current->getnext() != head){
		return checkduplicate(data, current->getnext());
	}
	//last element check
	return false;
}

bool SnowboardingRace::clearduplicates(Node *& current){ //Place Duplicate Fix Function
	if(checkduplicate(head, current)){
		current->setplace(current->getplace() -1);
		return true;
	}
	else if(current->getnext() != head){
		return clearduplicates(current->getnext());
	}
	return true;
}
bool SnowboardingRace::reorderlist(){ // Leaderboard Fix Wrapper
	if(!head){ // Empty List Case
		cout <<"empty list";
		return false;
	}
	else{
		reorderlist(head);
	}
	return true;

}

bool SnowboardingRace::reorderlist(Node *& current){ //Recursive Leaderboard Fix Function
	if(current && current->getnext() != head){
		current->setplace(findplace(current, head,5, 5));	
		return reorderlist(current->getnext());
	}
	if(current){
		current->setplace(findplace(current, head,5, 5));	
	}

	return true;
}


//Racing Functions
//
bool SnowboardingRace::progressrace(Node * current){ //Increments Each Nodes Value 
	if(current){
		current->increasetime(current);
		if(current->gettime() > 50){
			cout <<"\nWinner : " << current->getname() << "\nENTER TO CONTINUE" << endl;
			cin.get();
			return false;
		}
		else if(current->getnext() != head){
			progressrace(current->getnext());
		}
		else{
			return true;
		}
	}
	return true;
}
bool SnowboardingRace::racestart(){// Racing Menu Function, This is where the user interacts
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
				removeall(head);
				start = false;
			}
		}
		if(toupper(gamebutton) =='B'){//Display Functions
			displayplayers();
		}
		if(toupper(gamebutton) =='C'){ //Retrieval Functions
			retrieve();
		}
		if(toupper(gamebutton) =='D'){ //Removal Functions
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
			cout <<"(A) Stunt (B) Carve (C) Heel Slide : " ;
			cin >> button;
			cin.ignore(100, '\n');
			if(toupper(button) =='A'){
				stunt();
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
				carve(head);
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
				heelslide(head);
				if(!progressrace(head))
				{
					cout <<"\n\nRace over !" << endl;
					displayplayers();
					cout <<endl;
					removeall(head);
					start = false;
				}
			}	
		}

		if(toupper(gamebutton) =='F'){ // Quit Race
			start = false;
		}
	}

	return true;
}
