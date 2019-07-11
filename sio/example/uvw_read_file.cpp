/*
 * Created by 李晨曦 on 2019-07-11.
 */

#include "uvw.hpp"
#include "spdlog/spdlog.h"

using namespace uvw;
using OpenFlags = uvw::details::UVFileOpenFlags;

auto main(int argc, char *argv[]) -> int {
    auto loop = Loop::create();
    spdlog::set_level(spdlog::level::debug);
    auto file_resource = loop->resource<FileReq>();
    file_resource->once<ErrorEvent>([=](const ErrorEvent &event, FileReq &file) {
        spdlog::error("open {0:s} on ErrorEvent: {1:s}", argv[1], event.what());
    });
    file_resource->once<FsEvent<details::UVFsType::OPEN>>([](const FsEvent<details::UVFsType::OPEN> &event,
    uvw::FileReq &file) {
        spdlog::debug("file {:s} opened", event.path);
        file.once<FsEvent<details::UVFsType::STAT>>([](const FsEvent<details::UVFsType::STAT> &event,
        uvw::FileReq &file) {
            spdlog::debug("file {0:s} stat, size: {1:d}", event.path, event.stat.st_size);
            file.once<FsEvent<details::UVFsType::READ>>([](const FsEvent<details::UVFsType::READ> &event,
            uvw::FileReq &file) {
                spdlog::info("file contents: {:s}", event.data.get());
            });
            file.once<ErrorEvent>([](const ErrorEvent &event, FileReq &file) {
                spdlog::error("read on ErrorEvent: {:s}", event.what());
            });
            file.read(0, event.stat.st_size);
        });
        file.once<ErrorEvent>([](const ErrorEvent &event, FileReq &file) {
            spdlog::error("stat on ErrorEvent: {:s}", event.what());
        });
        file.stat();
    });
    file_resource->open(argv[1], OpenFlags::RDONLY, S_IRUSR);
    loop->run();
    return 0;
}