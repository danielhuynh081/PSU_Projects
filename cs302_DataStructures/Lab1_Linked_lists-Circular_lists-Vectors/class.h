#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include <algorithm>

using namespace std;

void menu();

//Parent class
class snowsport
{
	public:
		snowsport(){} //standard constructor
		snowsport(string nameinput, int ageinput, int placeinput): racetime(0),  place(placeinput){ //main constructor
			name = new char[strlen(nameinput.c_str()) + 1];
			strcpy(name, nameinput.c_str());

		}
		snowsport(const snowsport & copysport){  //copy constructor
			name = new char[strlen(copysport.name) +1];
			strcpy(name, copysport.name);
			place = copysport.getplace();
			racetime = copysport.gettime();
		}
		snowsport & operator = (const snowsport & copysport){ //Assignment operator
			if (this != &copysport){
				delete [] name;

				name = new char[strlen(copysport.name) + 1];
				strcpy(name, copysport.name);

				place = copysport.place;
				racetime = copysport.racetime;
			}
			return *this;
		}
		~snowsport(){ //destructor
			if(name){
				delete [] name;
				name = nullptr;
			}

		}

		//Getters
		char *  getname() const { 
			return name;
		}
		int gettime() const {
			return racetime;
		}
		int getplace()const {
			return place;
		}

		//Setters
		bool increasetime(int i){
			racetime += i;
			return true;
		}
		bool slowtime(int i){
			racetime -=i;
			return true;
		}
		int settime(int increase){
			racetime += increase;
			return true;
		}
		bool setplace(int i){
			place = i;
			return true;
		}




	protected:
		char * name;	
		int racetime;
		int place;

};


class Node
{
	public:
		Node(snowsport datainput): data(datainput), next(nullptr){} //Constructor
		~Node(){ //Destructor
		};

		//Getters
		Node *& getnext(){
			return next;
		}
		const Node * getnext2()const{
			return next;
		}
		snowsport&getData(){
			return data;
		}
		const snowsport&getData2()const{
			return data;
		}
		string getname() const{
			return data.getname();
		}
		int gettime(){
			return data.gettime();
		}
		int getplace(){
			return getData().getplace();
		}

		//Setters
		bool setnext(Node* nextinput){
			next= nextinput;
			return true;
		}
		bool settime(int increase){
			data.settime(increase);
			return true;
		}
		bool setplace(int i){
			getData().setplace(i);
			return true;
		}

		bool increasetime(Node * current){ //Race Progression
			if(rand() % 10 + 1 == 7){
				cout <<endl << current->getname() << " has hit a rock! they lose momentum" << endl;
				current->settime(rand() % 4  + 1);
				return true;
			}
			else{
				current->settime(rand() % 8 +1);
			}
			return true;
		}

		bool increasetime(int i){ //Unique Class Increase
			getData().increasetime(i);

			return true;
		}
		bool slowtime(int i){ //Unique Class Decrease
			getData().slowtime(i);
			return true;
		}

	private:
		snowsport data;
		Node * next;
};

//Derived class 1
class snowboarding: public snowsport
{
	public:
		snowboarding(): snowsport(){} //Default Constructor
		snowboarding(string name, int ageinput, int placeinput): snowsport(name, ageinput, placeinput){} //Main Constructor
		~snowboarding(){} //Destructor

		//Unique Class Function 1
		bool stunt(){
			int stunt = rand() % 5 + 1;
			switch(stunt){
				case 1:
					cout <<"\nyou hit a hand stand" << endl;
					return true;
				case 2:
					cout <<"\nyou land a 180 spin" << endl;
					return true;
				case 3:
					cout <<"\nyou close your eyes for 30 seconds "	<< endl;
					return true;
				case 4:
					cout <<"\nyou land a backflip"<< endl;
					return true;
				case 5:
					cout <<"\nyou land a 360 flip " << endl;
					return true;
			}
			return true;
		}
		//Unique Class Function 2
		bool carve(Node *& current){
			cout <<"You start carving and it gives you a short boost";
			current->increasetime(2);
			return true;
		}
		//Unique Class Function 3
		bool heelslide(Node *& current){
			cout <<"You heelslide and it slows you down";
			current->slowtime(6);
			return true;
		}


