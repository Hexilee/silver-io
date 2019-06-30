/*
 * Created by 李晨曦 on 2019-06-30.
 */

#include "coroutine.hpp"

using namespace sio::coroutine;

template<typename T>
auto Coroutine<T>::yield() {
    Gen::this_generator->yield(Context::Hup);
}

template<typename T>
auto Coroutine<T>::done(T value) {
    Gen::this_generator->done(value);
}
