load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")

cc_library(
    name = "wasm3",
    srcs = glob(["source/*.c"]),
    hdrs = glob(["source/*.h"]),
    strip_include_prefix = "source/",
    visibility = ["//visibility:public"],
)

cc_binary(
    name = "app",
    srcs = ["platforms/app/main.c"],
    visibility = ["//visibility:public"],
    deps = [":wasm3"],
)
