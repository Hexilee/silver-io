/*
 * Created by 李晨曦 on 2019-06-25.
 */

#ifndef SILVER_IO_FUTURE_HPP
#define SILVER_IO_FUTURE_HPP
#include <functional>
namespace future {
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
    
    class Context {
      public:
        virtual auto wake() -> void;
    };
    
    class FuncContext: public Context {
        std::function<auto() -> void> waker;
      public:
        FuncContext(std::function<auto() -> void> waker);
        auto wake() -> void override;
    };
    
    template<class Output>
    class Future {
      public:
        virtual auto poll(const Context &ctx) -> Poll<Output>;
    };
}
#endif //SILVER_IO_FUTURE_HPP
