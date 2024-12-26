#include <iostream>
#include <string>

using namespace std;

bool noPair(int **Old, int **New, int row, int col)
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (Old[i][j] != New[i][j])
            {
                return false;
            }
        }
    }

    return true;
}

bool Finish(int **arr, int row, int col)
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (arr[i][j] == 1 || arr[i][j] == 0)
            {
                return false;
            }
        }
    }

    return true;
}

void Increase(int **arr, int row, int col, int maxRow, int maxCol, int **rec)
{
    if (row >= 1 && (arr[row - 1][col] == 0 || arr[row - 1][col] == 1) && rec[row - 1][col] == 0)
    {
        arr[row - 1][col] += 1;
        rec[row - 1][col] = 1;
    }

    if (row < maxRow - 1 && (arr[row + 1][col] == 0 || arr[row + 1][col] == 1) && rec[row + 1][col] == 0)
    {
        arr[row + 1][col] += 1;
        rec[row + 1][col] = 1;
    }

    if (col >= 1 && (arr[row][col - 1] == 0 || arr[row][col - 1] == 1) && rec[row][col - 1] == 0)
    {
        arr[row][col - 1] += 1;
        rec[row][col - 1] = 1;
    }

    if (col < maxCol - 1 && (arr[row][col + 1] == 0 || arr[row][col + 1] == 1) && rec[row][col + 1] == 0)
    {
        arr[row][col + 1] += 1;
        rec[row][col + 1] = 1;
    }
}

void Solve(int **arr, int time, int row, int col)
{
    while (1)
    {
        int** tempArr = new int*[row];
        int** record = new int*[row];

        for (int i = 0; i < row; ++i) {
            tempArr[i] = new int[col];
            for (int j = 0; j < col; ++j) {
                tempArr[i][j] = arr[i][j]; 
            }
        }

        for (int i = 0; i < row; ++i) {
            record[i] = new int[col];
            for (int j = 0; j < col; ++j) {
                record[i][j] = 0; 
            }
        }

        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                if (tempArr[i][j] == 2)
                {
                    Increase(arr, i, j, row, col, record);
                }
            }
        }

        time++;
      
      	if(noPair(tempArr, arr, row, col)){
        	if(Finish(arr, row, col)){
            	cout << time - 1;

            	for (int i = 0; i < row; ++i) {
                	delete[] tempArr[i];
            	}
            	delete[] tempArr;

                for (int i = 0; i < row; ++i) {
                	delete[] record[i];
            	}
            	delete[] record;

            	return;
            }
          	else{
            	cout << -1;

            	for (int i = 0; i < row; ++i) {
                	delete[] tempArr[i];
            	}
            	delete[] tempArr;

                for (int i = 0; i < row; ++i) {
                	delete[] record[i];
            	}
            	delete[] record;
            
            	return;
            }
        }
    }
}

int main()
{
    int row = 0, col = 0;
    int time = 0;

    cin >> row >> col;

    int **arr = new int *[row];

    for (int i = 0; i < row; i++)
    {
        arr[i] = new int[col];
    }

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            cin >> arr[i][j];
        }
    }

    Solve(arr, time, row, col);

    for (int i = 0; i < row; ++i)
    {
        delete[] arr[i];
    }

    delete[] arr;
}