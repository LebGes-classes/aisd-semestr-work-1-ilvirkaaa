#pragma once // защита от повтоного включения
#include <vector>
#include <climits>

class SegmentTree {
private:
    std::vector<int> t;  // дерево отрезков
    std::vector<int> lz; // масиив для отложенных обновлений
    std::vector<int> a;  // исходный массив
    int n;               // размер массива

    void build(int v, int tl, int tr); // строит дерево отрезков
    void push(int v, int tl, int tr); // проталкивает отложенные добавления вниз по дереву
    int sum(int v, int tl, int tr, int l, int r);
    int min(int v, int tl, int tr, int l, int r);
    int max(int v, int tl, int tr, int l, int r);
    void set(int v, int tl, int tr, int pos, int val); // обновляет значение в одной позиции
    void add(int v, int tl, int tr, int l, int r, int delta); // прибавляет delta ко всем элементам на отрезке

public:
    SegmentTree(const std::vector<int>& arr); // контруктор
    int getSum(int l, int r); // возращает сумму 
    int getMin(int l, int r);
    int getMax(int l, int r);
    void update(int pos, int val); // меняет значение
    void updateRange(int l, int r, int delta); // прибавляет дельта
    void print(); // вы
};
