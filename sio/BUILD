cc_library(
    name = "sio",
    srcs = glob([
        "*.cpp",
        "executor/*.cpp",
    ]),
    hdrs = glob([
        "*.hpp",
        "executor/*.hpp",
    ]),
    includes = [
        ".",
        "executor/*.hpp",
    ],
    deps = [
        "//future:sio_future",
        "@uvw//:uvw",
    ],
    copts = [
        "-std=c++17"
    ],
)

