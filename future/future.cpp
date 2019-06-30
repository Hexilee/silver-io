/*
 * Created by 李晨曦 on 2019-06-25.
 */

#include "future.hpp"

using namespace sio::future;
using sio::future::ThreadLocalContext;
using moodycamel::BlockingConcurrentQueue;

template<class T>
auto Poll<T>::pending() -> Poll {
    Poll poll;
    poll.complete = false;
    return poll;
}

template<class T>
auto Poll<T>::is_complete() -> bool {
    return complete;
}

template<class T>
auto Poll<T>::get() -> Output {
    return value;
}


template<class T>
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
