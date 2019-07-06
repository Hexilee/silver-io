/*
 * Created by 李晨曦 on 2019-07-04.
 */

#include "file.hpp"

using namespace uvw;
using namespace sio::fs;
using namespace sio::future;
using std::make_unique;

auto OpenFileFuture::poll() -> Poll<Result<File>> {
    if (!is_register) {
        auto open_resource = EventLoop->resource<FileReq>();
        open_resource->once<ErrorEvent>([this](const ErrorEvent &event, FileReq &file) {
            queue.enqueue(Result<File>(unique_ptr<File>(nullptr), event.code()));
            future::ThreadLocalContext->wake();
        });
        open_resource->once<FsEvent<details::UVFsType::OPEN>>([this](const FsEvent<details::UVFsType::OPEN> &,
        uvw::FileReq &file) {
            queue.enqueue(Result<File>(make_unique<File>(file), 0));
            future::ThreadLocalContext->wake();
        });
        open_resource->open(path, flags, mode);
        is_register = true;
    }
    if (queue.try_dequeue(file_result)) {
        return Poll(file_result);
    } else {
        return Poll<Result<File>>();
    }
}

OpenFileFuture::OpenFileFuture(const char *path, Flags<OpenFlags> &&flags, int mode)
: path(path), flags(flags), mode(mode), is_register(false),
  file_result(Result<File>(unique_ptr<File>(nullptr), 0)),
  queue(ConcurrentQueue<Result<File>>(1)) {}

auto sio::fs::open(const char *path, Flags<OpenFlags> &&flags, int mode) -> OpenFileFuture {
    return OpenFileFuture(path, std::forward<Flags<OpenFlags>>(flags), mode);
}

File::File(FileReq &req) : req(req) {}
