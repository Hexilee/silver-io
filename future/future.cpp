/*
 * Created by 李晨曦 on 2019-06-25.
 */

#include "future.hpp"

using namespace future;

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

FuncContext::FuncContext(std::function<auto() -> void> waker) : waker(waker) {}

auto FuncContext::wake() -> void {
    waker();
}
