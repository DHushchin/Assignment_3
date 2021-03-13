#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

void FindSize(ifstream& , size_t&, size_t&);
char** CreateMatrix(size_t&, size_t&);
void FillMatrix(ifstream&, char**, size_t&, size_t&);
void DeleteMatrix(char**, size_t&, size_t&);
void PrintMatrix(char** Matrix, size_t& rows, size_t& columns);

int main()
{
    ifstream input("..\\..\\iofiles\\input.txt");
    size_t rows, columns;
    char** Matrix;
    FindSize(input, rows, columns);
    Matrix = CreateMatrix(rows, columns);
    input.close();
    input.clear();
    input.open("..\\..\\iofiles\\input.txt");
    FillMatrix(input, Matrix, rows, columns);
    PrintMatrix(Matrix, rows, columns);
    DeleteMatrix(Matrix, rows, columns);
    input.close();
    return 0;
}

void FindSize(ifstream& input, size_t& rows, size_t& columns) {
    string currStr;
    rows = 0;
    while (!input.eof()) {
        getline(input, currStr);
        columns = currStr.length();
        rows++;
    }
}

char** CreateMatrix(size_t& rows, size_t& columns) {
    char** Matrix = new char* [rows];
    for (size_t i = 0; i < rows; i++)
    {
        Matrix[i] = new char[columns];
    }
    return Matrix;
}

void PrintMatrix(char** Matrix, size_t& rows, size_t& columns) {
    cout << "Inputted this problem:" << endl << endl;
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < columns; j++)
        {
            cout << Matrix[i][j];
        }
        cout << endl;
    }
}

void FillMatrix(ifstream& input, char** Matrix, size_t& rows, size_t& columns) {
    for (size_t i = 0; i < rows; i++)
    {
        string currStr;
        getline(input, currStr);
        for (size_t j = 0; j < columns; j++)
        {
            Matrix[i][j] = currStr[j];
        }
    }
}

void DeleteMatrix(char** Matrix, size_t &rows, size_t& columns) {
    for (size_t i = 0; i < rows; i++)
    {
        delete[] Matrix[rows];
    }
    delete Matrix;
}