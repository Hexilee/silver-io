/*
 * Created by 李晨曦 on 2019-06-29.
 */

#ifndef SILVER_IO_ASYNC_HPP
#define SILVER_IO_ASYNC_HPP
#include <thread>
#include <iostream>
#include <functional>
#include <memory>
#include <type_traits>
#include "future/future.hpp"
#include "future/stream.hpp"
#include "coroutine/coroutine.hpp"
#include "coroutine/co_future.hpp"
#include "coroutine/stream_iter.hpp"

#define await sio::coroutine::Awaiter() <<
#define async sio::coroutine::Asyncer() <<
namespace sio::coroutine {
    using sio::future::Future;
    using sio::future::Stream;
    using sio::future::PollStatus;
    using std::function;
    using std::unique_ptr;
    using std::make_unique;
    
    class Awaiter {
      public:
        template<typename T>
        auto operator<<(Future<T> &&f) -> T &&;
        
        template<typename T>
        auto operator<<(Stream<T> &&s) -> StreamIter<T>;
    };
    
    class Asyncer {
      public:
        template<typename Fn>
        auto operator<<(Fn &&lambda) -> unique_ptr<Future<typename std::result_of<Fn(void)>::type>>;
    };
    
    template<typename T>
    auto Awaiter::operator<<(sio::future::Future<T> &&f) -> T && {
        auto poll_result = f.poll();
        while (poll_result.status() == PollStatus::Pending) {
            sio::coroutine::Coroutine<T>::yield();
            poll_result = f.poll();
        }
        return poll_result.release();
    }
    
    template<typename T>
    auto Awaiter::operator<<(Stream<T> &&s) -> StreamIter<T> {
        return StreamIter<T>(s);
    }
    
    template<typename Fn>
    auto Asyncer::operator<<(Fn &&lambda) -> unique_ptr<Future<Ret<Fn>>> {
        return make_unique<CoFuture<Fn> >(std::forward<Fn>(lambda));
    }
}
#endif //SILVER_IO_ASYNC_HPP
