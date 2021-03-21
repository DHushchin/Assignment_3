#include <iostream>
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


struct Point {
    int i, j;
    int dist;
    int id;
    int parent_id;

    bool operator ==(const Point& other) {
        return this->i == other.i && this->j == other.j;
    }

    bool operator !=(const Point& other) {
        return !(this->i == other.i && this->j == other.j);
    }

    Point() {

    }

    Point(const Point& other) {
        this->i = other.i;
        this->j = other.j;
        this->id = other.id;
        this->parent_id = other.parent_id;
    }

    ~Point();
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
void FindReach(Point&, vector<Point>&, vector<Point>&, char**, int, int, int);
void Dijkstra(char**, int, int);

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

void FindScopes(Point& point1, Point& point2) {
    cout << endl << "Enter I coord of start point: "; cin >> point1.i;
    cout << "Enter J coord of start point: "; cin >> point1.j;
    cout << "Enter I coord of end point: "; cin >> point2.i;
    cout << "Enter J coord of end point: "; cin >> point2.j;
    cout << endl;
}

bool isVisited(Point point, vector<Point> visited) {
    for (size_t i = 0; i < visited.size(); i++) {
        if (visited[i] == point) return true;
    }
    return false;
}

void FindReach(Point& point, vector<Point>& reachable, vector<Point>& visit, char** matr, int rows, int columns, int min) {
    if (point.j > 0 && (matr[point.i][point.j - 1] != 'X')) {
        Point point1(point);
        --point1.j;
        if (!isVisited(point1, visit)) {
            Point left;
            left.i = point.i;
            left.j = point1.j;
            left.parent_id = point1.id;
            left.dist = point1.dist + 10;
            reachable.push_back(left);
            visit.push_back(left);
        }
        else {
            if (visit[point1.id].dist > point1.dist) {
               visit[point1.id].dist = point1.dist;
               visit[point1.id].parent_id = point1.parent_id;
            }
        }
    }
 

    if (point.j < columns - 1 && (matr[point.i][point.j + 1] != 'X')) {
        Point point1(point);
        ++point1.j;
        if (!isVisited(point1, visit)) {
            Point right;
            right.i = point1.i;
            right.j = point1.j;
            right.parent_id = point1.dist;
            right.dist = point1.id + 10;
            reachable.push_back(right);
        }
        else {
            if (visit[point1.id].dist > point1.dist) {
                visit[point1.id].dist = point1.dist;
                visit[point1.id].parent_id = point1.parent_id;
            }
        }
    }

    if (point.i > 0 && (matr[point.i - 1][point.j] != 'X')) {
        Point point1(point);
        --point1.i;
        if (!isVisited(point1, visit)) {
            Point up;
            up.i = point1.i;
            up.j = point1.j;
            up.parent_id = point1.id;
            up.dist = point1.dist + 10;
            reachable.push_back(up);
        }
        else {
            if (visit[point1.id].dist > point1.dist) {
                visit[point1.id].dist = point1.dist;
                visit[point1.id].parent_id = point1.parent_id;
            }
        }
    }

    if (point.i < rows - 1 && (matr[point.i + 1][point.j] != 'X')) {
        Point point1(point);
        ++point1.i;
        if (!isVisited(point1, visit)) {
            Point down;
            down.i = point1.i;
            down.j = point1.j;
            down.parent_id = point1.id;
            down.dist = point1.dist + 10;
            reachable.push_back(down);
        }
        else {
            if (visit[point1.id].dist > point1.dist) {
                visit[point1.id].dist = point1.dist;
                visit[point1.id].parent_id = point1.parent_id;
            }
        }
    }
}

void Dijkstra(char** Matrix, int rows, int columns)
{
    Point start, end;
    FindScopes(start, end);
    start.id = 0;
    start.dist = 0;
    vector<Point> visited, reachable;
    visited.push_back(start);
    int min_dist = INF;
    FindReach(start, reachable, visited, Matrix, rows, columns, min_dist);
    int i = 0;
    while (!isVisited(end, visited)) {
        FindReach(reachable[i], reachable, visited, Matrix, rows, columns, min_dist);
        i++;
    }
}