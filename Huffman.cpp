#include <iostream>
#include <string>

using namespace std;

struct Node
{
    int value;
    Node *left;
    Node *right;
    char symbol;

    Node(int val, char sym) : value(val), left(nullptr), right(nullptr), symbol(sym) {};
};

Node *root;

void Input(Node *tree[100], string &code, int &index)
{
    string input;
    char symbol[100] = {};
    getline(cin, input);

    for (int i = 0; i < input.length(); i++)
    {
        if (i % 2 == 0)
        {
            symbol[index] = input[i];
            index++;
        }
    }

    for (int i = 0; i < index; i++)
    {
        int In = 0;
        cin >> In;
        Node *node = new Node(In, symbol[i]);
        tree[i] = node;
    }

    cin >> code;
}

void huffTree(Node *tree[100], int index)
{
    int end = index - 1;

    while (index != 1)
    {
        int min = 1000;
        int i1 = 0, i2 = 0;

        for (int i = 0; i < end + 1; i++)
        {
            for (int j = i + 1; j < end + 1; j++)
            {
                if (tree[i] != nullptr && tree[j] != nullptr)
                {
                    if (tree[i]->value + tree[j]->value < min)
                    {
                        min = tree[i]->value + tree[j]->value;
                        i1 = i;
                        i2 = j;
                    }
                }
            }
        }

        Node *newNode = new Node(min, '0');
        newNode->right = tree[i2];
        newNode->left = tree[i1];

        tree[i2] = newNode;
        tree[i1] = nullptr;
        index--;
    }

    root = tree[end];
}

void Decode(string code)
{
    Node *target = root;

    for (int i = 0; i < code.length(); i++)
    {
        if (code[i] == '0')
        {
            target = target->left;
        }
        else
        {
            target = target->right;
        }

        if (target->right == nullptr || target->left == nullptr)
        {
            cout << target->symbol;
            target = root;
        }
    }
}

int main()
{
    int index = 0;
    string code;
    Node *tree[100] = {nullptr};

    Input(tree, code, index);

    huffTree(tree, index);

    Decode(code);
}