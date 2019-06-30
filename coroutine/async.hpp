/*
 * Created by 李晨曦 on 2019-06-29.
 */

#ifndef SILVER_IO_ASYNC_HPP
#define SILVER_IO_ASYNC_HPP
#include <thread>
#include <iostream>
#include "future/future.hpp"
#include "coroutine/coroutine.hpp"

#define await Await() <<
namespace sio::coroutine {
    using sio::future::Future;
    
    class Await {
      public:
        template<typename T>
        auto operator<<(Future<T> &f) -> const T &;
    };
    
    auto fn() {
        auto f = sio::future::FutureOk(1);
        auto result = await f;
        std::cout << result << std::endl;
    }
}
#endif //SILVER_IO_ASYNC_HPP
