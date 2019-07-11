load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository", "new_git_repository")
new_git_repository(
    name = "uvw",
    build_file = "uvw.BUILD",
    remote = "https://github.com/skypjack/uvw.git",
    tag = "v1.17.1_libuv-v1.29",
)

new_git_repository(
    name = "libuv",
    build_file = "libuv.BUILD",
    remote = "https://github.com/libuv/libuv.git",
    tag = "v1.29.1",
)

new_git_repository(
    name = "concurrentqueue",
    build_file = "concurrentqueue.BUILD",
    remote = "https://github.com/cameron314/concurrentqueue.git",
    tag = "v1.0.0-beta",
)

git_repository(
    name = "gtest",
    remote = "https://github.com/google/googletest.git",
    tag = "release-1.8.1",
)

new_git_repository(
    name = "spdlog",
    build_file = "spdlog.BUILD",
    remote = "https://github.com/gabime/spdlog.git",
    tag = "v1.3.1",
)
