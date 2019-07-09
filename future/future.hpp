/*
 * Created by 李晨曦 on 2019-06-25.
 */

#ifndef SILVER_IO_FUTURE_HPP
#define SILVER_IO_FUTURE_HPP
#include <functional>
#include <memory>
#include <iostream>
#include <variant>
#include "future/context.hpp"
#include "blockingconcurrentqueue.h"

namespace sio::future {
    using std::shared_ptr;
    using std::unique_ptr;
    using moodycamel::BlockingConcurrentQueue;
    
    template<typename T, typename S>
    class StatusBox {
        T value;
        S stat;
      public:
        using Status = S;
        using Output = T;
        explicit StatusBox(S stat); // T need default constructor
        StatusBox(T &&value, S stat);
        auto status() const -> const Status &;
        auto release() -> Output &&;
        
        friend auto operator<<(std::ostream &os, const StatusBox &box) -> std::ostream & {
            os << "value: " << box.value << " stat: " << box.stat;
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
        Poll() : Super(PollStatus::Pending) {};
        
        explicit Poll(T &&value) : Super(std::forward<T>(value), PollStatus::Ready) {};
    };
    
    template<typename T>
    class Future {
      public:
        auto wait() -> T &&;
        virtual auto poll() -> Poll<T> = 0;
        virtual ~Future() = default;
    };
    
    template<typename T>
    class FutureOk: public Future<T> {
        T value;
      public:
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
    auto StatusBox<T, S>::release() -> Output && {
        return std::move(value);
    }
    
    template<typename T, typename S>
    StatusBox<T, S>::StatusBox(T &&value, S stat):value(value), stat(stat) {}
    
    template<typename T, typename S>
    StatusBox<T, S>::StatusBox(S stat): stat(stat) {}
    
    template<typename T>
    auto Future<T>::wait() -> T && {
        BlockingConcurrentQueue<std::monostate> channel;
        ThreadLocalContext = make_shared<FuncContext>([&channel]() {
            channel.enqueue(std::monostate());
        });
        auto poll_result = poll();
        auto signal = std::monostate();
        while (poll_result.status() == PollStatus::Pending) {
            channel.wait_dequeue(signal);
            poll_result = poll();
        }
        return poll_result.release();
    }
    
    template<typename T>
    auto FutureOk<T>::poll() -> Poll<T> {
        return Poll(std::move(value));
    }
    
    template<typename T>
    FutureOk<T>::FutureOk(T &&value):value(value) {}
    
    template<typename T>
    auto CounterFuture<T>::poll() -> Poll<T> {
        return counter++ >= ceiling ? Poll(std::move(value)) : Poll<T>();
    }
}
#endif //SILVER_IO_FUTURE_HPP
