#pragma once
#include <iostream>
#include <map>
#include <list>
#include <vector>
#include <string>
#include"Node.h"
class Tree
{
	private:
		Node *root;
	public:
		Tree();
		void Build_Table(Node* root , std::vector<bool> code, std::map<char, std::vector<bool>> & table);
		void Build_Tree(std::map<char, int> freq);
		std::map <char, std::vector<bool>> get_Table();
		~Tree();
		std::string get_message(std::string text);
};