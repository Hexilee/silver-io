cc_library(
    name = "generator",
    srcs = glob([
        "*.cpp",
    ]),
    hdrs = glob([
        "*.hpp",
    ]),
    includes = [
        ".",
    ],
    linkopts = [
        "-lboost_coroutine"
    ],
    copts = [
        "-std=c++17"
    ],
    linkstatic = 1,
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
)

cc_binary(
    name = "fib",
    srcs = glob([
        "example/fib.*",
    ]),
    deps = [
        "generator"
    ],
    copts = [
        "-std=c++17"
    ],
)

