/*
 * Created by 李晨曦 on 2019-06-30.
 */

#include "generator/generator.hpp"
#include <iostream>

using std::cout;
using std::endl;
using sio::generator::Generator;

auto fab(int max) {
    return new Generator<int, int>([=] {
        auto n = max;
        int a = 0, b = 1, next;
        for (int i = 0; i < n; i++) {
            Generator<int, int>::this_generator->yield(a);
            next = a + b;
            a = b;
            b = next;
        }
        Generator<int, int>::this_generator->done(a);
    });
}

auto main() -> int {
    auto g = fab(10);
    cout << "yield " << g->current_yield() << endl;
    while (!g->is_complete()) {
        cout << "yield " << g->resume() << endl;
    }
    cout << "done: " << g->result() << endl;
    return 0;
}