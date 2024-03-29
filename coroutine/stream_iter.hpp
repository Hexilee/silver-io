/*
 * Created by 李晨曦 on 2019-07-02.
 */

#ifndef SILVER_IO_STREAM_ITER_HPP
#define SILVER_IO_STREAM_ITER_HPP
#include <iterator>
#include <memory>
#include "future/stream.hpp"
#include "coroutine/coroutine.hpp"

namespace sio::coroutine {
    using sio::future::Stream;
    using sio::future::Flow;
    using sio::future::FlowStatus;
    using std::unique_ptr;
    
    template<typename T>
    class StreamIter {
        Stream<T> &stream;
      public:
        using Stream = Stream<T>;
        using Flow = Flow<T>;
        explicit StreamIter(Stream &stream);
        static auto await_flow(Stream *stream) -> Flow &&;
        
        class iterator;
        
        auto begin() -> iterator;
        auto end() -> iterator;
    };
    
    template<typename T>
    auto StreamIter<T>::begin() -> StreamIter::iterator {
        return StreamIter::iterator(&stream);
    }
    
    template<typename T>
    auto StreamIter<T>::end() -> StreamIter::iterator {
        return StreamIter::iterator(&stream, Flow::Break());
    }
    
    template<typename T>
    auto StreamIter<T>::await_flow(Stream *stream) -> Flow && {
        auto flow = stream->flow();
        while (flow.status() == FlowStatus::Pending) {
            Coroutine<T>::yield();
            flow = stream->flow();
        }
        return std::move(flow);
    }
    
    template<typename T>
    class StreamIter<T>::iterator: public std::iterator<std::input_iterator_tag, T, ptrdiff_t, T *, T &&> {
        Stream *stream;
        Flow current_flow;
      public:
        explicit iterator(Stream *stream) : stream(stream), current_flow(await_flow(stream)) {
        }
        
        iterator(Stream *stream, Flow &&flow) : stream(stream), current_flow(flow) {}
        
        auto operator++() -> iterator & {
            current_flow = await_flow(stream);
            return *this;
        }
        
        auto operator++(int) -> const iterator {
            iterator retval = *this;
            ++(*this);
            return retval;
        }
        
        auto operator==(const iterator &other) const { return current_flow.status() == other.current_flow.status(); }
        
        auto operator!=(const iterator &other) const { return !(*this == other); }
        
        auto operator*() -> T && { return current_flow.release(); }
    };
    
    template<typename T>
    StreamIter<T>::StreamIter(Stream &stream):stream(stream) {}
}
#endif //SILVER_IO_STREAM_ITER_HPP
