/*
 * Created by 李晨曦 on 2019-06-25.
 */

#ifndef SILVER_IO_FUTURE_HPP
#define SILVER_IO_FUTURE_HPP
#include <functional>
#include <memory>
#include "context.hpp"
#include "blockingconcurrentqueue.h"

namespace sio::future {
    using std::shared_ptr;
    using moodycamel::BlockingConcurrentQueue;
    
    template<typename T>
    class Poll {
        T &value;
        bool complete;
      public:
        using Output = T;
        
        explicit Poll(Output &value) : value(value), complete(true) {};
        auto operator=(Poll &&other) noexcept -> Poll &;
        static auto pending() -> Poll;
        auto is_complete() -> bool;
        auto get() -> const Output &;
    };
    
    template<typename T>
    class Future {
      public:
        auto wait() -> T;
        virtual auto poll() -> Poll<T> = 0;
        virtual ~Future() = default;
    };
    
    template<typename T>
    class FutureOk: public Future<T> {
        T value;
      public:
        explicit FutureOk(const T &value);
        explicit FutureOk(T &&value);
        auto poll() -> Poll<T> override;
    };
    
    template<typename T>
    class CounterFuture: public Future<T> {
        T value;
        uint64_t counter;
        uint64_t ceiling;
      public:
        CounterFuture(T value, uint64_t ceiling) : value(value), counter(0), ceiling(ceiling) {}
        auto poll() -> Poll<T> override;
    };
    
    template<typename T>
    auto Poll<T>::pending() -> Poll {
        Poll poll;
        poll.complete = false;
        return poll;
    }
    
    template<typename T>
    auto Poll<T>::is_complete() -> bool {
        return complete;
    }
    
    template<typename T>
    auto Poll<T>::get() -> const Output & {
        return value;
    }
    
    template<typename T>
    auto Poll<T>::operator=(Poll &&other) noexcept -> Poll & {
        value = other.value;
        complete = other.complete;
        return *this;
    }
    
    template<typename T>
    auto Future<T>::wait() -> T {
        class Signal;
        BlockingConcurrentQueue<Signal> channel;
        ThreadLocalContext = make_shared<FuncContext>([&channel]() {
            channel.enqueue(Signal());
        });
        auto poll_result = Poll<T>::pending();
        Signal signal;
        while (!poll_result.is_complete()) {
            channel.wait_dequeue(&signal);
            poll_result = poll();
        }
        return poll_result.get();
    }
    
    template<typename T>
    auto FutureOk<T>::poll() -> Poll<T> {
        return Poll(value);
    }
    
    template<typename T>
    FutureOk<T>::FutureOk(T &&value):value(value) {}
    
    template<typename T>
    FutureOk<T>::FutureOk(const T &value):value(value) {}
    
    template<typename T>
    auto CounterFuture<T>::poll() -> Poll<T> {
        return counter++ >= ceiling ? Poll(value) : Poll<T>::pending();
    }
}
#endif //SILVER_IO_FUTURE_HPP
