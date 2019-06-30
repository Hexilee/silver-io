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
    
    template<typename T>
    class Poll {
        const T &value;
        bool complete;
      public:
        using Output = T;
        
        explicit Poll(const Output &value) : value(value), complete(true) {};
        auto operator=(Poll &&other) noexcept -> Poll &;
        static auto pending() -> Poll;
        auto is_complete() -> bool;
        auto get() -> const Output &;
    };
    
    
    template<typename T>
    class Future {
      public:
        auto wait() -> T;
        virtual auto poll(shared_ptr<Context> ctx) -> Poll<T>;
    };
    
    template<typename T>
    class FutureOk: public Future<T> {
        T value;
      public:
        FutureOk(const T &value);
        FutureOk(T &&value);
        auto poll(shared_ptr<Context> ctx) -> Poll<T> override;
    };
}
#endif //SILVER_IO_FUTURE_HPP
