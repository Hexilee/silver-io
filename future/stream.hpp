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
    
    std::ostream &operator<<(std::ostream &os, const FlowStatus &stat);
    
    template<typename T>
    class Flow: public StatusBox<T, FlowStatus> {
        using Super = StatusBox<T, FlowStatus>;
        
        explicit Flow(FlowStatus status) : Super(status) {};
      public:
        explicit Flow() : Flow(FlowStatus::Pending) {};
        
        explicit Flow(T &&value) : Super(std::forward<T>(value), FlowStatus::Continue) {};
        
        static auto Break() { return Flow(FlowStatus::Break); }
    };
    
    template<typename T>
    class Stream {
      public:
        using Flow = Flow<T>;
        virtual auto flow() -> Flow = 0;
        virtual ~Stream() = default;
    };
    
    template<int64_t From, int64_t To, int64_t Diff = 1>
    class RangeStream: public Stream<int64_t> {
        int64_t counter;
      public:
        RangeStream();
        auto flow() -> Flow override;
    };
    
    template<int64_t From, int64_t To, int64_t Diff>
    auto RangeStream<From, To, Diff>::flow() -> Flow {
        counter++;
        if (counter >= To) {
            return Flow::Break();
        }
        if ((counter - From) % Diff == 0) {
            return Flow(std::move(counter));
        }
        return Flow();
    }
    
    template<int64_t From, int64_t To, int64_t Diff>
    RangeStream<From, To, Diff>::RangeStream():counter(From - 1) {}
}
#endif //SILVER_IO_STREAM_HPP
