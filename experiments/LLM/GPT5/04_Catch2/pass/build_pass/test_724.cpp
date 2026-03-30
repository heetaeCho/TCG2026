// File: tests/config_name_724_tests.cpp

#include <gtest/gtest.h>

#include "catch2/catch_config.hpp"  // Provides Catch::Config and Catch::ConfigData
// If your include path differs, adjust accordingly.

namespace {

using namespace Catch;

// A small helper to compare StringRef without depending on implicit conversions.
// We construct a StringRef from const char* for equality checks.
inline void ExpectStringRefEq(const StringRef& actual, const char* expected) {
    EXPECT_TRUE(actual == StringRef{expected});
}

class ConfigNameTest_724 : public ::testing::Test {
protected:
    ConfigData data;
};

} // namespace

// Normal operation: returns explicit name when provided (non-empty)
TEST_F(ConfigNameTest_724, ReturnsExplicitNameWhenProvided_724) {
    data.name = "my-run-name";
    data.processName = "my-process";
    Config cfg{data};

    ExpectStringRefEq(cfg.name(), "my-run-name");
}

// Normal operation: falls back to processName when name is empty
TEST_F(ConfigNameTest_724, FallsBackToProcessNameWhenNameEmpty_724) {
    data.name.clear();
    data.processName = "proc.exe";
    Config cfg{data};

    ExpectStringRefEq(cfg.name(), "proc.exe");
}

// Boundary: both name and processName are empty => empty StringRef
TEST_F(ConfigNameTest_724, EmptyWhenBothNameAndProcessNameEmpty_724) {
    data.name.clear();
    data.processName.clear();
    Config cfg{data};

    // Expect empty string view
    EXPECT_TRUE(cfg.name().empty());
    ExpectStringRefEq(cfg.name(), "");
}

// Boundary: whitespace-only name is NOT empty => returned as-is
TEST_F(ConfigNameTest_724, WhitespaceOnlyNameIsReturned_724) {
    data.name = "   \t";
    data.processName = "ignored";
    Config cfg{data};

    ExpectStringRefEq(cfg.name(), "   \t");
}

// Boundary: long name is preserved
TEST_F(ConfigNameTest_724, LongNameIsPreserved_724) {
    // Create a long string (e.g., 10k characters)
    std::string longName(10'000, 'A');
    data.name = longName;
    data.processName = "ignored";
    Config cfg{data};

    // Check size and a couple of sentinel positions
    EXPECT_EQ(cfg.name().size(), longName.size());
    // Compare beginning and end via substrings to avoid copying entire string
    EXPECT_TRUE(StringRef{cfg.name().substr(0, 3)} == StringRef{"AAA"});
    EXPECT_TRUE(StringRef{cfg.name().substr(cfg.name().size() - 3, 3)} == StringRef{"AAA"});
}

// Normal operation: processName with path-like value
TEST_F(ConfigNameTest_724, ProcessNameWithPathLikeValue_724) {
    data.name.clear();
    data.processName = "/usr/local/bin/test-runner";
    Config cfg{data};

    ExpectStringRefEq(cfg.name(), "/usr/local/bin/test-runner");
}
