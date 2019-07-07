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
    ],
    copts = [
        "-std=c++17"
    ],
    linkopts = [
        "-lboost_coroutine"
    ],
)

