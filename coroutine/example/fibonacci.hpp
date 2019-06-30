/*
 * Created by 李晨曦 on 2019-06-30.
 */

#ifndef SILVER_IO_FIBONACCI_HPP
#define SILVER_IO_FIBONACCI_HPP
#include <boost/fiber/all.hpp>
#include <functional>

using boost::this_fiber::yield;
using boost::fibers::fiber;

auto fib(int n) -> std::function<void()> {
    int a = 0, b = 1;
    return [&]() {
        for (int i = 0; i < n; i++) {
            std::cout << a << std::endl;
            yield();
            int next = a + b;
            a = b;
            b = next;
        }
    };
}

#endif //SILVER_IO_FIBONACCI_HPP
