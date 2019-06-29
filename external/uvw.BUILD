cc_library(
    name = "uvw",
    hdrs = glob([
        "src/*.hpp",
        "src/uvw/*.hpp",
    ]),
    includes = [
        "src/",
    ],
    deps = [
        "@libuv//:uv",
    ],
    visibility = ["//visibility:public"],
)
