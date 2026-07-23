#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
void stdsort(vector<int> data);
void selectionsort(int array[10]);
void bubblesort(int array[10]); 
char button;
vector<int> data = {4,10,112,32,54,2,7,29,4};
int numbers[10]= {4,10,112,32,54,2,7,29,4};
bool check(int array[10], vector<int>&  data);
cout <<"press x to view selection sort: ";
cin >> button;
cin.ignore(100, '\n');

if(toupper(button) =='X'){

	selectionsort(numbers);

}

cout <<"press x to view bubble sort: ";
cin>>button;
cin.ignore(100, '\n');
if(toupper(button) =='X'){

	bubblesort(numbers);
}

cout<<"press x to check std sort ";
cin>>button;
cin.ignore(100, '\n');
if(toupper(button) =='X'){

	bubblesort(numbers);
}
bool match = check(numbers, data);
if(match)
{
	cout <<"its a match with std sort! " << endl;
}
else{
	cout <<"Not a match! " << endl;
}


return 0;
}

bool check(int  array[10], vector<int> & data)
{
	for(int i = 0; i < 10; ++i)
	{
		if(array[i] != data[i])
		{
			return false;
		}
	}
	return true;
}

void stdsort(vector<int> data)
{
	sort(data.begin(), data.end());
	for(int i : data){
		cout << " " << i;
	}
	cout <<endl;


}

void bubblesort(int array[10])
{
	for(int i =0; i < 10; ++i)
	{
		for(int i = 0; i < 10; ++i){

		if(array[i] > array[i+1])
		{
			swap(array[i], array[i+1]);
		}
		}
	}
	for(int i =0; i < 10; ++i)
	{
		cout <<" " << array[i];
	}
	cout << endl;
}

void selectionsort(int array[10])
{
	for(int i =0; i < 10; ++i)
	{
		int min = i;
		for(int k = i + 1; k < 10; ++k)
		{
			if(array[k] < array[min]){
				min = k;
			}

		}
		if(min != i){
			int holder = array[i];
			array[i] = array[min];
			array[min] = holder;
		}
	}
	for(int i =0; i < 10; ++i)
	{
		cout <<" " << array[i];
	}
	cout <<endl;


}

