/*
 * Created by 李晨曦 on 2019-07-02.
 */

#ifndef SILVER_IO_STREAM_HPP
#define SILVER_IO_STREAM_HPP
#include "future/future.hpp"

namespace sio::future {
    enum class FlowStatus {
        Pending,
        Continue,
        Break,
    };
    
    template<typename T>
    class Flow: public StatusBox<T, FlowStatus> {
        using Super = StatusBox<T, FlowStatus>;
        
        explicit Flow(FlowStatus stat) : Super(nullptr, stat) {};
      public:
        Flow() : Flow(FlowStatus::Pending) {};
        
        explicit Flow(T &value) : Super(&value, FlowStatus::Continue) {};
        
        static auto Break() -> Flow {
            return Flow(FlowStatus::Break);
        }
    };
}
#endif //SILVER_IO_STREAM_HPP
