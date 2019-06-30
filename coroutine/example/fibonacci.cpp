/*
 * Created by 李晨曦 on 2019-06-30.
 */

#include "fibonacci.hpp"

auto main() -> int {
    fiber f(fib(10));
    f.join();
}