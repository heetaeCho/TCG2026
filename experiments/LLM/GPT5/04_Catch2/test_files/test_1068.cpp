// File: tests/ExeName_1068_tests.cpp

#include <gtest/gtest.h>
#include <string>
#include "catch2/internal/catch_clara.hpp"

using Catch::Clara::ExeName;

namespace {

// -----------------------------
// Basic behavior
// -----------------------------

TEST(ExeNameTest_1068, DefaultNameIsExecutablePlaceholder_1068) {
    ExeName exe;
    // Observable behavior via the public accessor
    EXPECT_EQ(exe.name(), std::string("<executable>"));
}

TEST(ExeNameTest_1068, SetUpdatesName_1068) {
    ExeName exe;
    auto result = exe.set("my_app");
    (void)result; // Do not rely on internal details of ParserResult
    EXPECT_EQ(exe.name(), std::string("my_app"));
}

// -----------------------------
// External interactions
// -----------------------------

TEST(ExeNameTest_1068, RefConstructorWritesBackProvidedString_1068) {
    std::string sink = "initial";
    ExeName exe(sink);

    auto result = exe.set("cli_app");
    (void)result;

    // Verify externally observable interaction: the referenced string is updated
    EXPECT_EQ(sink, std::string("cli_app"));
    // Name accessor should reflect the same observable state
    EXPECT_EQ(exe.name(), std::string("cli_app"));
}

TEST(ExeNameTest_1068, LambdaConstructorInvokedWithNewName_1068) {
    bool called = false;
    std::string received;

    ExeName exe([&](std::string const& newName) {
        called = true;
        received = newName;
    });

    auto result = exe.set("bin_name");
    (void)result;

    // Verify the external interaction (lambda invocation and parameter)
    EXPECT_TRUE(called);
    EXPECT_EQ(received, std::string("bin_name"));

    // Also verify the observable name state via the public API
    EXPECT_EQ(exe.name(), std::string("bin_name"));
}

// -----------------------------
// Boundary cases
// -----------------------------

TEST(ExeNameTest_1068, SetSupportsUnicodeNames_1068) {
    ExeName exe;
    const std::string unicodeName = u8"한글_앱🚀";
    auto result = exe.set(unicodeName);
    (void)result;

    EXPECT_EQ(exe.name(), unicodeName);
}

TEST(ExeNameTest_1068, SetHandlesLongNames_1068) {
    ExeName exe;

    // reasonably long executable name (no assumption on max length internally)
    std::string longName(4096, 'a'); // 4KB of 'a'
    auto result = exe.set(longName);
    (void)result;

    EXPECT_EQ(exe.name().size(), longName.size());
    EXPECT_EQ(exe.name(), longName);
}

} // namespace
