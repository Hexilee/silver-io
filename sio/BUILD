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
        "@uvw//:uvw",
        "@concurrentqueue//:concurrentqueue",
    ],
    copts = [
        "-std=c++17"
    ],
)

