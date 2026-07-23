#include "class.h"

//CS302 Karla Fant Program 2, February 15th 2024 Daniel Huynh,
//This file is where i implemented my operators.
//
//Main Menu
void menu(){

	cout <<"(A) add pet | (B) remove pet | (c) display pets | (d) interact with pets | (e) retreive pet | (f) end program" << endl;
}

//Base Class Functions / Operators
//

istream& operator>>(istream & input , pet & data){ //Input Operator
	try{
		//Base Class
		int ageinput= 0;
		string nameinput,typeinput;
		cout <<"\nEnter Name:";
		input >> nameinput;
		input.ignore(100, '\n');

		data.name = new char[strlen(nameinput.c_str())];
		strcpy(data.name, nameinput.c_str());

		do{
		cout <<"\nEnter Age 1-50:";
		input >> ageinput;
		input.ignore(100, '\n');
		if(cin.fail()){
			cout <<"\nEnter a number"<< endl;
			cin.clear();
			cin.ignore(100, '\n');
		}
		}while(ageinput < 1 || ageinput>50);
		data.age = ageinput;

		return input;

	}catch(const exception & e){
		cerr << "exception caught: " << e.what() << endl;
	}
	return input;
}
ostream& operator<<(ostream & output , const pet & data){ //Output Operator
	try{
		//Base Class
		output << "\nName : " << data.name << endl;
		output <<"Age : " << data.age << endl;

		return output;
	}catch(const exception & e){
		cerr << "exception caught: " << e.what() << endl;
	}
	return output;
}

//Derived Class 1: Working Pet Functions / Operators
//

istream& operator>>(istream & input ,  workingPet &data){ //Input Operator
	try{
		//Base Class	
		input >> static_cast<pet &> (data);

		//Derived Class
		int strengthinput=0;
		int weightinput =0;
		do{
		cout <<"\nEnter the amount of lbs your pet can pull 1-100lbs?: " << endl;
		input >>strengthinput;
		input.ignore(100, '\n');
		if(cin.fail()){
			cout <<"\nEnter a number"<< endl;
			cin.clear();
			cin.ignore(100, '\n');
		}
		}while(strengthinput <1 || strengthinput > 100);

		do{
		cout <<"What is the weight of your pet? 1-150lbs: " << endl;
		input >>weightinput;
		input.ignore(100, '\n');
		if(cin.fail()){
			cout <<"\nEnter a number"<< endl;
			cin.clear();
			cin.ignore(100, '\n');
		}
		}while(weightinput < 1 || weightinput > 150);


		data.strength = strengthinput;
		data.weight = weightinput;
		return input;

	}catch(const exception & e){
		cerr << "exception caught: " << e.what() << endl;
	}
	return input;
}

ostream& operator<<(ostream & output,  workingPet &data){ //Output Operator
							  //Base Class
	output << static_cast<pet&> (data);

	//Derived Class
	output <<"Type : " << data.type << endl;
	output  <<"Strength : " << data.strength << " lbs" <<  endl;
	output <<"Weight : " << data.weight << " lbs" << endl;
	return output;
}


//Derived Class 2: Competitive Pet Functions
//

istream& operator>>(istream & input,  competitivePet & data){ //Input Operator
							      //
	try{
		// Base Class 
		input >> static_cast<pet &> (data);
		delete [] data.endurance;

		//Derived Class
		int speedinput;
		string enduranceinput;
		cout <<"\nEnter Endurance:";
		input >> enduranceinput;
		input.ignore(100, '\n');
		data.endurance= new char[strlen(enduranceinput.c_str()) +1];
		strcpy(data.endurance, enduranceinput.c_str());

		do{
		cout <<"\nEnter Your Pets Top Speed 1-100 mph:";
		input>>speedinput;
		input.ignore(100, '\n');
		if(cin.fail()){
			cout <<"\nEnter a number"<< endl;
			cin.clear();
			cin.ignore(100, '\n');
		}
		}while(speedinput <1 || speedinput > 100);

		data.speed = speedinput;
		return input;
	}catch(const exception & e){
		cerr << "exception caught: " << e.what() << endl;
	}
	return input;

}

ostream& operator<<(ostream & output ,  competitivePet & data){ //Output Operator
	try{
		//Base Class
		output << static_cast<pet &> (data);

		//Derived Class
		output <<"Type : " << data.type << endl;
		output <<"Top Speed : " << data.speed << " MPH " << endl;
		output <<"Endurance : " << data.endurance<< endl;

		return output;
	}catch(const exception & e){
		cerr << "exception caught: " << e.what() << endl;
	}
	return output;
}


//Derived Class 3: Breeding Pet Functions
//

istream& operator>>(istream & input ,  breedingPet &data){//Input Operator

	try{
		//Base Class
		input >> static_cast<pet&> (data);

		//Derived Class
		string breedinput;
		char button;

		cout <<"\nWhat is the breed? : ";
		input >> breedinput;
		input.ignore(100, '\n');

		data.breed= new char[strlen(breedinput.c_str()) +1];
		strcpy(data.breed, breedinput.c_str());

		cout <<"\nDescribe the furtype : ";
		input >> data.furtype;
		input.ignore(100, '\n');

		do{
			cout <<"\nWhat is your pets temperament? : (A) Friendly | (B) Shy | (C) Aggressive : ";
			input>>button;
			input.ignore(100, '\n');
			if(toupper(button) =='A'){
				data.temperament = "Friendly";
			}
			if(toupper(button) =='B'){
				data.temperament = "Shy";
			}
			if(toupper(button) =='C'){
				data.temperament = "Aggressive";
			}
		}while(toupper(button) !='A' && toupper(button) != 'B' && toupper(button)!= 'C');

		return input;
	}catch(const exception & e){
		cerr << "exception caught: " << e.what() << endl;
	}
	return input;
}

ostream& operator<<(ostream & output ,  breedingPet & data){ //Output Operator
	try{
		//Base Class 
		output << static_cast<pet&> (data);

		//Derived Class
		output <<"Type : " << data.type << endl;
		output <<"Breed : " << data.breed << endl;
		output <<"Furtype : " << data.furtype << endl;
		output <<"Temperament : " << data.temperament << endl;
		return output;
	}catch(const exception & e){
		cerr << "exception caught: " << e.what() << endl;
	}
	return output;

}
