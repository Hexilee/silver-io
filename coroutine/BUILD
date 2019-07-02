cc_library(
    name = "sio_coroutine",
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
        "//future:sio_future",
        "//generator:sio_generator"
    ],
    copts = [
        "-std=c++17"
    ],
    visibility = ["//visibility:public"],
)

cc_binary(
    name = "await_ok",
    srcs = glob([
        "example/await_ok.*",
    ]),
    includes = [
        "example/",
    ],
    copts = [
        "-std=c++17"
    ],
    deps = [
        "//coroutine:sio_coroutine"
    ]
)

cc_binary(
    name = "async",
    srcs = glob([
        "example/async.*",
    ]),
    includes = [
        "example/",
    ],
    copts = [
        "-std=c++17"
    ],
    deps = [
        "//coroutine:sio_coroutine"
    ],
    linkopts = [
        "-lboost_coroutine"
    ],
)

cc_test(
    name = "coroutine_sample",
    size = "small",
    srcs = glob([
        "test/*.cpp"
    ]),
    copts = [
        "-std=c++17"
    ],
    deps = [
        "@gtest//:gtest_main",
         "//coroutine:sio_coroutine"
    ],
    linkopts = [
        "-lboost_coroutine"
    ],
)
