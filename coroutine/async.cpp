/*
 * Created by 李晨曦 on 2019-06-29.
 */

#include "async.hpp"

using sio::coroutine::Awaiter;

template<typename T>
auto sio::coroutine::Awaiter::operator<<(sio::future::Future<T> &f) -> const T & {
    operator<<(std::move(f));
}

template<typename T>
auto sio::coroutine::Awaiter::operator<<(sio::future::Future<T>&& f) -> const T & {
    auto poll_result = f.poll(sio::future::ThreadLocalContext);
    while (!poll_result.is_complete()) {
        sio::coroutine::Coroutine<T>::yield();
        poll_result = f.poll(sio::future::ThreadLocalContext);
    }
    return poll_result.get();
}
