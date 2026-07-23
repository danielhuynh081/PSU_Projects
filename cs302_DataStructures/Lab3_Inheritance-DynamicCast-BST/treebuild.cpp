#include "class.h"


//Daniel Huynh, CS302, Karla Fant, Program 3
//This file holds functions that display and modify our tree.


//STL list Functions

//STL Insert
bool tree::adduser(){
	string nameinput;
	cout <<"\nWhat is your name? : ";
	cin >> nameinput;
	cin.ignore(100, '\n');

	users.push_back(nameinput);
	return true;
}


//STL Display Wrapper
bool tree::displayusers(){
	if(users.empty()){
		cout <<"No users in recent user list" << endl;
		return false;
	}
	cout <<"\nRecent User List:" << endl;
	return displayusers(0);
}

//Recursive STL Display
bool tree::displayusers(long unsigned int i){
	if(i < users.size()){
		cout << " \nName: " << users[i] << endl;
		return displayusers(++i);
	}

	return true;
}


//Insertion Wrapper Function
bool tree::addnode(){
	char c;
	game * newgame;
	do{
		cout <<"(A) Sport Game | (B) Gambling Game | (C) Video Game " << endl;
		cin >>c;
		cin.ignore(100, '\n');
	}while(toupper(c) !='A' && toupper(c) != 'B' && toupper(c) != 'C');
	switch(toupper(c)){
		case 'A':
			newgame = new sport();
			break;
		case 'B':
			newgame = new gambling();	
			break;
		case 'C':
			newgame = new videogame();
			break;
	}
	try{
	newgame->setgame();
	addnode(newgame);
	}catch(const bad_alloc & e){
		cerr <<"memory error: " << e.what() << endl;
	}
	return true;
}

//Insertion Function
bool tree::addnode( game * newgame){
	//Empty List Case
	if(!root){
		unique_ptr<Node> temp(new Node(newgame));
		root = move(temp);
		return true;
	}
	else{
		//Exception Handling for recursive call
		try{
			addnode(root, newgame);
			return true;
		}catch(const bad_alloc & e){
			cerr << "error adding nodes" << e.what() << endl;
		}
		catch(...){
			cerr <<"unknown error" << endl;
		}
	}

	return true;
}


//Insertion Function Recursive
bool tree::addnode(unique_ptr<Node> & current, game * newgame){
	if(!current) //Open spot for new game found
	{
		unique_ptr<Node> temp(new Node(newgame));
		current = move(temp);
		return true;
	}
	//Traversal
	if(current->getdata()->getname() <= newgame->getname()){
		addnode(current->getright(), newgame);
	}
	else if(current->getdata()->getname() > newgame->getname()){
		addnode(current->getleft(), newgame);
	}
	return true;
}

//Removal Functions

//Remove All Wrapper
bool tree::removeall(){
	if(!root){
		cout <<"\nempty tree"<< endl;
	}
	try{
		removeall(root.get());
		root=nullptr;
		return true;
	}catch(const exception &e){
		cerr <<"error: " << e.what() << endl;
	}
	catch(...){
		cerr<<"\nunknown error" << endl;
	}
	return true;
}

//Remove All Recursive
bool tree::removeall(Node * current){
	if(current){
		if(current->getleft().get()){
			removeall(current->getleft().get());
		}
		current->getdata().reset();
		if(current->getright().get()){
			removeall(current->getright().get());
		}
	}
	return true;
}


//Remove One Function Wrapper
bool tree::removeone()
{
	char gamepick;
	string gameremove;
	if(!root){
		cout <<"empty list" << endl;
		return false;
	}
	do{
		cout <<"\n(a) Remove Sport Game\n(b) Remove Gambling Game\n(c) Remove Video Game" << endl;
		cin>> gamepick;
		cin.ignore(100, '\n');
	}while(toupper(gamepick) != 'A' && toupper(gamepick) != 'B' && toupper(gamepick) != 'C');
	displaytype(root, gamepick, false);
	cout <<"\n*** Type exactly as seen ***\nWhich game would you like to remove?";
	cin >>gameremove;
	cin.ignore(100, '\n');
	if(root->getleft().get() == nullptr && root->getright().get() == nullptr)
	{
		if(root->getdata()->getname() == gameremove)
		{
			root.reset();
			return true;
		}
		cerr<<"game not found " << endl;
		return false;
	}

	try//exception handling
	{
		removeone(gamepick, root.get(), root.get(), gameremove);
		return true;
	}catch(const exception & e){
		cerr<<"exception error" << e.what() << endl;
		return false;
	}
	catch(...)
	{
		cerr <<"error removing" << endl;
		return false;
	}
	return true;
}


