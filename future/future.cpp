/*
 * Created by 李晨曦 on 2019-06-25.
 */

#include "future.hpp"

using namespace future;
using future::ThreadLocalContext;

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
    poll(ThreadLocalContext);
}
