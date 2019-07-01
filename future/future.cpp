/*
 * Created by 李晨曦 on 2019-06-25.
 */

#include "future/future.hpp"

using namespace sio::future;
using sio::future::ThreadLocalContext;
using moodycamel::BlockingConcurrentQueue;

template<typename T>
auto Poll<T>::pending() -> Poll {
    Poll poll;
    poll.complete = false;
    return poll;
}

template<typename T>
auto Poll<T>::is_complete() -> bool {
    return complete;
}

template<typename T>
auto Poll<T>::get() -> const Output & {
    return value;
}

template<typename T>
auto Poll<T>::operator=(Poll &&other) noexcept -> Poll & {
    value = other.value;
    complete = other.complete;
    return *this;
}

template<typename T>
auto Future<T>::wait() -> T {
    class Signal;
    BlockingConcurrentQueue<Signal> channel;
    ThreadLocalContext = make_shared<FuncContext>([&channel]() {
        channel.enqueue(Signal());
    });
    auto poll_result = Poll<T>::pending();
    Signal signal;
    while (!poll_result.is_complete()) {
        channel.wait_dequeue(&signal);
        poll_result = poll(ThreadLocalContext);
    }
    return poll_result.get();
}

template<typename T>
auto FutureOk<T>::poll(shared_ptr<Context> _ctx) -> Poll<T> {
    return Poll(value);
}

template<typename T>
FutureOk<T>::FutureOk(T &&value):value(value) {}

template<typename T>
FutureOk<T>::FutureOk(const T &value):value(value) {}