//Remove One Function Recursive
bool tree::removeone(char type, Node * parent, Node * current, string gamename)
{
	if(!current)//stopping statement, also prevents from accessing unaccesible memory
	{
		return false;
	}
	if(current)
	{
		if(gamename < current->getdata()->getname() && current->getleft().get())
		{
			return removeone(type, current, current->getleft().get(), gamename);
		}	
		else if(gamename > current->getdata()->getname() && current->getright().get())
		{
			return removeone(type, current, current->getright().get(), gamename);
		}
		else{
			if(current->getdata()->getname() == gamename && checktype(current, type))//node to be removed found
			{
				if(current->getleft() == nullptr && current->getright() == nullptr) //leaf case
				{
					if(parent){
						if(parent->getleft().get() == current){//check if its either in the left or right tree of the parent
							parent->setleft(nullptr);
						}
						else{
							parent->setright(nullptr);
						}
					}
					else{ //case of removing a single data tree
						root = nullptr;
					}
					return true;
				}
				else if(current->getleft() == nullptr && current->getright() != nullptr)//one right node
				{
					Node* temp = current->getright().release(); //set a hold for the right node of current
					if(parent)
					{
						if(parent->getleft().get() == current) //replace current with our hold 
						{
							parent->setleft(unique_ptr<Node>(temp));
						}
						else{
							parent->setright(unique_ptr<Node>(temp));
						}
					}else{//removing root case
						root = unique_ptr<Node>(temp);
					}
					return true;
				}
				else if( current->getleft() != nullptr && current->getright() == nullptr)//one left node
				{
					Node* temp = current->getleft().release(); //set hold for current in left node case
					if(parent)
					{
						if(parent->getleft().get() == current)//replace parent left node with temp hold
						{
							parent->setleft(unique_ptr<Node>(temp));
						}
						else{
							parent->setright(unique_ptr<Node>(temp));
						}
					}
					return true;
				}
				else{
					//middle of list
					Node*successor = current->getright().get(); //move one to the right for sucessor loop
					while(successor->getleft() != nullptr)
					{
						successor = successor->getleft().get(); //move to successor
					}
					current->setdata(move(successor->getdata())); //replace current wth sucessor
					if(current->getright().get())
					{
						return removeone(type, current, current->getright().get(), successor->getdata()->getname());
					}
				}
			}
		}
	}
	return false;
}

//Display Functions

//Display Function Wrapper For Main
bool tree::displayhelper(){
	char choice2;
	if(!root){
		cout <<"empty tree" << endl;
		return false;
	}
	do{
		cout <<"(A) Display All | (B) Display By Type " << endl;
		cin >> choice2;
		cin.ignore(100, '\n');
	}while(toupper(choice2) != 'A' && toupper(choice2) != 'B');
	if(toupper(choice2) =='A'){
		displayall();
	}
	if(toupper(choice2) =='B'){
		displaytype();
	}
	return true;
}

//Display All Nodes Wrapper
bool tree::displayall(){
	char detail;
	bool d;
	do{
		cout <<"\n(A) Display with detail | (B) Display game titles" << endl;
		cin >>detail;
		cin.ignore(100, '\n');
	}while(toupper(detail) !='A' && toupper(detail)!='B');
	if(toupper(detail) =='A'){
		d = true;
	}else{
		d = false;
	}
	return displayall(root, d);

}

//Display All Nodes Recursive
bool tree::displayall(unique_ptr<Node> & current, bool detail){
	if(current){
		if(current->getleft()){
			displayall(current->getleft(), detail);
		}
		if(detail){
			current->display();
		}
		else{
			cout<<"Name: " << current->getdata()->getname() << endl;
		}
		if(current->getright()){
			displayall(current->getright(), detail);
		}
	}
	return true;
}


//Display By Type Wrapper Function
bool tree::displaytype(){
	char gamepick;
	char detailpick;
	bool detail;

	do{
		cout <<"\n(A) Display Sports | (B) Display Gambling | (C) Display Videogames " << endl;
		cin >> gamepick;
		cin.ignore(100, '\n');
		cout <<"\n(A) Display with detail | (B) Display game titles" << endl;
		cin >>detailpick;
		cin.ignore(100, '\n');

	}while(toupper(gamepick) != 'A' && toupper(gamepick) != 'B' && toupper(gamepick) != 'C' && toupper(detailpick)!= 'A' && toupper(detailpick) != 'B');
	if(toupper(detailpick) =='A'){
		detail = true;
	}
	else{
		detail = false;
	}
	if(toupper(gamepick) =='A')
	{
		cout <<"Sports" << endl <<endl;
		displaytype(root, 'A', detail);
	}
	if(toupper(gamepick) =='B')
	{
		cout <<"Gambling" << endl << endl;
		displaytype(root, 'B', detail);
	}
	if(toupper(gamepick) =='C')
	{
		cout <<"Videogames" << endl << endl;
		displaytype(root, 'C', detail);
	}

	return true;
}


//Display By Type Recursive Function
bool tree::displaytype(unique_ptr<Node> &current, char gametype, bool detail)
{
	if(current)
	{
		if(current->getleft())
		{
			displaytype(current->getleft(), gametype, detail);
		}
		if(checktype(current.get(), gametype))
		{
			if(detail){
				current->display();
			}
			else{
				cout<<"Name: " << current->getdata()->getname() << endl;
			}
		}
		if(current->getright())
		{
			displaytype(current->getright(), gametype, detail);
		}
	}
	return true;
}

//Check Type Function
bool tree::checktype(Node* current, char typeinput)
{
	if(toupper(typeinput) =='A')
	{

		if(dynamic_cast<sport*>(current->getdata().get()))
		{
			return true;
		}
		else{
			return false;
		}
	}
	if(toupper(typeinput) =='B')
	{

		if(dynamic_cast<gambling*>(current->getdata().get()))
		{
			return true;
		}
		else{
			return false;
		}
	}
	if(toupper(typeinput) =='C')
	{

		if(dynamic_cast<videogame*>(current->getdata().get()))
		{
			return true;
		}
		else{
			return false;
		}
	}

	return true;
}






