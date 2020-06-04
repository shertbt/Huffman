#include "Node.h"
#include <cstddef>
Node::Node()
{
	left = NULL;
	right = NULL;
    sym = 0;
    freq = 0;
}

Node::Node(Node* r, Node* l)
{
	left = l;
	right = r;
	freq = l->freq + r->freq;
}
Node::~Node()
{
    delete (this->left);
    delete (this->right);
}

/*Node& Node::operator=(const Node& object) {
    if (this != &object) {
        delete(this->left);
        delete(this->right);
        this->sym = object.sym;
        this->freq = object.freq;
        if (object.left != nullptr) {
            this->left = new Node(*object.left);
  
        }
        else {
            this->left = nullptr;
        }
        if (object.right != nullptr) {
            this->right = new Node(*object.right);
            
        }
        else {
            this->right = nullptr;
        }
    }
    return *this;
}*/

