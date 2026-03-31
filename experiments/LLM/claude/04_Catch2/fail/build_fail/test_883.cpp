#include <gtest/gtest.h>
#include <string>
#include <stdexcept>

// Declaration of the function under test
std::string catch_path(std::string path);

// Test normal operation with lowercase "catch" and forward slash
TEST(CatchPathTest_883, LowercaseCatchWithForwardSlash_883) {
    std::string result = catch_path("/home/user/catch/src/file.cpp");
    EXPECT_EQ(result, "/home/user/catch");
}

// Test normal operation with uppercase "Catch" and forward slash
TEST(CatchPathTest_883, UppercaseCatchWithForwardSlash_883) {
    std::string result = catch_path("/home/user/Catch/src/file.cpp");
    EXPECT_EQ(result, "/home/user/Catch");
}

// Test with backslash separator
TEST(CatchPathTest_883, LowercaseCatchWithBackslash_883) {
    std::string result = catch_path("C:\\Users\\catch\\src\\file.cpp");
    EXPECT_EQ(result, "C:\\Users\\catch");
}

// Test with uppercase Catch and backslash separator
TEST(CatchPathTest_883, UppercaseCatchWithBackslash_883) {
    std::string result = catch_path("C:\\Users\\Catch\\src\\file.cpp");
    EXPECT_EQ(result, "C:\\Users\\Catch");
}

// Test when "catch" is at the beginning of the path
TEST(CatchPathTest_883, CatchAtBeginningWithSlash_883) {
    std::string result = catch_path("catch/src/file.cpp");
    EXPECT_EQ(result, "catch");
}

// Test when "Catch" is at the beginning of the path
TEST(CatchPathTest_883, UpperCatchAtBeginningWithSlash_883) {
    std::string result = catch_path("Catch/src/file.cpp");
    EXPECT_EQ(result, "Catch");
}

// Test when neither "catch" nor "Catch" is found — should throw
TEST(CatchPathTest_883, NoCatchThrowsDomainError_883) {
    EXPECT_THROW(catch_path("/home/user/project/src/file.cpp"), std::domain_error);
}

// Test with empty string — should throw
TEST(CatchPathTest_883, EmptyStringThrowsDomainError_883) {
    EXPECT_THROW(catch_path(""), std::domain_error);
}

// Test with "catch" but no separator after it (catch is at the end)
TEST(CatchPathTest_883, CatchAtEndNoTrailingSeparator_883) {
    std::string result = catch_path("/home/user/catch");
    // npos for end means substr(0, npos) returns entire string
    EXPECT_EQ(result, "/home/user/catch");
}

// Test with "Catch" but no separator after it
TEST(CatchPathTest_883, UpperCatchAtEndNoTrailingSeparator_883) {
    std::string result = catch_path("/home/user/Catch");
    EXPECT_EQ(result, "/home/user/Catch");
}

// Test that lowercase "catch" is preferred when both exist
TEST(CatchPathTest_883, BothCatchAndUpperCatch_LowercaseFirst_883) {
    std::string result = catch_path("/home/catch/Catch/src/file.cpp");
    EXPECT_EQ(result, "/home/catch");
}

// Test that when only uppercase "Catch" exists, it's used
TEST(CatchPathTest_883, OnlyUpperCatchPresent_883) {
    std::string result = catch_path("/home/user/Catch2/src/file.cpp");
    // "Catch" is found at position within "Catch2", next separator after "Catch" is "/"
    // find_first_of searches from start of "Catch" — let's check
    // path = "/home/user/Catch2/src/file.cpp"
    // "Catch" found at index 11
    // find_first_of("\\/", 11) finds "/" at index 17
    EXPECT_EQ(result, "/home/user/Catch2");
}

// Test with "catch" as part of a longer word (e.g., "catcher")
TEST(CatchPathTest_883, CatchAsPartOfLongerWord_883) {
    std::string result = catch_path("/home/user/catcher/src/file.cpp");
    // "catch" is found within "catcher", then find_first_of searches for slash after "catch"
    // "catcher/" — the slash is at position after "catcher"
    EXPECT_EQ(result, "/home/user/catcher");
}

// Test with multiple slashes and catch deep in path
TEST(CatchPathTest_883, CatchDeepInPath_883) {
    std::string result = catch_path("/a/b/c/d/catch/e/f/g.cpp");
    EXPECT_EQ(result, "/a/b/c/d/catch");
}

// Test where "CATCH" (all uppercase) is not found — should throw
TEST(CatchPathTest_883, AllUppercaseCATCHNotFound_883) {
    EXPECT_THROW(catch_path("/home/user/CATCH/src/file.cpp"), std::domain_error);
}

// Test with mixed separators
TEST(CatchPathTest_883, MixedSeparators_883) {
    std::string result = catch_path("C:\\Users/catch\\src/file.cpp");
    EXPECT_EQ(result, "C:\\Users/catch");
}

// Test exception message content
TEST(CatchPathTest_883, ExceptionMessageContent_883) {
    try {
        catch_path("no_match_here");
        FAIL() << "Expected std::domain_error";
    } catch (const std::domain_error& e) {
        EXPECT_STREQ(e.what(), "Couldn't find Catch's base path");
    }
}

// Test with "catch" only (no prefix, no suffix, no separator)
TEST(CatchPathTest_883, JustCatchAlone_883) {
    std::string result = catch_path("catch");
    EXPECT_EQ(result, "catch");
}

// Test with "Catch" only
TEST(CatchPathTest_883, JustUpperCatchAlone_883) {
    std::string result = catch_path("Catch");
    EXPECT_EQ(result, "Catch");
}

// Test: lowercase "catch" not found but "Catch" found
TEST(CatchPathTest_883, OnlyUpperCatchFoundFallback_883) {
    std::string result = catch_path("/home/user/Catch/tests");
    EXPECT_EQ(result, "/home/user/Catch");
}

// Test: "Catch" appears before "catch" in the string
TEST(CatchPathTest_883, UpperCatchBeforeLowerCatch_883) {
    std::string result = catch_path("/Catch/catch/file.cpp");
    // "catch" is searched first via find("catch"). "Catch" contains 'C' not 'c', 
    // but "catch" at position 7 also matches. Let's trace:
    // find("catch") on "/Catch/catch/file.cpp" — "catch" at index 7 matches lowercase.
    // Wait, "Catch" at index 1 has uppercase C. find("catch") looks for exact lowercase.
    // "/Catch/catch/file.cpp" — find("catch") finds at index 7 (the "catch" part)
    // So start = 7, end = find_first_of("\\/", 7) = 12
    EXPECT_EQ(result, "/Catch/catch");
}
