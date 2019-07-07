/*
 * Created by 李晨曦 on 2019-06-25.
 */

#ifndef SILVER_IO_FUTURE_HPP
#define SILVER_IO_FUTURE_HPP
#include <functional>
#include <memory>
#include <iostream>
#include "future/context.hpp"
#include "blockingconcurrentqueue.h"

namespace sio::future {
    using std::shared_ptr;
    using moodycamel::BlockingConcurrentQueue;
    
    template<typename T, typename S>
    class StatusBox {
        // must be valid or nullptr
        T *value;
        S stat;
      public:
        using Status = S;
        using Output = T;
        StatusBox(T *value, S stat);
        auto status() const -> const Status &;
        auto get() const -> Output &;
        
        friend auto operator<<(std::ostream &os, const StatusBox &box) -> std::ostream & {
            if (box.value == nullptr) {
                os << "value: null, stat: " << box.stat;
            } else {
                os << "value: " << *box.value << " stat: " << box.stat;
            }
            return os;
        };
        
    };
    
    enum class PollStatus {
        Pending,
        Ready,
    };
    
    template<typename T>
    class Poll: public StatusBox<T, PollStatus> {
        using Super = StatusBox<T, PollStatus>;
      public:
        Poll() : Super(nullptr, PollStatus::Pending) {};
        
        explicit Poll(T &value) : Super(&value, PollStatus::Ready) {};
    };
    
    template<typename T>
    class Future {
      public:
        auto wait() -> T &;
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
    
    template<typename T, typename S>
    auto StatusBox<T, S>::status() const -> const Status & {
        return stat;
    }
    
    template<typename T, typename S>
    auto StatusBox<T, S>::get() const -> Output & {
        return *value;
    }
    
    template<typename T, typename S>
    StatusBox<T, S>::StatusBox(T *value, S stat):value(value), stat(stat) {}
    
    template<typename T>
    auto Future<T>::wait() -> T & {
        class Signal;
        BlockingConcurrentQueue<Signal> channel;
        ThreadLocalContext = make_shared<FuncContext>([&channel]() {
            channel.enqueue(Signal());
        });
        auto poll_result = poll();
        auto signal = Signal();
        while (poll_result.status() == PollStatus::Pending) {
            channel.wait_dequeue(signal);
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
        return counter++ >= ceiling ? Poll(value) : Poll<T>();
    }
}
#endif //SILVER_IO_FUTURE_HPP
