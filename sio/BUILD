cc_library(
    name = "sio",
    srcs = glob([
        "*.cpp",
        "thread_local/*.cpp",
    ]),
    hdrs = glob([
        "*.hpp",
        "thread_local/*.hpp",
    ]),
    includes = [
        ".",
        "thread_local",
    ],
    deps = [
        "//future:future",
        "@uvw//:uvw",
    ],
)

