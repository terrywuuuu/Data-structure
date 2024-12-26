#include <iostream>
#include <string>

using namespace std;

struct Node
{
    char color;
    int value;
    Node *left;
    Node *right;
    Node *parent;

    Node(int val) : value(val), color('r'), left(nullptr), right(nullptr), parent(nullptr) {}
};

Node *root = new Node(0);
int i = 0;

void Rotation(string mode, Node *r)
{
    if (mode == "RR")
    {
        Node *newRoot = r->right;
        r->right = newRoot->left;

        if (newRoot->left != nullptr)
        {
            newRoot->left->parent = r;
        }

        if (r->parent != nullptr)
        {
            newRoot->parent = r->parent;

            if (r == r->parent->left)
            {
                r->parent->left = newRoot;
            }
            else
            {
                r->parent->right = newRoot;
            }
        }
        else
        {
            root = newRoot;
            newRoot->parent = nullptr;
        }

        newRoot->left = r;
        r->parent = newRoot;

        newRoot->color = 'b';
        newRoot->left->color = 'r';
        newRoot->right->color = 'r';
    }
    else if (mode == "RL")
    {
        Node *newRoot = r->right->left;
        r->right->left = newRoot->right;

        if (newRoot->right)
            newRoot->right->parent = r->right;
        newRoot->right = r->right;
        r->right->parent = newRoot;
        r->right = newRoot;

        r->right = newRoot->left;
        if (newRoot->left)
            newRoot->left->parent = r;
        newRoot->left = r;

        newRoot->parent = r->parent;
        r->parent = newRoot;

        if (newRoot->parent == nullptr)
        {
            root = newRoot;
        }
        else if (newRoot->parent->left == r)
        {
            newRoot->parent->left = newRoot;
        }
        else
        {
            newRoot->parent->right = newRoot;
        }

        newRoot->color = 'b';
        newRoot->left->color = 'r';
        newRoot->right->color = 'r';
    }
    else if (mode == "LL")
    {
        Node *newRoot = r->left;
        r->left = newRoot->right;

        if (newRoot->right != nullptr)
        {
            newRoot->right->parent = r;
        }

        if (r->parent != nullptr)
        {
            newRoot->parent = r->parent;

            if (r == r->parent->left)
            {
                r->parent->left = newRoot;
            }
            else
            {
                r->parent->right = newRoot;
            }
        }
        else
        {
            root = newRoot;
            newRoot->parent = nullptr;
        }

        newRoot->right = r;
        r->parent = newRoot;

        newRoot->color = 'b';
        newRoot->left->color = 'r';
        newRoot->right->color = 'r';
    }
    else if (mode == "LR")
    {
        Node *newRoot = r->left->right;
        r->left->right = newRoot->left;

        if (newRoot->left)
            newRoot->left->parent = r->left;
        newRoot->left = r->left;
        r->left->parent = newRoot;
        r->left = newRoot;

        r->left = newRoot->right;
        if (newRoot->right)
            newRoot->right->parent = r;
        newRoot->right = r;

        newRoot->parent = r->parent;
        r->parent = newRoot;

        if (newRoot->parent == nullptr)
        {
            root = newRoot;
        }
        else if (newRoot->parent->left == r)
        {
            newRoot->parent->left = newRoot;
        }
        else
        {
            newRoot->parent->right = newRoot;
        }

        newRoot->color = 'b';
        newRoot->left->color = 'r';
        newRoot->right->color = 'r';
    }
}

void doRotate(Node *node, Node *target)
{
    while (node != nullptr)
    {
        if (node->right != nullptr && node->right->color == 'r')
        {
            if (node->right->right != nullptr && node->right->right->color == 'r')
            {
                Rotation("RR", node);
                break;
            }
            else if (node->right->left != nullptr && node->right->left->color == 'r')
            {
                Rotation("RL", node);
                break;
            }
        }

        if (node->left != nullptr && node->left->color == 'r')
        {
            if (node->left->right != nullptr && node->left->right->color == 'r')
            {
                Rotation("LR", node);
                break;
            }
            else if (node->left->left != nullptr && node->left->left->color == 'r')
            {
                Rotation("LL", node);
                break;
            }
        }

        if (target->value >= node->value)
        {
            node = node->right;
        }
        else
        {
            node = node->left;
        }
    }
}

void changeColor(Node *cur, Node *node)
{
    while (cur != nullptr)
    {
        if (cur->left != nullptr && cur->right != nullptr && cur->left->color == 'r' && cur->right->color == 'r')
        {
            cur->color = 'r';
            cur->left->color = 'b';
            cur->right->color = 'b';
            return changeColor(root, node);
        }

        if (node->value >= cur->value)
        {
            cur = cur->right;
        }
        else
        {
            cur = cur->left;
        }
    }
}

void Insert(Node *cur, Node *node)
{
    Node *current = cur;
    Node *previous = nullptr;

    changeColor(current, node);

    current = root;
    doRotate(current, node);

    current = root;
    while (current != nullptr)
    {
        previous = current;

        if (node->value >= current->value)
        {
            current = current->right;

            if (current == nullptr)
            {
                previous->right = node;
                node->parent = previous;
            }
        }
        else
        {
            current = current->left;

            if (current == nullptr)
            {
                previous->left = node;
                node->parent = previous;
            }
        }
    }

    current = root;
    doRotate(current, node);

    root->color = 'b';
}

void Print(Node *node)
{
    i++;

    if (node->left == nullptr)
    {
        cout << "()";
    }
    else
    {
        cout << "(";
        Print(node->left);
    }

    cout << "<-" << node->value << "_" << node->color << "->";

    if (node->right == nullptr)
    {
        cout << "()";
    }
    else
    {
        cout << "(";
        Print(node->right);
    }

    i--;

    if (i != 0)
    {
        cout << ")";
    }
}

int main()
{
    string command;
    int val = 0;
    string input;

    while (cin >> command)
    {
        if (command == "Insert")
        {
            cin >> input;

            if (input.length() == 1)
            {
                char in = input[0];

                if (in - '0' <= 9)
                {
                    val = in - '0';
                }
                else
                {
                    val = static_cast<int>(in);
                }
            }
            else
            {
                val = stoi(input);
            }

            root->value = val;
            root->color = 'b';
            break;
        }
    }

    while (cin >> command)
    {
        if (command == "Print")
        {
            Print(root);
            cout << "\n";
        }
        else if (command == "Insert")
        {
            cin >> input;

            if (input.length() == 1)
            {
                char in = input[0];

                if (in - '0' <= 9)
                {
                    val = in - '0';
                }
                else
                {
                    val = static_cast<int>(in);
                }
            }
            else
            {
                val = stoi(input);
            }

            Node *node = new Node(val);
            Insert(root, node);
        }
    }
}