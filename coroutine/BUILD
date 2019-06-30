cc_library(
    name = "coroutine",
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
        "//future:future",
        "//generator:generator"
    ],
    copts = [
        "-std=c++17"
    ],
    visibility = ["//visibility:public"],
)

cc_binary(
    name = "fibonacci",
    srcs = glob([
        "example/fibonacci.*",
    ]),
    includes = [
        "example/",
    ],
    copts = [
        "-std=c++17"
    ],
    deps = [
        "//generator:generator"
    ]
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
        "//coroutine:coroutine"
    ]
)
