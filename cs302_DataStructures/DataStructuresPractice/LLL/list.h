#include <iostream>

using namespace std;

//List.h file for LLL
//
//
//
//

// List Definitions
struct node{
        int data;
        node * next;
};

class list{
        public: 
                list(){
                        head = NULL;
                }
                ~list(){
                        node * current =head;
                        while(current){
                                node * temp =current;
                                current=current->next;
                                delete temp;
                        }

                }
		list(const list & oldlist);
                //Setup
                void initialize();
                void display();

                //Insertion Functions
                void insertfront(int number);
                void insertback(int number);
                void insertmiddle(int number);
                void insertorder(int number);
		list reorganize();

		//Deletion Functions
		void deletefront();
		void deleteback();
		void deletemiddle(int number);
		void deletenode(node *current, node * previous);
		void deleteduplicates();
		bool checkduplicate(node* check, node* current);
		void deletebefore(int number);
		void deleteafter(int number);

		//Recursion?

        private:
                node * head;
};




