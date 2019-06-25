/*
 * Created by 李晨曦 on 2019-06-25.
 */

#ifndef SILVER_IO_FUTURE_HPP
#define SILVER_IO_FUTURE_HPP

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

template<class Output>
class Future {
  public:
    virtual auto poll(const Context &ctx) -> Poll<Output>;
};

#endif //SILVER_IO_FUTURE_HPP
