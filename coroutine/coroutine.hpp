/*
 * Created by 李晨曦 on 2019-06-30.
 */

#ifndef SILVER_IO_COROUTINE_HPP
#define SILVER_IO_COROUTINE_HPP
#include "generator/generator.hpp"

namespace sio::coroutine {
    using sio::generator::Generator;
    enum Context {
        Hup
    };
    
    template<typename T>
    class Coroutine: public Generator<Context, T> {
        using Gen = Generator<Context, T>;
      public:
        static auto yield() -> void;
        static auto done(T value) -> void;
    };
    
    template<typename T>
    auto Coroutine<T>::yield() -> void {
        Gen::this_generator->yield(Context::Hup);
    }
    
    template<typename T>
    auto Coroutine<T>::done(T value) -> void {
        Gen::this_generator->complete(value);
    }
}
#endif //SILVER_IO_COROUTINE_HPP
