#include "SegmentTree.h"
#include <iostream>

SegmentTree::SegmentTree(const std::vector<int>& arr) : a(arr), n(arr.size()) {
    t.resize(4 * n); // дерево требует примерно 4n памаяти
    lz.resize(4 * n); // массив тоже
    build(1, 0, n - 1); // строим дерево начиная с корня
}

void SegmentTree::build(int v, int tl, int tr) {
    if (tl == tr) { // если дошли до листа
        t[v] = a[tl]; // записываем значение массива
        return;
    }
    int tm = (tl + tr) / 2; // середина отрезка
    build(2 * v, tl, tm); // строим левое
    build(2 * v + 1, tm + 1, tr); // строим правое
    t[v] = t[2 * v] + t[2 * v + 1]; // суммируем значения
}

void SegmentTree::push(int v, int tl, int tr) {
    if (lz[v] != 0) { // если есть отложенное отправление
        t[v] += (tr - tl + 1) * lz[v]; //применяем его к текущему узлу
        if (tl != tr) { // если узел не лист
            lz[2 * v] += lz[v]; //передаем обновление левому
            lz[2 * v + 1] += lz[v]; // и правому
        }
        lz[v] = 0; // обновление выполнено
    }
}

int SegmentTree::sum(int v, int tl, int tr, int l, int r) {
    push(v, tl, tr); // проталкиваем ленивые обновления
    if (l > tr || r < tl) return 0; // отверзки не пересекаются - 0
    if (l <= tl && tr <= r) return t[v]; // текущий отрезок полностью входит в запрос - возвращаем значение
    int tm = (tl + tr) / 2; // разбиваем отрезок пополам
    return sum(2 * v, tl, tm, l, r) + sum(2 * v + 1, tm + 1, tr, l, r); // суммируем результаты
}

int SegmentTree::min(int v, int tl, int tr, int l, int r) {
    push(v, tl, tr);
    if (l > tr || r < tl) return INT_MAX;
    if (l <= tl && tr <= r) return t[v];
    int tm = (tl + tr) / 2;
    return std::min(min(2 * v, tl, tm, l, r), min(2 * v + 1, tm + 1, tr, l, r));
}

int SegmentTree::max(int v, int tl, int tr, int l, int r) {
    push(v, tl, tr);
    if (l > tr || r < tl) return INT_MIN;
    if (l <= tl && tr <= r) return t[v];
    int tm = (tl + tr) / 2;
    return std::max(max(2 * v, tl, tm, l, r), max(2 * v + 1, tm + 1, tr, l, r));
}

void SegmentTree::set(int v, int tl, int tr, int pos, int val) {
    push(v, tl, tr); // проталкиваем ленивые обновления
    if (tl == tr) { // дошли до нужного листа
        t[v] = val; // обновляем значение
        return;
    }
    int tm = (tl + tr) / 2;
    if (pos <= tm) set(2 * v, tl, tm, pos, val); // ищем поицию в левом поддереве
    else set(2 * v + 1, tm + 1, tr, pos, val); // или в правом
    t[v] = t[2 * v] + t[2 * v + 1]; // обновляем сумму в текущем узле
}

void SegmentTree::add(int v, int tl, int tr, int l, int r, int delta) {
    push(v, tl, tr); // проталкиваем ленивые обновления
    if (l > tr || r < tl) return; // отрезки не пересекаются - выходим
    if (l <= tl && tr <= r) { // текущий отрезок полностью внутри обновления
        t[v] += (tr - tl + 1) * delta; // обновляем значение узла
        if (tl != tr) { // если не лист
            lz[2 * v] += delta; //откладываем обновление для левого
            lz[2 * v + 1] += delta; // и для правого
        }
        return;
    }
    int tm = (tl + tr) / 2;
    add(2 * v, tl, tm, l, r, delta); // рекурсивно обновляем лев
    add(2 * v + 1, tm + 1, tr, l, r, delta); // и правое
    t[v] = t[2 * v] + t[2 * v + 1];
}

// Публичные методы
int SegmentTree::getSum(int l, int r) {
    if (l < 0 || r >= n || l > r) return -1;
    return sum(1, 0, n - 1, l, r);
}

int SegmentTree::getMin(int l, int r) {
    if (l < 0 || r >= n || l > r) return INT_MAX;
    return min(1, 0, n - 1, l, r);
}

int SegmentTree::getMax(int l, int r) {
    if (l < 0 || r >= n || l > r) return INT_MIN;
    return max(1, 0, n - 1, l, r);
}

void SegmentTree::update(int pos, int val) {
    if (pos < 0 || pos >= n) return;
    set(1, 0, n - 1, pos, val);
}

void SegmentTree::updateRange(int l, int r, int delta) {
    if (l < 0 || r >= n || l > r) return;
    add(1, 0, n - 1, l, r, delta);
}

void SegmentTree::print() {
    std::cout << "Tree: ";
    for (int x : t) if (x != 0) std::cout << x << " ";
    std::cout << "\nLazy: ";
    for (int x : lz) if (x != 0) std::cout << x << " ";
    std::cout << "\n";
}
