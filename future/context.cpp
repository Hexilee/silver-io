/*
 * Created by 李晨曦 on 2019-06-28.
 */

#include "context.hpp"

using namespace sio::future;

FuncContext::FuncContext(std::function<auto() -> void>&& waker) : waker(waker) {}

auto FuncContext::wake() -> void {
    waker();
}

thread_local shared_ptr<Context> sio::future::ThreadLocalContext = make_shared<FuncContext>([]() {
    // do nothing
});