	private:
};

//Derived class 2
class snowmobiling: public snowsport
{
	public:
		snowmobiling(): snowsport(){} //Default Constructor
		snowmobiling(string name, int ageinput, int placeinput): snowsport(name, ageinput, placeinput){ //Main Constructor
		}
		~snowmobiling(){} //Destructor

		//Unique Class Function 1
		bool checkdistance(Node *& current){
			cout <<"\nYour current distance away from the finish line is : " << 50-current->gettime() << " meters. " << endl;
			return true;
		}
		//Unique Class Function 2
		bool driftvehicle(Node *& current){ 
			cout << "\nYou drift around a corner and cut time :O\n";
			current->increasetime(3);
			return true;
		}
		//Unique Class Function 3
		bool turboboost(Node *& current){
			cout <<"you use your turbo and gain speed " ;
			current->increasetime(5);
			return true;
		}

	private:
};

//Derived Class 3
class skiing: public snowsport
{
	public:
		skiing(){} //Default Constructor
		skiing(string name, int ageinput, int placeinput): snowsport(name, ageinput, placeinput){} //Main Constructor
		~skiing(){} //Destructor

		//Unique Class Function 1
		bool leanforward(Node *& current){
			cout <<"\nYou lean forward and become one with your skis\n";
			current->increasetime(3);
			return true;
		}
		//Unique Class Function 2
		bool decreasespeed(Node *& current){
			cout <<"\nYou slide down the hill perpendicularly and lose speed, but feel more stable\n"; //Increase Race tine
			current->slowtime(4);
			return true;
		}
		//Unique Class Function 3
		bool tuckelbows(Node *& current){
			cout <<"\nYou tuck your elbows in and focus\n " ; //Increase Racetime
			current->increasetime(5);
			return true;
		}
	private:
};


//Node for our CLL and LLL

//Linear Linked List Racing Class
class SnowmobileRace: public snowmobiling
{
	public:
		SnowmobileRace(){ //Constructor
		}
		SnowmobileRace(const SnowmobileRace & copysport){
			if(copysport.snowmobile){
				snowmobile = new char[strlen(copysport.snowmobile)];
				strcpy(snowmobile, copysport.snowmobile);
			}else{
				snowmobile = nullptr;
			}
			if(copysport.head){
				copylist(head, copysport.head);
			}
		}
		
		SnowmobileRace &operator=(const SnowmobileRace & copysport){
			if(this != &copysport){
				if(copysport.snowmobile){
					snowmobile = new char [strlen(copysport.snowmobile)];
					strcpy(snowmobile,copysport.snowmobile);
				}else{
					snowmobile = nullptr;
				}
				if(copysport.head){
					if(head){
						removeall(head);
					}
					copylist(head,copysport.head);
				}
			}
			return * this;
		}
		~SnowmobileRace(){ //Destructor
			if(snowmobile){
				delete [] snowmobile;
			}
			if(head){
				head = nullptr;
			}

		};

		//Menu
		bool racemenu(){
			cout <<"\n(A) Proceed With Race | (B) Display Leaderboard | (C) Retrieve A Place 1-5 | (D) Kick PLayers | (E) Interact with vehicle | (F) Quit Race\n\n";
			return true;
		}
		//Set snowmobile model
		bool setmobile();



		//Adding players
		bool addplayer(snowmobiling racer);
		bool addrecursive(Node * data, Node* current);

		//Display function
		bool displayplayers();
		bool displayrecursive(Node* current, int num);

		//Remove one
		bool removeone(string nameinput); //remove one racer wrapper
		bool removerecursive(string name, Node*current, Node * previous); //recursive remove one function

		//Recursively remove all nodes in our list
		bool removeall();
		bool removeall(Node* current);

		//Retrieve 
		bool retrieve();
		bool retrieverecursive(Node* current, int mover, int goal);

