/*
 * Created by 李晨曦 on 2019-07-07.
 */
#include "sio/executor/exec.hpp"
#include "sio/fs/file.hpp"
#include <iostream>

auto main() -> int {
    auto file = block_on sio::fs::open(".gitignore");
    if (!file.is_ok()) {
        auto status = file.get_status();
        std::cout << status.what() << std::endl;
        return status.code();
    }
    auto stat = file.get_value()->req.statSync();
    if (!stat.first) {
        std::cout << "file stat fail" << std::endl;
        return 0;
    }
    auto content = file.get_value()->req.readSync(0, stat.second.st_size);
    if (!content.first) {
        std::cout << "file read fail" << std::endl;
        return 0;
    }
    
    std::cout << content.second.first << std::endl;
    return 0;
}