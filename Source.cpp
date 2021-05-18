#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <algorithm>
#include <vector>
using namespace std;


//
// FIFO Rule
//
void fifoRule(int myRef[], int myFrame, int size)
{
	ofstream fout;
	fout.open("output_FIFO.txt");
	queue<int> myQueue;

	for (int i = 0; i < size; i++)
	{
		queue<int> temp = myQueue;
		int flag = 1;
		while (!temp.empty())
		{
			if(temp.front() == myRef[i])
			{
				flag = 0;
			}
			temp.pop();
		}
		if (flag == 1)
		{
			if(myQueue.empty() || myQueue.size() < myFrame)
			{
				myQueue.push(myRef[i]);
			}
			else
			{
				myQueue.pop();
				myQueue.push(myRef[i]);
			}
		}

		cout << endl << myRef[i] << "   :   ";
		fout << myRef[i] << "   :   ";
		
		temp = myQueue;
		if (flag == 0)
		{
			cout << "NO Page fault";
			fout << "NO Page fault";
			fout << endl;
		}
		else
		{
			for(int j = 0; j < myFrame; j++)
			{
				int popped;
				cout << "| ";
				fout << "| ";
				if(!temp.empty())
				{
					popped = temp.front();
					temp.pop();
					cout << popped << " | ";
					fout << popped << " | ";
				}
				else
				{
					cout << "-" << " | ";
					fout << "-" << " | ";
				}
			}
			fout << endl;
		}
			
	}		
	cout << endl;
	fout << endl;
	
	fout.close();
}

//
// Optimal Rule
//

void optimalRule(int myRef[], int myFrame, int size)
{
	ofstream fout;
	fout.open("output_Optimal.txt");
	vector<int> myVector;

	for (int i = 0; i < size; i++)
	{
		vector<int> temp = myVector;
		int flag = 1;
		while (!temp.empty())
		{
			if(temp.back() == myRef[i])
			{
				flag = 0;
			}
			temp.pop_back();
		}
		if (flag == 1)
		{
			if(myVector.empty() || myVector.size() < myFrame)
			{
				myVector.push_back(myRef[i]);
			}
			else
			{
				int index = 0;
				int myFlag = 0;
				for(int j = i + 1; j < size; j++)
				{
					if(index < myFrame)
					{
						if(myVector[index] == myRef[j])
						{
							index++;
						}
					}
					
					if(index >= myFrame)
					{
						myFlag = 1;
					}
				}
				if(myFlag == 0)
				{
					myVector[index] = myRef[i];
				}
				else
				{
					int tempj = i + 1;
					index = 0;
					for(int j = i + 1; j < size; j++)
					{
						if(index < myFrame)
						{
							if(myVector[index] == myRef[j])
							{
								index++;
								if(tempj < j)
								{
									tempj = j;
								}
								j = i + 1;
							}
						}
							
					}
					
					for(int index = 0; index < myFrame; index++)
					{
						if(myVector[index] == myRef[tempj])
						{
							myVector[index] = myRef[i];
						}
					}
				}
			}
		}

		cout << endl << myRef[i] << "   :   ";
		fout << myRef[i] << "   :   ";

		temp = myVector;
		reverse(temp.begin(), temp.end());
		if (flag == 0)
		{
			cout << "NO Page fault";
			fout << "NO Page fault";
			fout << endl;
		}
		else
		{
			for(int j = 0; j < myFrame; j++)
			{
				int popped;
				cout << "| ";
				fout << "| ";

				if(!temp.empty())
				{
					popped = temp.back();
					temp.pop_back();
					cout << popped << " | ";
					fout << popped << " | ";
				}
				else
				{
					cout << "-" << " | ";
					fout << "-" << " | ";
				}
			}
			fout << endl;
		}
			
	}		
	cout << endl;
	fout << endl;

	fout.close();
}



//
// LFU Rule (not available)
//

void lfuRule(int myRef[], int myFrame, int size)
{
	ofstream fout;
	fout.open("output_LFU.txt");

	int myArray[myFrame];
	int countFrequency[myFrame];
	int timeFrequency[myFrame];

	for (int j = 0; j < myFrame; j++)
	{
		myArray[j] = -1;
		countFrequency[j] = 0;
		timeFrequency[j] = 0;
	}

	for (int i = 0; i < size; i++)
	{
		int flag = 1;
		for (int j = 0; j < myFrame; j++)
		{
			if(myRef[i] == myArray[j])
			{
				flag = 0;
				countFrequency[j]++;
				break;
			}
		}

		if (flag == 1)
		{
			int min = 0;
			for(int k = 1; k < myFrame; k++)
			{
				if(countFrequency[k] < countFrequency[min])
				{
					min = k;
				}
				else if(countFrequency[k] == countFrequency[min] && timeFrequency[k] > timeFrequency[min])
				{
					min = k;
				}
			}
			myArray[min] = myRef[i];
			countFrequency[min] = 1;
			timeFrequency[min] = 0;
		}

		cout << endl << myRef[i] << "   :   ";
		fout << myRef[i] << "   :   ";

		if (flag == 0)
		{
			cout << "NO Page fault";
			fout << "NO Page fault";
			fout << endl;
		}
		else
		{
			for(int j = 0; j < myFrame; j++)
			{
				cout << "| ";
				fout << "| ";

				if(myArray[j] != -1)
				{
					timeFrequency[j]++;
					cout << myArray[j] << " | ";
					fout << myArray[j] << " | ";
				}
				else
				{
					cout << "-" << " | ";
					fout << "-" << " | ";
				}
			}
			fout << endl;
		}
			
	}		
	cout << endl;
	fout << endl;

	fout.close();
}

int main()
{
	//
	// Calculating the size of reference string from text file given
	//

	ifstream file;
	string filename = "input.txt";
	file.open(filename);

	int size = 0;	// size of Reference String
	string temp;

	while(!file.eof())
	{
		getline(file, temp);
		if(temp.length() > 0)
		{
			size += 1;
		}		
	}
	
	cout << "Size of reference string is: " << size << endl;
	file.close();

	//
	// Storing all the elements from text file into an integer array (size of array calculated above)
	//

	file.open(filename);

	int myRef[size];	// integer array
	int looper = 0;
	
	while(!file.eof())
	{
		getline(file, temp);
		
		if(temp.length() == 0)
		{}
		else
		{
			myRef[looper] = stoi(temp);
		}
		looper += 1;
	}

	//
	// Getting total frames as input from user
	//

	int myFrame;	// total frames from user
	
	do{
	
		cout << endl << "Please enter how many frames to use (range: 3-6): ";
		cin >> myFrame;	
	
	}while(myFrame < 3 || myFrame > 6);

	int choice = 0;	// choose algorithm to use from user
	
	do{
	
		cout << endl << "--- Please choose which algorithm to use ---";
		cout << endl << "1. FIFO Rule";
		cout << endl << "2. Optimal Rule";
		cout << endl << "3. LFU Rule";
		cout << endl;
		cin >> choice;	
	
	}while(choice < 1 || choice > 3);

	cout << endl << "___Applying Page Replacement Algorithm___" << endl;
	if(choice == 1)
	{
		fifoRule(myRef, myFrame, size);	
	}
	else if(choice == 2)
	{
		optimalRule(myRef, myFrame, size);	
	}
	else
	{
		lfuRule(myRef, myFrame, size);	
	}
	return 0;
}

