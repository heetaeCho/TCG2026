// pluralise_ostream_tests_596.cpp
#include <gtest/gtest.h>
#include <sstream>

// Include the provided (or project) headers
// Adjust the include path to match your repository layout.
#include "catch2/internal/catch_string_manip.hpp"

using Catch::pluralise;

class PluraliseOstreamTest_596 : public ::testing::Test {
protected:
    static std::string Str(const pluralise& p) {
        std::ostringstream oss;
        oss << p;
        return oss.str();
    }
};

// Normal operation: count == 1 -> no trailing 's'
TEST_F(PluraliseOstreamTest_596, OneCount_NoPluralSuffix_596) {
    pluralise p(1, "test");
    EXPECT_EQ(Str(p), "1 test");
}

// Boundary: count == 0 -> pluralized (since it is not 1)
TEST_F(PluraliseOstreamTest_596, ZeroCount_HasPluralSuffix_596) {
    pluralise p(0, "item");
    EXPECT_EQ(Str(p), "0 items");
}

// Normal operation: count > 1 -> pluralized
TEST_F(PluraliseOstreamTest_596, ManyCount_HasPluralSuffix_596) {
    pluralise p(2, "case");
    EXPECT_EQ(Str(p), "2 cases");
}

// Boundary: empty label -> still prints count and space, and pluralizes when != 1
TEST_F(PluraliseOstreamTest_596, EmptyLabel_FormatsAndPluralizes_596) {
    pluralise p(3, "");
    // Expect: "3 " + "" + "s"
    EXPECT_EQ(Str(p), "3 s");
}

// Observable behavior: label already ends with 's' — operator still appends another 's' when count != 1
TEST_F(PluraliseOstreamTest_596, LabelAlreadyEndsWithS_AppendsAnotherS_596) {
    pluralise p(5, "class");
    // Observable output should include the additional 's'
    EXPECT_EQ(Str(p), "5 classs");
}

// Large number handling: ensure full count is streamed and pluralized
TEST_F(PluraliseOstreamTest_596, VeryLargeCount_PrintsFullNumberAndPlural_596) {
    const std::uint64_t big = 1234567890123456789ULL;
    pluralise p(big, "widget");
    EXPECT_EQ(Str(p), "1234567890123456789 widgets");
}
