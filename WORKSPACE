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