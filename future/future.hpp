/*
 * Created by 李晨曦 on 2019-06-25.
 */

#ifndef SILVER_IO_FUTURE_HPP
#define SILVER_IO_FUTURE_HPP
#include <functional>
#include <memory>
#include "context.hpp"
namespace future {
    using std::shared_ptr;
    template<class Output>
    class Poll {
        Output value;
        bool complete;
      public:
        explicit Poll(const Output value) : Output(value), complete(true) {};
        static auto pending() -> Poll;
        auto is_complete() -> bool;
        auto get() -> Output;
    };
    
    
    template<class Output>
    class Future {
      public:
        auto wait() -> Output;
        virtual auto poll(const shared_ptr<Context> ctx) -> Poll<Output>;
    };
}
#endif //SILVER_IO_FUTURE_HPP
