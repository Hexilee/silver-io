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
    template<class T>
    class Poll {
        using Output = T;
        Output value;
        bool complete;
      public:
        explicit Poll(const Output value) : value(value), complete(true) {};
        static auto pending() -> Poll;
        auto is_complete() -> bool;
        auto get() -> Output;
    };
    
    
    template<class T>
    class Future {
      public:
        auto wait() -> T;
        virtual auto poll(const shared_ptr<Context> ctx) -> Poll<T>;
    };
}
#endif //SILVER_IO_FUTURE_HPP
