// File: tests/value_try_get_string_43.cpp

#include <gtest/gtest.h>
#include <string>
#include "JsonBox/Value.h"

using JsonBox::Value;
using std::string;

class JsonBoxValueTryGetStringTest_43 : public ::testing::Test {};

// [Normal] Returns stored string when Value holds a string
TEST_F(JsonBoxValueTryGetStringTest_43, ReturnsStoredStringWhenString_43) {
    const Value v(string("hello"));
    string def = "default";
    const string& out = v.tryGetString(def);

    EXPECT_EQ("hello", out);
    // Should not be the same reference as the default argument
    EXPECT_NE(&out, &def);
}

// [Boundary] Returns stored empty string (not the default) when Value holds an empty string
TEST_F(JsonBoxValueTryGetStringTest_43, ReturnsStoredEmptyWhenStringEmpty_43) {
    const Value v(string(""));
    string def = "default";
    const string& out = v.tryGetString(def);

    EXPECT_EQ("", out);
    EXPECT_NE(&out, &def);
}

// [Normal] Returns the provided default when Value is an integer
TEST_F(JsonBoxValueTryGetStringTest_43, ReturnsDefaultWhenInteger_43) {
    const Value v(42);
    string def = "default";
    const string& out = v.tryGetString(def);

    EXPECT_EQ("default", out);
    // Must be the exact same reference as the default argument
    EXPECT_EQ(&out, &def);
}

// [Normal] Returns the provided default when Value is a double
TEST_F(JsonBoxValueTryGetStringTest_43, ReturnsDefaultWhenDouble_43) {
    const Value v(3.14);
    string def = "fallback";
    const string& out = v.tryGetString(def);

    EXPECT_EQ("fallback", out);
    EXPECT_EQ(&out, &def);
}

// [Normal] Returns the provided default when Value is a boolean
TEST_F(JsonBoxValueTryGetStringTest_43, ReturnsDefaultWhenBoolean_43) {
    const Value v(true);
    string def = "nope";
    const string& out = v.tryGetString(def);

    EXPECT_EQ("nope", out);
    EXPECT_EQ(&out, &def);
}

// [Boundary] Returns the provided default when Value is null (default-constructed)
TEST_F(JsonBoxValueTryGetStringTest_43, ReturnsDefaultWhenNull_43) {
    const Value v; // null
    string def = "zzz";
    const string& out = v.tryGetString(def);

    EXPECT_EQ("zzz", out);
    EXPECT_EQ(&out, &def);
}

// [Boundary] Empty-string default is returned by reference when not a string
TEST_F(JsonBoxValueTryGetStringTest_43, ReturnsEmptyDefaultByRefWhenNotString_43) {
    const Value v(0); // not a string
    string def = "";
    const string& out = v.tryGetString(def);

    EXPECT_TRUE(out.empty());
    EXPECT_EQ(&out, &def); // identity: must refer to caller-provided default
}

// [Normal] Works with C-string constructor holding a string
TEST_F(JsonBoxValueTryGetStringTest_43, ReturnsStoredWhenConstructedFromCString_43) {
    const Value v("abc");
    string def = "xyz";
    const string& out = v.tryGetString(def);

    EXPECT_EQ("abc", out);
    EXPECT_NE(&out, &def);
}
