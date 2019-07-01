cc_library(
    name = "sio_future",
    srcs = glob([
        "*.cpp",
    ]),
    hdrs = glob([
        "*.hpp",
    ]),
    includes = [
        ".",
    ],
    deps = [
        "@concurrentqueue//:concurrentqueue",
    ],
    copts = [
        "-std=c++17"
    ],
    visibility = ["//visibility:public"],
    linkstatic = 1,
)
