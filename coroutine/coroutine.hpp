/*
 * Created by 李晨曦 on 2019-06-30.
 */

#ifndef SILVER_IO_COROUTINE_HPP
#define SILVER_IO_COROUTINE_HPP
#include "generator/generator.hpp"

namespace sio::coroutine {
    using sio::generator::Generator;
    
    // TODO: replace with std::monostate
    enum Context {
        Hup
    };
    
    template<typename T>
    class Coroutine: public Generator<Context, T> {
        using Gen = Generator<Context, T>;
      public:
        explicit Coroutine(std::function<T()> &&fn);
        static auto yield() -> void;
    };
    
    template<typename T>
    auto Coroutine<T>::yield() -> void {
        Gen::yield(Context::Hup);
    }
    
    template<typename T>
    Coroutine<T>::Coroutine(std::function<T()> &&fn): Generator<Context, T>(std::forward<std::function<T()>>(fn)) {}
}
#endif //SILVER_IO_COROUTINE_HPP
