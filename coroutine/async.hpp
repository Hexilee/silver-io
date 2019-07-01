/*
 * Created by 李晨曦 on 2019-06-29.
 */

#ifndef SILVER_IO_ASYNC_HPP
#define SILVER_IO_ASYNC_HPP
#include <thread>
#include <iostream>
#include <functional>
#include <memory>
#include "future/future.hpp"
#include "coroutine/coroutine.hpp"
#include "coroutine/co_future.hpp"

#define await sio::coroutine::Awaiter() <<
#define async sio::coroutine::Asyncer() <<

namespace sio::coroutine {
    using sio::future::Future;
    using std::function;
    using std::unique_ptr;
    using std::make_unique;
    
    class Awaiter {
      public:
        template<typename T>
        auto operator<<(Future<T> &&f) -> const T &;
    };
    
    class Asyncer {
      public:
        template<typename T>
        auto operator<<(function<auto() -> T> &&f) -> unique_ptr<Future<T>>;
    };
    
    template<typename T>
    auto Awaiter::operator<<(sio::future::Future<T> &&f) -> const T & {
        auto poll_result = f.poll();
        while (!poll_result.is_complete()) {
            sio::coroutine::Coroutine<T>::yield();
            poll_result = f.poll();
        }
        return poll_result.get();
    }
    
    template<typename T>
    auto Asyncer::operator<<(function<auto() -> T> &&f) -> unique_ptr<Future<T>> {
        return make_unique<CoFuture>(f);
    }
}
#endif //SILVER_IO_ASYNC_HPP
