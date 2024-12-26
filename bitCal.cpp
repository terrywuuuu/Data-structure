#include <iostream>
#include <string>

using namespace std;

void BitCal(string &in)
{
    int *stack = new int[in.length()];
    int *result = new int[in.length()];
    int indexs = 0, indexr = 0;

    for (int i = 0; i < in.length(); i++)
    {
        if (in[i] != '~' && in[i] != '&' && in[i] != '^' && in[i] != '|')
        {
            stack[indexs] = in[i] - '0';
            result[indexr++] = stack[indexs++];
        }
        else
        {
            if (in[i] == '~')
            {
                int a = stack[indexs - 1];
                indexs--;
                stack[indexs] = ~a;
                result[indexr++] = stack[indexs++];
            }
            else
            {
                int a = stack[indexs - 2];
                int b = stack[indexs - 1];
                indexs -= 2;

                if (in[i] == '&')
                {
                    stack[indexs] = a & b;
                    result[indexr++] = stack[indexs++];
                }
                else if (in[i] == '^')
                {
                    stack[indexs] = a ^ b;
                    result[indexr++] = stack[indexs++];
                }
                else if (in[i] == '|')
                {
                    stack[indexs] = a | b;
                    result[indexr++] = stack[indexs++];
                }
            }
        }
    }

    for (int i = 0; i < indexr; i++)
    {
        cout << result[i] << " ";
    }

    delete[] stack;
    delete[] result;
}

bool Precedence(char a, char b)
{
    if (a == '~')
    {
        return true;
    }
    else if (a == '&' && b != '~')
    {
        return true;
    }
    else if (a == '^' && (b != '~' && b != '&'))
    {
        return true;
    }
    else if (a == '|' && b == '|')
    {
        return true;
    }
    else
    {
        return false;
    }
}

string IntoPost(string in)
{
    string stack = "(";
    string post = "";
    in.push_back(')');

    for (int i = 0; i < in.length(); i++)
    {
        if (in[i] == '(')
        {
            stack.push_back('(');
        }
        else if (in[i] == ')')
        {
            int index=stack.length()-1;

            while (index>=0)
            {
                if (stack[index] == '(')
                {
                    stack.erase(index, 1);
                    break;
                }

                post.push_back(stack[index]);
                stack.erase(index, 1);
                index--;
            }
        }
        else if (in[i] == '~' || in[i] == '&' || in[i] == '^' || in[i] == '|')
        {
            int index=stack.length()-1;

            while (index>=0)
            {
                if (stack[index] != '(' && Precedence(stack[index], in[i]))
                {
                    post.push_back(stack[index]);
                    stack.erase(index, 1);
                    index--;
                }
                else
                {
                    stack.push_back(in[i]);
                    break;
                }
            }
        }
        else
        {
            post.push_back(in[i]);
        }
    }

    return post;
}

void Cal(string &in, int index)
{
    int num = 0;

    if (in[index - 1] != ')' && in[index - 2] != '(')
    {
        in.insert(index - 1, 1, '(');
    }
    else if (in[index - 2] == '(')
    {
        return;
    }
    else
    {
        for (int i = index - 1; i >= 0; i--)
        {
            if (in[i] == ')')
            {
                num++;
            }
            else if (in[i] == '(')
            {
                num--;
            }

            if (num == 0)
            {
                if ((i > 0 && in[i - 1] != '(') || i == 0)
                {
                    in.insert(i, 1, '(');
                    break;
                }
                else
                {
                    return;
                }
            }
        }
    }

    index++;
    num = 0;

    if (in[index + 1] != '(')
    {
        in.insert(index + 2, 1, ')');
    }
    else
    {
        for (int i = index + 1; i < in.length(); i++)
        {
            if (in[i] == '(')
            {
                num++;
            }
            else if (in[i] == ')')
            {
                num--;
            }

            if (num == 0)
            {
                in.insert(i + 1, 1, ')');
                break;
            }
        }
    }
}

void Brackets(string &in)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < in.length(); j++)
        {
            switch (i)
            {
            case 0:
                if (in[j] == '~' && in[j - 1] != '(')
                {
                    in.insert(j, 1, '(');
                    int num = 0;

                    if (in[j + 2] != '(')
                    {
                        in.insert(j + 3, 1, ')');
                    }
                    else
                    {
                        for (int z = j + 2; z < in.length(); z++)
                        {
                            if (in[z] == '(')
                            {
                                num++;
                            }
                            else if (in[z] == ')')
                            {
                                num--;
                            }

                            if (num == 0)
                            {
                                in.insert(z + 1, 1, ')');
                                break;
                            }
                        }
                    }
                    j++;
                }

                break;
            case 1:
                if (in[j] == '&')
                {
                    Cal(in, j);
                    j++;
                }

                break;
            case 2:
                if (in[j] == '^')
                {
                    Cal(in, j);
                    j++;
                }

                break;
            case 3:
                if (in[j] == '|')
                {
                    Cal(in, j);
                    j++;
                }

                break;
            }
        }
    }
}

int main()
{
    string input;
    cin >> input;

    string Post = IntoPost(input);
    cout << Post << endl;

    BitCal(Post);
}