// File: textflow_operator_plus_columns_tests_623.cpp
#include <gtest/gtest.h>
#include <sstream>
#include "catch2/internal/catch_textflow.hpp"

using Catch::TextFlow::Column;
using Catch::TextFlow::Columns;

namespace {

// Helper: check that `needle` appears before `other` inside `hay`.
// We do not assume any exact layout, only the relative order.
static ::testing::AssertionResult AppearsBefore(
    const std::string& hay, const std::string& needle, const std::string& other) {
    const auto i = hay.find(needle);
    const auto j = hay.find(other);
    if (i == std::string::npos) {
        return ::testing::AssertionFailure() << "'" << needle << "' not found in output.";
    }
    if (j == std::string::npos) {
        return ::testing::AssertionFailure() << "'" << other << "' not found in output.";
    }
    if (i < j) return ::testing::AssertionSuccess();
    return ::testing::AssertionFailure()
           << "Expected '" << needle << "' to appear before '" << other << "'.";
}

} // namespace

// Normal operation: result contains both columns, in the same order.
// TEST_ID: 623
TEST(TextFlow_OperatorPlus_623, AddsTwoColumnsInOrder_623) {
    Column left("alpha");
    Column right("beta");

    Columns cols = left + right;

    std::ostringstream oss;
    oss << cols;

    const std::string out = oss.str();
    // Observable behavior: both inputs appear in the rendered output.
    EXPECT_NE(out.find("alpha"), std::string::npos);
    EXPECT_NE(out.find("beta"),  std::string::npos);
    // And the left column's content appears before the right's.
    EXPECT_TRUE(AppearsBefore(out, "alpha", "beta"));
}

// Boundary condition: empty left-hand text combined with non-empty right.
// We only assert observable effects (presence of the non-empty text).
// TEST_ID: 623
TEST(TextFlow_OperatorPlus_623, HandlesEmptyLeft_623) {
    Column empty_left("");
    Column nonempty_right("R");

    Columns cols = empty_left + nonempty_right;

    std::ostringstream oss;
    oss << cols;

    const std::string out = oss.str();
    EXPECT_NE(out.find("R"), std::string::npos);
}

// Boundary condition: non-empty left with empty right.
// Still expect the left content to be present and precede any right content.
// TEST_ID: 623
TEST(TextFlow_OperatorPlus_623, HandlesEmptyRight_623) {
    Column nonempty_left("L");
    Column empty_right("");

    Columns cols = nonempty_left + empty_right;

    std::ostringstream oss;
    oss << cols;

    const std::string out = oss.str();
    EXPECT_NE(out.find("L"), std::string::npos);
    // If empty right contributes nothing visible, this still passes;
    // We do not assert on the empty string's position.
}

// Robustness: very long strings should be preserved in the output without assumptions
// about wrapping; we only check that both substrings occur.
// TEST_ID: 623
TEST(TextFlow_OperatorPlus_623, PreservesLongTexts_623) {
    const std::string long_left  = std::string(300, 'A');  // 300 'A's
    const std::string long_right = std::string(250, 'B');  // 250 'B's

    Column left(long_left);
    Column right(long_right);

    Columns cols = left + right;

    std::ostringstream oss;
    oss << cols;

    const std::string out = oss.str();
    EXPECT_NE(out.find(long_left.substr(0, 20)),  std::string::npos);
    EXPECT_NE(out.find(long_right.substr(0, 20)), std::string::npos);
    EXPECT_TRUE(AppearsBefore(out, long_left.substr(0, 20), long_right.substr(0, 20)));
}

// Chaining sanity: the Columns returned by (left + right) should be usable
// in subsequent operations (e.g., streaming), confirming we really received a Columns.
// We avoid testing other operator+ overloads; we only validate that streaming works.
// TEST_ID: 623
TEST(TextFlow_OperatorPlus_623, ResultStreamsLikeColumns_623) {
    Column left("first");
    Column right("second");

    Columns cols = left + right;

    std::ostringstream oss;
    oss << cols;

    const std::string out = oss.str();
    EXPECT_NE(out.find("first"),  std::string::npos);
    EXPECT_NE(out.find("second"), std::string::npos);
}

