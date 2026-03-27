// TextFlow_ostream_operator_617_tests.cpp
#include <gtest/gtest.h>
#include <sstream>

#include "catch2/internal/catch_textflow.hpp"

using Catch::TextFlow::Column;

namespace {

// Helper: make very wide column so wrapping never changes the input
static Column VeryWide(std::string text) {
    Column c{std::move(text)};
    c.width(1000); // ensure single "line" per explicit line in input
    return c;
}

} // namespace

// [617] Normal: single-line text is written verbatim with no trailing newline
TEST(TextFlowOstreamOperator_617, SingleLine_NoTrailingNewline_617) {
    Column col = VeryWide("Hello");
    std::ostringstream oss;
    oss << col;
    EXPECT_EQ(oss.str(), "Hello");
}

// [617] Boundary: empty text produces empty output (no extra newline)
TEST(TextFlowOstreamOperator_617, EmptyString_617) {
    Column col = VeryWide("");
    std::ostringstream oss;
    oss << col;
    EXPECT_TRUE(oss.str().empty());
}

// [617] Normal: multi-line input (explicit '\n's) is preserved exactly
TEST(TextFlowOstreamOperator_617, MultiLine_PreservesLineBreaks_617) {
    const std::string input = "first line\nsecond line\nthird";
    Column col = VeryWide(input);
    std::ostringstream oss;
    oss << col;
    EXPECT_EQ(oss.str(), input);
}

// [617] Boundary: multi-line output must not end with an extra newline
TEST(TextFlowOstreamOperator_617, MultiLine_NoExtraNewlineAtEnd_617) {
    Column col = VeryWide("a\nb");
    std::ostringstream oss;
    oss << col;
    const std::string out = oss.str();
    ASSERT_EQ(out.size(), 3u);       // "a\nb"
    EXPECT_NE(out.back(), '\n');     // no trailing newline
}

// [617] Interaction: streaming appends to existing stream content
TEST(TextFlowOstreamOperator_617, AppendsToExistingStreamContent_617) {
    Column col = VeryWide("world");
    std::ostringstream oss;
    oss << "hello-";
    oss << col;
    EXPECT_EQ(oss.str(), "hello-world");
}

// [617] Chaining: returned ostream& allows chaining multiple Column writes
TEST(TextFlowOstreamOperator_617, SupportsChainedInsertions_617) {
    Column col1 = VeryWide("A");
    Column col2 = VeryWide("B");
    std::ostringstream oss;

    (oss << col1 << col2);
    EXPECT_EQ(oss.str(), "AB");
}
