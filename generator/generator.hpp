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
        // managed by _resume
        Yield *_yield;
        Resume *_resume;
        R _result;
        auto set_this_generator() -> void;
      public:
        explicit Generator(std::function<auto() -> R> &&fn);
        ~Generator();
        static thread_local Generator<Y, R> *this_generator;
        auto resume() -> Y;
        auto yield(Y value) -> void;
        auto complete(R ret) -> void;
        auto is_complete() -> bool;
        auto result() -> R &;
    };
    
    template<typename Y, typename R>
    thread_local Generator<Y, R> *Generator<Y, R>::this_generator = nullptr;
    
    template<typename Y, typename R>
    Generator<Y, R>::Generator(std::function<auto() -> R> &&fn) {
        _resume = new Resume([=](Yield &yield) {
            _yield = &yield;
            set_this_generator();
            complete(fn());
        });
    }
    
    template<typename Y, typename R>
    Generator<Y, R>::~Generator() {
        delete _resume;
    }
    
    template<typename Y, typename R>
    auto Generator<Y, R>::set_this_generator() -> void {
        this_generator = this;
    }
    
    template<typename Y, typename R>
    auto Generator<Y, R>::resume() -> Y {
        auto ret = _resume->get();
        set_this_generator();
        (*_resume)();
        return ret;
    }
    
    template<typename Y, typename R>
    auto Generator<Y, R>::yield(Y value) -> void {
        (*_yield)(value);
    }
    
    template<typename Y, typename R>
    auto Generator<Y, R>::complete(R ret) -> void {
        _result = ret;
    }
    
    template<typename Y, typename R>
    auto Generator<Y, R>::is_complete() -> bool {
        return !(*_resume);
    }
    
    template<typename Y, typename R>
    auto Generator<Y, R>::result() -> R & {
        return _result;
    }
}
#endif //SILVER_IO_GENERATOR_HPP
