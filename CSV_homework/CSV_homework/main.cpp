#include <iostream>
#include <fstream>
using namespace std;

bool csv_vaild(ifstream& myfile, int idx)
{//경로가 이상함, 열 갯수가 부족함, 모든 행이 같은 열을 가지지 않음
	bool validchecker = 0;
	bool after_first_line = false;
	int past_index = 0;

	validchecker = !myfile.is_open();


	if (!validchecker)
	{
		int index = 1;
		bool quote_mode = false;

		int idx_buf = 0;
		char buf[5000] = "";

		myfile.getline(buf, 5000);
		while (!myfile.eof())
		{
			idx_buf = 0;
			if (quote_mode == false)
			{
				index = 1;
			}


			while (buf[idx_buf] != '\0')
			{



				if (quote_mode == false && buf[idx_buf] == ',')
				{
					index++;
				}
				if (buf[idx_buf] == '"')
				{
					quote_mode = !quote_mode;
				}


				idx_buf++;
			}
			if (!quote_mode)
			{
				validchecker = (index < idx);
				if (validchecker) break;
				if (after_first_line)
				{
					validchecker = !(past_index == index);
				}
				if (validchecker) break;


				past_index = index;
				after_first_line = true;
			}
			myfile.getline(buf, 5000);
		}

	}


	return validchecker;
}

void csv_indexoutput(ifstream& myfile,int idx)
{
	cout << "Result :" << endl;

	int index = 1;
	bool quote_mode = false;

	int idx_buf = 0;
	int idx_output = 0;
	char buf[5000]=""; char output[5000]="";

	myfile.getline(buf, 5000);
	while (!myfile.eof())
	{



		idx_buf = 0;
		idx_output = 0;

		if (quote_mode == false)
		{
			index=1;
		}
		

		while (buf[idx_buf] != '\0')
		{
			if (index != idx)
			{


				if (quote_mode == false && buf[idx_buf] == ',')
				{
					index++;
				}
				if (buf[idx_buf] == '"')
				{
					quote_mode = !quote_mode;
				}
			}
			else
			{
				if (quote_mode == false)
				{

					/*if (buf[idx_buf] != ' ' && buf[idx_buf] != '"')
					{
						output[idx_output] = buf[idx_buf];
					}
					if (buf[idx_buf] == '"')
					{
						quote_mode = !quote_mode;
					}*/
					switch (buf[idx_buf])
					{
					case 0x20: break;
					case 0x22: {quote_mode = !quote_mode; }break;
					case 0x2C: {output[idx_output] = '\0'; index++; }break;
					default: {output[idx_output] = buf[idx_buf]; idx_output++; }
					}
				}
				else
				{
					if (buf[idx_buf] != '"')
					{
						output[idx_output] = buf[idx_buf]; idx_output++;
					}
					else
					{
						if (buf[idx_buf + 1] == '"')
						{
							output[idx_output] = buf[idx_buf];
							idx_output++; idx_buf++;
						}
						else
						{
							quote_mode = !quote_mode;
						}
					}
				}
			}
			idx_buf++;
		}


		cout << output;
		if (quote_mode== false)
		{
			cout << "  //";
		}
		cout<< endl;
		myfile.getline(buf, 5000);
	}
	cout << endl;
}


int main(int argc, char* argv[])
{
	bool fail = false;
	//char trajectory[200] = "C:\\Users\\user\\Documents\\카카오톡 받은 파일\\comma.csv";
	
	for (int i = 0; i < argc; i++)
	{
		cout << "argv[" << i << "]="<<argv[i] << endl;
	}


	int idx = argv[2][0] - 0x30;

	int csv_checker = 0;

	while (argv[1][csv_checker] != '\0')
	{
		csv_checker++;
	}

	if (argv[1][csv_checker - 3] != 'c') { fail = true; }
	if (argv[1][csv_checker - 2] != 's') { fail = true; }
	if (argv[1][csv_checker - 1] != 'v') { fail = true; }

	ifstream* myfile=new ifstream(argv[1]);

	if (!fail)
	{
		fail = csv_vaild(*myfile, idx);
	}
	myfile->close();
	myfile = new ifstream(argv[1]);

	if (fail)
	{
		cout << "FAIL, CODE : 1"<<endl;
	}
	else
	{
		cout << "SUCCESS, CODE : 0" << endl;
		csv_indexoutput(*myfile, idx);
	}


	
	return 0;
}