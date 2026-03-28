// File: tests/jsonutils_append_comma_newline_528_tests.cpp

#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <cstdint>

// Include the public interface under test
#include "catch2/internal/catch_jsonwriter.hpp"

namespace {

std::string callIndent(std::uint64_t level) {
    std::ostringstream oss;
    Catch::JsonUtils::indent(oss, level);
    return oss.str();
}

} // namespace

// Normal operation: when should_comma == false, it should NOT write a comma,
// then it should write '\n' followed by whatever indent(level) produces,
// and it should set should_comma to true.
TEST(JsonUtils_528, AppendNoCommaThenNewlineAndIndent_SetsFlagTrue_528) {
    std::ostringstream oss;
    bool should_comma = false;
    const std::uint64_t level = 2;

    Catch::JsonUtils::appendCommaNewline(oss, should_comma, level);

    const std::string expected = std::string("\n") + callIndent(level);
    EXPECT_EQ(oss.str(), expected);
    EXPECT_TRUE(should_comma);
}

// Normal operation: when should_comma == true, it SHOULD write a comma,
// then '\n' and indent(level). Flag should remain true.
TEST(JsonUtils_528, AppendCommaThenNewlineAndIndent_FlagStaysTrue_528) {
    std::ostringstream oss;
    bool should_comma = true;
    const std::uint64_t level = 3;

    Catch::JsonUtils::appendCommaNewline(oss, should_comma, level);

    const std::string expected = std::string(",\n") + callIndent(level);
    EXPECT_EQ(oss.str(), expected);
    EXPECT_TRUE(should_comma);
}

// Boundary: level == 0 should still write the correct prefix
// (comma depending on flag), newline, and whatever indent(0) outputs.
TEST(JsonUtils_528, Boundary_LevelZero_NoCommaCase_528) {
    std::ostringstream oss;
    bool should_comma = false;
    const std::uint64_t level = 0;

    Catch::JsonUtils::appendCommaNewline(oss, should_comma, level);

    const std::string expected = std::string("\n") + callIndent(level);
    EXPECT_EQ(oss.str(), expected);
    EXPECT_TRUE(should_comma);
}

// Boundary: level == 0 with a comma expected.
TEST(JsonUtils_528, Boundary_LevelZero_WithCommaCase_528) {
    std::ostringstream oss;
    bool should_comma = true;
    const std::uint64_t level = 0;

    Catch::JsonUtils::appendCommaNewline(oss, should_comma, level);

    const std::string expected = std::string(",\n") + callIndent(level);
    EXPECT_EQ(oss.str(), expected);
    EXPECT_TRUE(should_comma);
}

// Interaction over multiple calls: starting from should_comma == false,
// the first call should omit comma, the second should include it.
// Both calls should add "\n" + indent(level) each time.
TEST(JsonUtils_528, MultipleCalls_CommaAppearsOnlyFromSecondCall_528) {
    std::ostringstream oss;
    bool should_comma = false;
    const std::uint64_t level = 1;

    // First call: no comma expected
    Catch::JsonUtils::appendCommaNewline(oss, should_comma, level);
    // Second call: comma expected
    Catch::JsonUtils::appendCommaNewline(oss, should_comma, level);

    const std::string expected =
        std::string("\n") + callIndent(level) +    // first call
        ",\n" + callIndent(level);                 // second call

    EXPECT_EQ(oss.str(), expected);
    EXPECT_TRUE(should_comma);
}

// Sanity/robustness: Using a relatively larger level should still produce
// exactly the same structure: optional comma, newline, then indent(level).
// We do not assert the specific indentation content, only that it matches
// the public indent() output for that level.
TEST(JsonUtils_528, LargerLevel_UsesIndentOutputAsOracle_528) {
    std::ostringstream oss;
    bool should_comma = true;
    const std::uint64_t level = 8; // large enough to exercise indentation

    Catch::JsonUtils::appendCommaNewline(oss, should_comma, level);

    const std::string expected = std::string(",\n") + callIndent(level);
    EXPECT_EQ(oss.str(), expected);
    EXPECT_TRUE(should_comma);
}
