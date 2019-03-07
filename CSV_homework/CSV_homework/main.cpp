#include <iostream>
#include <fstream>
using namespace std;

void csv_indexoutput(ifstream& myfile,int idx)
{
	cout << "결과는" << endl;

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
	cout << "입니다" << endl;
}


int main()
{
	
	ifstream* myfile=new ifstream("C:\\Users\\user\\Documents\\카카오톡 받은 파일\\comma.csv");



	csv_indexoutput(*myfile, 2);

	
	return 0;
}