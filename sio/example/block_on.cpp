/*
 * Created by 李晨曦 on 2019-07-07.
 */
#include "sio/executor/exec.hpp"
#include "sio/fs/file.hpp"
#include "spdlog/spdlog.h"

auto main() -> int {
    spdlog::set_level(spdlog::level::debug);
    auto file = block_on sio::fs::open(".gitignore");
    if (!file.is_ok()) {
        auto status = file.get_status();
        spdlog::error("open file fail: {:s}", status.what());
        return status.code();
    }
    auto stat = file.get_value()->req.statSync();
    if (!stat.first) {
        spdlog::error("file stat fail");
        return 0;
    }
    auto content = file.get_value()->req.readSync(0, stat.second.st_size);
    if (!content.first) {
        spdlog::error("file read fail");
        return 0;
    }
    
    spdlog::info("file contents: {:s}", content.second.first.get());
    return 0;
}