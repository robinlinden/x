load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

# Misc tools
# =========================================================

# HEAD as of 2022-12-17.
http_archive(
    name = "hedron_compile_commands",
    sha256 = "9b5683e6e0d764585f41639076f0be421a4c495c8f993c186e4449977ce03e5e",
    strip_prefix = "bazel-compile-commands-extractor-c6cd079bef5836293ca18e55aac6ef05134c3a9d",
    url = "https://github.com/hedronvision/bazel-compile-commands-extractor/archive/c6cd079bef5836293ca18e55aac6ef05134c3a9d.tar.gz",
)

# Bazel
# =========================================================

http_archive(
    name = "platforms",  # Apache-2.0
    sha256 = "5308fc1d8865406a49427ba24a9ab53087f17f5266a7aabbfc28823f3916e1ca",
    url = "https://github.com/bazelbuild/platforms/releases/download/0.0.6/platforms-0.0.6.tar.gz",
)

# Third-party
# =========================================================

http_archive(
    name = "wasm3",  # MIT
    build_file = "//third_party:wasm3.BUILD",
    sha256 = "b778dd72ee2251f4fe9e2666ee3fe1c26f06f517c3ffce572416db067546536c",
    strip_prefix = "wasm3-0.5.0",
    url = "https://github.com/wasm3/wasm3/archive/v0.5.0.tar.gz",
)

# Third-party setup
# =========================================================

load("@hedron_compile_commands//:workspace_setup.bzl", "hedron_compile_commands_setup")

hedron_compile_commands_setup()
