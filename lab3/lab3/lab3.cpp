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

class Queue {
private:
    int* arr;
    int head = 0;
    int tail = 0;
    int count = 0;

public:
    Queue() { // конструктор
        arr = new int[100];
    }

    Queue(const Queue& other) { // конструктор копирования
        this->head = other.head;
        this->tail = other.tail;
        this->count = other.count;
        this->arr = new int[100];
        for (int i = other.head; i < other.tail; i++) {
            this->arr[i] = other.arr[i];
        }

    }

    ~Queue() { // деструктор
        delete[] arr;
    }

    void push(int x) {
        arr[tail++] = x;
        ++count;
    }

    int pop() {
        if (head != tail) {
            ++head;
            --count;
            return arr[head - 1];
        }
        else {
            cout << "Empty" << endl;
            return -1;
        }
    }

    bool is_empty() {
        return head == tail;
    }

    int front() {
        if (head == tail) {
            cout << "Empty. Error: ";
            return -1;
        }
        else return arr[head];
    }

};

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
        delete[] Matrix[i];
    }
    delete Matrix;
}