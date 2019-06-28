/*
 * Created by 李晨曦 on 2019-06-28.
 */

#include "context.hpp"

using namespace future;

FuncContext::FuncContext(std::function<auto() -> void> waker) : waker(waker) {}

auto FuncContext::wake() -> void {
    waker();
}

auto ThreadLocalContext = make_shared<FuncContext>([]() {
    // do nothing
});

