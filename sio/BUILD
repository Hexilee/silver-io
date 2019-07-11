cc_library(
    name = "sio",
    srcs = glob([
        "*.cpp",
        "executor/*.cpp",
        "fs/*.cpp",
    ]),
    hdrs = glob([
        "*.hpp",
        "executor/*.hpp",
        "fs/*.hpp",
    ]),
    includes = [
        ".",
        "executor/*.hpp",
        "fs/*.hpp",
    ],
    deps = [
        "//future:sio_future",
        "//coroutine:sio_coroutine",
        "@uvw//:uvw",
        "@concurrentqueue//:concurrentqueue",
        "@spdlog//:spdlog",
    ],
    copts = [
        "-std=c++17"
    ],
    visibility = ["//visibility:public"],
)


cc_binary(
    name = "block_on",
    srcs = glob([
        "example/block_on.cpp",
    ]),
    deps = [
        "//sio:sio",
    ],
    copts = [
        "-std=c++17"
    ],
    linkopts = [
        "-lboost_coroutine"
    ],
)

cc_binary(
    name = "uvw_read_file",
    srcs = glob([
        "example/uvw_read_file.cpp",
    ]),
    deps = [
        "@uvw//:uvw",
        "@spdlog//:spdlog",
    ],
    copts = [
        "-std=c++17"
    ],
)