		//Leaderboard
		bool checkduplicate(Node *&current, Node *& data);
		bool clearduplicates(Node *& current);
		bool reorderlist();	
		bool reorderlist(Node *& current);
		int findplace(Node *& data, Node *& current, int i, int travel);


		//Application
		bool progressrace(Node * current);
		bool racestart();



		//Getter
		string getsnowmobile() const{
			return snowmobile;
		}

	private:
		bool copylist(Node *& newcurrent,const Node * current){
			if(current){
				newcurrent->setnext(new Node(current->getData2()));
				if(current->getnext2() != nullptr){
					return copylist(newcurrent->getnext() , current->getnext2());
				}
				return true;
			}


		}
		char * snowmobile;
		Node * head;


};

//Circular Linked List racing class
class SnowboardingRace:public snowboarding
{
	public:
		SnowboardingRace():head(nullptr), tail(nullptr){} //Constructor
		~SnowboardingRace(){
			if(head || tail){
				head = nullptr;
				tail = nullptr;
			}
		} //Destructor
		  //Menu
		bool racemenu(){
			cout <<"\n(A) Proceed With Race | (B) Display Leaderboard | (C) Retrieve A Place 1-5 | (D) Kick PLayers | (E) Stunt | (F) Quit Race\n\n";
			return true;
		}
		//adding players
		bool addplayer(const snowsport & racer);
		bool addrecursive(Node * data, Node * current);

		//Displaying players
		bool displayplayers();
		bool displayrecursive(Node* current);

		//Removing players
		bool removeone(string nameinput); //remove one racer wrapper
		bool removerecursive(string name, Node*current, Node * previous); //recursive remove one function

		bool removeall();
		bool removeall(Node* current);

		//Retrieving players
		bool retrieve();
		bool retrieverecursive(Node* current, int mover, int goal);

		//Leaderboard updates

		bool checkduplicate(Node *&current, Node *& data);
		bool clearduplicates(Node *& current);
		bool reorderlist();	
		bool reorderlist(Node *& current);
		int findplace(Node *& data, Node *& current, int i, int travel);


		//Racing function
		bool progressrace(Node * current);	
		bool racestart();

	private:
		Node * head;
		Node* tail;

};

class SkiRace: public skiing
{
	public:
		SkiRace():head(nullptr){} //Constructor
		~SkiRace(){ //Destuctor
			if(head){
				head = nullptr;
			}

		}

		//Menu
		bool racemenu(){
			cout <<"\n(A) Proceed With Race | (B) Display Leaderboard | (C) Retrieve A Place 1-5 | (D) Kick PLayers | (E) Stunt | (F) Quit Race\n\n";
			return true;
		}

		//Adding Players
		bool addplayer(skiing racer);
		bool addrecursive(Node * data, Node* current);

		//Display Function
		bool displayplayers();
		bool displayrecursive(Node* current, int num);

		//Remove One
		bool removeone(string nameinput); //remove one racer wrapper
		bool removerecursive(string name, Node*current, Node * previous); //recursive remove one function

		//Recursively Remove All Nodes In Our List
		bool removeall();
		bool removeall(Node* current);

		//Retrieve 
		bool retrieve();
		bool retrieverecursive(Node* current, int mover, int goal);

		//Leaderboard
		bool checkduplicate(Node *&current, Node *& data);
		bool clearduplicates(Node *& current);

		bool reorderlist();	
		bool reorderlist(Node *& current);

		int findplace(Node *& data, Node *& current, int i, int travel);

		//Application
		bool progressrace(Node * current);
		bool racestart();


	private:
		Node * head;
};

//Vector Class
class playerlist
{
	public:
		bool addplayer(const Node & player){//Adding Function
			recentplayers.push_back(player);
			return true;
		}
		bool displaylist(){ //Vector Display Function Wrapper
			if(recentplayers.empty()){
				cout <<"There are no recent players";
				return false;
			}
			return displaylist(0);
		}
		bool displaylist( unsigned int i ) const { // Recursive Display Function
			if(i < recentplayers.size()){
				cout <<"Name : " << recentplayers[i].getname() << endl;
				displaylist(++i);
			}

			return true;
		}
	private:
		vector<Node> recentplayers;
};

