/*
 * Created by 李晨曦 on 2019-06-30.
 */

#include "generator/generator.hpp"
#include <iostream>

using std::cout;
using std::endl;
using sio::generator::Generator;

auto fab(int n) {
    int a = 0, b = 1, next;
    return new Generator<int, int>([&]() {
        for (int i = 0; i < n; i++) {
            Generator<int, int>::this_generator->yield(a);
            next = a + b;
            a = b;
            b = next;
        }
    });
}

auto main() -> int {
    auto g = fab(10);
    cout << g->is_complete() << endl;
}