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
string encode_text(string text, map<char, string> table)
{
	string result = "";
	for (char symbol : text)
	{
		result += table[symbol];
	}
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
	string text;
	ifstream input(filename, ios::in);
	int alphabet_size = 0;
	input >> alphabet_size;
	int i = 0;
	char letter = 0;
	int n = 0;
	map<char, int> freq;
	while (i != alphabet_size) 
	{
		letter = input.get(); 
		input >> n; 
		freq[letter] = n;
		i++;
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
	map<char, string> table;
	table = Huff.get_Table();

	for (map<char, string>::iterator it = table.begin(); it != table.end(); ++it)
	{
		int replace_position = text.find(it->second);
		string tmp;
		tmp.push_back((char)it->first);
		text.replace(replace_position, it->second.size(), tmp);
	}


	return text;
}
void decode_output_file(string out_name, string message)
{
	fstream file;
	file.open(out_name, ios::out);
	
	for (int i = 0; i < message.size(); i++)
	{
		file << message[i];
	}


	file.close();
}
int main()
{
	map<char, int> freq;
	string text;
	text = get_data(filename_input);
	freq = get_frequency(text);
	Tree Huff;
	Huff.Build_Tree(freq);
	map<char, string> table;
	table = Huff.get_Table();
	string encode;
	encode = encode_text(text, table);
	string out_name;
	encode_output_file(out_name, encode, freq);
	string decode;
	decode = decode_data(filename);
	decode_output_file(out_name,decode);
	return 0;
}