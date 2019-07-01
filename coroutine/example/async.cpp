/*
 * Created by 李晨曦 on 2019-07-02.
 */

#include "coroutine/async.hpp"

using namespace sio::coroutine;
using namespace sio::future;

auto async_task(uint64_t n) {
    return async [=] {
        for (uint64_t i = 0; i < n; i++) {
            auto f = CounterFuture(n, n);
            std::cout << "await result(" << i << "): " << (await std::move(f)) << std::endl;
        }
        return n * n;
    };
}

auto main() -> int {
    auto task = async_task(5);
    auto poll_result = task->poll();
    while (!poll_result.is_complete()) {
        poll_result = task->poll();
    }
    std::cout << "done: " << poll_result.get() << std::endl;
    return 0;
}