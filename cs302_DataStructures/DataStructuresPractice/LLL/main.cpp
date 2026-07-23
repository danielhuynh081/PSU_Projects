#include "list.h"

// Daniel Huynh, August 19th, 2025. This File is to refresh myself on workig with Linear Linked Lists in CPP
//
// I will be refreshing myself by solving problems that range from beginner to intermediate
//
// 1. List Creation
// 2. Insertion
//    - Insert Front - DONE
//    - Insert Back - DONE
//    - Insert Middle - DONE 
//    - Insert in order - DONE
//    - Reverse list - Maybe later 
//    - Order list from lowest to highest - DONE

// 3. Deletion
//    - Delete Front - DONE
//    - Delete Back - DONE
//    - Delete Duplicates
//    - Delete Before/After
//    - Delete Middle - DONE
//


// Main
int main(){

	list mylist;
//	mylist.initialize();
	mylist.insertfront(1);
	mylist.insertfront(1);
	mylist.insertfront(2);
	mylist.insertfront(3);
	mylist.insertfront(2);
	mylist.insertfront(5);
	mylist.insertfront(5);
	mylist.insertfront(5);
	mylist.insertfront(5);
//	mylist.insertback(250);
//	mylist.insertmiddle(67);
//	mylist.insertorder(3);
	mylist.display();
	mylist.deleteduplicates();
	mylist.display();
	

	/*
	mylist.deletefront();
	cout <<"\nNew List Below:"<<endl;
	mylist.display();
	mylist.deleteback();
	cout <<"\nNew List Below:"<<endl;
	mylist.display();
	mylist.deletemiddle(4);
	cout <<"\nNew List Below:"<<endl;
	mylist.display();
	*/

//	list newlist= mylist.reorganize();
//	newlist.display();

//	list listcopy = mylist;
//	cout << "\nLIST COPY:\n" << endl;
//	listcopy.display();

	return 0;
}
