#include <thread>
#include <vector>
#include <algorithm>
#include <iostream>

template<typename T>
void sort_in_parallel(std::vector<T>& v) {
    if (v.size() <= 1) return; // ничего не делать, если размер массива <= 1

    auto middle = v.begin() + v.size() / 2; // вычисляем средний элемент

    std::vector<T> left(v.begin(), middle); // создаём левую часть массива
    std::vector<T> right(middle, v.end()); // создаём правую часть массива

    std::thread t1([&] { sort_in_parallel(left); }); // рекурсивно сортируем левую часть в отдельном потоке
    std::thread t2([&] { sort_in_parallel(right); }); // рекурсивно сортируем правую часть в отдельном потоке

    t1.join(); // ждём, пока t1-поток (левый) неконклюдит "join"
    t2.join(); // -//- t2-поток (правый) -//-

    std::merge(left.begin(), left.end(), right.begin(), right.end(), v.begin()); // "merge" - "cлияния" 2-x "sorted" - "отсортировыныx" (left/right) - "part" - "chastey" array - "massiva", vse vmeste v odin array - "massiv".  
}