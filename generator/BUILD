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
    linkstatic = 1,
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
)

