load("@rules_cc//cc:defs.bzl", "cc_test")

cc_test(
    name = "tests",
    size = "small",
    srcs = glob(["*_test.cc"]),
    deps = [
        "//maze",
        "@googletest//:gtest_main",
    ],
)
