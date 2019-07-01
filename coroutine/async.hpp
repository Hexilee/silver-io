/*
 * Created by 李晨曦 on 2019-06-29.
 */

#ifndef SILVER_IO_ASYNC_HPP
#define SILVER_IO_ASYNC_HPP
#include <thread>
#include <iostream>
#include "future/future.hpp"
#include "coroutine/coroutine.hpp"

#define await sio::coroutine::Awaiter() <<
namespace sio::coroutine {
    using sio::future::Future;
    
    class Awaiter {
      public:
        template<typename T>
        auto operator<<(Future<T> &f) -> const T &;

        template<typename T>
        auto operator<<(Future<T> &&f) -> const T &;
    };
    
    template<typename T>
    auto sio::coroutine::Awaiter::operator<<(sio::future::Future<T> &f) -> const T & {
        return (*this) << std::move(f);
    }
    
    template<typename T>
    auto sio::coroutine::Awaiter::operator<<(sio::future::Future<T> &&f) -> const T & {
        auto poll_result = f.poll(sio::future::ThreadLocalContext);
        while (!poll_result.is_complete()) {
            sio::coroutine::Coroutine<T>::yield();
            poll_result = f.poll(sio::future::ThreadLocalContext);
        }
        return poll_result.get();
    }
    
}
#endif //SILVER_IO_ASYNC_HPP
