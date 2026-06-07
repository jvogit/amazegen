load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_binary(
    name = "amazegen",
    srcs = ["main.cc"],
    deps = [
        "//maze",
        "@abseil-cpp//absl/container:flat_hash_map",
        "@abseil-cpp//absl/flags:flag",
        "@abseil-cpp//absl/flags:parse",
        "@abseil-cpp//absl/log",
        "@abseil-cpp//absl/status:statusor",
        "@abseil-cpp//absl/strings",
    ],
)
