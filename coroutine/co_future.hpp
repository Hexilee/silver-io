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
    template <typename T>
    class CoFuture: public Future<T>, Coroutine<T> {
      public:
        explicit CoFuture(std::function<auto () -> T>&& fn);
        auto poll() -> Poll<T> override;
    };
    
    template<typename T>
    auto CoFuture<T>::poll() -> Poll<T> {
        this->resume();
        return this->is_complete() ? Poll(this->result()) : Poll<T>();
    }
    
    template<typename T>
    CoFuture<T>::CoFuture(std::function<auto () -> T>&& fn): Coroutine<T>(std::move(fn)) {}
}
#endif //SILVER_IO_CO_FUTURE_HPP
