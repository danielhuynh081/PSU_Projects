#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#pragma once

using namespace std;

//CS302 Karla Fant Program 2, February 15th 2024 Daniel Huynh,
//This is my class file that holds my base class, derived classes, and data strcture class. 
//template functions have been moved into the tpp file and the other functions have been put into cpp files


void menu();
//Base Class
//
class pet
{
	public:
		pet(string typeinput): type(typeinput){}
		~pet(){
			if(name){
				delete [] name;
			}
		}
		//Copy Constructor
		pet(const pet & copy){
			name = new char[strlen(copy.name) +1];
			strcpy(name, copy.name);
			age = copy.age;
			type = copy.type;
		}
		//Assignment Operator
		pet & operator=(const pet & copy){
			if(this != &copy){
				delete [] name;

				name = new char[strlen(copy.name) + 1];
				strcpy(name, copy.name);
				age = copy.age;
			}
			return *this;
		}
		//Getters
		string getname(){
			return name;
		}
		int getage(){
			return age;
		}

		bool display();
		//Output Operator <<
		friend ostream& operator<<(ostream & output , const pet & data);

		//Input Operator >>
		friend istream& operator>>(istream & input , pet & data);				

		// Relational Operators, used to create a sorted insert
		// <= Operator
		friend bool operator<=(const pet & leftdata, const pet & rightdata){
			return leftdata.age <= rightdata.age;
		}
		// == Operator, Go on a walk
		friend bool operator==(const pet & leftdata, int minutes){
			cout <<"You walked " << leftdata.name << " for " << minutes << " minutes " << endl;
			return true;
		}

		// Compound Operator +=, feed pets treats
		friend bool operator+=(const pet & leftdata, int treat){
			cout <<"\nYou fed " << leftdata.name << " " << treat << " treats ";
			return true;
		}





	protected:
		string type;
		char * name;
		int age;
};

//Derived Class 1
class workingPet: public pet
{
	public:
		workingPet():pet("Working Pet"){}
		~workingPet(){}
		//Input Operator >>
		friend istream& operator>>(istream & input ,  workingPet &data);

		//Output Operator <<
		friend ostream& operator<<(ostream & output ,  workingPet &data);

		//Relational Operator <, comaparing strength
		friend bool operator<(const workingPet & leftdata, const workingPet & rightdata){
			return leftdata.strength < rightdata.strength;
		}
		//Relational Operator >=, equal strength comparrison
		friend bool operator>=(const workingPet & leftdata, const workingPet & rightdata){
			return leftdata.strength == rightdata.strength;
		}


	private:
		int strength;
		int weight;

};

//Derived Class 2
class competitivePet:public pet
{
	public:
		competitivePet():pet("Competitive Pet"){}
		~competitivePet(){
			if(endurance){
				delete [] endurance;
			}
		}
		//Copy Constructor
		competitivePet(const competitivePet & copy):pet(copy){
			endurance=  new char[strlen(copy.endurance)+1];
			strcpy(endurance, copy.endurance);
			speed = copy.speed;
			type = copy.type;
		}

		//Assignment Operator
		competitivePet & operator=(const competitivePet & copy){
			if(this != &copy){
				pet::operator=(copy);

				endurance=  new char[strlen(copy.endurance)+1];
				strcpy(endurance, copy.endurance);
				speed = copy.speed;
				type = copy.type;
				
			}
			return *this;
		}

		//Input Operator >>
		friend istream& operator>>(istream & input, competitivePet & data);

		//Output Operator <<
		friend ostream& operator<<(ostream & output ,  competitivePet & data);

		//Relational Operator > Speed Comparrison
		friend int operator>(const competitivePet & pet, const competitivePet & pet2){
			if(pet.speed > pet2.speed){
				return 0;
			}
			else if(pet.speed < pet2.speed){
				return 1;
			}
			return -1;
		}

	private:
		char * endurance;
		int speed;
};

