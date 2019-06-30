/*
 * Created by 李晨曦 on 2019-06-30.
 */

#include "generator.hpp"

using namespace sio::generator;

template<typename Y, typename R>
Generator<Y, R>::Generator(std::function<auto() -> void> &&fn) {
    _resume = new Resume([&](Yield yield) {
        _yield = yield;
        set_this_generator();
        fn();
    });
}

template<typename Y, typename R>
Generator<Y, R>::~Generator() {
    delete _yield;
    delete _resume;
}

template<typename Y, typename R>
auto Generator<Y, R>::set_this_generator() -> void {
    this_generator = this;
}

template<typename Y, typename R>
auto Generator<Y, R>::resume() -> const Y& {
    set_this_generator();
    _resume();
    return _resume->get();
}

template<typename Y, typename R>
auto Generator<Y, R>::yield(Y value) -> void {
    _yield(value);
}

template<typename Y, typename R>
auto Generator<Y, R>::yield() -> void {
    _yield(nullptr);
}

template<typename Y, typename R>
auto Generator<Y, R>::complete(R ret) -> void {
    _result = ret;
}

template<typename Y, typename R>
auto Generator<Y, R>::is_complete() -> bool {
    return !*_resume;
}

template<typename Y, typename R>
auto Generator<Y, R>::result() -> const R & {
    return _result;
}
