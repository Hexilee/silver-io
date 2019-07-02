/*
 * Created by 李晨曦 on 2019-07-02.
 */

#ifndef SILVER_IO_STREAM_HPP
#define SILVER_IO_STREAM_HPP
namespace sio::future {
    enum class FlowStatus {
        Pending,
        Continue,
        Break,
    };
    
    template<typename T>
    class Flow {
        T *value;
        FlowStatus stat;
      public:
        using Status = FlowStatus;
        using Output = T;
        
        Flow() : value(nullptr), stat(Status::Pending) {};
        Flow(Status stat) : value(nullptr), stat(stat) {};
        explicit Flow(Output &value) : value(&value), stat(Status::Continue) {};
        auto operator=(Flow &&other) noexcept -> Flow &;
        auto status() -> const Status &;
        auto get() -> Output &&;
    };
    
    template<typename T>
    auto Flow<T>::status() -> const Poll::Status & {
        return stat;
    }
    
    template<typename T>
    auto Flow<T>::get() -> Output && {
        return std::move(*value);
    }
    
    template<typename T>
    auto Flow<T>::operator=(Poll &&other) noexcept -> Poll & {
        value = other.value;
        stat = other.stat;
        return *this;
    }
}
#endif //SILVER_IO_STREAM_HPP
