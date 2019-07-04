/*
 * Created by 李晨曦 on 2019-07-02.
 */

#ifndef SILVER_IO_CO_FUTURE_HPP
#define SILVER_IO_CO_FUTURE_HPP
#include <functional>
#include "future/future.hpp"
#include "coroutine/coroutine.hpp"

namespace sio::coroutine {
    using sio::future::Future;
    using sio::future::Poll;
    using std::function;
    
    template<typename Fn>
    class CoFuture;
    
    template<typename Fn>
    using Ret = typename std::result_of<Fn(void)>::type;
    
    template<typename Fn>
    class CoFuture
    : public Future<Ret<Fn>>, Coroutine<Ret<Fn>> {
      public:
        explicit CoFuture(Fn &&fn);
        auto poll() -> Poll<Ret<Fn>> override;
    };
    
    template<typename Fn>
    auto CoFuture<Fn>::poll() -> Poll<Ret<Fn>> {
        this->resume();
        return this->is_complete() ? Poll(this->result()) : Poll<Ret<Fn>>();
    }
    
    template<typename Fn>
    CoFuture<Fn>::CoFuture(Fn &&fn): Coroutine<Ret<Fn>>(static_cast<std::function<Ret<Fn>()>>([=] {
        Coroutine<Ret<Fn>>::yield();
        return fn();
    })) {}
}
#endif //SILVER_IO_CO_FUTURE_HPP
