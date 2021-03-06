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
Tree::~Tree()
{
    delete root;
}
void Tree::Build_Table(Node* root,std::vector<bool> code,std::map<char, std::vector<bool>>&table)
{
    
    if (root->left != NULL) {
        code.push_back(0);
        Build_Table(root->left, code,table);
        code.pop_back();
        code.push_back(1);
        Build_Table(root->right,code,table);
    }
    else {
        table[root->sym] = code;
        
}
    
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

std::map <char, std::vector<bool>> Tree::get_Table()
{
    std::map<char, std::vector<bool>> table;
    std::vector<bool> code;
    Build_Table(root, code, table);
    return table;
}

std::string Tree::get_message(std::string text,int dif)
{
    Node* p = root;
    std::string message = "";
    int count = 0;
    char symbol = 0;
    char byte = 0;
    for (int i=0;i<text.size()-1;i++)
    {
        byte = text[i];
        while (count != 8)
        {
            bool b = byte & (1 << (7 - count));
            if (b==1) p = p->right;
            else p = p->left;
            if (p->left == NULL && p->right == NULL)
            {
                symbol = p->sym;
                message += symbol;
                p = root; 
              
            }
            count++;
        }  
        count = 0;
    }
    count = 0;
    int j = text.size()-1;
    byte = text[j];
     while (count != (8 - dif))
    {
        bool b = byte & (1 << (7 - count));
        if (b == 1) p = p->right;
        else p = p->left;
        if (p->left == NULL && p->right == NULL)
        {
            symbol = p->sym;
            message += symbol;
            p = root;

        }
        count++;
    }
    return message;
}