/*
 * Created by 李晨曦 on 2019-07-04.
 */

#ifndef SILVER_IO_FILE_HPP
#define SILVER_IO_FILE_HPP
#include "sio/sio.hpp"
#include "uvw.hpp"
#include "concurrentqueue.h"
#include "future/future.hpp"
#include <memory>

namespace sio::fs {
    using sio::future::Future;
    using moodycamel::ConcurrentQueue;
    using std::unique_ptr;
    using uvw::Flags;
    using uvw::ErrorEvent;
    using OpenFlags = uvw::details::UVFileOpenFlags;
    
    class File {
      public:
        uvw::FileReq &req;
        explicit File(uvw::FileReq &req);
    };
    
    class OpenFileFuture: public Future<Result<File>> {
        const char *path;
        Flags<OpenFlags> flags;
        int mode;
        bool is_register;
        Result<File> file_result;
        ConcurrentQueue<Result<File>> queue;
        auto poll() -> future::Poll<Result<File>> override;
      public:
        explicit OpenFileFuture(const char *path, Flags<OpenFlags> &&flags, int mode);
    };
    
    auto open(const char *, Flags<OpenFlags> &&flags = OpenFlags::RDONLY, int mode = S_IRUSR) -> OpenFileFuture;
}
#endif //SILVER_IO_FILE_HPP
