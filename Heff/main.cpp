#include <iostream>
#include <map>
#include <fstream>
#include <list>
#include <vector>
#include <string>
#include "Tree.h"

using namespace std;

string get_data(string filename)//считывание текста из файла в text
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

map<char, int> get_frequency(string text)//получение частоты символов
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
void encode_output_file(string out_name, string message, map<char, int> freq)
{
	int alphabet_size = freq.size();
	fstream file;
	file.open(out_name, ios::out);
	file << alphabet_size;
	for (map<char, int>::iterator it = freq.begin(); it != freq.end(); ++it)
	{
		file << it->first << it->second;
	}
	
	for (int i = 0; i < message.size(); i++)
	{
			file << message[i];
	}
	
	
	file.close();
}
string decode_data(string filename)
{
	string text="";
	string message = "";
	ifstream input(filename, ios::in);
	int alphabet_size = 0;
	input >> alphabet_size;
	int i = 0;
	char letter = 0;
	int n = 0;
	map<char, int> freq;
	while (i != alphabet_size) 
	{
		letter=input.get(); 
		input >> n; 
		freq[letter] = n;
		i++;
	}
	for (map<char, int>::iterator it = freq.begin(); it != freq.end(); ++it)
	{
		cout << it->first << " - " << it->second << endl;
	}
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
	
	Tree Huff;
	Huff.Build_Tree(freq);
	message = Huff.get_message(text);
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
	map<char, int> freq;
	string text;
	text = get_data("C:\\Users\\ƒмитрий\\Desktop\\input.txt");
	//cout << text << endl;
	//int original_len = text.size()*8;
	freq = get_frequency(text);
	//Tree Huff;
	//Huff.Build_Tree(freq);
	//map<char, std::vector<bool>> table;
	//table = Huff.get_Table();

	//string encode;
	//encode = encode_text(text, table);

	//encode_output_file("C:\\Users\\ƒмитрий\\Desktop\\output.txt", encode, freq);
	
	//int encode_file_len = encode.size()+freq.size()*8+freq.size()*32+32;
	//int compression = original_len / encode_file_len;
	string decode;
	decode = decode_data("C:\\Users\\ƒмитрий\\Desktop\\output.txt");
	cout << decode << endl;
	//decode_output_file("C:\\Users\\ƒмитрий\\Desktop\\decode.txt",decode);
	return 0;
}