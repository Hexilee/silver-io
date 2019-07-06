/*
 * Created by 李晨曦 on 2019-06-25.
 */

#ifndef SILVER_IO_SIO_HPP
#define SILVER_IO_SIO_HPP
#include "future/future.hpp"
#include <thread>
#include "uvw.hpp"

namespace sio {
    using std::thread;
    using std::shared_ptr;
    using std::unique_ptr;
    using std::make_unique;
    using uvw::ErrorEvent;
    extern thread_local shared_ptr<uvw::Loop> EventLoop;
    auto init_event_loop() -> std::unique_ptr<thread>;
    
    template<typename T>
    class Result {
        unique_ptr<T> value;
        int status_code;
      public:
        Result(unique_ptr<T> &&value, int status_code);
        Result(const Result &);
        auto operator=(Result &&) noexcept -> Result &;
        auto operator=(const Result &) noexcept -> Result &;
        auto get_value() const -> const unique_ptr<T> &;
        auto get_status() const -> ErrorEvent;
        auto is_ok() const -> bool;
    };
    
    template<typename T>
    Result<T>::Result(unique_ptr<T> &&value, int status_code)
    : value(std::forward<unique_ptr<T>>(value)), status_code(status_code) {}
    
    template<typename T>
    Result<T>::Result(const Result &other)
    : value(make_unique<T>(*other.value)), status_code(other.status_code) {
    
    }
    
    template<typename T>
    auto Result<T>::operator=(Result &&other) noexcept -> Result & {
        this->value = std::move(other.value);
        this->status_code = other.status_code;
        return *this;
    }
    
    template<typename T>
    auto Result<T>::operator=(const Result &other) noexcept -> Result & {
        this->value = make_unique<T>(*other.value);
        this->status_code = other.status_code;
        return *this;
    }
    
    template<typename T>
    auto Result<T>::get_value() const -> const unique_ptr<T> & {
        return value;
    }
    
    template<typename T>
    auto Result<T>::get_status() const -> ErrorEvent {
        return ErrorEvent(status_code);
    }
    
    template<typename T>
    auto Result<T>::is_ok() const -> bool {
        return status_code == 0;
    }
}
#endif //SILVER_IO_SIO_HPP
