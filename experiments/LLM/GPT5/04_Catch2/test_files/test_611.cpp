// AnsiSkippingString_end_tests_611.cpp
#include <gtest/gtest.h>
#include "catch2/internal/catch_textflow.hpp"

using Catch::TextFlow::AnsiSkippingString;

class AnsiSkippingStringEndTest_611 : public ::testing::Test {};

// Normal operation: calling end() on an empty string should be valid and
// usable with substring to produce an empty result.
TEST_F(AnsiSkippingStringEndTest_611, EndOnEmpty_AllowsEmptySubstring_611) {
    const AnsiSkippingString s("");
    auto it_end = s.end();
    std::string out = s.substring(it_end, it_end);
    EXPECT_EQ(out, "");
}

// Normal operation: calling end() on a non-empty string should be valid and
// usable with substring to produce an empty result when begin==end.
TEST_F(AnsiSkippingStringEndTest_611, EndOnNonEmpty_AllowsEmptySubstring_611) {
    const AnsiSkippingString s("abc");
    auto it_end = s.end();
    std::string out = s.substring(it_end, it_end);
    EXPECT_EQ(out, "");
}

// Boundary: Ensure const and non-const overloads of end() (if both are available
// via the interface) behave consistently and can be used interchangeably
// with substring to yield an empty string for equal iterators.
TEST_F(AnsiSkippingStringEndTest_611, ConstAndNonConstEndBehaveConsistently_611) {
    AnsiSkippingString s("hello");
    auto it_end_nc = s.end();

    const AnsiSkippingString& cs = s;
    auto it_end_c = cs.end();

    // We don't assert internal equality operators; we check observable behavior.
    std::string out1 = s.substring(it_end_nc, it_end_nc);
    std::string out2 = cs.substring(it_end_c, it_end_c);

    EXPECT_EQ(out1, "");
    EXPECT_EQ(out2, "");
}

// Stability: Multiple calls to end() on the same (const) object should be
// interchangeable when used with substring.
TEST_F(AnsiSkippingStringEndTest_611, MultipleEndCallsAreInterchangeable_611) {
    const AnsiSkippingString s("some text \x1b[31mwith ansi\x1b[0m");
    auto e1 = s.end();
    auto e2 = s.end();

    // Again, verify via observable behavior only.
    EXPECT_EQ(s.substring(e1, e1), "");
    EXPECT_EQ(s.substring(e2, e2), "");
    // Cross-usage should also produce an empty substring
    EXPECT_EQ(s.substring(e1, e2), "");
    EXPECT_EQ(s.substring(e2, e1), "");
}
