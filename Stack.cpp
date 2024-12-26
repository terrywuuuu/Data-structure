#include <iostream>
#include <string>

using namespace std;

class stack
{
private:
    int top;
    pair<string, int> arr[100] = {};

public:
    stack() : top(-1) {};

    void push(pair<string, int> data)
    {
        top++;

        if (top < 100)
        {
            arr[top] = data;
        }
        else
        {
            top--;
        }
    }

    void print()
    {
        int packNum = top / 3 + 1;
        int firstPack = top - top / 3 * 3;
        int start = 0;

        if (firstPack == 0)
        {
            cout << "Backpack: " << packNum << endl;
            packNum--;
            cout << arr[top].first << ": " << arr[top].second << endl;
            cout<<"\n";
            start = top - 1;
        }
        else if (firstPack == 1)
        {
            int max = arr[top].second;
            start = top - 2;

            cout << "Backpack: " << packNum << endl;
            packNum--;

            if (arr[top - 1].second > max)
            {
                cout << arr[top - 1].first << ": " << arr[top - 1].second << endl;
                cout << arr[top].first << ": " << arr[top].second << endl;
            }
            else
            {
                cout << arr[top].first << ": " << arr[top].second << endl;
                cout << arr[top - 1].first << ": " << arr[top - 1].second << endl;
            }
            cout<<"\n";
        }
        else
        {
            start = top;
        }

        for (int i = start; i >= 0; i -= 3)
        {
            cout << "Backpack: " << packNum << endl;
            packNum--;

            int max = arr[i].second;

            if (arr[i - 1].second > max && arr[i - 2].second > max)
            {
                if (arr[i - 2].second > arr[i - 1].second)
                {
                    cout << arr[i - 2].first << ": " << arr[i - 2].second << endl;
                    cout << arr[i - 1].first << ": " << arr[i - 1].second << endl;
                    cout << arr[i].first << ": " << arr[i].second << endl;
                }
                else
                {
                    cout << arr[i - 1].first << ": " << arr[i - 1].second << endl;
                    cout << arr[i - 2].first << ": " << arr[i - 2].second << endl;
                    cout << arr[i].first << ": " << arr[i].second << endl;
                }
            }
            else if(max > arr[i - 1].second && max > arr[i - 2].second){
                if(arr[i - 2].second > arr[i - 1].second){
                    cout << arr[i].first << ": " << arr[i].second << endl;
                    cout << arr[i - 2].first << ": " << arr[i - 2].second << endl;
                    cout << arr[i - 1].first << ": " << arr[i - 1].second << endl;
                }
                else{
                    cout << arr[i].first << ": " << arr[i].second << endl;
                    cout << arr[i - 1].first << ": " << arr[i - 1].second << endl;
                    cout << arr[i - 2].first << ": " << arr[i - 2].second << endl;
                }
            }
            else
            {
                if(max > arr[i - 1].second){
                    cout << arr[i - 2].first << ": " << arr[i - 2].second << endl;
                    cout << arr[i].first << ": " << arr[i].second << endl;
                    cout << arr[i - 1].first << ": " << arr[i - 1].second << endl;
                }
                else{
                    cout << arr[i - 1].first << ": " << arr[i - 1].second << endl;
                    cout << arr[i].first << ": " << arr[i].second << endl;
                    cout << arr[i - 2].first << ": " << arr[i - 2].second << endl;
                }
            }

            cout << "\n";
        }
    }
};

int main()
{
    string input;
    stack treasure;

    while (getline(cin, input))
    {
        int index = 0;
        string temp = "";
        string label;
        int value = 0;

        if (input.empty())
        {
            break;
        }

        for (int i = 0; i < input.size(); i++)
        {
            if (input[i] == ' ')
            {
                index = i + 1;
                break;
            }

            temp += input[i];
        }

        label = temp;
        temp = "";

        for (int i = index; i < input.size(); i++)
        {
            temp += input[i];
        }

        try
        {
            value = stoi(temp);
        }
        catch (const invalid_argument &e)
        {
            cerr << "Invalid input for value: " << temp << endl;
            continue;
        }

        treasure.push({label, value});
    }

    treasure.print();

    return 0;
}