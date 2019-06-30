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
    
    template <typename T>
    class Coroutine: public Generator<Context, T> {
        using Gen = Generator<Context, T>;
      public:
        static auto yield();
        static auto done(T value);
    };
}
#endif //SILVER_IO_COROUTINE_HPP
