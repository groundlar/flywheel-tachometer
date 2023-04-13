load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "hello-time",
    srcs = ["hello-time.cc"],
    hdrs = ["hello-time.h"],
    visibility = [
        "//main:__pkg__",
        "//test:__pkg__"
    ],
)

cc_library(
    name = "rpm_calculation",
    srcs = ["rpm_calculation.cc"],
    hdrs = ["rpm_calculation.h"],
    visibility = [
        "//main:__pkg__",
        "//test:__pkg__"
    ],
)