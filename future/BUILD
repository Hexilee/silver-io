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

cc_test(
    name = "future_test",
    size = "small",
    srcs = glob([
        "test/*.cpp"
    ]),
    copts = [
        "-std=c++17"
    ],
    deps = [
        "@gtest//:gtest_main",
         "//future:sio_future"
    ],
)
