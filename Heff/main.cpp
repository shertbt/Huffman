#include <iostream>
#include <map>
#include <iomanip>
#include <fstream>
#include <list>
#include <vector>
#include <string>
#include "Tree.h"
#include <windows.h>

using namespace std;

string get_data(string filename)
{
	string text;
	ifstream input(filename, ios::in);
	while (!input.eof())
	{
		string temp;
		getline(input, temp);
		if (!input.eof())
		{
			temp += '\n';
		}
		text += temp;
	}

	return text;
}

map<char, int> get_frequency(string text)
{
	map<char, int> freq;
	for (char b : text)
	{
		freq[b]++;
	}
	return freq;
}
string encode_text(string text, map<char, std::vector<bool>> table)
{
	string result = "";
	char s = 0;
	int count = 0;
	for (char symbol : text)
	{
		vector<bool> code = table[symbol];
		for (int n = 0; n < code.size(); n++)
		{
			s = s | code[n] << (7 - count);
			count++;
			if (count == 8)
			{
				count = 0;
				result += s;
				s = 0;
			}
		}
	}
	if(count!=0) result += s;
	return result;
}
void writeHeader(string out_name, map<char, int> freq, int dif)
{
	fstream tab(out_name, ios::binary | ios::app);
	int alphabet_size = freq.size();
	tab.write((char*)&dif, sizeof(char));
	tab.write((char*)&alphabet_size, sizeof(int));
	for (map<char, int>::iterator it = freq.begin(); it != freq.end(); ++it)
	{
		tab.write((char*)&it->first,sizeof(char));
		tab.write((char*)&it->second,sizeof(int));
	}
	tab.close();
}
void encode_output_file(string out_name, string message, map<char, int> freq,int dif)
{
	writeHeader(out_name, freq, dif);
	fstream file;
	file.open(out_name,ios::binary | ios::app);
	
	for (int i = 0; i < message.size(); i++)
	{
			file << message[i];
	}
	
	
	file.close();
}
string readHeader(string filename,map<char, int>& freq,int &dif)
{
	string text = "";
	fstream tab(filename, ios::binary | ios::in);
	int alphabet_size = 0;
	int dif_bit = 0;
	tab.read((char*)&dif_bit, sizeof(char));
	dif = dif_bit;
	tab.read((char*)&alphabet_size, sizeof(int));
	int i = 0;
	char letter;
	int n = 0;
	while (i != alphabet_size)
	{
		tab.read((char*)&letter, sizeof(char));
		tab.read((char*)&n, sizeof(int));
		freq[letter] = n;
		i++;
	}
	
	while (!tab.eof())
	{
		string temp;
		getline(tab, temp);
		if (!tab.eof())
		{
			temp += '\n';
		}
		text += temp;
	}
	return text;
}
string decode_data(string filename)
{
	string text="";
	string message = "";
	map<char, int> freq;
	int dif = 0;
	text=readHeader(filename, freq, dif);
	/*for (map<char, int>::iterator it = freq.begin(); it != freq.end(); ++it)
	{
		cout << it->first << " - " << it->second << endl;
	}*/
	//cout << text<<endl;
	//cout << dif << endl;
	Tree Huff;
	Huff.Build_Tree(freq);
	message = Huff.get_message(text,dif);
	return message;
}

void decode_output_file(string out_name, string message)
{
	ofstream file(out_name, ios::out);
	
	for (int i = 0; i < message.size(); i++)
	{
		file << message[i];
	}

}

int main()
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	int arg;
	cout << "(1)-encode; (0)-decode" << endl;
	cin >> arg;
	switch (arg) {
		case 1:
		{
			string filename;
			cout << "Enter the file name" << endl;
			cin>>filename;
			string filename_out;
			cout << "Save in...." << endl;
			cin>>filename_out;
			string text;
			text = get_data(filename);
			map<char, int> freq;
			freq = get_frequency(text);
			Tree Huff;
			Huff.Build_Tree(freq);
			map<char, std::vector<bool>> table;
			table = Huff.get_Table();
			string encode;
			encode = encode_text(text, table);
			int len = 0;
			for (map<char, int>::iterator it = freq.begin(); it != freq.end(); ++it)
			{
				std::vector<bool> code = table[it->first];
				int f = it->second;
				len += (f * code.size());
			}
			int en_len = encode.length() * 8;
			int difference = en_len - len;
			encode_output_file(filename_out, encode, freq, difference);
			float coef = (float)text.length() / (encode.length() + 5 + freq.size() * 5);
			cout << "Compression ratio:" << fixed << setprecision(2) << coef << endl;
		}
			break;
		case 0:
		{
			string filename;
			cout << "Enter the file name" << endl;
			cin>>filename;
			string filename_out;
			cout << "Save in...." << endl;
			cin>>filename_out;
			string decode;
			decode = decode_data(filename);
			decode_output_file(filename_out, decode);
		}	
			break;
		default:
			cout << "Wrong input" << endl;
			break;
	}

	return 0;
}