load("@rules_cc//cc:defs.bzl", "cc_test")

cc_test(
  name = "hello-test",
  size = "small",
  srcs = ["hello-test.cc"],
  deps = [
    "//main:hello-greet",
    "@com_google_googletest//:gtest_main",
    ],
)

cc_test(
  name = "tests",
  size = "small",
  srcs = glob(["**/*.cc"]),
  deps = [
    "//main:hello-greet",
    "//lib:hello-time",
    "@com_google_googletest//:gtest_main",
    ],
)