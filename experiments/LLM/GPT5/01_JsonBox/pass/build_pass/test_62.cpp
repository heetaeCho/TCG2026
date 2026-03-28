// File: Value_LoadFromString_Test_62.cpp

#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "JsonBox/Value.h"

using namespace JsonBox;

class ValueLoadFromStringTest_62 : public ::testing::Test {
protected:
  static std::string Dump(const Value& v, bool indent = false, bool escapeAll = false) {
    std::ostringstream os;
    v.writeToStream(os, indent, escapeAll);
    return os.str();
  }
};

// Normal: integer parsing
TEST_F(ValueLoadFromStringTest_62, ParsesInteger_62) {
  Value v;
  v.loadFromString("123");

  EXPECT_TRUE(v.isInteger());
  EXPECT_EQ(123, v.getInteger());
}

// Normal: boolean parsing
TEST_F(ValueLoadFromStringTest_62, ParsesBoolean_62) {
  Value v1, v2;
  v1.loadFromString("true");
  v2.loadFromString("false");

  EXPECT_TRUE(v1.isBoolean());
  EXPECT_TRUE(v1.getBoolean());
  EXPECT_TRUE(v2.isBoolean());
  EXPECT_FALSE(v2.getBoolean());
}

// Normal: string parsing with escape
TEST_F(ValueLoadFromStringTest_62, ParsesString_62) {
  Value v;
  v.loadFromString("\"hello\\nworld\"");

  ASSERT_TRUE(v.isString());
  EXPECT_EQ(std::string("hello\nworld"), v.getString());
}

// Normal: array parsing
TEST_F(ValueLoadFromStringTest_62, ParsesArray_62) {
  Value v;
  v.loadFromString("[1, 2, 3]");

  ASSERT_TRUE(v.isArray());
  const Array& arr = v.getArray();
  ASSERT_EQ(3u, arr.size());
  EXPECT_TRUE(arr[0].isInteger());
  EXPECT_EQ(1, arr[0].getInteger());
  EXPECT_EQ(2, arr[1].getInteger());
  EXPECT_EQ(3, arr[2].getInteger());
}

// Normal: object parsing (nested)
TEST_F(ValueLoadFromStringTest_62, ParsesObject_62) {
  Value v;
  v.loadFromString("{\"a\": [1, 2], \"b\": true, \"c\": {\"k\": \"v\"}}");

  ASSERT_TRUE(v.isObject());
  const Object& obj = v.getObject();

  ASSERT_EQ(3u, obj.size());
  ASSERT_TRUE(obj.at("a").isArray());
  ASSERT_EQ(2u, obj.at("a").getArray().size());
  EXPECT_EQ(2, obj.at("a").getArray()[1].getInteger());

  ASSERT_TRUE(obj.at("b").isBoolean());
  EXPECT_TRUE(obj.at("b").getBoolean());

  ASSERT_TRUE(obj.at("c").isObject());
  EXPECT_TRUE(obj.at("c").getObject().at("k").isString());
  EXPECT_EQ("v", obj.at("c").getObject().at("k").getString());
}

// Boundary: leading/trailing whitespace should be ignored
TEST_F(ValueLoadFromStringTest_62, IgnoresLeadingTrailingWhitespace_62) {
  const std::string with_ws = "  \n\t  {\"x\":42}\n  \t ";
  const std::string clean   = "{\"x\":42}";

  Value v1, v2;
  v1.loadFromString(with_ws);
  v2.loadFromString(clean);

  // Compare observable serialized outputs
  EXPECT_EQ(Dump(v2, /*indent=*/false, /*escapeAll=*/false),
            Dump(v1, /*indent=*/false, /*escapeAll=*/false));

  ASSERT_TRUE(v1.isObject());
  EXPECT_EQ(42, v1.getObject().at("x").getInteger());
}

// Verification of external interaction (behavioral equivalence):
// loadFromString should behave the same as feeding the same JSON via loadFromStream
TEST_F(ValueLoadFromStringTest_62, EquivalentToLoadFromStream_62) {
  const std::string json = "{\"a\": [1, 2, 3], \"b\": false, \"s\":\"t\\t\"}";

  Value via_string;
  via_string.loadFromString(json);

  Value via_stream;
  std::istringstream is(json);
  via_stream.loadFromStream(is);

  // Observable equality via serialized output (no assumptions about internal state)
  EXPECT_EQ(Dump(via_stream, /*indent=*/false, /*escapeAll=*/false),
            Dump(via_string,  /*indent=*/false, /*escapeAll=*/false));
}
