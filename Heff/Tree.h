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
		std::map <char, std::string> Build_Table(Node *root);
		void Build_Tree(std::map<char, int> freq);
		std::map <char, std::string> get_Table();
		~Tree();
};