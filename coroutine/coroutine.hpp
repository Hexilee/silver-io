/*
 * Created by 李晨曦 on 2019-06-30.
 */

#ifndef SILVER_IO_COROUTINE_HPP
#define SILVER_IO_COROUTINE_HPP
#include <variant>
#include "generator/generator.hpp"

namespace sio::coroutine {
    using sio::generator::Generator;
    
    template<typename T>
    class Coroutine: public Generator<std::monostate, T> {
        using Gen = Generator<std::monostate, T>;
      public:
        explicit Coroutine(std::function<T()> &&fn);
        static auto yield() -> void;
    };
    
    template<typename T>
    auto Coroutine<T>::yield() -> void {
        Gen::yield(std::monostate());
    }
    
    template<typename T>
    Coroutine<T>::Coroutine(std::function<T()> &&fn): Generator<std::monostate,
                                                                T>(std::forward<std::function<T()>>(fn)) {}
}
#endif //SILVER_IO_COROUTINE_HPP