//Derived Class 3
class breedingPet: public pet
{
	public:
		breedingPet():pet("Breeding Pet"){}
		~breedingPet(){
			if(breed){
				delete [] breed;
			}
		}
		//Copy Constructor
		breedingPet(const breedingPet & copy): pet(copy){
			breed = new char[strlen(copy.breed) +1];
			strcpy(breed, copy.breed);
			furtype = copy.furtype;
			temperament = copy.temperament;
		}

		//Assignment Operator
		breedingPet & operator=(const breedingPet & copy){
			if(this != &copy){
				pet::operator=(copy);
				breed = new char[strlen(copy.breed) +1];
				strcpy(breed, copy.breed);

				furtype = copy.furtype;
				temperament = copy.temperament;
			}
			return *this;
		}
		//Getters
		string gettemperament(){
			return temperament;
		}

		//Input Operator >>
		friend istream& operator>>(istream & output ,  breedingPet &data);
		//Output Operator <<
		friend ostream& operator<<(ostream & output ,  breedingPet &data);

		//Equality Operator !=, this will determine which pets are compatible
		friend bool operator!=(const breedingPet & leftpet, const breedingPet & rightpet)
		{
			if(leftpet.temperament== "Aggressive" || rightpet.temperament== "Aggressive"){
				cout <<"\nThese two wont get along very well, theres too much tension" << endl;
				return true;
			}
			else if(leftpet.temperament== "Shy" || rightpet.temperament== "Shy"){
				cout <<"\nThis might take some time, but its possible" << endl;
				return true;
			}
			cout <<"\nThis is a good match " << endl;
			return true;
		}

	private:
		char * breed;
		string furtype;
		string temperament;


};

//STL List 
class list
{
	public:
		list() {}
		~list() {
			petlist.clear();
		}
		// Binary Arithmetic + Operator, adds pet into STL list
		friend bool operator+( list & obj, const pet & data){
			obj.petlist.push_back(data);
			return true;
		}
		bool display(){
			if(petlist.empty()){
				cout <<"\nNo pets have been added in any list " << endl;
				return false;
			}
			cout <<"\nList of all pets" << endl;
			return display(0);
		}
		bool display(unsigned int i){
			if(i == petlist.size()){
				return true;
			}
			cout << petlist[i] << endl;


			return display(++i);
		}

	private:
		vector<pet> petlist;
};

//Template Node Class
template <typename T>
class Node
{
	public:
		Node(const T & newdata): data(newdata), next(nullptr), previous(nullptr){}
		~Node(){

		}

		//Getters
		T & getdata(){
			return data;
		}
		Node<T> *& getnext(){
			return next;
		}
		Node<T> * getprevious(){
			return previous;
		}

		//Setters
		bool setnext( Node<T> *data){
			next = data;
			return true;
		}
		bool setprevious( Node<T> * data){
			previous = data;
			return true;
		}

	private:
		T data;
		Node<T> * next;
		Node<T> * previous;

};

//Template DLL Class
//
template <typename T>
class DLL
{
	public:
		DLL(): head(nullptr), tail(nullptr){}
		~DLL(){
			head = tail = nullptr;
		}


		bool insertpet(const T & newpet); //Insertion Wrapper
		bool insertpet(Node<T> *& current,  Node<T> *& current2); //Sorted Recursive Insert
			
		//Removal Functions
		bool removepet();// Remove One Wrapper Function
		bool removepet(Node<T> *& current, string name, int age);//Remove One Recursive
   
		bool removeall();//Remove All Wrapper
		

		bool removeall(Node<T> *& current);// Remove All Recursive Function
		
		bool removenode(Node<T> *& current); // Node Removal Function
			

		//Display Functions
		bool display();//Display Wrapper
			
		bool display(Node<T> *& current); //Display Recursive Function
			
		bool displaynames(); //Display Wrapper
		
		bool displaynames(Node<T> *& current); //Display Recursive Function
		
		//Retrieve Functions
		Node<T> * retrieve();//Retrieve Wrapper Function
		
		Node<T> * retrieve(Node<T> *& current, string nameinput, int ageinput); //Retrieve Recursive Function
			
		//Interaction Functions
		bool interact();



	private:
		Node<T> * head;
		Node<T> * tail;
};

#include "pets.tpp"
