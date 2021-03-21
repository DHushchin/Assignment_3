#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <queue>

#define X_STEP 20
#define Y_STEP 20
#define INF INT_MAX

using namespace std;

void FindSize(ifstream& , size_t&, size_t&);
char** CreateMatrix(size_t&, size_t&);
void FillMatrix(ifstream&, char**, size_t&, size_t&);
void DeleteMatrix(char**, size_t&, size_t&);
void PrintMatrix(char** Matrix, size_t& rows, size_t& columns);
int FindSizeGraph(char** Matrix, size_t& rows, size_t& columns);
int** CreateGraph(int& size);
void FillGraph(int** Graph, int& size);

class Queue {
private:
    int* arr;
    int head = 0;
    int tail = 0;
    int count = 0;

public:
    Queue();
    Queue(const Queue& other);
    ~Queue();
    void push(int x);
    int pop();
    bool is_empty();
    int front();
};


struct Point {
    int x, y;
};

inline double heuristic(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

bool isBlock(char** matr, int i, int j) { 
    if (matr[i][j] = 'X') return true;
    else return false;
}


int main()
{
    ifstream input("..\\..\\iofiles\\newinput.txt");
    size_t rows, columns;
    char** Matrix;
    FindSize(input, rows, columns);
    Matrix = CreateMatrix(rows, columns);
    input.close();
    input.clear();
    input.open("..\\..\\iofiles\\newinput.txt");
    FillMatrix(input, Matrix, rows, columns);
    PrintMatrix(Matrix, rows, columns);
    input.close();
    //graph
    int sizeOfGraph = FindSizeGraph(Matrix, rows, columns);
    cout << sizeOfGraph;


    DeleteMatrix(Matrix, rows, columns);
    return 0;
}

Queue::Queue() { // конструктор
    arr = new int[100];
}

Queue::Queue(const Queue& other) { // конструктор копирования
    this->head = other.head;
    this->tail = other.tail;
    this->count = other.count;
    this->arr = new int[100];
    for (int i = other.head; i < other.tail; i++) {
        this->arr[i] = other.arr[i];
    }
}

Queue::~Queue() { // деструктор
    delete[] arr;
}

void Queue::push(int x) {
    arr[tail++] = x;
    ++count;
}

int Queue::pop() {
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

bool Queue::is_empty() {
    return head == tail;
}

int Queue::front() {
    if (head == tail) {
        cout << "Empty. Error: ";
        return -1;
    }
    else return arr[head];
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

void FindScopes(int& start, int& end) {
    cout << "start = ";
    cin >> start;
    cout << "end";
    cin >> end;
}

void Dijkstra(int** Graph, int& Size)
{
    int st, end;
    FindScopes(st, end);
    int index;
    int* distance = new int[Size];
    bool* visited = new bool[Size];
    for (int i = 0; i < Size; i++)
    {
        distance[i] = INF; visited[i] = false;
    }
    distance[st] = 0;
    for (int count = 0; count < Size - 1; count++)
    {
        int min = INF;
        for (int i = 0; i < Size; i++)
            if (!visited[i] && distance[i] <= min)
            {
                min = distance[i]; index = i;
            }
        visited[index] = true;
        for (int i = 0; i < Size; i++)
            if (!visited[i] && Graph[index][i] && distance[index] != INF &&
                distance[index] + Graph[index][i] < distance[i])
                distance[i] = distance[index] + Graph[index][i];
    }
}

int FindSizeGraph(char** Matrix, size_t& rows, size_t& columns) {
    int size = 0;
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < columns; j++)
        {
            if (Matrix[i][j] != 'X' && Matrix[i][j] == ' ') {
                size++;
            }
        }
    }
    return size;
}

int** CreateGraph(int& size) {
    int** graph = new int* [size];
    for (size_t i = 0; i < size; i++)
    {
        graph[i] = new int[size];
    }
}

void FillGraph(int** Graph, int& size) {

}