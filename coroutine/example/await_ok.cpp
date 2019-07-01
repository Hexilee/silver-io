/*
 * Created by 李晨曦 on 2019-06-30.
 */

#include <iostream>
#include "coroutine/async.hpp"
#include "future/future.hpp"
using sio::future::FutureOk;

auto main() -> int {
    auto f = FutureOk(1);
    auto a = await f;
    std::cout << a << std::endl;
    return 0;
}