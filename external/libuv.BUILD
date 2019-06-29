genrule(
    name = "build_libuv",
    srcs = glob(["**"]),
    outs = ["build/libuv_a.a"],
    cmd = "mkdir -p build ; cd build" +
          "&& cmake ../.." +
          "&& cmake --build .",
)


cc_library(
    name = "uv",
    srcs = ["build/libuv_a.a"],
    hdrs = glob([
        "include/*.h",
        "include/uv/*.h",
    ]),
    includes = [
        "include/",
    ],
    visibility = ["//visibility:public"],
)
