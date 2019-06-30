/*
 * Created by 李晨曦 on 2019-06-30.
 */

#ifndef SILVER_IO_GENERATOR_HPP
#define SILVER_IO_GENERATOR_HPP
#include <boost/coroutine2/all.hpp>

namespace sio::generator {
    template<typename T>
    using boost_coroutine = boost::coroutines2::coroutine<T>;
    
    template<typename Yield, typename Return>
    class Generator;
    
    template<typename Y, typename R>
    class Generator {
        using Yield = typename boost_coroutine<Y>::push_type;
        using Resume = typename boost_coroutine<Y>::pull_type;
        Yield *_yield;
        Resume *_resume;
        R _result;
        auto set_this_generator() -> void;
      public:
        explicit Generator(std::function<auto() -> void> &&fn);
        ~Generator();
        static thread_local Generator<Y, R> *this_generator;
        auto resume() -> const Y &;
        auto yield(Y value) -> void;
        auto done(R ret) -> void;
        auto is_complete() -> bool;
        auto result() -> const R &;
    };
    
    template<typename Y, typename R>
    thread_local Generator<Y, R> *Generator<Y, R>::this_generator = nullptr;
}
#endif //SILVER_IO_GENERATOR_HPP
