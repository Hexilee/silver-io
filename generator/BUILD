cc_library(
    name = "sio_generator",
    hdrs = glob([
        "*.hpp",
    ]),
    includes = [
        ".",
    ],
    copts = [
        "-std=c++17"
    ],
    visibility = ["//visibility:public"],
)

cc_binary(
    name = "boost_coroutine",
    srcs = glob([
        "example/boost_coroutine.*",
    ]),
    linkopts = [
        "-lboost_coroutine"
    ],
    copts = [
        "-std=c++17"
    ],
)

cc_binary(
    name = "fib",
    srcs = glob([
        "example/fib.*",
    ]),
    deps = [
        "sio_generator"
    ],
    linkopts = [
        "-lboost_coroutine"
    ],
    copts = [
        "-std=c++17"
    ],
)

cc_test(
    name = "test",
    size = "small",
    srcs = glob([
        "test/*.cpp",
    ]),
    deps = [
        "@gtest//:gtest_main",
        "sio_generator"
    ],
    linkopts = [
        "-lboost_coroutine"
    ],
    copts = [
        "-std=c++17"
    ],
)

