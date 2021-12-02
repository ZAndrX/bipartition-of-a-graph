#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
using namespace std;

//функция вывода, если граф двдольный
void output(char color[], int n, ofstream& out) {
    string str1, str2;
    for (int i = 0; i < n; i++)
        if (color[i] == 1) str1 += to_string(i + 1) + " ";
        else
            str2 += to_string(i + 1) + " ";
    str1.erase(str1.length() - 1, 1);
    str2.erase(str2.length() - 1, 1);
    out << str1 << endl << str2;
}

//инвертирование цвета
char invert(char ch) {
    if (ch == 1) return 2;
    return 1;
}

//поиск и вывод нечетного цикла
void search_while(int pred[], int begin, int n, int t, ofstream& out) {
    if (t == begin) {
        out << "NOT BIPARTITE" << endl << t + 1 << " ";
    }
    else {
        search_while(pred, begin, n, pred[t], out);
        out << t + 1 << " ";
    }
}

//обход в глубину
void dfs(int** matrix, int n, int number, char color[], char now_color, bool& rez, ofstream& out, int pred[]) {
    for (int i = 0; i < n && rez; i++) {
        if (matrix[i][number] == 1 && color[i] == 0) {
            color[i] = invert(now_color);
            pred[i] = number;
            dfs(matrix, n, i, color, color[i], rez, out, pred);
        }
        else
            if (matrix[i][number] == 1 && color[i] == now_color) {
                rez = false;
                pred[i] = number;
                search_while(pred, i, n, number, out);
                return;
            };
    }
    return;
}
//основной блок программы
int main()
{
    clock_t start = clock();
    int n;
    bool rez = true;
    int** matrix;
    char* color;
    int* pred;
    ifstream in("input.txt");
    ofstream out("output.txt");
    in >> n;
    color = new char[n];
    matrix = new int* [n];
    pred = new int[n];

    //зануление
    for (int i = 0; i < n; i++) {
        matrix[i] = new int[n];
        color[i] = 0;
    }

    //ввод матрицы смежности
    for (int row = 0; row < n; row++)
        for (int col = 0; col < n; col++)
            in >> matrix[row][col];

    //покраска первой вершины
    color[0] = 1;
    //запуск обхода в глубину
    dfs(matrix, n, 0, color, color[0], rez, out, pred);

    //Вывод, если граф двудольный
    if (rez) output(color, n, out);

    //освобождение памяти
    delete[] color;
    for (int i = 0; i < n; i++)  delete[] matrix[i];
    delete[] matrix;
    delete[] pred;
    in.close();
    out.close();

    //вывод времени выполнения
    cout << (clock() - start) / (double)CLOCKS_PER_SEC << " seconds" << endl;
}



