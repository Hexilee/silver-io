/*
 * Created by 李晨曦 on 2019-06-29.
 */

#ifndef SILVER_IO_ASYNC_HPP
#define SILVER_IO_ASYNC_HPP
#include <thread>
#include <iostream>
#include "future/future.hpp"
#include "coroutine/coroutine.hpp"

#define await sio::coroutine::Await() <<
namespace sio::coroutine {
    using sio::future::Future;
    
    class Await {
      public:
        template<typename T>
        auto operator<<(Future<T> &f) -> const T &;
        
        template<typename T>
        auto operator<<(Future<T> && f) -> const T &;
    };
}
#endif //SILVER_IO_ASYNC_HPP
