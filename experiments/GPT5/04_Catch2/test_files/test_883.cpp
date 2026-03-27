// File: tests/coverage_helper_test_883.cpp
#include <gtest/gtest.h>
#include <stdexcept>
#include <string>

// SUT declaration (treat implementation as a black box)
std::string catch_path(std::string path);

class CoverageHelperTest_883 : public ::testing::Test {};

// Normal operation: Unix-style path, lowercase "catch"
TEST_F(CoverageHelperTest_883, ReturnPrefixUnix_883) {
    const std::string in = "/home/user/catch2/src/file.cpp";
    const std::string out = catch_path(in);
    EXPECT_EQ(out, "/home/user/catch2");
}

// Normal operation: Windows-style path, lowercase "catch"
TEST_F(CoverageHelperTest_883, ReturnPrefixWindows_883) {
    const std::string in = "C:\\dev\\catch2\\include\\catch.hpp";
    const std::string out = catch_path(in);
    EXPECT_EQ(out, "C:\\dev\\catch2");
}

// Normal operation: Capitalized "Catch"
TEST_F(CoverageHelperTest_883, ReturnPrefixCapitalized_883) {
    const std::string in = "/opt/Catch2/include/catch.hpp";
    const std::string out = catch_path(in);
    EXPECT_EQ(out, "/opt/Catch2");
}

// Boundary: "catch" at the start of the string
TEST_F(CoverageHelperTest_883, CatchAtStart_883) {
    const std::string in = "catch2/include/catch.hpp";
    const std::string out = catch_path(in);
    EXPECT_EQ(out, "catch2");
}

// Boundary: no separator after the matched token -> returns whole string
TEST_F(CoverageHelperTest_883, NoSeparatorAfterMatch_883) {
    const std::string in = "/src/project/catch2";
    const std::string out = catch_path(in);
    EXPECT_EQ(out, "/src/project/catch2");
}

// Behavior with multiple candidates: earlier "Catch" exists, but later lowercase "catch" also exists.
// The observable behavior should select the occurrence used by the implementation.
// (We only assert the returned prefix without inferring internals.)
TEST_F(CoverageHelperTest_883, PrefersLowercaseOccurrenceIfPresent_883) {
    const std::string in = "/a/CatchSomething/foo/bar/catch2/include/x.hpp";
    const std::string out = catch_path(in);
    EXPECT_EQ(out, "/a/CatchSomething/foo/bar/catch2");
}

// Exceptional case: neither "catch" nor "Catch" appears -> throws domain_error with expected message
TEST_F(CoverageHelperTest_883, ThrowsWhenNoCatchFound_883) {
    const std::string in = "/usr/local/project/src/header.hpp";
    try {
        (void)catch_path(in);
        FAIL() << "Expected std::domain_error";
    } catch (const std::domain_error& e) {
        EXPECT_STREQ(e.what(), "Couldn't find Catch's base path");
    } catch (...) {
        FAIL() << "Expected std::domain_error";
    }
}
