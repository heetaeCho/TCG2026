// StringMaker_convert_tests_78.cpp
#include <gtest/gtest.h>
#include <string>
#include <sstream>

// Include the SUT interface (public headers only)
#include "catch2/catch_tostring.hpp"

using Catch::StringMaker;

// A simple stream-insertable custom type to verify that StringMaker
// routes formatting through operator<< (observable via returned string).
struct Widget {
    int id{};
};

std::ostream& operator<<(std::ostream& os, const Widget& w) {
    os << "Widget{" << w.id << "}";
    return os;
}

// ----------------------------
// Tests
// ----------------------------

TEST(StringMakerTest_78, Convert_Int_Positive_78) {
    // Normal operation: basic integral value
    const int v = 42;
    const std::string s = StringMaker<int>::convert(v);
    EXPECT_EQ(s, "42");
}

TEST(StringMakerTest_78, Convert_Int_Negative_78) {
    // Boundary-ish: negative integral value
    const int v = -7;
    const std::string s = StringMaker<int>::convert(v);
    EXPECT_EQ(s, "-7");
}

TEST(StringMakerTest_78, Convert_String_NonEmpty_78) {
    // Normal operation: std::string round-trip
    const std::string in = "hello";
    const std::string out = StringMaker<std::string>::convert(in);
    EXPECT_EQ(out, "hello");
}

TEST(StringMakerTest_78, Convert_String_Empty_78) {
    // Boundary: empty string should remain empty after conversion
    const std::string in;
    const std::string out = StringMaker<std::string>::convert(in);
    EXPECT_TRUE(out.empty());
}

TEST(StringMakerTest_78, Convert_Bool_True_78) {
    // Normal operation: boolean true
    const std::string s = StringMaker<bool>::convert(true);
    EXPECT_EQ(s, "true");
}

TEST(StringMakerTest_78, Convert_Bool_False_78) {
    // Normal operation: boolean false
    const std::string s = StringMaker<bool>::convert(false);
    EXPECT_EQ(s, "false");
}

TEST(StringMakerTest_78, Convert_Nullptr_78) {
    // Exceptional-ish/boundary: nullptr formatting via public overload
    const std::string s = StringMaker<std::nullptr_t>::convert(nullptr);
    EXPECT_EQ(s, "nullptr");
}

TEST(StringMakerTest_78, Convert_StreamInsertableCustomType_78) {
    // Verification of external interaction via observable effect:
    // since Widget is stream-insertable, StringMaker<Widget>::convert
    // should produce whatever operator<< writes.
    Widget w{7};
    const std::string s = StringMaker<Widget>::convert(w);
    EXPECT_EQ(s, "Widget{7}");
}
