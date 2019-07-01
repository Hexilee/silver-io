/*
 * Created by 李晨曦 on 2019-07-02.
 */

#include "coroutine/async.hpp"

using namespace sio::coroutine;

auto async_task(uint64_t n) -> unique_ptr<Future<uint64_t >> {
    return async [=] {
        return n;
    };
}

auto main() -> int {
    auto task = async_task(5);
}