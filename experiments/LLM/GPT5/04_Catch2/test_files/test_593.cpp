// TrimTests_593.cpp
#include <gtest/gtest.h>
#include <string>

// Public interface headers
#include "catch2/internal/catch_stringref.hpp"

// Forward declaration of the function under test (already implemented elsewhere)
namespace Catch {
    StringRef trim(StringRef ref);
}

using Catch::StringRef;

class TrimTest_593 : public ::testing::Test {};

/*
 * Normal operation: leading and trailing ASCII whitespace are removed.
 */
TEST_F(TrimTest_593, TrimsSpacesTabsNewlines_593) {
    StringRef in(" \t\n\rabc\t \n\r");
    StringRef out = Catch::trim(in);

    std::string s = static_cast<std::string>(out);
    EXPECT_EQ(s, "abc");
    EXPECT_EQ(out.size(), 3u);
}

/*
 * Boundary: no whitespace to trim -> returned view should match input
 * (same content, same size, and same starting pointer).
 */
TEST_F(TrimTest_593, NoTrimReturnsSameView_593) {
    std::string src = "alpha";
    StringRef in(src);
    StringRef out = Catch::trim(in);

    EXPECT_EQ(static_cast<std::string>(out), "alpha");
    EXPECT_EQ(out.size(), in.size());
    EXPECT_EQ(out.data(), in.data()); // same starting address when nothing is trimmed
}

/*
 * Boundary: empty input -> empty output.
 */
TEST_F(TrimTest_593, EmptyInputYieldsEmptyOutput_593) {
    StringRef in("");
    StringRef out = Catch::trim(in);

    EXPECT_TRUE(out.empty());
    EXPECT_EQ(out.size(), 0u);
    // Accessing out.data() is allowed, but content is unspecified; size/empty is sufficient.
}

/*
 * Boundary: input with only whitespace -> empty output.
 */
TEST_F(TrimTest_593, AllWhitespaceBecomesEmpty_593) {
    StringRef in(" \t\n\r \t");
    StringRef out = Catch::trim(in);

    EXPECT_TRUE(out.empty());
    EXPECT_EQ(out.size(), 0u);
}

/*
 * Normal operation: internal whitespace is preserved; only edges are trimmed.
 */
TEST_F(TrimTest_593, PreservesInternalWhitespace_593) {
    StringRef in("   a b\tc  ");
    StringRef out = Catch::trim(in);

    EXPECT_EQ(static_cast<std::string>(out), "a b\tc");
}

/*
 * Mixed edges: leading tabs/newlines and trailing spaces/newlines are trimmed.
 * Interior newlines are preserved.
 */
TEST_F(TrimTest_593, PreservesInteriorNewlines_593) {
    StringRef in("\n\t  line1\nline2  \n  ");
    StringRef out = Catch::trim(in);

    EXPECT_EQ(static_cast<std::string>(out), "line1\nline2");
}

/*
 * Pointer arithmetic check (observable via public interface):
 * start pointer advances by the number of trimmed leading characters.
 */
TEST_F(TrimTest_593, StartPointerAdvancesAfterLeadingTrim_593) {
    const char* raw = "  xyz";
    StringRef in(raw);
    StringRef out = Catch::trim(in);

    EXPECT_EQ(static_cast<std::string>(out), "xyz");
    // Two leading spaces should advance the view by 2 bytes.
    EXPECT_EQ(out.data(), raw + 2);
    EXPECT_EQ(out.size(), 3u);
}

/*
 * Non-ASCII whitespace (e.g., NBSP U+00A0) is not trimmed because the interface
 * only guarantees trimming of standard ASCII WS via observable behavior.
 * This verifies that bytes not equal to ' ', '\t', '\n', or '\r' are preserved.
 */
TEST_F(TrimTest_593, NonAsciiNbspNotTrimmed_593) {
    // Build a std::string with NBSP bytes around "abc".
    // UTF-8 NBSP is 0xC2 0xA0.
    std::string s = u8"\u00A0abc\u00A0";
    StringRef in(s);
    StringRef out = Catch::trim(in);

    // Expect no trimming: output bytes should equal input bytes.
    EXPECT_EQ(static_cast<std::string>(out), s);
    EXPECT_EQ(out.data(), in.data());
    EXPECT_EQ(out.size(), in.size());
}
