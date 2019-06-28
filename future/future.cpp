/*
 * Created by 李晨曦 on 2019-06-25.
 */

#include "future.hpp"

using namespace future;
using future::ThreadLocalContext;
using moodycamel::BlockingConcurrentQueue;

template<class Output>
auto Poll<Output>::pending() -> Poll {
    Poll poll;
    poll.complete = false;
    return poll;
}

template<class Output>
auto Poll<Output>::is_complete() -> bool {
    return complete;
}

template<class Output>
auto Poll<Output>::get() -> Output {
    return value;
}


template<class Output>
auto Future<Output>::wait() -> Output {
    class Signal;
    BlockingConcurrentQueue<Signal> channel;
    ThreadLocalContext = make_shared<FuncContext>([&channel]() {
        channel.enqueue(Signal());
    });
    auto poll_result = Poll<Output>::pending();
    Signal signal;
    while (!poll_result.is_complete()) {
        channel.wait_dequeue(&signal);
        poll_result = poll(ThreadLocalContext);
    }
    return poll_result.get();
}
