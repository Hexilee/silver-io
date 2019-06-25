/*
 * Created by 李晨曦 on 2019-06-25.
 */

#ifndef SILVER_IO_FUTURE_HPP
#define SILVER_IO_FUTURE_HPP

template<class Output>
class Future {
  public:
    virtual auto poll() -> Output;
};

#endif //SILVER_IO_FUTURE_HPP
