// File: args_exename_tests_401.cpp

#include <gtest/gtest.h>
#include "catch2/internal/catch_clara.hpp"

using Catch::Clara::Args;

// Helper to safely convert Catch::StringRef to std::string
static std::string ToStdString(const Catch::StringRef& sr) {
    return std::string(sr.c_str(), sr.size());
}

class ArgsTest_401 : public ::testing::Test {};

// [Normal] argc/argv constructor: exeName() should be argv[0]
TEST_F(ArgsTest_401, FromArgcArgv_ReturnsFirstToken_401) {
    // Own the strings so their storage outlives argv pointers
    std::vector<std::string> storage = { "myprog", "arg1", "arg2" };
    std::vector<const char*> argv;
    argv.reserve(storage.size());
    for (const auto& s : storage) argv.push_back(s.c_str());

    const int argc = static_cast<int>(argv.size());
    Args args(argc, argv.data());

    EXPECT_EQ(ToStdString(args.exeName()), "myprog");
}

// [Boundary] argc/argv with a single element (program name only)
TEST_F(ArgsTest_401, FromArgcArgv_SingleArgument_401) {
    std::vector<std::string> storage = { "prog_only" };
    std::vector<const char*> argv;
    for (const auto& s : storage) argv.push_back(s.c_str());

    const int argc = static_cast<int>(argv.size());
    Args args(argc, argv.data());

    EXPECT_EQ(ToStdString(args.exeName()), "prog_only");
}

// [Normal] initializer_list constructor: exeName() should be the first element
TEST_F(ArgsTest_401, FromInitList_ReturnsFirstElement_401) {
    Args args({ "prog_init", "a", "b", "c" });

    EXPECT_EQ(ToStdString(args.exeName()), "prog_init");
}

// [Boundary] initializer_list with a single element
TEST_F(ArgsTest_401, FromInitList_SingleElement_401) {
    Args args({ "just_prog" });

    EXPECT_EQ(ToStdString(args.exeName()), "just_prog");
}
