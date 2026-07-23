#include "class.h"

// Daniel Huynh, CS302 Data Structures, Karla Fant, January 10th, 2024
// This program allows users to compete in snow sport races using linked lists, circular linked lists, and vectors.
// This file contains the main function and menu used to navigate the program.

int main()
{
	//Variable declaration
	string name ="";
	char start, select ='\0';
	vector<Node> recentplayers;
	int age =0;

	//Races
	SnowboardingRace SnowRace; //CLL
	SnowmobileRace MobileRace; // LLL
	SkiRace Skiracing; // LLL
	playerlist recentlist; //vector

	//Start menu1
	do
	{
		cout <<"welcome to the snow racing program, press x to start";
		cin >>start;
		cin.ignore(100, '\n');
		if(toupper(start) != 'X'){
			cout <<"\nWrong character entered, try again\n";
		}

	}while(toupper(start) != 'X');
	//Start menu2, this navigates our program
	while(toupper(start) =='X')
	{
		menu();
		cin >> select;
		cin.ignore(100, '\n');
		if(toupper(select) =='A') //Snowboarding
		{
			//register into recent players
			cout <<"what is your name?" << endl;
			cin>>name;
			cin.ignore(100, '\n');
			cout <<"what is your age?" << endl;
			cin >>age;
			cin.ignore(100, '\n');

			cout <<"snowboarding selected";

			snowboarding obj(name, age,1);
			recentlist.addplayer(obj);
			SnowRace.addplayer(obj);
			//add NPC racers
			SnowRace.addplayer(snowboarding("ryan", 12,2));
			SnowRace.addplayer(snowboarding("emma", 12,3));
			SnowRace.addplayer(snowboarding("cody", 12,4));
			SnowRace.addplayer(snowboarding("jacob", 12,5));

			SnowRace.racestart();

		}
		if(toupper(select) =='B') //Snowmobiling
		{
			cout <<"what is your name?" << endl;
			cin>>name;
			cin.ignore(100, '\n');
			cout <<"what is your age?" << endl;
			cin >>age;
			cin.ignore(100, '\n');

			cout <<"snowmobiling selected";
			snowmobiling obj(name, age,1);
			MobileRace.addplayer(obj);
			MobileRace.setmobile();
			//add NPC racers
			MobileRace.addplayer(snowmobiling("ryan", 12,2));
			MobileRace.addplayer(snowmobiling("emma", 12,3));
			MobileRace.addplayer(snowmobiling("cody", 12,4));
			MobileRace.addplayer(snowmobiling("jacob", 12,5));
			MobileRace.racestart();


		}
		if(toupper(select) =='C') //Skiing
		{
			cout <<"what is your name?" << endl;
			cin>>name;
			cin.ignore(100, '\n');
			cout <<"what is your age?" << endl;
			cin >>age;
			cin.ignore(100, '\n');

			cout <<"skiing selected";
			//add NPC racers
			skiing obj(name, age,1);
			Skiracing.addplayer(obj);
			//add NPC racers
			Skiracing.addplayer(skiing("ryan", 12,2));
			Skiracing.addplayer(skiing("emma", 12,3));
			Skiracing.addplayer(skiing("cody", 12,4));
			Skiracing.addplayer(skiing("jacob", 12,5));
			Skiracing.racestart();




		}	
		if(toupper(select) =='D'){ //vector displaying
			recentlist.displaylist();


		}
		if(toupper(select) =='E'){
			start = 'z';
			cout <<"\nQuitting application\n";
		}
	}

	return 0;
}
