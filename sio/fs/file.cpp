/*
 * Created by 李晨曦 on 2019-07-04.
 */

#include "file.hpp"
#include "spdlog/spdlog.h"

using namespace uvw;
using namespace sio::fs;
using namespace sio::future;
using std::make_unique;

auto OpenFileFuture::poll() -> Poll<Result<File>> {
    if (!is_register) {
        auto open_resource = EventLoop->resource<FileReq>();
        open_resource->once<ErrorEvent>([this, context = future::ThreadLocalContext](const ErrorEvent &event, FileReq &file) {
            spdlog::error("open_resource on ErrorEvent {:s}", event.what());
            queue.enqueue(Result<File>(unique_ptr<File>(nullptr), event.code()));
            context->wake();
        });
        open_resource->once<FsEvent<details::UVFsType::OPEN>>([this, context = future::ThreadLocalContext](const FsEvent<details::UVFsType::OPEN> &event,
        uvw::FileReq &file) {
            spdlog::debug("open_resource on FsEvent<details::UVFsType::OPEN> {:s}", event.path);
            queue.enqueue(Result<File>(make_unique<File>(file), 0));
            context->wake();
        });
        open_resource->open(path, flags, mode);
        is_register = true;
        spdlog::debug("OpenFileFuture poll register: open {0}", path);
    }
    if (queue.try_dequeue(file_result) && file_result.is_ok()) {
        spdlog::debug("OpenFileFuture poll ready");
        return Poll(std::move(file_result));
    } else {
        spdlog::debug("OpenFileFuture poll pending");
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
