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
        "//future:future",
        "@uvw//:uvw",
    ],
)

