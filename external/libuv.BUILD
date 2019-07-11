UV_COMMON_SOURCES = glob(["src/*.c", "src/*.h"])
UV_COMMON_HEADERS = [
    "include/uv.h",
    "include/uv/errno.h",
    "include/uv/threadpool.h",
    "include/uv/version.h",
    "include/uv/tree.h",
]

UV_WIN_SOURCES = UV_COMMON_SOURCES + glob(["src/win/*.c", "src/win/*.h"])
UV_WIN_HEADERS = UV_COMMON_HEADERS + [
    "include/uv/win.h",
]

UV_UNIX_SOURCES = UV_COMMON_SOURCES + [
  "src/unix/async.c",
  "src/unix/atomic-ops.h",
  "src/unix/core.c",
  "src/unix/dl.c",
  "src/unix/fs.c",
  "src/unix/getaddrinfo.c",
  "src/unix/getnameinfo.c",
  "src/unix/internal.h",
  "src/unix/loop.c",
  "src/unix/loop-watcher.c",
  "src/unix/pipe.c",
  "src/unix/poll.c",
  "src/unix/process.c",
  "src/unix/signal.c",
  "src/unix/spinlock.h",
  "src/unix/stream.c",
  "src/unix/tcp.c",
  "src/unix/thread.c",
  "src/unix/tty.c",
  "src/unix/udp.c",
]

UV_UNIX_HEADERS = UV_COMMON_HEADERS + [
    "include/uv/unix.h",
]

UV_DARWIN_SOURCES = UV_UNIX_SOURCES + [
  "src/unix/bsd-ifaddrs.c",
  "src/unix/darwin.c",
  "src/unix/darwin-proctitle.c",
  "src/unix/fsevents.c",
  "src/unix/kqueue.c",
  "src/unix/proctitle.c",
]

UV_DARWIN_HEADERS = UV_UNIX_HEADERS + [
    "include/uv/darwin.h",
]

UV_BSD_SOURCES = UV_UNIX_SOURCES + [
  "src/unix/bsd-ifaddrs.c",
  "src/unix/bsd-proctitle.c",
  "src/unix/freebsd.c",
  "src/unix/kqueue.c",
  "src/unix/posix-hrtime.c",
]

UV_BSD_HEADERS = UV_UNIX_HEADERS + [
    "include/uv/bsd.h",
]


UV_LINUX_SOURCES = UV_UNIX_SOURCES + [
    "src/unix/linux-core.c",
    "src/unix/linux-inotify.c",
    "src/unix/linux-syscalls.c",
    "src/unix/linux-syscalls.h",
    "src/unix/procfs-exepath.c",
    "src/unix/proctitle.c",
    "src/unix/sysinfo-loadavg.c",
]

UV_LINUX_HEADERS = UV_UNIX_HEADERS + [
    "include/uv/linux.h",
]

UV_MSYS_SOURCES = UV_UNIX_SOURCES + [
    "src/unix/cygwin.c",
    "src/unix/bsd-ifaddrs.c",
    "src/unix/no-fsevents.c",
    "src/unix/no-proctitle.c",
    "src/unix/posix-hrtime.c",
    "src/unix/posix-poll.c",
    "src/unix/procfs-exepath.c",
    "src/unix/sysinfo-loadavg.c",
    "src/unix/sysinfo-memory",
]

UV_MSYS_HEADERS = UV_UNIX_HEADERS


cc_library(
  name = "uv",
  srcs = select({
    "@bazel_tools//src/conditions:windows": UV_WIN_SOURCES,
    "@bazel_tools//src/conditions:windows_msvc": UV_WIN_SOURCES,
    "@bazel_tools//src/conditions:windows_msys": UV_MSYS_SOURCES,
    "@bazel_tools//src/conditions:darwin": UV_DARWIN_SOURCES,
    "@bazel_tools//src/conditions:darwin_x86_64": UV_DARWIN_SOURCES,
    "@bazel_tools//src/conditions:freebsd": UV_BSD_SOURCES,
    "@bazel_tools//src/conditions:linux_x86_64": UV_LINUX_SOURCES,
    "@bazel_tools//src/conditions:linux_aarch64": UV_LINUX_SOURCES,
    "//conditions:default": UV_LINUX_SOURCES,
  }),
  hdrs = select({
    "@bazel_tools//src/conditions:windows": UV_WIN_HEADERS,
    "@bazel_tools//src/conditions:windows_msvc": UV_WIN_HEADERS,
    "@bazel_tools//src/conditions:windows_msys": UV_MSYS_HEADERS,
    "@bazel_tools//src/conditions:darwin": UV_DARWIN_HEADERS,
    "@bazel_tools//src/conditions:darwin_x86_64": UV_DARWIN_HEADERS,
    "@bazel_tools//src/conditions:freebsd": UV_BSD_HEADERS,
    "@bazel_tools//src/conditions:linux_x86_64": UV_LINUX_HEADERS,
    "@bazel_tools//src/conditions:linux_aarch64": UV_LINUX_HEADERS,
    "//conditions:default": UV_LINUX_HEADERS,
  }),
  includes = ["include", "src"],
  visibility = ["//visibility:public"],
)
