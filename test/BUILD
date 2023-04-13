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
