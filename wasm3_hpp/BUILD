load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")

cc_library(
    name = "wasm3_hpp",
    srcs = ["wasm3.cc"],
    hdrs = ["wasm3.hpp"],
    deps = ["@wasm3"],
)

cc_binary(
    name = "app",
    srcs = ["main.cc"],
    visibility = ["//visibility:public"],
    deps = ["@wasm3"],
)
