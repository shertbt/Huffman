#pragma once
class Node
{
private:

	char sym;
	int freq;
	Node* left, * right;
	friend class Tree;

public:
	Node();
	~Node();
	Node(Node* l, Node*r );
	//Node& operator=(const Node& object);
	struct Compare {
		bool operator() (const Node* l, const Node* r) const 
		{
			return (l->freq < r->freq);
		}
	};

};