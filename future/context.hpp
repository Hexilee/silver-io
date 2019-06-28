/*
 * Created by 李晨曦 on 2019-06-28.
 */

#ifndef SILVER_IO_CONTEXT_HPP
#define SILVER_IO_CONTEXT_HPP
#include <memory>
#include <exception>
#include <functional>

namespace future {
    using namespace future;
    using std::shared_ptr;
    using std::make_shared;
    
    class Context;
    
    class FuncContext;
    
    extern thread_local shared_ptr<Context> ThreadLocalContext;
    
    class Context {
      public:
        virtual auto wake() -> void;
        virtual ~Context() = 0;
    };
    
    class FuncContext: public Context {
        std::function<auto() -> void> waker;
      public:
        FuncContext(std::function<auto() -> void> waker);
        auto wake() -> void override;
    };
}
#endif //SILVER_IO_CONTEXT_HPP
