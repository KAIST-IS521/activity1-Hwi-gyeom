#include <iostream>
#include <fstream>
using namespace std;

void csv_test(ifstream myfile)
{
	char tt=myfile.get();
	cout << tt << endl;
}


int main()
{
	ifstream myfile("ÀÌ¸§µé.csv");

	char buffer[500] = "";
	myfile.getline(buffer, 500,',');
	cout <<buffer<<endl;


	return 0;
}