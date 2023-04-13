load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

# Hedron's Compile Commands Extractor for Bazel
# https://github.com/hedronvision/bazel-compile-commands-extractor
http_archive(
    name = "hedron_compile_commands",

    # Replace the commit hash in both places (below) with the latest, rather than using the stale one here.
    # Even better, set up Renovate and let it do the work for you (see "Suggestion: Updates" in the README).
    url = "https://github.com/hedronvision/bazel-compile-commands-extractor/archive/7831ea1a9e183a0b23206f7f56726e313ddac5c1.tar.gz",
    strip_prefix = "bazel-compile-commands-extractor-7831ea1a9e183a0b23206f7f56726e313ddac5c1",
    # When you first run this tool, it'll recommend a sha256 hash to put here with a message like: "DEBUG: Rule 'hedron_compile_commands' indicated that a canonical reproducible form can be obtained by modifying arguments sha256 = ..."
)
load("@hedron_compile_commands//:workspace_setup.bzl", "hedron_compile_commands_setup")
hedron_compile_commands_setup()

# gTest library for cpp testing
http_archive(
    name = "com_google_googletest",
    url = "https://github.com/google/googletest/archive/refs/tags/v1.13.0.zip",
    sha256 = "ffa17fbc5953900994e2deec164bb8949879ea09b411e07f215bfbb1f87f4632",
    #build_file = "@//:gtest.BUILD",
    strip_prefix = "googletest-1.13.0",
)
