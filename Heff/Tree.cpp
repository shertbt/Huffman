#include "Tree.h"
#include <iostream>
#include <map>
#include <list>
#include <vector>
#include <string>

Tree::Tree()
{
    root = nullptr;
}

std::map <char, std::string> Tree::Build_Table(Node* root)
{
    std::map<char, std::string> table;
    std::string code;
    if (root->left != NULL) {
        code += '0';
        Build_Table(root->left);
    }
    if (root->right != NULL) {
        code += '1';
        Build_Table(root->right);
    }
    if (root->left == NULL && root->right == NULL) {
        table[root->sym] = code;
   
    }
    if (!code.empty())
        code.pop_back();

    return table;
}

void Tree::Build_Tree(std::map<char, int> freq)
{
    std::list<Node*> freq_list;
    std::map<char, int>::iterator i;
    for (i = freq.begin(); i != freq.end(); i++)
    {
        Node* p = new Node();
        p->sym = i->first;
        p->freq = i->second;
        freq_list.push_back(p);
    }

    while (freq_list.size() != 1)
    {
        freq_list.sort(Node::Compare());
        Node* SonL = freq_list.front();
        freq_list.pop_front();
        Node* SonR = freq_list.front();
        freq_list.pop_front();
        Node* parent = new Node(SonL, SonR);
        freq_list.push_back(parent);
    }
   root = freq_list.front();
}

std::map <char, std::string> Tree::get_Table()
{
    return(Build_Table(root));
}