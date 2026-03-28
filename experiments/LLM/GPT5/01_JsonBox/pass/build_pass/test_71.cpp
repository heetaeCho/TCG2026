// File: Value_IstreamCtor_Test_71.cpp
#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <map>
#include <vector>

// Include the real header under test
#include "JsonBox/Value.h"

using JsonBox::Value;
using JsonBox::Object;
using JsonBox::Array;

class ValueIstreamCtorTest_71 : public ::testing::Test {
protected:
    static std::istringstream MakeStream(const std::string& s) {
        return std::istringstream{s};
    }
};

// --- Normal operation ---

TEST_F(ValueIstreamCtorTest_71, ParsesString_71) {
    auto in = ValueIstreamCtorTest_71::MakeStream("\"hello\"");
    Value v(in);
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(std::string("hello"), v.getString());
}

TEST_F(ValueIstreamCtorTest_71, ParsesInteger_71) {
    auto in = ValueIstreamCtorTest_71::MakeStream("123");
    Value v(in);
    ASSERT_TRUE(v.isInteger());
    EXPECT_EQ(123, v.getInteger());
}

TEST_F(ValueIstreamCtorTest_71, ParsesDouble_71) {
    auto in = ValueIstreamCtorTest_71::MakeStream("3.1415");
    Value v(in);
    ASSERT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(3.1415, v.getDouble());
}

TEST_F(ValueIstreamCtorTest_71, ParsesBooleanTrue_71) {
    auto in = ValueIstreamCtorTest_71::MakeStream("true");
    Value v(in);
    ASSERT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueIstreamCtorTest_71, ParsesBooleanFalse_71) {
    auto in = ValueIstreamCtorTest_71::MakeStream("false");
    Value v(in);
    ASSERT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

TEST_F(ValueIstreamCtorTest_71, ParsesNull_71) {
    auto in = ValueIstreamCtorTest_71::MakeStream("null");
    Value v(in);
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueIstreamCtorTest_71, ParsesObjectAndMembers_71) {
    auto in = ValueIstreamCtorTest_71::MakeStream("{\"a\":1,\"b\":\"x\"}");
    Value v(in);
    ASSERT_TRUE(v.isObject());
    const Object& obj = v.getObject();
    ASSERT_EQ(2u, obj.size());
    ASSERT_TRUE(obj.count("a"));
    ASSERT_TRUE(obj.count("b"));
    EXPECT_TRUE(obj.at("a").isInteger());
    EXPECT_EQ(1, obj.at("a").getInteger());
    EXPECT_TRUE(obj.at("b").isString());
    EXPECT_EQ(std::string("x"), obj.at("b").getString());
}

TEST_F(ValueIstreamCtorTest_71, ParsesArrayAndElements_71) {
    auto in = ValueIstreamCtorTest_71::MakeStream("[1,\"x\",true]");
    Value v(in);
    ASSERT_TRUE(v.isArray());
    const Array& arr = v.getArray();
    ASSERT_EQ(3u, arr.size());
    EXPECT_TRUE(arr[0].isInteger());
    EXPECT_EQ(1, arr[0].getInteger());
    EXPECT_TRUE(arr[1].isString());
    EXPECT_EQ(std::string("x"), arr[1].getString());
    EXPECT_TRUE(arr[2].isBoolean());
    EXPECT_TRUE(arr[2].getBoolean());
}

// --- Boundary conditions ---

TEST_F(ValueIstreamCtorTest_71, IgnoresLeadingAndTrailingWhitespace_71) {
    auto in = ValueIstreamCtorTest_71::MakeStream(" \t\n  42  \n");
    Value v(in);
    ASSERT_TRUE(v.isInteger());
    EXPECT_EQ(42, v.getInteger());
}

TEST_F(ValueIstreamCtorTest_71, ConsumesOnlyFirstJsonValue_71) {
    // Two JSON values separated by space. The ctor should parse only the first.
    auto in = ValueIstreamCtorTest_71::MakeStream("1  2");
    Value v(in);
    ASSERT_TRUE(v.isInteger());
    EXPECT_EQ(1, v.getInteger());

    // The stream should still contain the second value.
    int nextVal = 0;
    in >> nextVal; // extraction should read the remaining '2'
    EXPECT_EQ(2, nextVal);
    // After reading the second, EOF should be set.
    EXPECT_TRUE(in.eof());
}

TEST_F(ValueIstreamCtorTest_71, StreamStateAfterExactRead_ReachesEOF_71) {
    auto in = ValueIstreamCtorTest_71::MakeStream("\"end\"");
    Value v(in);
    // After parsing exactly one value with no trailing bytes, the stream should be at EOF.
    // Extracting another char should fail.
    char c;
    in >> c;
    EXPECT_TRUE(in.fail());
    EXPECT_TRUE(in.eof());
}

// (Optional) A minimal malformed input check that does not assume exception type.
// We only assert that constructing from valid JSON doesn't throw; for malformed,
// behavior is implementation-defined, so we avoid asserting specifics.
// This placeholder ensures we do not rely on undocumented error signaling.

/*
TEST_F(ValueIstreamCtorTest_71, MalformedInputBehavior_71) {
    auto in = ValueIstreamCtorTest_71::MakeStream("{bad json");
    // We intentionally do not assert throws/no-throws, as the interface does not define it.
    // This test is commented out to adhere strictly to black-box behavior guarantees.
}
*/

