﻿#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <queue>

#define INF INT_MAX

using namespace std;

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

class Point {
public:
    int i{0}, j{0};
    int dist{0};
    int id{0};
    int parent_id{0};
  
    Point() {};


    Point(const Point& other) {
        this->i = other.i;
        this->j = other.j;
        this->dist = other.dist;
        this->id = other.id;
        this->parent_id = other.parent_id;
    };

    ~Point() {};

    bool operator ==(const Point& other) {
        return this->i == other.i && this->j == other.j;
    };

    bool operator !=(const Point& other) {
        return !(this->i == other.i && this->j == other.j);
    };
};

inline double heuristic(int x1, int y1, int x2, int y2) {
    return fabs(x1 - x2) + fabs(y1 - y2);
}

void FindSize(ifstream&, size_t&, size_t&);
char** CreateMatrix(size_t&, size_t&);
void FillMatrix(ifstream&, char**, size_t&, size_t&);
void DeleteMatrix(char**, size_t&, size_t&);
void PrintMatrix(char** Matrix, size_t& rows, size_t& columns);
void FindScopes(Point&, Point&);
bool isVisited(Point, vector<Point>);
void FindReach(Point, vector<Point>&, vector<Point>&, char**, int, int, int);
void CreatePoint(Point, vector<Point>&, vector<Point>&);
void Dijkstra(char**, int, int);
void Output(char**, size_t, size_t);

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
    input.close();
    Dijkstra(Matrix, rows, columns);
    Output(Matrix, rows, columns);
    DeleteMatrix(Matrix, rows, columns);
    Queue Q;
    Q.push(1);
    Q.push(2);
    Q.push(3);
    Q.push(4);
    Q.push(5);
    Q.push(6);
    Q.push(7);
    cout << Q.front() << endl;
    Q.pop();
    cout << Q.front() << endl;
    Q.pop();
    cout << Q.front() << endl;
    Q.pop();
    cout << Q.front() << endl;
    Q.pop();
    cout << Q.front() << endl;
    Q.pop();
    cout << Q.front() << endl;
    Q.pop();
    cout << Q.front() << endl;
    system("pause");
    return 0;
}

Queue::Queue() { // конструктор
    arr = new int[3];
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
    if (count >= 3) {
        int* new_arr = new int[count * 2 + 1];
        for (int i = 0; i < count; i++) {
            new_arr[i] = arr[i];
        }

        delete[] arr;
        this->arr = new_arr;
        for (int i = 0; i < count; i++) {
            arr[i] = new_arr[i];
        }
    }
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

void Output(char** Matrix, size_t rows, size_t columns)
{
    ofstream output("..\\..\\iofiles\\output.txt");
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < columns; j++)
        {
            output << Matrix[i][j];
        }
        output << endl;
    }
    output.close();
    cout << "Saved to output.txt" << endl;
}

void FindScopes(Point& point1, Point& point2) {
    cout << endl << "Enter I coord of start point: "; cin >> point2.i;
    cout << "Enter J coord of start point: "; cin >> point2.j;
    cout << "Enter I coord of end point: "; cin >> point1.i;
    cout << "Enter J coord of end point: "; cin >> point1.j;
    cout << endl;
}

bool isVisited(Point point, vector<Point> visited) {
    for (size_t i = 0; i < visited.size(); i++) {
        if (visited[i] == point) return true;
    }
    return false;
}

void CreatePoint(Point point1, vector<Point>& reachable, vector<Point>& visited) {
    if (!isVisited(point1, visited)) {
        Point newPoint;
        newPoint.i = point1.i;
        newPoint.j = point1.j;
        newPoint.parent_id = point1.id;
        newPoint.dist = point1.dist + 10;
        newPoint.id = visited.size();
        reachable.push_back(newPoint);
        visited.push_back(newPoint);
    }
    else {
        if (visited[point1.id].dist > point1.dist) {
            visited[point1.id].dist = point1.dist;
            visited[point1.id].parent_id = point1.parent_id;
        }
    }
}

void FindReach(Point point, vector<Point>& reachable, vector<Point>& visited, char** matr, int rows, int columns, int min) {
    if (point.j > 0 && (matr[point.i][point.j - 1] != 'X')) {
        Point point1(point);
        --point1.j;
        CreatePoint(point1, reachable, visited);
    }


    if (point.j < (columns - 1) && (matr[point.i][point.j + 1] != 'X')) {
        Point point1(point);
        ++point1.j;
        CreatePoint(point1, reachable, visited);   
    }


    if (point.i > 0 && (matr[point.i - 1][point.j] != 'X')) {
        Point point1(point);
        --point1.i;
        CreatePoint(point1, reachable, visited);
    }


    if (point.i < (rows - 1) && matr[point.i + 1][point.j] != 'X') {
        Point point1(point);
        ++point1.i;
        CreatePoint(point1, reachable, visited);
    }
}

void Dijkstra(char** Matrix, int rows, int columns)
{
    Point start, end;
    FindScopes(start, end);
    start.parent_id = -1;
    start.id = 0;
    start.dist = 0;
    vector<Point> visited, reachable;
    visited.push_back(start);
    int min_dist = INF;
    FindReach(start, reachable, visited, Matrix, rows, columns, min_dist);
    int k = 0;
    while (!isVisited(end, visited)) {
        FindReach(reachable[k], reachable, visited, Matrix, rows, columns, min_dist);
        k++;
    }
    end = visited[visited.size()-1];
    Point curr = end;
    int i = 49;
    while (curr.parent_id != -1) {
        Matrix[curr.i][curr.j] = (char)i;
        i++;
        if (i == 58) i = 97;
        curr = visited[curr.parent_id];
    }
    if (curr.parent_id == -1) {
        Matrix[curr.i][curr.j] = (char)i;
        i++;
    }
}