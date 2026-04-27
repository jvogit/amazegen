load("@rules_cc//cc:defs.bzl", "cc_test")

cc_test(
    name = "tests",
    size = "small",
    srcs = ["maze_test.cc"],
    deps = [
        "//maze",
        "@googletest//:gtest_main",
    ],
)
