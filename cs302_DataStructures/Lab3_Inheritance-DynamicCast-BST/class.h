#include <iostream>
#include <cstring>
#include <cctype>
#include <vector>
#include <string>
#include <memory>

using namespace std;


//Base Class
class game
{
	public:
		game(){}
		game(string nameinput,  int ageinput, int playerinput): name(nameinput), age(ageinput), players(playerinput){}

		virtual ~game(){}
		virtual void display() = 0;
		virtual void setgame() = 0;
		virtual void checkvalid(int age, int players, char op1, char op2) =0;
		string getname(){
			return name;
		}
		int getage(){
			return age;
		}
		int getplayers(){
			return players;
		}
	protected:
		string name;
		int age;
		int players;


};

//Derived Class 1 Sport
class sport: public game
{
	public:
		sport(){}
		sport(string nameinput, int ageinput, int playerinput, string locationinput, string difficultyinput): game(nameinput, ageinput, playerinput), location(locationinput), difficulty(difficultyinput){}
		~sport(){}

		void display();
		void setgame();
		bool checkvalid(int age, int players, char op1, char op2);

		//Getterrs
		string getlocation(){
			return location;
		}
		string getdifficulty(){
			return difficulty;
		}



	private:
		string location;
		string difficulty;



};

//Derived Class 2 Gambling
class gambling: public game
{
	public:
		gambling(){}
		gambling(string nameinput, int ageinput, int playerinput, string materialinput, string riskinput): game(nameinput, ageinput, playerinput), materials(materialinput), risk(riskinput){}
		~gambling(){}

		void display();
		void setgame();
		bool checkvalid(int age, int players, char op1, char op2);

		//Getters
		string getmaterials(){
			return materials;
		}
		string getrisk(){
			return risk;
		}

	private:
		string materials;
		string risk;

};


//Derived Class 3 Videogame
class videogame: public game
{
	public:
		videogame(){}
		videogame(string nameinput, int ageinput, int playerinput, string genreinput, string hourinput): game(nameinput, ageinput, playerinput), genre(genreinput), hours(hourinput){}
		~videogame(){}

		void display();
		void setgame();
		bool checkvalid(int age, int players, char op1, char op2);

		//Getters
		string getgenre(){
			return genre;
		}
		string gethours(){
			return hours;
		}

	private:
		string genre;
		string hours;

};

class Node
{
	public:
		Node(game * insert):data(insert), left(nullptr), right(nullptr){}
		~Node(){}
		bool display(){
			return data->display();
		}

		//Getters
		unique_ptr<game> & getdata(){
			return data;

		}
		unique_ptr<Node> & getleft(){
			return left;
		}
		unique_ptr<Node> & getright(){
			return right;
		}

		//Setters
		bool setleft(unique_ptr<Node> current){
			left = move(current);
			return true;
		}
		bool setright(unique_ptr<Node> current){
			right = move(current);
			return true;
		}
		bool setdata(unique_ptr<game> current){
			data = move(current);
			return true;
		}
	private:
		unique_ptr<game> data;
		unique_ptr<Node> left;
		unique_ptr<Node> right;
		string color;
};

class tree
{
	public:
		tree(): root(nullptr){}
		~tree(){}

		//Search Game
		bool searchgame();

		//STL List Functions
		bool adduser();
		bool displayusers();
		bool displayusers(long unsigned int i);
			
		//Insertion Functions
		bool addnode();
		bool addnode( game * newgame);
		bool addnode(unique_ptr<Node> & current, game * newgame);

		//Display Functions
		bool displayhelper();
		bool displayall();
		bool displayall(unique_ptr<Node> & current, bool detail);

		bool displaysearch(unique_ptr<Node> & current, char type, int age, int players, char op1, char op2);

		bool displaytype();
		bool displaytype(unique_ptr<Node> & current, char typepick, bool detail);

		//Removal
		bool removeone();
		bool removeone(string nameinput, unique_ptr<Node> & current);
		//bool removeone(char type, Node * parent, Node * current, string gamename);
		bool removeone(char type, Node * parent, Node * current, string gamename);


		bool removeall();
		bool removeall(Node * current);

		//check type
		bool checktype(Node * current, char type);
		bool checktype(Node * current, char type, int age, int players, char op1, char op2);

	private:
		unique_ptr<Node> root;
		vector<string> users;
};

